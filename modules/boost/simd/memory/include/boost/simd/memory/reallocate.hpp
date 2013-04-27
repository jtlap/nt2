//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012 - 2013   MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_MEMORY_REALLOCATE_HPP_INCLUDED
#define BOOST_SIMD_MEMORY_REALLOCATE_HPP_INCLUDED

/*!
  @file
  @brief Defines and implement the reallocate function
**/

#include <boost/simd/memory/allocate.hpp>
#include <boost/simd/memory/deallocate.hpp>
#include <boost/simd/memory/is_aligned.hpp>
#include <boost/simd/memory/config.hpp>
#include <boost/simd/memory/parameters.hpp>
#include <boost/simd/memory/aligned_realloc.hpp>
#include <boost/simd/memory/align_ptr.hpp>
#include <boost/simd/meta/align_ptr.hpp>

#include <boost/dispatch/attributes.hpp>
#include <algorithm>
#include <cstring>
#include <cstddef>

namespace boost { namespace simd {  namespace memory
{
  /*!
    @brief Aligned memory reallocation

    Reallocated a raw buffer of aligned bytes on an arbitrary alignment boundary.

    @param ptr     Pointer to the memory to reallocate.
    @param nbytes  New number of bytes to allocate
    @param align   Hint on the alignment boundary used at allocation.

    @return A pointer to a reallocated memory block

    @pre @c align is a power of 2
    @post Returned pointer is aligned on @c align
  **/
  BOOST_FORCEINLINE byte*
  reallocate(byte* ptr, std::size_t nbytes, std::size_t align)
  {
    return static_cast<byte*>(aligned_realloc(ptr,nbytes,align));
  }

  /*!
    @brief Aligned memory reallocation with a static alignment

    Reallocated a raw buffer of aligned bytes on statically specified alignment
    boundary.

    @param ptr          Pointer to the memory to reallocate.
    @param nbytes       New number of bytes to allocate
    @tparam Alignment   Hint on the alignment boundary used at allocation. By
                        default, this parameter is equal to the current system
                        SIMD alignment requirement.

    @return A pointer to a reallocated memory block

    @pre @c Alignment is a power of 2
    @post Returned pointer is aligned on @c Alignment
  **/
  template<std::size_t Alignment>
  BOOST_FORCEINLINE
  typename meta::align_ptr<byte ,Alignment>::type
  reallocate( byte* ptr, std::size_t nbytes )
  {
    return align_ptr<Alignment>(reallocate(ptr, nbytes, Alignment));
  }

  //// INTERNAL ONLY
  BOOST_FORCEINLINE
  meta::align_ptr<byte ,BOOST_SIMD_CONFIG_ALIGNMENT>::type
  reallocate( byte* ptr, std::size_t nbytes )
  {
    return reallocate<BOOST_SIMD_CONFIG_ALIGNMENT>( ptr, nbytes );
  }

  /*!
    @brief Aligned allocator-based memory reallocation

    Reallocated a raw buffer of aligned bytes on an arbitrary alignment boundary
    using an allocator.

    @param alloc  Allocator performing the (de)allocation
    @param ptr    Pointer to the memory to reallocate.
    @param nbytes New number of bytes to allocate
    @param align  Hint on the alignment boundary used at allocation. By default,
                  this parameter is equal to the current system SIMD alignment
                  requirement.

    @return A pointer to a reallocated memory block containing @c nbytes bytes.

    @pre @c align is a power of 2
    @post Returned pointer is aligned on @c align
  **/
  template<class Allocator>
  BOOST_FORCEINLINE
  typename  boost::dispatch::meta::
            enable_if_type< typename Allocator::pointer
                          , byte*
                          >::type
  reallocate(Allocator& alloc, byte* ptr, std::size_t nbytes, std::size_t align)
  {
    // Resizing to 0 free the pointer data and return
    if(nbytes == 0)
    {
      deallocate(alloc, ptr );
      return 0;
    }

    // Reallocating empty pointer performs allocation
    if(ptr == 0) return allocate(alloc, nbytes, align );

    details::aligned_block_header const old( details::get_block_header( ptr ) );
    std::size_t const oldSize( old.userBlockSize );

    // Return if idempotent reallocation is performed with constant alignment
    // TODO Try to just readjust if possible (aka align is lower than before ?)
    if( oldSize == nbytes && is_aligned(ptr,align) ) return ptr;

    // Else reallocate manually/copy/deallocate old data
    byte* fresh_ptr = allocate(alloc, nbytes, align );
    if( !fresh_ptr ) return 0;

    std::memcpy( fresh_ptr, ptr, std::min( nbytes, oldSize ) );
    deallocate(alloc, ptr );

    return fresh_ptr;
  }

  /*!
    @brief Statically aligned allocator-based memory reallocation

    Reallocated a raw buffer of aligned bytes on statically specified alignment
    boundary using an allocator.

    @param alloc   Allocator performing the (de)allocation
    @param ptr     Pointer to the memory to reallocate.
    @param nbytes  New number of bytes to allocate
    @tparam Alignment  Static Hint on the alignment boundary used at allocation.

    @return A pointer to a reallocated memory block containing @c nbytes bytes.

    @pre @c Alignment is a power of 2
    @post Returned pointer is aligned on @c Alignment
  **/
  template<std::size_t Alignment, class Allocator>
  BOOST_FORCEINLINE
  typename  boost::dispatch::meta::
            enable_if_type< typename Allocator::pointer
                          , typename meta::align_ptr<byte ,Alignment>::type
                          >::type
  reallocate( Allocator& alloc, byte* ptr, std::size_t nbytes )
  {
    return align_ptr<Alignment>(reallocate(alloc,ptr,nbytes));
  }

  /// INTERNAL ONLY
  template<class Allocator>
  BOOST_FORCEINLINE
  typename  boost::dispatch::meta::
            enable_if_type< typename Allocator::pointer
                          , typename meta::align_ptr
                                    < byte
                                    , BOOST_SIMD_CONFIG_ALIGNMENT
                                    >::type
                          >::type
  reallocate( Allocator& alloc, byte* ptr, std::size_t nbytes )
  {
    return align_ptr<BOOST_SIMD_CONFIG_ALIGNMENT>(reallocate(alloc,ptr,nbytes));
  }
} } }

#endif
