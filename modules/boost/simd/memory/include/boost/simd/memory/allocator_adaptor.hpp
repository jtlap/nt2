//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_MEMORY_ALLOCATOR_ADAPTOR_HPP_INCLUDED
#define BOOST_SIMD_MEMORY_ALLOCATOR_ADAPTOR_HPP_INCLUDED

#include <cstddef>
#include <boost/simd/memory/config.hpp>
#include <boost/simd/memory/allocator.hpp>

namespace boost { namespace simd {  namespace memory
{
  //////////////////////////////////////////////////////////////////////////////
  // Adapt an allocator to be algined
  //////////////////////////////////////////////////////////////////////////////
  template<class Allocator>
  struct  allocator_adaptor : Allocator
  {
    typedef Allocator base_type;

    ////////////////////////////////////////////////////////////////////////////
    // Internal typedefs
    ////////////////////////////////////////////////////////////////////////////
    typedef typename base_type::value_type       value_type;
    typedef typename base_type::pointer          pointer;
    typedef typename base_type::const_pointer    const_pointer;
    typedef typename base_type::reference        reference;
    typedef typename base_type::const_reference  const_reference;
    typedef typename base_type::size_type        size_type;
    typedef typename base_type::difference_type  difference_type;

    template<class U> struct rebind
    {
      typedef typename Allocator::template rebind<U>::other base;
      typedef allocator_adaptor<base>                       other;
    };

    ////////////////////////////////////////////////////////////////////////////
    // Ctor/dtor
    ////////////////////////////////////////////////////////////////////////////
     allocator_adaptor() : base_type() {}
    ~allocator_adaptor() {}

    template<class Z>
    allocator_adaptor ( allocator_adaptor<Z> const& src)
                      : base_type(src.base())
    {}

    allocator_adaptor& operator=(allocator_adaptor const& src)
    {
      base_type::operator=(src);
      return *this;
    }

    ////////////////////////////////////////////////////////////////////////////
    // Access to base allocator
    ////////////////////////////////////////////////////////////////////////////
    base_type&        base()        { return static_cast<base_type&>(*this); }
    base_type const&  base() const  { return static_cast<base_type const&>(*this); }

    ////////////////////////////////////////////////////////////////////////////
    // Memory handling
    ////////////////////////////////////////////////////////////////////////////
    pointer allocate( size_type c, const void* = 0 )
    {
      byte* ptr = memory::allocate( base(), c*sizeof(value_type));
      return reinterpret_cast<pointer>(ptr);
    }

    void deallocate (pointer p, size_type s)
    {
      boost::simd::memory::deallocate(base(), reinterpret_cast<byte*>(p));
    }
  };

  template<class A>
  bool operator==(allocator_adaptor<A> const& a, allocator_adaptor<A> const& b)
  {
    return a.base() == b.base();
  }

  template<class A>
  bool operator!=(allocator_adaptor<A> const& a, allocator_adaptor<A> const& b)
  {
    return a.base() != b.base();
  }
} } }

#endif
