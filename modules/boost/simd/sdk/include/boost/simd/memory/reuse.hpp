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
#include <boost/simd/memory/align_ptr.hpp>
#include <boost/simd/memory/deallocate.hpp>
#include <boost/simd/memory/is_aligned.hpp>
#include <boost/simd/memory/aligned_reuse.hpp>
#include <boost/simd/preprocessor/parameters.hpp>
#include <boost/simd/meta/align_ptr.hpp>

#include <boost/dispatch/attributes.hpp>
#include <algorithm>
#include <cstring>
#include <cstddef>

namespace boost { namespace simd
{
  /*!
    @brief Aligned memory recycling with arbitrary dynamic alignment

    Recycles a raw buffer of aligned bytes on an arbitrary alignment boundary
    without preserving data.

    @param ptr    Pointer to the memory to reuse.
    @param nbytes New number of bytes to allocate
    @param align  Hint on the alignment boundary used at allocation.

    @return A pointer to a reused memory block
  **/
  BOOST_FORCEINLINE void*
  reuse(void* ptr, std::size_t nbytes, std::size_t align)
  {
    return aligned_reuse(ptr,nbytes,align);
  }

  /*!
    @brief Aligned memory recycling

    Recycles a raw buffer of aligned bytes on an arbitrary static
    alignment boundary without preserving data.

    @param ptr    Pointer to the memory to reuse.
    @param nbytes New number of bytes to allocate.

    @tparam Alignment Static hint on the alignment boundary used at allocation.
                      By default, this alignment is equal to current SIMD
                      alignment.

    @return A pointer to a reused memory block
  **/
  template<std::size_t Alignment>
  BOOST_FORCEINLINE typename meta::align_ptr<void,Alignment>::type
  reuse( void* ptr, std::size_t nbytes )
  {
    return align_ptr<Alignment>(aligned_reuse(ptr, nbytes, Alignment));
  }

  /// INTERNAL ONLY
  BOOST_FORCEINLINE
  meta::align_ptr<void>::type reuse( void* ptr, std::size_t nbytes )
  {
    return reuse<BOOST_SIMD_CONFIG_ALIGNMENT>( ptr, nbytes );
  }

  /*!
    @brief Allocator-based aligned memory recycling on arbitrary alignment

    Recycles a raw buffer of aligned bytes using an Allocator without
    preserving data.

    @param alloc  Allocator performing the (de)allocation
    @param ptr    Pointer to the memory to reuse.
    @param nbytes New number of bytes to allocate
    @param align  Hint on the alignment boundary used at allocation. By
                  default, this parameter is equals to the current system
                  SIMD alignment requirement.

    @return A pointer to a reused memory block containing \c nbytes bytes.
  **/
  template<class Allocator>
  BOOST_FORCEINLINE
  #if defined(DOXYGEN_ONLY)
  void*
  #else
  typename  boost::dispatch::meta::
            enable_if_type<typename Allocator::pointer, void*>::type
  #endif
  reuse( Allocator& alloc, void* ptr, std::size_t nbytes, std::size_t align )
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

    // Return if idempotent recycling is performed with constant alignment
    // TODO Try to just reajust if possible (aka align is lower than before ?)
    if( oldSize == nbytes && is_aligned(ptr,align) ) return ptr;

    // Else reuse manually/copy/deallocate old data
    void* fresh_ptr = allocate(alloc, nbytes, align );
    if( !fresh_ptr ) return 0;

    deallocate(alloc, ptr );

    return fresh_ptr;
  }

  /*!
    @brief Allocator-based aligned memory recycling on arbitrary static alignment

    Recycles a raw buffer of aligned bytes using an Allocator and a static
    Alignment. By default, this alignment is equal to current SIMD preferred
    alignment.

    @param alloc   Allocator performing the (de)allocation
    @param ptr     Pointer to the memory to reuse.
    @param nbytes  New number of bytes to allocate

    @tparam Alignment Static Hint on the alignment boundary used at allocation.
                      By default, this alignment is equal to current SIMD
                      alignment.

    @return A pointer to a reused memory block containing \c nbytes bytes.
  **/
  template<std::size_t Alignment, class Allocator>
  BOOST_FORCEINLINE
  #if defined(DOXYGEN_ONLY)
  void*
  #else
  typename  boost::dispatch::meta::
            enable_if_type<typename Allocator::pointer,void*>::type
  #endif
  reuse( Allocator& alloc, void* ptr, std::size_t nbytes )
  {
    return align_ptr<Alignment>(reuse(alloc,ptr,nbytes,Alignment));
  }

  /// @overload
  template<class Allocator>
  BOOST_FORCEINLINE
  #if defined(DOXYGEN_ONLY)
  void*
  #else
  typename  boost::dispatch::meta::
            enable_if_type< typename Allocator::pointer
                          , typename meta::align_ptr<void>::type
                          >::type
  #endif
  reuse( Allocator& alloc, void* ptr, std::size_t nbytes )
  {
    return reuse<BOOST_SIMD_CONFIG_ALIGNMENT>(alloc,ptr,nbytes);
  }
} }

#endif
