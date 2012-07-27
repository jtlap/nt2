//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_SDK_MEMORY_CONTAINER_REF_HPP_INCLUDED
#define NT2_SDK_MEMORY_CONTAINER_REF_HPP_INCLUDED

#include <nt2/sdk/memory/container.hpp>
#include <boost/mpl/if.hpp>
#include <boost/type_traits/remove_const.hpp>
#include <boost/type_traits/is_const.hpp>

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
  template<class T, class S>
  struct container_ref
  {
    typedef typename boost::mpl::
            if_< boost::is_const<T>
               , container<typename boost::remove_const<T>::type, S> const
               , container<T, S>
               >::type                           base_t;

    typedef typename base_t::allocator_type      allocator_type;
    typedef typename base_t::value_type          value_type;
    typedef typename base_t::size_type           size_type;
    typedef typename base_t::difference_type     difference_type;
    typedef typename boost::mpl::
            if_< boost::is_const<T>
               , typename base_t::const_reference
               , typename base_t::reference
               >::type                           reference;
    typedef typename boost::mpl::
            if_< boost::is_const<T>
               , typename base_t::const_pointer
               , typename base_t::pointer
               >::type                           pointer;
    typedef typename boost::mpl::
            if_< boost::is_const<T>
               , typename base_t::const_iterator
               , typename base_t::iterator
               >::type                           iterator;
    typedef iterator                             const_iterator;
    typedef reference                            const_reference;
    typedef pointer                              const_pointer;

    typedef typename base_t::extent_type         extent_type;
    typedef typename base_t::index_type          index_type;
    typedef typename base_t::order_type          order_type;

    typedef typename base_t::specific_data_type  specific_data_type;

    container_ref() : base(0), ptr(0)
    {
    }

    container_ref(base_t& b) : base(&b), ptr(b.raw())
    {
    }

    //==========================================================================
    /**!
     * Swap the contents of two container of same type and settings
     * \param x First \c container to swap
     * \param y Second \c container to swap
     **/
    //==========================================================================
    BOOST_FORCEINLINE void swap(container_ref<T,S>& y)
    {
      boost::swap(*this, y);
    }

    //==========================================================================
    /*!
     * @brief Resize a container using new dimensions set
     */
    //==========================================================================
    template<class Size>
    void resize( Size const& szs ) const
    {
      base->resize(szs);
      ptr = base->raw();
    }

    //==========================================================================
    /*!
     * @brief Add element at end of container, reshape to 1D
     */
    //==========================================================================
    void push_back( T const& t )
    {
      base->push_back(t);
      ptr = base->raw();
    }

    //==========================================================================
    /*!
     * @brief Return the container dimensions set
     * @return A reference to a constant Fusion RandomAccessSequence containing
     * the size of the container over each of its dimensions.
     **/
    //==========================================================================
    BOOST_FORCEINLINE extent_type const& extent() const
    {
      return base->extent();
    }

    //==========================================================================
    /*!
     * @brief Return the container number of element
     * @return The number of logical element stored in the buffer.
     **/
    //==========================================================================
    BOOST_FORCEINLINE size_type size() const
    {
      return base->size();
    }

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
      return extent()[dim_t::value];
    }

    //==========================================================================
    /*!
     * @brief Check for container emptyness
     * @return A boolean that evaluates to \c true if the container stores no
     * value, \c false otherwise.
     */
    //==========================================================================
    BOOST_FORCEINLINE bool empty() const { return base->empty(); }

    //==========================================================================
    /*!
     * Return the begin of the raw memory
     */
    //==========================================================================
    BOOST_FORCEINLINE pointer       raw() const { return ptr; }

    //==========================================================================
    /*!
     * Return the begin of the data
     */
    //==========================================================================
    BOOST_FORCEINLINE iterator       begin() const { return base->begin(); }

    //==========================================================================
    /*!
     * Return the end of the data
     */
    //==========================================================================
    BOOST_FORCEINLINE iterator       end() const   { return base->end(); }

    //==========================================================================
    // Linear Random Access
    //==========================================================================
    BOOST_FORCEINLINE reference operator[](size_type i) const
    {
      return (*base)[i];
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
    specific_data_type&  specifics() const { return base->specifics(); }

  private:
    base_t*                     base;
    mutable pointer             ptr;
  };

  //============================================================================
  /**!
   * Swap the contents of two container of same type and settings
   * \param x First \c container to swap
   * \param y Second \c container to swap
   **/
  //============================================================================
  template<class T, class S> inline
  void swap(container_ref<T,S>& x, container_ref<T,S>& y)  { x.swap(y); }
} }

namespace nt2 { namespace meta
{
  //============================================================================
  // Register container as a proper container
  //============================================================================
  template<class T, class S>
  struct is_container< memory::container_ref<T, S> > : boost::mpl::true_ {};
} }

namespace boost { namespace dispatch { namespace meta
{
  //============================================================================
  // value_of specializations
  //============================================================================
  template<class T, class S>
  struct value_of< nt2::memory::container_ref<T, S> >
  {
    typedef typename boost::remove_const<T>::type type;
  };

  template<class T, class S>
  struct value_of< nt2::memory::container_ref<T, S> const >
  {
    typedef typename boost::remove_const<T>::type type;
  };

  template<class T, class S>
  struct value_of< nt2::memory::container_ref<T, S>& >
  {
    typedef T& type;
  };

  template<class T, class S>
  struct value_of< nt2::memory::container_ref<T, S> const& >
  {
    typedef T& type;
  };

  //============================================================================
  // model_of specialization
  //============================================================================
  template<class T, class S>
  struct model_of< nt2::memory::container_ref<T, S> >
  {
    struct type
    {
      template<class X>
      struct apply
      {
        typedef typename boost::mpl::if_< boost::is_const<T>, X const, X>::type Xc;
        typedef nt2::memory::container_ref<Xc, S> type;
      };
    };
  };

  //============================================================================
  // container hierarchy
  //============================================================================
  template<class T, class S, class Origin>
  struct hierarchy_of< nt2::memory::container_ref<T, S>, Origin >
  {
    typedef typename nt2::memory::container_ref<T, S>::base_t::semantic_t     semantic_t;
    typedef typename semantic_t::template apply<T,S,Origin>::type type;
  };
} } }

#endif
