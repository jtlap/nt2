//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_SDK_MEMORY_CONTAINER_SHARED_REF_HPP_INCLUDED
#define NT2_SDK_MEMORY_CONTAINER_SHARED_REF_HPP_INCLUDED

#include <nt2/sdk/memory/container.hpp>
#include <nt2/core/container/dsl/forward.hpp>
#include <boost/dispatch/meta/terminal_of_shared.hpp>
#include <boost/dispatch/meta/scalar_of.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>

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
  template<class Container, bool Own = false>
  struct container_shared_ref
  {
    typedef Container                                                         base_t;
    typedef typename base_t::value_type                                       value_type;
    typedef typename base_t::size_type                                        size_type;
    typedef typename base_t::extent_type                                      extent_type;
    typedef typename base_t::order_type                                       order_type;
    typedef typename base_t::specific_data_type                               specific_data_type;

    typedef typename boost::dispatch::meta::scalar_of<Container&>::type       reference;
    typedef typename boost::dispatch::meta::scalar_of<Container const&>::type const_reference;
    typedef typename boost::dispatch::meta::scalar_of<Container>::type*       pointer;
    typedef typename boost::dispatch::meta::scalar_of<Container>::type const* const_pointer;
    typedef pointer                                                           iterator;

    container_shared_ref() : base_(), ptr(0)
    {
    }

    container_shared_ref(boost::shared_ptr<base_t> const& b) : base_(b), ptr(b->raw())
    {
    }

    //==========================================================================
    /**!
     * Swap the contents of two container of same type and settings
     * \param x First \c container to swap
     * \param y Second \c container to swap
     **/
    //==========================================================================
    BOOST_FORCEINLINE void swap(container_shared_ref<Container, Own>& y)
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
      base_->resize(szs);
      ptr = base_->raw();
    }

    //==========================================================================
    /*!
     * @brief Add element at end of container, reshape to 1D
     */
    //==========================================================================
    void push_back( value_type const& t )
    {
      base_->push_back(t);
      ptr = base_->raw();
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
      return base_->extent();
    }

    //==========================================================================
    /*!
     * @brief Return the container number of element
     * @return The number of logical element stored in the buffer.
     **/
    //==========================================================================
    BOOST_FORCEINLINE size_type size() const
    {
      return base_->size();
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
    BOOST_FORCEINLINE bool empty() const { return base_->empty(); }

    //==========================================================================
    /*!
     * Return the begin of the raw memory
     */
    //==========================================================================
    BOOST_FORCEINLINE pointer       raw() const { return Own ? base_->raw() : ptr; }

    //==========================================================================
    /*!
     * Return the begin of the data
     */
    //==========================================================================
    BOOST_FORCEINLINE iterator       begin() const { return base_->begin(); }

    //==========================================================================
    /*!
     * Return the end of the data
     */
    //==========================================================================
    BOOST_FORCEINLINE iterator       end() const   { return base_->end(); }

    //==========================================================================
    // Linear Random Access
    //==========================================================================
    BOOST_FORCEINLINE reference operator[](size_type i) const
    {
      return (*base_)[i];
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
    specific_data_type&  specifics() const { return base_->specifics(); }

    boost::shared_ptr<Container> base() const { return base_; }

  private:
    boost::shared_ptr<Container>   base_;
    mutable pointer                ptr;
  };

  //============================================================================
  /**!
   * Swap the contents of two container of same type and settings
   * \param x First \c container to swap
   * \param y Second \c container to swap
   **/
  //============================================================================
  template<class Container, bool Own> inline
  void swap(container_shared_ref<Container, Own>& x, container_shared_ref<Container, Own>& y)  { x.swap(y); }
} }

namespace nt2 { namespace meta
{
  //============================================================================
  // Register container as a proper container
  //============================================================================
  template<class Container, bool Own>
  struct is_container< memory::container_shared_ref<Container, Own> > : boost::mpl::true_ {};

  template<class Container, bool Own>
  struct is_container_ref< memory::container_shared_ref<Container, Own> > : boost::mpl::true_ {};

} }

namespace boost { namespace dispatch { namespace meta
{
  //============================================================================
  // value_of specializations
  //============================================================================
  template<class Container, bool Own>
  struct value_of< nt2::memory::container_shared_ref<Container, Own> >
   : value_of<Container>
  {
  };

  template<class Container, bool Own>
  struct value_of< nt2::memory::container_shared_ref<Container, Own> const >
   : value_of<Container>
  {
  };

  template<class Container, bool Own>
  struct value_of< nt2::memory::container_shared_ref<Container, Own>& >
   : value_of<Container>
  {
  };

  template<class Container, bool Own>
  struct value_of< nt2::memory::container_shared_ref<Container, Own> const& >
   : value_of<Container>
  {
  };

  //============================================================================
  // model_of specialization
  //============================================================================
  template<class Container, bool Own>
  struct model_of< nt2::memory::container_shared_ref<Container, Own> >
  {
    struct type
    {
      template<class X>
      struct apply
      {
        typedef nt2::memory::container_shared_ref<X, Own> type;
      };
    };
  };

  //============================================================================
  // container hierarchy
  //============================================================================
  template<class Container, bool Own, class Origin>
  struct hierarchy_of< nt2::memory::container_shared_ref<Container, Own>, Origin >
   : hierarchy_of< Container, Origin >
  {
  };

  template<class T, class S>
  struct terminal_of_shared< nt2::memory::container<T, S> >
  {
    typedef nt2::memory::container<T, S> container;
    typedef nt2::memory::container_shared_ref<container, true> container_ref;
    typedef boost::proto::basic_expr< boost::proto::tag::terminal, boost::proto::term<container_ref>, 0> basic_expr;
    typedef nt2::container::expression< basic_expr, container, boost::proto::is_proto_expr > type;
    static type make() { return type(basic_expr::make(container_ref(boost::make_shared<container>()))); }
  };
} } }

#endif
