//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_MEMORY_ALLOCATOR_HPP_INCLUDED
#define BOOST_SIMD_MEMORY_ALLOCATOR_HPP_INCLUDED

#include <cstddef>
#include <boost/simd/memory/config.hpp>
#include <boost/simd/memory/allocate.hpp>
#include <boost/simd/memory/deallocate.hpp>

namespace boost { namespace simd
{
  //////////////////////////////////////////////////////////////////////////////
  // Allocate a raw buffer of bytes
  //////////////////////////////////////////////////////////////////////////////
  template<class T> struct allocator
  {
    ////////////////////////////////////////////////////////////////////////////
    // Internal typedefs
    ////////////////////////////////////////////////////////////////////////////
    typedef T               value_type;
    typedef T*              pointer;
    typedef T const*        const_pointer;
    typedef T&              reference;
    typedef T const&        const_reference;
    typedef std::size_t     size_type;
    typedef std::ptrdiff_t  difference_type;

    template<class U> struct rebind { typedef allocator<U> other; };

    ////////////////////////////////////////////////////////////////////////////
    // Ctor/dtor
    ////////////////////////////////////////////////////////////////////////////
                      allocator() {}
    template<class U> allocator(allocator<U> const& ) {}
                     ~allocator() {}

    allocator& operator=(allocator const& ) { return *this; }

    ////////////////////////////////////////////////////////////////////////////
    // Address handling
    ////////////////////////////////////////////////////////////////////////////
    pointer       address(reference r)       { return &r; }
    const_pointer address(const_reference r) { return &r; }

    ////////////////////////////////////////////////////////////////////////////
    // Size handling
    ////////////////////////////////////////////////////////////////////////////
    size_type max_size() const  { return size_type(~0); }

    ////////////////////////////////////////////////////////////////////////////
    // Object lifetime handling
    ////////////////////////////////////////////////////////////////////////////
    void construct(pointer p, const T& t)
    {
      p = new ((void*)p) value_type (t);
    }

    void destroy(pointer p) { p->~value_type(); }

    ////////////////////////////////////////////////////////////////////////////
    // Memory handling
    ////////////////////////////////////////////////////////////////////////////
    pointer allocate( size_type c, const void* = 0 ) const
    {
      return reinterpret_cast<pointer>( boost::simd
                                             ::allocate(c*sizeof(value_type))
                                      );
    }

    void deallocate (pointer p, size_type ) const
    {
      boost::simd::deallocate( p );
    }
  };

  template<class T>
  bool operator== (allocator<T> const&, allocator<T> const&)
  {
    return true;
  }

  template<class T>
  bool operator!= (allocator<T> const&, allocator<T> const&)
  {
    return false;
  }
} }

#endif
