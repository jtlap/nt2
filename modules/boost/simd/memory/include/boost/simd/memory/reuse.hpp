//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012 - 2013   MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_MEMORY_REUSE_HPP_INCLUDED
#define BOOST_SIMD_MEMORY_REUSE_HPP_INCLUDED

#include <boost/simd/memory/allocate.hpp>
#include <boost/simd/memory/deallocate.hpp>
#include <boost/simd/memory/is_aligned.hpp>
#include <boost/simd/memory/parameters.hpp>
#include <boost/simd/memory/aligned_reuse.hpp>
#include <boost/simd/memory/align_ptr.hpp>
#include <boost/simd/memory/meta/align_ptr.hpp>

#include <boost/dispatch/attributes.hpp>
#include <algorithm>
#include <cstring>
#include <cstddef>

namespace boost { namespace simd {  namespace memory
{
  /*!
    @brief Aligned memory recycling

    Reallocated a raw buffer of aligned bytes on an arbitrary alignment boundary.

    @param ptr     Pointer to the memory to reuse.
    @param nbytes  New number of bytes to allocate
    @param align   Hint on the alignment boundary used at allocation.

    @return A pointer to a reused memory block
  **/
  BOOST_FORCEINLINE byte*
  reuse(byte* ptr, std::size_t nbytes, std::size_t align)
  {
    return static_cast<byte*>(aligned_reuse(ptr,nbytes,align));
  }

  /*!
    @brief Aligned memory recycling with a static alignment

    Reallocated a raw buffer of aligned bytes on current architecture preferred
    SIMD comaptible alignment.

    @param ptr     Pointer to the memory to reuse.
    @param nbytes  New number of bytes to allocate

    @return A pointer to a reused memory block
  **/
  template<std::size_t Alignment>
  BOOST_FORCEINLINE
  typename meta::align_ptr<byte* ,Alignment>::type
  reuse( byte* ptr, std::size_t nbytes )
  {
    return align_ptr<Alignment>(aligned_reuse(ptr, nbytes, Alignment));
  }

  /*!
    @brief Aligned memory recycling

    Reallocated a raw buffer of aligned bytes on current architecture preferred
    SIMD comaptible alignment.

    @param ptr     Pointer to the memory to reuse.
    @param nbytes  New number of bytes to allocate

    @return A pointer to a reused memory block
  **/
  BOOST_FORCEINLINE meta::align_ptr<byte*,BOOST_SIMD_CONFIG_ALIGNMENT>::type
  reuse( byte* ptr, std::size_t nbytes )
  {
    return reuse<BOOST_SIMD_CONFIG_ALIGNMENT>( ptr, nbytes );
  }

  /*!
     Reallocated a raw buffer of aligned bytes using an Allocator.

     @param alloc   Allocator performing the (de)allocation
     @param ptr     Pointer to the memory to reuse.
     @param nbytes  New number of bytes to allocate
     @param align   Hint on the alignment boundary used at allocation. By
     default, this parameter is equals to the current system SIMD alignment
     requirement.

     @return A pointer to a reused memory block containing \c nbytes bytes.
  **/
  template<class Allocator>
  BOOST_FORCEINLINE
  typename  boost::dispatch::meta::
            enable_if_type< typename Allocator::pointer
                          , byte*
                          >::type
  reuse( Allocator& a, byte* ptr, std::size_t nbytes, std::size_t align )
  {
    /// Resizing to 0 free the pointer data and return
    if(nbytes == 0)
    {
      deallocate(a, ptr );
      return 0;
    }

    /// Reallocating empty pointer performs allocation
    if(ptr == 0) return allocate(a, nbytes, align );

    details::aligned_block_header const old( details::get_block_header( ptr ) );
    std::size_t const oldSize( old.userBlockSize );

    /// Return if idempotent recycling is performed with constant alignment
    /// TODO Try to just reajust if possible (aka align is lower than before ?)
    if( oldSize == nbytes && is_aligned(ptr,align) ) return ptr;

    /// Else reuse manually/copy/deallocate old data
    byte* fresh_ptr = allocate(a, nbytes, align );
    if( !fresh_ptr ) return 0;

    deallocate(a, ptr );

    return fresh_ptr;
  }  }

  /*!
     Reallocated a raw buffer of aligned bytes using an Allocator and a static
     Alignment.

     @param alloc   Allocator performing the (de)allocation
     @param ptr     Pointer to the memory to reuse.
     @param nbytes  New number of bytes to allocate
     @tparam Alignment  Static Hint on the alignment boundary used at allocation.

     @return A pointer to a reused memory block containing \c nbytes bytes.
  **/
  template<std::size_t Alignment, class Allocator>
  BOOST_FORCEINLINE
  typename  boost::dispatch::meta::
            enable_if_type< typename Allocator::pointer
                          , byte*
                          >::type
  reuse( Allocator& a, byte* ptr, std::size_t nbytes )
  {
    return align_ptr<Alignment>(reuse(a,ptr,nbytes));
  }

  /*!
     Reallocated a raw buffer of aligned bytes using an Allocator and a default
     Alignment.

     @param alloc   Allocator performing the (de)allocation
     @param ptr     Pointer to the memory to reuse.
     @param nbytes  New number of bytes to allocate

     @return A pointer to a reused memory block containing \c nbytes bytes.
  **/
  template<class Allocator>
  BOOST_FORCEINLINE
  typename  boost::dispatch::meta::
            enable_if_type< typename Allocator::pointer
                          , byte*
                          >::type
  reuse( Allocator& a, byte* ptr, std::size_t nbytes )
  {
    return align_ptr<BOOST_SIMD_CONFIG_ALIGNMENT>(reuse(a,ptr,nbytes));
  }
} } }

#endif
