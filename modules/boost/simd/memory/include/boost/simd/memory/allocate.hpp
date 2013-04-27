//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_MEMORY_ALLOCATE_HPP_INCLUDED
#define BOOST_SIMD_MEMORY_ALLOCATE_HPP_INCLUDED

/*!
  @file
  @brief Defines and implement the allocate function
**/

#include <boost/simd/memory/config.hpp>
#include <boost/simd/memory/align_on.hpp>
#include <boost/simd/memory/parameters.hpp>
#include <boost/simd/memory/aligned_malloc.hpp>
#include <boost/simd/memory/align_ptr.hpp>
#include <boost/simd/meta/align_ptr.hpp>

#include <boost/dispatch/attributes.hpp>
#include <boost/dispatch/meta/enable_if_type.hpp>
#include <boost/throw_exception.hpp>
#include <cstddef>

namespace boost { namespace simd {  namespace memory
{
  /*!
    @brief Non-throwing allocation of aligned memory on custom alignment

    Allocate a buffer of bytes aligned on an arbitrary alignment.

    @param nbytes Number of bytes to allocate.
    @param align  Alignment boundary to follow
    @param t      Tag indicating the nothrow behavior of this function.

    @return A pointer to an aligned memory block of @c nbytes bytes. If the
            allocation fails, it returns a null pointer.
  **/
  BOOST_FORCEINLINE BOOST_SIMD_MALLOC BOOST_DISPATCH_NOTHROW byte*
  allocate( std::size_t nbytes, std::size_t align, std::nothrow_t const & t )
  {
    return static_cast<byte*>(aligned_malloc(nbytes, align));
  }

  /*!
    @brief Non-throwing allocation of aligned memory with static alignment

    Allocate a buffer of bytes aligned on an arbitrary statically specified
    alignment.

    @param nbytes Number of bytes to allocate.
    @param t      Tag indicating the nothrow behavior of this function.

    @return A pointer to an aligned memory block of @c nbytes bytes. If the
            allocation fails, it returns a null pointer. For optimization
            purpose, this pointer is marked as properly aligned by using
            compiler specific attributes.
  **/
  template<std::size_t Alignment>
  BOOST_FORCEINLINE BOOST_DISPATCH_NOTHROW
  typename meta::align_ptr<byte,Alignment>::type
  allocate(std::size_t nbytes, std::nothrow_t const & t)
  {
    return align_ptr<Alignment>( allocate( nbytes, Alignment, t) );
  }

  /*!
    @brief Non-throwing allocation of aligned memory

    Allocate a buffer of bytes aligned on current architecture preferred SIMD
    compatible alignment.

    @param nbytes Number of bytes to allocate.
    @param t      Tag indicating the nothrow behavior of this function.

    @return A pointer to an aligned memory block of @c nbytes bytes. If the
            allocation fails, it returns a null pointer. For optimization
            purpose, this pointer is marked as properly aligned by using
            compiler specific attributes.
  **/
  BOOST_FORCEINLINE BOOST_SIMD_MALLOC BOOST_DISPATCH_NOTHROW
  meta::align_ptr<byte,BOOST_SIMD_CONFIG_ALIGNMENT>::type
  allocate(std::size_t nbytes, std::nothrow_t const & t)
  {
    return allocate<BOOST_SIMD_CONFIG_ALIGNMENT>( nbytes, t );
  }

  /*!
    @brief Throwing allocation of aligned memory on custom alignment

    Allocate a buffer of bytes aligned on an arbitrary alignment.

    @param nbytes       Number of bytes to allocate.
    @param align        Alignment boundary to follow

    @return A pointer to an aligned memory block of @c nbytes bytes. If the
            allocation fails, it throws a @c std::bad_alloc exception.
  **/
  BOOST_FORCEINLINE BOOST_SIMD_MALLOC byte*
  allocate( std::size_t nbytes, std::size_t align )
  {
    byte* result = allocate(nbytes, align, std::nothrow_t());
    if(!result) boost::throw_exception( std::bad_alloc() );

    return result;
  }

  /*!
    @brief Throwing allocation of aligned memory with static alignment

    Allocate a buffer of bytes aligned on an arbitrary statically specified
    alignment.

    @param nbytes Number of bytes to allocate.
    @param t      Tag indicating the nothrow behavior of this function.

    @return A pointer to an aligned memory block of @c nbytes bytes. If the
            allocation fails, it throws a @c std::bad_alloc exception. For
            optimization purpose, this pointer is marked as properly aligned
            by using compiler specific attributes.
  **/
  template<std::size_t Alignment>
  BOOST_FORCEINLINE
  typename meta::align_ptr<byte,Alignment>::type
  allocate(std::size_t nbytes)
  {
    return align_ptr<Alignment>( allocate( nbytes, Alignment) );
  }

  /*!
    @brief Throwing allocation of aligned memory

    Allocate a buffer of bytes aligned on current architecture preferred SIMD
    compatible alignment.

    @param nbytes       Number of bytes to allocate.

    @return A pointer to an aligned memory block of @c nbytes bytes. If the
            allocation fails, it throws a @c std::bad_alloc exception. For
            optimization purpose, this pointer is marked as properly aligned
            by using compiler specific attributes.
  **/
  BOOST_FORCEINLINE BOOST_SIMD_MALLOC
  meta::align_ptr<byte,BOOST_SIMD_CONFIG_ALIGNMENT>::type
  allocate( std::size_t nbytes )
  {
    return allocate<BOOST_SIMD_CONFIG_ALIGNMENT>(nbytes);
  }

  /*!
    @brief Allocator based allocation of aligned memory

    Allocate a buffer of bytes aligned on an arbitrary alignment using
    a custom allocator.

    @param alloc  The \c Allocator to use for performing allocation
    @param nbytes Number of bytes to allocate.
    @param align        Alignment boundary to follow

    @return A pointer to an aligned memory block of @c nbytes bytes. If the
            allocation fails, it returns a null pointer. For optimization
            purpose, this pointer is marked as properly aligned by using
            compiler specific attributes.
  **/
  template<class Allocator>
  BOOST_FORCEINLINE
  typename boost::dispatch::meta
                ::enable_if_type< typename Allocator::pointer
                                , byte*
                                >::type
  allocate( Allocator& alloc, std::size_t nbytes, std::size_t align )
  {
    // How many bytes are needed to store all the data + overhead
    std::size_t size  = nbytes + align
                      + sizeof( details::aligned_block_header );

    // How many elements are needed to store proper number of bytes
    std::size_t nelems = size/sizeof(typename Allocator::value_type);

    // Allocate and adjust
    return  static_cast<byte*>
            ( details::adjust_pointer ( alloc.allocate(nelems)
                                      , size
                                      , align
                                      )
            );
  }

  /*!
    @brief Allocator based allocation of aligned memory with static alignment

    Allocate a buffer of bytes aligned on an arbitrary statically specified
    alignment using a custom allocator.

    @param alloc  The \c Allocator to use for performing allocation
    @param nbytes Number of bytes to allocate.
    @param align        Alignment boundary to follow

    @return A pointer to an aligned memory block of @c nbytes bytes. If the
            allocation fails, it returns a null pointer. For optimization
            purpose, this pointer is marked as properly aligned by using
            compiler specific attributes.
  **/
  template<std::size_t Alignment, class Allocator>
  BOOST_FORCEINLINE
  typename boost::dispatch::meta
                ::enable_if_type< typename Allocator::pointer
                                , typename meta::align_ptr<byte,Alignment>::type
                                >::type
  allocate( Allocator& alloc, std::size_t nbytes )
  {
    return align_ptr<Alignment>( allocate(alloc,nbytes,Alignment) );
  }

  /*!
    @brief Allocator based allocation of aligned memory

    Allocate a buffer of bytes aligned on current architecture preferred SIMD
    compatible alignment using a custom allocator.

    @param alloc  The \c Allocator to use for performing allocation
    @param nbytes Number of bytes to allocate.

    @return A pointer to an aligned memory block of @c nbytes bytes. If the
            allocation fails, it returns a null pointer. For optimization
            purpose, this pointer is marked as properly aligned by using
            compiler specific attributes.
  **/
  template<class Allocator>
  BOOST_FORCEINLINE
  typename boost::dispatch::meta
                ::enable_if_type< typename Allocator::pointer
                                , typename meta::align_ptr
                                          < byte
                                          , BOOST_SIMD_CONFIG_ALIGNMENT
                                          >::type
                                >::type
  allocate( Allocator& alloc, std::size_t nbytes )
  {
    return allocate<BOOST_SIMD_CONFIG_ALIGNMENT>(alloc,nbytes);
  }
} } }

#endif
