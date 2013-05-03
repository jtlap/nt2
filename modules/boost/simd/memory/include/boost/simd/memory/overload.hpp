//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_MEMORY_OVERLOAD_HPP_INCLUDED
#define BOOST_SIMD_MEMORY_OVERLOAD_HPP_INCLUDED

/*!
  @file
  @brief
**/

#include <cstddef>
#include <boost/simd/memory/allocate.hpp>
#include <boost/simd/memory/deallocate.hpp>
#include <boost/simd/memory/parameters.hpp>

/*!
  @brief

**/
#define BOOST_SIMD_MEMORY_OVERLOAD_NEW_DELETE(Alignment)                       \
void* operator new(std::size_t sz, const std::nothrow_t& throw_status)         \
{                                                                              \
  return boost::simd::allocate(sz, Alignment, throw_status);           \
}                                                                              \
                                                                               \
void* operator new(std::size_t sz)                                             \
{                                                                              \
  return boost::simd::allocate(sz, Alignment);                         \
}                                                                              \
                                                                               \
void* operator new(std::size_t , void* p)                                      \
{                                                                              \
  return p;                                                                    \
}                                                                              \
                                                                               \
void* operator new[](std::size_t s, void* p)                                   \
{                                                                              \
  return p;                                                                    \
}                                                                              \
                                                                               \
void* operator new[](std::size_t sz, const std::nothrow_t& throw_status)       \
{                                                                              \
  return boost::simd::allocate(sz, Alignment, throw_status);           \
}                                                                              \
                                                                               \
void* operator new[](std::size_t sz)                                           \
{                                                                              \
  return boost::simd::allocate(sz, Alignment);                         \
}                                                                              \
                                                                               \
void operator delete(void* m)                                                  \
{                                                                              \
  boost::simd::deallocate(m);                                          \
}                                                                              \
                                                                               \
void operator delete[](void* m)                                                \
{                                                                              \
  boost::simd::deallocate(m);                                          \
}                                                                              \
                                                                               \
void operator delete(void* m, const std::nothrow_t&)                           \
{                                                                              \
  boost::simd::deallocate(m);                                          \
}                                                                              \
                                                                               \
void operator delete[](void* m, const std::nothrow_t&)                         \
{                                                                              \
  boost::simd::deallocate(m);                                          \
}                                                                              \
/**/

namespace boost { namespace simd
{
  /*!
    @brief

  **/
  template<std::size_t Alignment = BOOST_SIMD_CONFIG_ALIGNMENT>
  struct aligned_object
  {
    public:
    BOOST_SIMD_MEMORY_OVERLOAD_NEW_DELETE(Alignment)
  };
} }

#endif
