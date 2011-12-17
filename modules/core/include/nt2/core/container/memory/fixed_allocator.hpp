//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_CONTAINER_MEMORY_FIXED_ALLOCATOR_HPP_INCLUDED
#define NT2_CORE_CONTAINER_MEMORY_FIXED_ALLOCATOR_HPP_INCLUDED

#include <cstddef>

namespace nt2 {  namespace memory
{
  //============================================================================
  /**!
   * fixed_allocator is a stateful allocator that wraps an already allocated
   * pointer into an allocator interface.
   **/
  //============================================================================
  template<class T> struct fixed_allocator
  {
    //==========================================================================
    // Allocator static expression conformance
    //==========================================================================
    typedef T               value_type;
    typedef T*              pointer;
    typedef T const*        const_pointer;
    typedef T&              reference;
    typedef T const&        const_reference;
    typedef std::size_t     size_type;
    typedef std::ptrdiff_t  difference_type;

    template<class U> struct rebind { typedef fixed_allocator<U> other; };

    //==========================================================================
    // Ctor/dtor
    //==========================================================================
     fixed_allocator( pointer ptr = pointer() ) : pointee_(ptr) {}
    ~fixed_allocator() {}

    //==========================================================================
    // Assignment operator
    //==========================================================================
    fixed_allocator& operator=(fixed_allocator const& src)
    {
      pointee_ = src.pointee_;
      return *this;
    }

    //==========================================================================
    // Transtyping constructor - Only vlaid if T* and U* are covnertible
    //==========================================================================
    template<class U>
    fixed_allocator(fixed_allocator<U> const& src)
    {
      pointee_ = static_cast<pointer>(src.pointee());
    }

    //==========================================================================
    // Original pointer value
    //==========================================================================
    pointer pointee_;

    //==========================================================================
    // Pointer accessors
    //==========================================================================
    pointer&        pointee()       { return pointee_; }
    pointer const&  pointee() const { return pointee_; }
    
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
    void construct(pointer p, const T& t) { p = new (p) value_type(t);  }
    void destroy(pointer p)               { p->~value_type();           }

    ////////////////////////////////////////////////////////////////////////////
    // Memory handling
    ////////////////////////////////////////////////////////////////////////////
    pointer allocate( size_type , const void* = 0 ) const { return pointee_; }
    void    deallocate(pointer, size_type) const {}
  };

  //============================================================================
  /**!
   * Checks if two fixed_allocator are equal. Such allocators are equal if and
   * only if they share the same pointee.
   **/
  //============================================================================    
  template<class T>
  bool operator==(fixed_allocator<T> const& lhs, fixed_allocator<T> const& rhs)
  {
    return lhs.pointee() == rhs.pointee();
  }

  //============================================================================
  /**!
   * Checks if two fixed_allocator are non-equal. Such allocators are not equal
   * only if they share different pointees.
   **/
  //============================================================================    
  template<class T>
  bool operator!=(fixed_allocator<T> const& lhs, fixed_allocator<T> const& rhs)
  {
    return !(lhs == rhs);
  }
} }

#endif
