//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_SDK_MEMORY_CONTAINER_HPP_INCLUDED
#define NT2_SDK_MEMORY_CONTAINER_HPP_INCLUDED

#include <nt2/core/settings/size.hpp>
#include <nt2/core/settings/index.hpp>
#include <nt2/core/settings/option.hpp>
#include <nt2/core/settings/semantic.hpp>
#include <nt2/core/settings/interleaving.hpp>
#include <nt2/core/settings/normalize.hpp>
#include <nt2/core/settings/storage_order.hpp>
#include <nt2/core/settings/specific_data.hpp>
#include <nt2/sdk/memory/composite_buffer.hpp>
#include <nt2/core/settings/storage_scheme.hpp>
#include <nt2/core/container/table/semantic.hpp>
#include <nt2/include/functions/scalar/numel.hpp>
#include <boost/fusion/include/is_sequence.hpp>
#include <nt2/sdk/memory/adapted/container.hpp>
#include <boost/mpl/at.hpp>

namespace nt2 { namespace memory
{
  //============================================================================
  /*!
   * container is the base class handling a container semantic, layout and
   * memory used by the nt2 proto terminal class. It is built from a value
   * \c Type and a list of \c Settings describing how it should behave both at
   * runtime and compile-time.
   *
   * \tparam Type    Value type to store in the table
   * \tparam Setting Options list describing the behavior of the container
   **/
  //============================================================================
  template<class T, class S> class container
  {
  public:
    //==========================================================================
    // Find out how to normalize this container settings
    //  - if no semantic is given, we infers it behaves as a simple table.
    // Once semantic normalization occured, every options is present in
    // settings_type.
    //==========================================================================
    typedef typename meta::option < S
                                  , tag::semantic_
                                  , tag::table_
                                  >::type                   semantic_t;
    typedef typename meta::normalize<semantic_t,T,S>::type  settings_type;

    //==========================================================================
    // Compute buffer type from storage_scheme
    //==========================================================================
    typedef typename meta::option < settings_type
                                  , tag::storage_scheme_
                                  >::type                       scheme_t;
    typedef typename scheme_t::template apply<T,settings_type>  scheme_type;
    typedef typename scheme_type::type                          base_buffer_t;

    //========================================================================
    // If T is a composite, adapt our buffer accordingly
    //========================================================================
    typedef typename meta::option < settings_type
                                  , tag::interleaving_
                                  >::type                       interleaving_t;
    typedef typename boost::mpl::if_< boost::mpl::and_
                                      < boost::fusion::traits::is_sequence<T>
                                      , interleaving_t
                                      >
                                    , composite_buffer<base_buffer_t>
                                    , base_buffer_t
                                    >::type                           buffer_t;

    //==========================================================================
    // Container interface
    //==========================================================================
    typedef typename buffer_t::allocator_type   allocator_type;
    typedef typename buffer_t::value_type       value_type;
    typedef typename buffer_t::iterator         iterator;
    typedef typename buffer_t::const_iterator   const_iterator;
    typedef typename buffer_t::reference        reference;
    typedef typename buffer_t::const_reference  const_reference;
    typedef typename buffer_t::size_type        size_type;
    typedef typename buffer_t::difference_type  difference_type;
    typedef typename buffer_t::pointer          pointer;
    typedef typename buffer_t::const_pointer    const_pointer;

    //==========================================================================
    // Specific data type - Used for per-hardware site special member
    //==========================================================================
    typedef typename specific_data< typename  boost::dispatch::
                                              default_site<T>::type
                                  , T
                                  >::type       specific_data_type;

    //==========================================================================
    // size_type is the type used to store the container dimensions set
    //==========================================================================
    typedef typename meta::option<settings_type, tag::of_size_>::type extent_type;

    //==========================================================================
    // index_type is the type used to store the container base index
    //==========================================================================
    typedef typename meta::option<settings_type,tag::index_>::type    index_type;

    //==========================================================================
    // order_type is the type used to represent the container storage order
    //==========================================================================
    typedef typename meta::option<settings_type,tag::storage_order_>::type  order_type;

    //==========================================================================
    // require_static_init detects if container is initialized in default ctor
    //==========================================================================
    typedef typename
            meta::option<settings_type,tag::storage_duration_>::type duration_t;
    typedef boost::mpl::
            bool_ <   !( boost::mpl::at_c<typename extent_type::values_type, 0>::type::value <= 0 )
                  &&  !boost::is_same<duration_t,automatic_>::value
                  >                                         require_static_init;
    //==========================================================================
    // has_static_size detects if container size is known at compile time
    //==========================================================================
    typedef boost::mpl::
            bool_ <   extent_type::static_status
                  ||  boost::is_same<duration_t,automatic_>::value
                  >                                         has_static_size;

    //==========================================================================
    /*!
     * @brief Default constructor
     *
     * A default-constructed \c nt2::memory::container is initialized to be:
     *  - empty if its size is dynamic
     *  - pre-allocated if its size is static or its storage is automatic
     */
    //==========================================================================
    container() : data_(), specific_()
    {
      init(sizes_, require_static_init());
    }

    //==========================================================================
    /*!
     * @brief Constructor from an allocator
     * Construct a container from an allocator instance.
     *
     * @param a Allocator used for container construction
     *
     * Such \c nt2::memory::container is initialized to be:
     *  - empty if its size is dynamic
     *  - pre-allocated if its size is static or its storage is automatic
     *
     * \c nt2::memory::container is aware of stateful allocator and will handle
     * them properly.
     */
    //==========================================================================
    container ( allocator_type const& a ) : data_(a), specific_()
    {
      init(sizes_, require_static_init());
    }

    //==========================================================================
    /*!
     * @brief Constructor from a dimension set
     * Construct a container from a Fusion RandomAccessSequence of integral
     * values representing the logical number of element in each dimensions.
     *
     * @param sz Fusion Sequence to use as dimensions
     * @param a Allocator used for container construction
     *
     * Passing a dimension set to a nt2::memory::container with automatic
     * storage or set up to use a static dimension set will result in a
     * assert being raised.
     *
     * \c nt2::memory::container is aware of stateful allocator and will handle
     * them properly.
     */
    //==========================================================================
    template<class Size>
    container ( Size const& sz, allocator_type const& a = allocator_type() )
              : data_(a), sizes_(sz), specific_()
    {
      //========================================================================
      //       ****INVALID_CONSTRUCTOR_FOR_STATICALLY_SIZED_CONTAINER****
      // If you trigger this assert, you tried to initialize a container
      // with a static size or an automatic storage scheme from a runtime set of
      // dimensions. Fix your code to remove such constructor call.
      //       ****INVALID_CONSTRUCTOR_FOR_STATICALLY_SIZED_CONTAINER****
      //========================================================================
      BOOST_ASSERT_MSG( !has_static_size::value || sz == extent_type(), "Invalid constructor for statically sized container" );

      init(sizes_);
    }

    //==========================================================================
    /**!
     * Swap the contents of two container of same type and settings
     * \param x First \c container to swap
     * \param y Second \c container to swap
     **/
    //==========================================================================
    BOOST_FORCEINLINE void swap(container<T,S>& y)
    {
      data_.swap(y.data_);
      sizes_.swap(y.sizes_);
      specific_.swap(y.specific_);
    }

    //==========================================================================
    /*!
     * @brief Resize a container using new dimensions set
     */
    //==========================================================================
    template<class Size> void resize( Size const& szs )
    {
      resize(szs,boost::mpl::bool_<!extent_type::static_status>());
    }

    //==========================================================================
    /*!
     * @brief Add element at end of container, reshape to 1D
     */
    //==========================================================================
    void push_back( T const& t)
    {
      data_.push_back(t);
      sizes_ = extent_type(numel(sizes_) + 1);
    };

    //==========================================================================
    /*!
     * @brief Return the container dimensions set
     * @return A reference to a constant Fusion RandomAccessSequence containing
     * the size of the container over each of its dimensions.
     **/
    //==========================================================================
    BOOST_FORCEINLINE extent_type const& extent() const { return sizes_;  }

    //==========================================================================
    /*!
     * @brief Return the container number of element
     * @return The number of logical element stored in the buffer.
     **/
    //==========================================================================
    BOOST_FORCEINLINE size_type size() const { return data_.size();  }

    //==========================================================================
    /*!
     * @brief Return the container number of element along the main dimension
     *
     * leading_size retrieves the number of element of the leading dimension in
     * a settings independant way.
     *
     * @return The number of elements stored on the main dimension
     */
    //==========================================================================
    BOOST_FORCEINLINE size_type leading_size() const
    {
      typedef typename boost::mpl
                            ::apply < order_type
                                    , boost::mpl::size_t<extent_type::static_size>
                                    , boost::mpl::size_t<0U>
                                    >::type                     dim_t;
      return sizes_[dim_t::value];
    }

    //==========================================================================
    /*!
     * @brief Check for container emptyness
     * @return A boolean that evaluates to \c true if the container stores no
     * value, \c false otherwise.
     */
    //==========================================================================
    BOOST_FORCEINLINE bool empty() const { return data_.empty(); }

    //==========================================================================
    /*!
     * Return the begin of the raw memory
     */
    //==========================================================================
    BOOST_FORCEINLINE pointer       raw()       { return data_.raw(); }
    BOOST_FORCEINLINE const_pointer raw() const { return data_.raw(); }

    //==========================================================================
    /*!
     * Return the begin of the data
     */
    //==========================================================================
    BOOST_FORCEINLINE iterator       begin()       { return data_.begin(); }
    BOOST_FORCEINLINE const_iterator begin() const { return data_.begin(); }

    //==========================================================================
    /*!
     * Return the end of the data
     */
    //==========================================================================
    BOOST_FORCEINLINE iterator       end()       { return data_.end(); }
    BOOST_FORCEINLINE const_iterator end() const { return data_.end(); }

    //==========================================================================
    // Linear Random Access
    //==========================================================================
    BOOST_FORCEINLINE reference operator[](size_type i)
    {
      specific_.synchronize();
      return data_[i];
    }

    BOOST_FORCEINLINE const_reference operator[](size_type i) const
    {
      specific_.synchronize();
      return data_[i];
    }

    //==========================================================================
    /*!
     * @brief Access to the architecture specific container data
     * As the inner structure of a container may change with the hardware
     * configuration, a specific data segment is provided to gather informations
     * that may be required for proper operation on said configuration.
     *
     * @return A reference to the specific data of the container.
     **/
    //==========================================================================
    BOOST_FORCEINLINE
    specific_data_type&  specifics()       { return specific_; }
    BOOST_FORCEINLINE
    specific_data_type&  specifics() const { return specific_; }

    //==========================================================================
    // Check if a position is safely R/W in the current container
    //==========================================================================
    BOOST_FORCEINLINE bool is_safe(size_type p) const { return data_.is_safe(p); }

  protected:
    //==========================================================================
    // Initialization of inner data_ and sizes_
    // Note that the number of non-zero (nnz) is delegated to the storage scheme
    //==========================================================================
    template<class Size> BOOST_FORCEINLINE void init( Size const& )
    {
      data_.resize( scheme_type::nnz( sizes_ ) );
    }

    //==========================================================================
    // Handle the conditionnal default initialization of statically sized
    // dynamic container
    //==========================================================================
    template<class Size> BOOST_FORCEINLINE
    void init(Size const& sz, boost::mpl::true_ const&  ) { init(sz); }

    template<class Size> BOOST_FORCEINLINE
    void init(Size const&   , boost::mpl::false_ const& ) {}

    //==========================================================================
    // Handle the conditionnal resize of statically sized container
    //==========================================================================
    template<class Size> void resize( Size const& szs, boost::mpl::true_ const& )
    {
      if( szs != sizes_ )
      {
        sizes_ = extent_type(szs);
        init(sizes_);
      }
    }

    template<class Size> void resize( Size const& szs, boost::mpl::false_ const& )
    {
      //========================================================================
      //     ****STATICALLY_SIZED_CONTAINER_CANT_BE_RESIZED_DYNAMICALLY****
      // If you trigger this assert, you tried to resize a container
      // with a static size to a different runtime dimension set.
      // Fix your code to remove such resize call.
      //     ****STATICALLY_SIZED_CONTAINER_CANT_BE_RESIZED_DYNAMICALLY****
      //========================================================================
      BOOST_ASSERT_MSG( szs == extent_type()
                      , "Statically sized container can't be resized dynamically"
                      );
    }

  private:
    buffer_t                    data_;
    extent_type                 sizes_;
    mutable specific_data_type  specific_;
  };

  //============================================================================
  /**!
   * Swap the contents of two container of same type and settings
   * \param x First \c container to swap
   * \param y Second \c container to swap
   **/
  //============================================================================
  template<class T, class S> inline
  void swap (container<T,S>& x, container<T,S>& y)  { x.swap(y); }
} }

#endif
