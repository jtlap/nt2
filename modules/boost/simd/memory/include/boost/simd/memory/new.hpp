//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012 - 2013   MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_MEMORY_NEW_HPP_INCLUDED
#define BOOST_SIMD_MEMORY_NEW_HPP_INCLUDED

/*!
  @file
  @brief Defines and implements global aligned new and delete overload
**/

#include <new>
#include <cstddef>
#include <boost/simd/memory/allocate.hpp>
#include <boost/simd/memory/deallocate.hpp>
#include <boost/simd/preprocessor/malloc.hpp>
#include <boost/simd/preprocessor/parameters.hpp>

/*!
  @brief Aligned new operator for single object

  This is a global overload for the non-throwing operator new for single object
  that performs allocation respecting the current architecture
  SIMD alignment.

  @param sz Number of bytes to allocates
  @param throw_status Non-throwing markup

  @return A pointer referencing a newly allocated aligned memory block
**/
inline BOOST_SIMD_MALLOC void*
operator new(std::size_t sz, const std::nothrow_t& throw_status) throw()
{
  return boost::simd::allocate(sz, throw_status);
}

/*!
  @brief Aligned new operator for single object

  This is a global overload for the throwing operator new for single object
  that performs allocation respecting the current architecture
  SIMD alignment or throw a @c std::bad_alloc if not.

  @param sz Number of bytes to allocates

  @return A pointer referencing a newly allocated aligned memory block
**/
inline BOOST_SIMD_MALLOC void*
operator new(std::size_t sz) throw(std::bad_alloc)
{
  return boost::simd::allocate(sz);
}

/*!
  @brief Aligned new operator for single object

  This is a global overload for the non-throwing operator new
  for single object that performs allocation aligned on an arbitrary boundary.

  @param sz Number of bytes to allocates
  @param align Alignment boundary to respect
  @param throw_status Non-throwing markup

  @return A pointer referencing a newly allocated aligned memory block
**/
inline BOOST_SIMD_MALLOC void*
operator new( std::size_t sz, std::size_t align
            , const std::nothrow_t& throw_status
            ) throw()
{
  return boost::simd::allocate(sz, align, throw_status);
}

/*!
  @brief Aligned new operator for single object

  This is a global overload for the throwing operator new for single object
  that performs allocation aligned on an arbitrary boundary
  or throw a @c std::bad_alloc if not.

  @param sz Number of bytes to allocates
  @param align Alignment boundary to respect

  @return A pointer referencing a newly allocated aligned memory block
**/
inline BOOST_SIMD_MALLOC void*
operator new(std::size_t sz, std::size_t align) throw(std::bad_alloc)
{
  return boost::simd::allocate(sz, align);
}

/*!
  @brief Aligned new operator for multiple objects

  This is a global overload for the non-throwing operator new
  for multiple objects that performs allocation respecting the current
  architecture SIMD alignment.

  @param sz Number of bytes to allocates
  @param throw_status Non-throwing markup

  @return A pointer referencing a newly allocated aligned memory block
**/
inline BOOST_SIMD_MALLOC void*
operator new[](std::size_t sz, const std::nothrow_t& throw_status) throw()
{
  return boost::simd::allocate(sz, throw_status);
}

/*!
  @brief Aligned new operator for multiple objects

  This is a global overload for the throwing operator new for multiple objects
  that performs allocation respecting the current architecture
  SIMD alignment or throw a @c std::bad_alloc if not.

  @param sz Number of bytes to allocates

  @return A pointer referencing a newly allocated aligned memory block
**/
inline BOOST_SIMD_MALLOC void*
operator new[](std::size_t sz) throw(std::bad_alloc)
{
  return boost::simd::allocate(sz);
}

/*!
  @brief Aligned new operator for multiples object  with specific alignment

  This is a global overload for the non-throwing operator new
  for multiples object that performs allocation aligned on an arbitrary boundary.

  @param sz Number of bytes to allocates
  @param align Alignment boundary to respect
  @param throw_status Non-throwing markup

  @return A pointer referencing a newly allocated aligned memory block
**/
inline BOOST_SIMD_MALLOC void*
operator new[]( std::size_t sz, std::size_t align
              , const std::nothrow_t& throw_status
              ) throw()
{
  return boost::simd::allocate(sz, align, throw_status);
}

/*!
  @brief Aligned new operator for multiple objects with specific alignment

  This is a global overload for the throwing operator new for multiple objects
  that performs allocation aligned on an arbitrary boundary or throw a
  @c std::bad_alloc if not.

  @param sz Number of bytes to allocates
  @param align Alignment boundary to respect

  @return A pointer referencing a newly allocated aligned memory block
**/
inline BOOST_SIMD_MALLOC void*
operator new[](std::size_t sz, std::size_t align) throw(std::bad_alloc)
{
  return boost::simd::allocate(sz,align);
}

/*!
  @brief Aligned delete operator

  @param m Pointer referencing the memory block to free
**/
inline void operator delete(void* m)  throw()
{
  boost::simd::deallocate(m);
}

/*!
  @brief Aligned delete[] operator

  @param m Pointer referencing the memory block to free
**/
inline void operator delete[](void* m) throw()
{
  boost::simd::deallocate(m);
}

/// @overload
inline void operator delete(void* m, const std::nothrow_t&) throw()
{
  boost::simd::deallocate(m);
}

/// @overload
inline void operator delete[](void* m, const std::nothrow_t&) throw()
{
  boost::simd::deallocate(m);
}

#endif
