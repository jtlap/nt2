//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012 - 2013   MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_MEMORY_DETAILS_ALLOCATOR_WRAPPER_HPP_INCLUDED
#define BOOST_SIMD_MEMORY_DETAILS_ALLOCATOR_WRAPPER_HPP_INCLUDED

#include <boost/config.hpp>

namespace boost { namespace simd { namespace details
{
  template<typename Allocator> struct allocator_malloc
  {
    allocator_malloc(Allocator& a) : alloc(a)
    {
    }

    void* operator()(std::size_t sz)
    {
      #ifndef BOOST_NO_EXCEPTIONS
      try
      {
        return alloc.allocate((sz-1)/sizeof(typename Allocator::value_type)+1);
      }
      catch(...)
      {
        return 0;
      }
      #else
      return alloc.allocate((sz-1)/sizeof(typename Allocator::value_type)+1);
      #endif
    }

    Allocator& alloc;

    private:
    allocator_malloc& operator=(allocator_malloc const&);
  };

  template<typename Allocator> struct allocator_free
  {
    allocator_free(Allocator& a, std::size_t s) : alloc(a), sz(s) {}

    void operator()(void* ptr)
    {
      typedef typename Allocator::pointer type;
      return alloc.deallocate(type(ptr), (sz-1) / sizeof(typename Allocator::value_type) + 1);
    }

    Allocator& alloc;
    std::size_t sz;

    private:
    allocator_free& operator=(allocator_free const&);
  };
} } }

#endif
