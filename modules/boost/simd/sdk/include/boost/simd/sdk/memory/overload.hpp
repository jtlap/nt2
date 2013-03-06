//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_SDK_MEMORY_OVERLOAD_HPP_INCLUDED
#define BOOST_SIMD_SDK_MEMORY_OVERLOAD_HPP_INCLUDED

#include <cstddef>
#include <boost/simd/sdk/memory/allocate.hpp>
#include <boost/simd/sdk/memory/deallocate.hpp>

////////////////////////////////////////////////////////////////////////////////
// Macro for operator new/new[] overload with aligned allocation
////////////////////////////////////////////////////////////////////////////////
#define BOOST_SIMD_MEMORY_OVERLOAD_NEW_DELETE(A)                           \
void* operator new(std::size_t s)                                   \
{                                                                   \
  return boost::simd::memory::allocate(s);                                  \
}                                                                   \
void* operator new[](std::size_t s)                                 \
{                                                                   \
  return boost::simd::memory::allocate(s);                                  \
}                                                                   \
void operator delete(void *p)                                       \
{                                                                   \
  boost::simd::memory::deallocate(reinterpret_cast<boost::simd::memory::byte*>(p)); \
}                                                                   \
void operator delete[](void *p)                                     \
{                                                                   \
  boost::simd::memory::deallocate(reinterpret_cast<boost::simd::memory::byte*>(p)); \
}                                                                   \
/**/

#endif
