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
    // Is buffer size completely static
    ////////////////////////////////////////////////////////////////////////////
    BOOST_STATIC_CONSTANT ( bool, is_static_value =
                                  !boost::is_arithmetic<Base>::value
                              &&  !boost::is_arithmetic<Size>::value
                          );
    typedef boost::mpl::bool_<!boost::is_arithmetic<Base>::value> has_static_base;
    typedef boost::mpl::bool_<!boost::is_arithmetic<Size>::value> has_static_size;
    typedef boost::mpl::bool_<is_static_value>                    is_static;

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
    // Swapping
    ////////////////////////////////////////////////////////////////////////////
    void swap( buffer_base& src ) { impl.swap(src.impl); }

    ////////////////////////////////////////////////////////////////////////////
    // Size related helpers
    ////////////////////////////////////////////////////////////////////////////
    size_type   size()      const { return impl.end_ - impl.begin_;       }
    size_type   capacity()  const { return impl.capacity_ - impl.origin_; }
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
    void default_init() { default_init(is_static()); }

    ////////////////////////////////////////////////////////////////////////////
    // init allocates memory and performs construction iif T is not trivial
    ////////////////////////////////////////////////////////////////////////////
    void init( Base const& b, Size const& s )
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
      if(!capacity()) impl.allocate(src.lower(),src.size());
      else            impl.resize  (src.lower(),src.size());
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
    void resize( Size const& s )  { resize(s,has_static_size());  }
    void rebase( Base const& b )  { rebase(b,has_static_base());  }
    void restructure( Base const& b, Size const& s )
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
      init(Base(),Size());
    }

    void resize( Size const&, boost::mpl::true_ const&) {}
    void rebase( Base const&, boost::mpl::true_ const&) {}

    ////////////////////////////////////////////////////////////////////////////
    // Dynamically computed related members
    ////////////////////////////////////////////////////////////////////////////
    void default_init( boost::mpl::false_ const&) {}

    void resize( Size const& s, boost::mpl::false_ const&)
    {
      impl.resize(s);
    }

    void rebase( Base const& b,  boost::mpl::false_ const&)
    {
      impl.rebase(b);
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
