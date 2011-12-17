//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_CONTAINER_MEMORY_STATIC_ALLOCATOR_HPP_INCLUDED
#define NT2_CORE_CONTAINER_MEMORY_STATIC_ALLOCATOR_HPP_INCLUDED

#include <cstddef>
#include <boost/array.hpp>
#include <boost/assert.hpp>

namespace nt2 {  namespace memory
{
  //============================================================================
  /**!
   * static_allocator is a stateful allocator that wraps a statically allocated
   * memory block into an allocator interface.
   **/
  //============================================================================
  template<class T, class Size> struct static_allocator
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

    template<class U> struct rebind { typedef static_allocator<U,Size> other; };

    //==========================================================================
    // Ctor/dtor
    //==========================================================================
     static_allocator() {}
    ~static_allocator() {}

    //==========================================================================
    // Assignment operator
    //==========================================================================
    static_allocator& operator=(static_allocator const& src)
    {
      data_ = src.data_;
      return *this;
    }

    //==========================================================================
    // Transtyping constructor - Only valid if T and U are convertible
    //==========================================================================
    template<class U>
    static_allocator(static_allocator<U,Size> const& src)
    {
      std::copy(src.data().begin(),src.data().end(),data_.begin());
    }

    //==========================================================================
    // Stored data
    //==========================================================================
    boost::array<T,Size::value> data_;

    //==========================================================================
    // Data accessors
    //==========================================================================
    boost::array<T,Size::value> const&  data() const { return data_; }
    
    ////////////////////////////////////////////////////////////////////////////
    // Address handling
    ////////////////////////////////////////////////////////////////////////////
    pointer       address(reference r)       { return &r; }
    const_pointer address(const_reference r) { return &r; }

    ////////////////////////////////////////////////////////////////////////////
    // Size handling
    ////////////////////////////////////////////////////////////////////////////
    size_type max_size() const  { return Size::value; }

    ////////////////////////////////////////////////////////////////////////////
    // Object lifetime handling
    ////////////////////////////////////////////////////////////////////////////
    void construct(pointer p, const T& t) { p = new (p) value_type(t);  }
    void destroy(pointer p)               { p->~value_type();           }

    ////////////////////////////////////////////////////////////////////////////
    // Memory handling
    ////////////////////////////////////////////////////////////////////////////
    pointer allocate( size_type s, const void* = 0 )
    {
      BOOST_ASSERT_MSG
      ( (s <= max_size())
      , "Allocation request more memory than available in this static_allocator"
      );
      
      return &data_[0];
    }
    
    void    deallocate(pointer, size_type) const {}
  };

  //============================================================================
  /**!
   * Checks if two static_allocator are equal. Such allocators are equal if and
   * only if they own the same data block
   **/
  //============================================================================    
  template<class T,class Size>
  bool operator== ( static_allocator<T,Size> const& lhs
                  , static_allocator<T,Size> const& rhs
                  )
  {
    return lhs.data().begin() == rhs.data().begin();
  }

  //============================================================================
  /**!
   * Checks if two static_allocator are non-equal. Such allocators are not equal
   * only if they share different data block.
   **/
  //============================================================================    
  template<class T,class Size>
  bool operator!= ( static_allocator<T,Size> const& lhs
                  , static_allocator<T,Size> const& rhs
                  )
  {
    return !(lhs == rhs);
  }
} }

#endif
