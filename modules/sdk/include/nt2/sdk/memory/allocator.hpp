/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_SDK_MEMORY_ALLOCATOR_HPP_INCLUDED
#define NT2_SDK_MEMORY_ALLOCATOR_HPP_INCLUDED

#include <cstddef>
#include <nt2/sdk/error/error.hpp>
#include <nt2/sdk/memory/config.hpp>
#include <nt2/sdk/memory/align_on.hpp>
#include <nt2/sdk/memory/allocate.hpp>
#include <nt2/sdk/memory/deallocate.hpp>
#include <nt2/sdk/memory/reallocate.hpp>

namespace nt2 { namespace memory
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
      p = new (p) value_type(t);
    }

    void destroy(pointer p) { p->~value_type(); }

    ////////////////////////////////////////////////////////////////////////////
    // Memory handling
    ////////////////////////////////////////////////////////////////////////////
    pointer allocate( size_type c, const void* = 0 ) const
    {
      byte* ptr = memory::allocate(c*sizeof(value_type));
      return reinterpret_cast<pointer>(ptr);
    }

    void deallocate (pointer p, size_type s) const
    {
      nt2::memory::deallocate(reinterpret_cast<byte*>(p),s*sizeof(value_type));
    }

    ////////////////////////////////////////////////////////////////////////////
    // Extended Allocator interface -- reallocate
    ////////////////////////////////////////////////////////////////////////////
    pointer resize(pointer p, size_type n, size_type o )
    {
      if( o < n )
      {
        byte* ptr = reallocate( reinterpret_cast<byte*>(p)
                              , n*sizeof(value_type)
                              , o*sizeof(value_type)
                              );
        return reinterpret_cast<pointer>(ptr);
      }
      else
      {
        return p;
      }
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
