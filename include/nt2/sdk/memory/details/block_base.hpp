/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_SDK_MEMORY_DETAILS_BLOCK_BASE_HPP_INCLUDED
#define NT2_SDK_MEMORY_DETAILS_BLOCK_BASE_HPP_INCLUDED

////////////////////////////////////////////////////////////////////////////////
// Base clas for memory block
////////////////////////////////////////////////////////////////////////////////
#include <nt2/sdk/memory/meta/align_on.hpp>
#include <nt2/sdk/memory/details/block_impl.hpp>
#include <boost/type_traits/has_trivial_assign.hpp>
#include <boost/type_traits/has_trivial_destructor.hpp>
#include <boost/type_traits/has_trivial_constructor.hpp>

namespace nt2 { namespace details
{
  template<class Type, class Lower, class Upper, class Allocator>
  class buffer_base
  {
    public:
    ////////////////////////////////////////////////////////////////////////////
    // Public types
    ////////////////////////////////////////////////////////////////////////////
    typedef typename Allocator::template rebind<Type>::other  allocator_type;
    typedef typename allocator_type::value_type               value_type;
    typedef typename allocator_type::pointer                  pointer;
    typedef typename allocator_type::const_pointer            const_pointer;
    typedef typename allocator_type::reference                reference;
    typedef typename allocator_type::const_reference          const_reference;
    typedef typename allocator_type::size_type                size_type;
    typedef typename allocator_type::difference_type          difference_type;

    ////////////////////////////////////////////////////////////////////////////
    // Is buffer size completely static
    ////////////////////////////////////////////////////////////////////////////
    BOOST_STATIC_CONSTANT ( bool, is_static_value =
                                  !boost::is_arithmetic<Lower>::value
                              &&  !boost::is_arithmetic<Upper>::value
                          );
    typedef boost::mpl::bool_<is_static_value> is_static;

    ////////////////////////////////////////////////////////////////////////////
    // Buffer data holder type
    ////////////////////////////////////////////////////////////////////////////
    typedef buffer_impl<value_type,allocator_type> data_type;

    ////////////////////////////////////////////////////////////////////////////
    // Implementation data
    ////////////////////////////////////////////////////////////////////////////
    data_type impl;

    ////////////////////////////////////////////////////////////////////////////
    // Constructors
    ////////////////////////////////////////////////////////////////////////////
    buffer_base()                     : impl(allocator_type()) {}
    buffer_base( Allocator const& a ) : impl(a) {}

    ////////////////////////////////////////////////////////////////////////////
    // C++0x rvalue constructor. Steal ressources and empty out
    ////////////////////////////////////////////////////////////////////////////
    #if defined(BOOST_HAS_RVALUE_REFS)
    buffer_base(buffer_base&& rhs) : impl( std::move(rhs.impl) )
    {
      rhs.impl.origin_  = rhs.impl.capacity_
                        = rhs.impl.begin_
                        = rhs.impl.end_       = 0;
    }
    #endif

    ////////////////////////////////////////////////////////////////////////////
    // Destructors
    ////////////////////////////////////////////////////////////////////////////
    ~buffer_base() { cleanup(); }

    ////////////////////////////////////////////////////////////////////////////
    // Size related helpers
    ////////////////////////////////////////////////////////////////////////////
    size_type size()        const { return size(is_static());      }
    size_type capacity()    const { return capacity(is_static());  }
    difference_type lower() const { return lower(is_static());     }
    difference_type upper() const { return upper(is_static());     }

    ////////////////////////////////////////////////////////////////////////////
    // Multi-pass components
    // We choose to split construction in two pass to help having proper
    // garantees on exception safety for buffer. This allow us to write
    // code which is exception safe and don't require tons of try/catch blocks.
    ////////////////////////////////////////////////////////////////////////////

    ////////////////////////////////////////////////////////////////////////////
    // default_init checks for staticallity before calling init()
    ////////////////////////////////////////////////////////////////////////////
    void default_init() { default_init(is_static()); }

    ////////////////////////////////////////////////////////////////////////////
    // init allocates memory and performs construction iif T is not trivial
    ////////////////////////////////////////////////////////////////////////////
    void init( Lower const& l, Upper const& u )
    {
      size_type sz = impl.allocate(l,u);
      construct(sz,typename boost::has_trivial_constructor<value_type>::type());
    }

    ////////////////////////////////////////////////////////////////////////////
    // assign performs optimized copy that is compatible with move semantic.
    // Note that if T is trivial, copy uses memcpy as an optimization
    ////////////////////////////////////////////////////////////////////////////
    void assign(buffer_base const& src)
    {
      if(!capacity()) impl.allocate(src.lower(),src.upper());
      else            impl.resize  (src.lower(),src.upper());

      copy(src,typename boost::has_trivial_assign<value_type>::type());
    }

    ////////////////////////////////////////////////////////////////////////////
    // resize current buffer
    ////////////////////////////////////////////////////////////////////////////
    void resize( Lower const& l, Upper const& u ) { resize(l,u,is_static()); }

    ////////////////////////////////////////////////////////////////////////////
    // clear empties the data by putting its size back to 0.
    ////////////////////////////////////////////////////////////////////////////
    void clear()
    {
      destroy(typename boost::has_trivial_destructor<value_type>::type());
      impl.end_ = impl.begin_;
    }

    protected:
    ////////////////////////////////////////////////////////////////////////////
    // Internals elements
    ////////////////////////////////////////////////////////////////////////////
    void cleanup()
    {
      clear();
      if(impl.origin_) impl.deallocate(impl.origin_,capacity());
    }

    protected:
    ////////////////////////////////////////////////////////////////////////////
    // Specialized internals relative to staticality of buffer_base
    ////////////////////////////////////////////////////////////////////////////
    void default_init( boost::mpl::true_ const&)
    {
      init(Lower(),Upper());
    }

    void resize( Lower const&, Upper const&, boost::mpl::true_ const&) {}

    size_type size( boost::mpl::true_ const&) const
    {
      return Upper::value - Lower::value + 1;
    }

    size_type capacity( boost::mpl::true_ const&) const
    {
      return meta::align_on_c<(Upper::value-Lower::value+1)>::value;
    }

    difference_type lower( boost::mpl::true_ const&) const
    {
      return Lower::value;
    }

    difference_type upper( boost::mpl::true_ const&) const
    {
      return Upper::value;
    }

    ////////////////////////////////////////////////////////////////////////////
    // Dynamically computed related members
    ////////////////////////////////////////////////////////////////////////////
    void default_init( boost::mpl::false_ const&) {}

    void resize( Lower const& l, Upper const& u, boost::mpl::false_ const&)
    {
      impl.resize(l,u);
    }

    size_type size( boost::mpl::false_ const&) const
    {
      return impl.end_ - impl.begin_;
    }

    size_type capacity( boost::mpl::false_ const&) const
    {
      return impl.capacity_ - impl.origin_;
    }

    difference_type lower( boost::mpl::false_ const&) const
    {
      return impl.origin_ - impl.begin_;
    }

    difference_type upper( boost::mpl::bool_<false> const&) const
    {
      return size() - 1 + lower();
    }

    protected:
    ////////////////////////////////////////////////////////////////////////////
    // Specialized internals relative to type properties
    ////////////////////////////////////////////////////////////////////////////

    ////////////////////////////////////////////////////////////////////////////
    // value_type is trivial
    //  => construction and destruction are trivial
    //  => copy is done bitwise
    ////////////////////////////////////////////////////////////////////////////
    void construct(size_type, boost::mpl::true_ const&) {}
    void destroy(boost::mpl::true_ const&)              {}
    void copy(buffer_base const& src, boost::mpl::true_ const&)
    {
      ::memcpy(impl.origin_,src.impl.origin_,src.size()*sizeof(value_type));
    }

    ////////////////////////////////////////////////////////////////////////////
    // value_type is non trivial
    //  => construction and destruction use Allocator
    //  => copy is done using proper assignment
    ////////////////////////////////////////////////////////////////////////////
    void construct(size_type n, boost::mpl::false_ const&)
    {
      value_type v;
      for(size_type i=0;i<n;++i) impl.construct(&impl.origin_[i],v);
    }

    void destroy(boost::mpl::false_ const&)
    {
      for(size_type i=0;i<size();++i) impl.destroy(&impl.origin_[i]);
    }

    void copy(buffer_base const& src, boost::mpl::false_ const&)
    {
      for(size_type i=0;i<src.size();++i) impl.origin_[i] = src.impl.origin_[i];
    }
  };
} }

#endif
