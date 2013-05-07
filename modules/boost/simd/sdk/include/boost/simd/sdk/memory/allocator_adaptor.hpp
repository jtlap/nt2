//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_SDK_MEMORY_ALLOCATOR_ADAPTOR_HPP_INCLUDED
#define BOOST_SIMD_SDK_MEMORY_ALLOCATOR_ADAPTOR_HPP_INCLUDED

#include <cstddef>
#include <boost/simd/sdk/memory/config.hpp>
#include <boost/simd/sdk/memory/allocator.hpp>

namespace boost { namespace simd {  namespace memory
{
  //////////////////////////////////////////////////////////////////////////////
  // Adapt an allocator to be algined
  //////////////////////////////////////////////////////////////////////////////
  template<class T, class Allocator>
  struct allocator_adaptor : Allocator::template rebind<T>::other
  {
    ////////////////////////////////////////////////////////////////////////////
    // Rebase Current allocator
    ////////////////////////////////////////////////////////////////////////////
    typedef typename Allocator::template rebind<T>::other base_type;

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
      typedef allocator_adaptor<U,Allocator> other;
    };

    ////////////////////////////////////////////////////////////////////////////
    // Ctor/dtor
    ////////////////////////////////////////////////////////////////////////////
     allocator_adaptor() : base_type() {}
    ~allocator_adaptor() {}

     template<class U>
     allocator_adaptor(allocator_adaptor<U,Allocator> const& src)
                      : base_type(src.base()) {}

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
      boost::simd::memory::deallocate ( base(), reinterpret_cast<byte*>(p)
                                      , s*sizeof(value_type)
                              );
    }

    ////////////////////////////////////////////////////////////////////////////
    // Extended Allocator interface -- reallocate
    ////////////////////////////////////////////////////////////////////////////
    pointer resize(pointer p, size_type n, size_type o )
    {
      if( o < n )
      {
        byte* ptr = reallocate( base()
                              , reinterpret_cast<byte*>(p)
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

  template<class T,class A>
  bool operator== ( allocator_adaptor<T,A> const& a
                  , allocator_adaptor<T,A> const& b
                  )
  {
    return a.base() == b.base();
  }

  template<class T,class A>
  bool operator!= ( allocator_adaptor<T,A> const& a
                  , allocator_adaptor<T,A> const& b
                  )
  {
    return a.base() != b.base();
  }
} } }

#endif
