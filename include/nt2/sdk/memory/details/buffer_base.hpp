/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_SDK_MEMORY_DETAILS_BUFFER_BASE_HPP_INCLUDED
#define NT2_SDK_MEMORY_DETAILS_BUFFER_BASE_HPP_INCLUDED

////////////////////////////////////////////////////////////////////////////////
// Base class for memory buffer
////////////////////////////////////////////////////////////////////////////////
#include <boost/type_traits/is_same.hpp>
#include <nt2/sdk/memory/meta/align_on.hpp>
#include <nt2/sdk/memory/details/buffer_impl.hpp>
#include <boost/type_traits/has_trivial_assign.hpp>
#include <boost/type_traits/has_trivial_destructor.hpp>
#include <boost/type_traits/has_trivial_constructor.hpp>
#include <nt2/sdk/meta/strip.hpp>

namespace nt2 { namespace details
{
  template<class Type, class Base, class Size, class Allocator>
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
    typedef typename allocator_type::difference_type          index_type;

    ////////////////////////////////////////////////////////////////////////////
    // Build Base/Size value types
    ////////////////////////////////////////////////////////////////////////////
    typedef typename meta::strip<Base>::type  base_value_type;
    typedef typename meta::strip<Size>::type  size_value_type;

    ////////////////////////////////////////////////////////////////////////////
    // Is buffer size completely static
    ////////////////////////////////////////////////////////////////////////////
    BOOST_STATIC_CONSTANT ( bool, is_static_value =
                                  !boost::is_arithmetic<base_value_type>::value
                              &&  !boost::is_arithmetic<size_value_type>::value
                          );
    typedef boost::mpl::bool_<!boost::is_arithmetic<base_value_type>::value> has_static_base;
    typedef boost::mpl::bool_<!boost::is_arithmetic<size_value_type>::value> has_static_size;
    typedef boost::mpl::bool_<is_static_value>                    is_static;

    ////////////////////////////////////////////////////////////////////////////
    // Implementation data
    ////////////////////////////////////////////////////////////////////////////
    typedef buffer_impl<value_type,allocator_type> data_type;
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
      rhs.impl.origin_  = rhs.impl.begin_
                        = rhs.impl.end_       = 0;
    }
    #endif

    ////////////////////////////////////////////////////////////////////////////
    // Destructors
    ////////////////////////////////////////////////////////////////////////////
    ~buffer_base() { cleanup(); }

    ////////////////////////////////////////////////////////////////////////////
    // Swapping
    ////////////////////////////////////////////////////////////////////////////
    void swap( buffer_base& src ) { impl.swap(src.impl); }

    ////////////////////////////////////////////////////////////////////////////
    // Size related helpers
    ////////////////////////////////////////////////////////////////////////////
    size_type   size()      const { return impl.end_ - impl.begin_;       }
    index_type  lower()     const { return impl.origin_ - impl.begin_;    }
    index_type  upper()     const { return size() - 1 + lower();          }

    typename data_type::pointer origin() const { return impl.origin_; }

    ////////////////////////////////////////////////////////////////////////////
    // Multi-pass components
    // We choose to split construction in two pass to help having proper
    // garantees on exception safety for buffer. This allow us to write
    // code which is exception safe and don't require tons of try/catch blocks.
    ////////////////////////////////////////////////////////////////////////////

    ////////////////////////////////////////////////////////////////////////////
    // default_init checks for staticallity before calling init()
    ////////////////////////////////////////////////////////////////////////////
    void default_init() { if(is_static::value) init(base_value_type(),size_value_type()); }

    ////////////////////////////////////////////////////////////////////////////
    // init allocates memory and performs construction iif T is not trivial
    ////////////////////////////////////////////////////////////////////////////
    void init( base_value_type const& b, size_value_type const& s )
    {
      impl.allocate(b,s);
      construct(s,typename boost::has_trivial_constructor<value_type>::type());
    }

    ////////////////////////////////////////////////////////////////////////////
    // assign performs optimized copy that is compatible with move semantic.
    // Note that if T is trivial, copy uses memcpy as an optimization
    ////////////////////////////////////////////////////////////////////////////
    template<class Buffer> void assign(Buffer const& src)
    {
      if(!size()) impl.allocate(src.lower(),src.size());
      else
      {
         impl.resize(src.size());
         impl.rebase(src.lower());
      }
      fill(src);
    }

    template<class Buffer> void fill(Buffer const& src)
    {
      typedef boost::has_trivial_constructor<value_type>              trivial;
      typedef boost::is_same<typename Buffer::value_type, value_type> types;

      copy(src,typename boost::mpl::bool_<types::value && trivial::value>());
    }

    ////////////////////////////////////////////////////////////////////////////
    // resize current buffer
    ////////////////////////////////////////////////////////////////////////////
    void resize( size_value_type const& s )
    {
      impl.resize(s);
    }

    void rebase( base_value_type const& b )
    {
      impl.rebase(b);
    }

    void restructure( base_value_type const& b, size_value_type const& s )
    {
      resize(s);
      rebase(b);
    }

    ////////////////////////////////////////////////////////////////////////////
    // clear empties the data by putting its size back to 0.
    ////////////////////////////////////////////////////////////////////////////
    void clear()
    {
      destroy(typename boost::has_trivial_destructor<value_type>::type());
      impl.end_ = impl.begin_;
    }

    protected:
    void cleanup()
    {
      clear();
      if(impl.origin_) impl.deallocate(impl.origin_,size());
    }

    ////////////////////////////////////////////////////////////////////////////
    // value_type is trivial
    //  => construction and destruction are trivial
    //  => copy is done bitwise
    ////////////////////////////////////////////////////////////////////////////
    void construct(size_type, boost::mpl::true_ const&) {}
    void destroy(boost::mpl::true_ const&)              {}

    template<class Buffer>
    void copy(Buffer const& src, boost::mpl::true_ const&)
    {
      ::memcpy(impl.origin_,src.origin(),src.size()*sizeof(value_type));
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

    template<class Buffer>
    void copy(Buffer const& src, boost::mpl::false_ const&)
    {
      for(size_type i=0;i<src.size();++i) impl.origin_[i] = src.impl.origin_[i];
    }
  };
} }

#endif
