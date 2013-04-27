//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_MEMORY_NEW_HPP_INCLUDED
#define BOOST_SIMD_MEMORY_NEW_HPP_INCLUDED

/*!
  @file
  @brief Global aligned new and delete overload
**/

#include <new>
#include <cstddef>
#include <boost/simd/memory/allocate.hpp>
#include <boost/simd/memory/deallocate.hpp>
#include <boost/simd/memory/parameters.hpp>

/*!
  @brief Aligned new operator

  This is a global overload for the nothrow new operator that performs
  allocation respecting the current architecture SIMD alignment.

**/
void* operator new(std::size_t sz, const std::nothrow_t& throw_status) throw()
{
  return boost::simd::memory::allocate(sz, throw_status);
}

/*!
  @brief Aligned new operator
**/
void* operator new(std::size_t sz) throw(std::bad_alloc)
{
  return boost::simd::memory::allocate(sz);
}

/*!
  @brief Aligned new operator
**/
void* operator new( std::size_t sz, std::size_t align
                  , const std::nothrow_t& throw_status
                  ) throw()
{
  return boost::simd::memory::allocate(sz, align, throw_status);
}

/*!
  @brief Aligned new operator
**/
void* operator new(std::size_t sz, std::size_t align) throw(std::bad_alloc)
{
  return boost::simd::memory::allocate(sz, align);
}

/*!
  @brief Aligned new[] operator
**/
void* operator new[]( std::size_t sz, std::size_t align
                    , const std::nothrow_t& throw_status
                    ) throw()
{
  return boost::simd::memory::allocate(sz, align, throw_status);
}

/*!
  @brief Aligned new[] operator
**/
void* operator new[](std::size_t sz, std::size_t align) throw(std::bad_alloc)
{
  return boost::simd::memory::allocate(sz,align);
}

/*!
  @brief Aligned new[] operator
**/
void* operator new[](std::size_t sz, const std::nothrow_t& throw_status) throw()
{
  return boost::simd::memory::allocate(sz, throw_status);
}

/*!
  @brief Aligned new[] operator
**/
void* operator new[](std::size_t sz) throw(std::bad_alloc)
{
  return boost::simd::memory::allocate(sz);
}

/*!
  @brief Aligned delete operator
**/
void operator delete(void* m)  throw()
{
  boost::simd::memory
             ::deallocate(reinterpret_cast<boost::simd::memory::byte*>(m));
}

/*!
  @brief Aligned delete[] operator
**/
void operator delete[](void* m) throw()
{
  boost::simd::memory
             ::deallocate(reinterpret_cast<boost::simd::memory::byte*>(m));
}

/*!
  @brief Aligned delete operator
**/
void operator delete(void* m, const std::nothrow_t&) throw()
{
  boost::simd::memory
             ::deallocate(reinterpret_cast<boost::simd::memory::byte*>(m));
}

/*!
  @brief Aligned delete[] operator
**/
void operator delete[](void* m, const std::nothrow_t&) throw()
{
  boost::simd::memory
             ::deallocate(reinterpret_cast<boost::simd::memory::byte*>(m));
}

#endif
