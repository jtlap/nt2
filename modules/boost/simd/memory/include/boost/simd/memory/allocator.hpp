//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012 - 2013   MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_MEMORY_ALLOCATOR_HPP_INCLUDED
#define BOOST_SIMD_MEMORY_ALLOCATOR_HPP_INCLUDED

#include <boost/simd/memory/allocate.hpp>
#include <boost/simd/memory/deallocate.hpp>
#include <cstddef>

namespace boost { namespace simd
{
  /*!
    @brief SIMD-aware allocator

    Provides a standard, stateless allocator that take allocates memory block
    compatible with current architecture SIMD constraints.

    @tparam Type of elements to allocate
  **/
  template<class T> struct allocator
  {
    typedef T               value_type;
    typedef T*              pointer;
    typedef T const*        const_pointer;
    typedef T&              reference;
    typedef T const&        const_reference;
    typedef std::size_t     size_type;
    typedef std::ptrdiff_t  difference_type;

    /*!
      @brief Allocator type rebinding meta-function

      Standard internal meta-function to build an @c allocator<U> from an
      @c allocator<T>

      @tparam U Type to rebind the current allocator to
    **/
    template<class U> struct rebind
    {
      typedef allocator<U> other;
    };

    /// Default constructor
    allocator() {}

    /// Constructor from another SIMD allocator
    template<class U> allocator(allocator<U> const& ) {}

    /// Retrieve the address of an element
    pointer       address(reference r)       { return &r; }

    /// @overload
    const_pointer address(const_reference r) { return &r; }

    /// Maximum amount of memory that can be allocated
    size_type max_size() const  { return size_type(~0); }

    /// Performs the construction of a given value in a given memory block
    void construct(pointer p, const T& t)
    {
      p = new ((void*)p) value_type (t);
    }

    /// Performs the destruction of a given value in a given memory block
    void destroy(pointer p) { p->~value_type(); }

    /// Allocate a block of SIMD compatible memory
    pointer allocate( size_type c, const void* = 0 ) const
    {
      return reinterpret_cast<pointer>( boost::simd
                                             ::allocate(c*sizeof(value_type))
                                      );
    }

    /// Deallocate a pointer allocated by the current allocator
    void deallocate (pointer p, size_type ) const
    {
      boost::simd::deallocate( p );
    }
  };

  /// Equality comparison between two allocators
  template<class T>
  bool operator== (allocator<T> const&, allocator<T> const&)
  {
    return true;
  }

  /// Inequality comparison between two allocators
  template<class T>
  bool operator!= (allocator<T> const&, allocator<T> const&)
  {
    return false;
  }
} }

#endif
