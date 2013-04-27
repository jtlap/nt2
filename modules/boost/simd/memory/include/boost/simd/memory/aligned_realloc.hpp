//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_MEMORY_ALIGNED_REALLOC_HPP_INCLUDED
#define BOOST_SIMD_MEMORY_ALIGNED_REALLOC_HPP_INCLUDED

#include <boost/simd/memory/config.hpp>
#include <boost/simd/memory/details/aligned_stash.hpp>
#include <boost/dispatch/attributes.hpp>
#include <boost/config.hpp>

#include <malloc.h>
#include <new>

/// ICC warns about combination of inline and noinline,
/// except it's a valid use-case here
#if defined(BOOST_INTEL)
#pragma warning push
#pragma warning disable 2196
#endif

namespace boost { namespace simd { namespace memory
{
#if defined( _MSC_VER ) && defined( BOOST_SIMD_MEMORY_USE_BUILTINS )

  BOOST_FORCEINLINE
  void* aligned_realloc(void* const ptr, std::size_t sz, std::size_t align)
  {
    return ::_aligned_realloc( ptr, sz, align );
  }

#elif defined( __APPLE__ )

  BOOST_FORCEINLINE
  void* aligned_realloc( void * const ptr, std::size_t sz, std::size_t)
  {
    return std::realloc( ptr, sz );
  }

#elif     defined( BOOST_SIMD_CONFIG_SUPPORT_POSIX_MEMALIGN )                  \
      || (defined( _GNU_SOURCE ) && !defined( __ANDROID__ ))

  BOOST_DISPATCH_NOINLINE inline
  void* aligned_realloc( void * const ptr, std::size_t sz, std::size_t align )
  {
    /// Resizing to 0 free the pointer data and return
    if(sz == 0)
    {
      aligned_free( ptr );
      return 0;
    }

    /// Reallocating empty pointer performs allocation
    if(ptr == 0) return aligned_malloc( sz, align );

#ifdef __ANDROID__
    // https://groups.google.com/forum/?fromgroups=#!topic/android-ndk/VCEUpMfSh_o
    std::size_t const oldSize( ::dlmalloc_usable_size( ptr ) );
#else
    std::size_t const oldSize( ::malloc_usable_size( ptr ) );
#endif

    /// @todo Replace the magic number with something smarter.
    ///                                   (26.10.2012.) (Domagoj Saric)
    if ( ( oldSize - sz ) < 32 ) return ptr;

    void* BOOST_DISPATCH_RESTRICT const new_ptr = std::realloc(ptr, sz);

    /// Return empty ptr is needed
    if(!new_ptr) return 0;

    /// Return ptr if correctly aligned
    if( simd::is_aligned(new_ptr,align ) ) return new_ptr;

    /// If not, allocate, move then free the old
    void * BOOST_DISPATCH_RESTRICT const fresh_ptr = aligned_malloc(sz,align);

    /// Return if nullptr
    if( !fresh_ptr ) return 0;

    /// Copy + free
    std::memcpy( fresh_ptr, new_ptr, std::min( sz, oldSize ) );
    aligned_free( new_ptr );

    return fresh_ptr;
  }

#else

  BOOST_DISPATCH_NOINLINE inline
  void * aligned_realloc( void * const ptr, std::size_t sz, std::size_t align )
  {
    /// Resizing to 0 free the pointer data and return
    if(sz == 0)
    {
      aligned_free( ptr );
      return 0;
    }

    /// Reallocating empty pointer performs allocation
    if(ptr == 0) return aligned_malloc( sz, align );

    details::aligned_block_header const oldHeader( details::get_block_header( ptr ) );
    std::size_t const oldSize( oldHeader.userBlockSize );

    /// Return if idempotent reallocation is performed
    if( oldSize == sz ) return ptr;

    /// Else actaully realloc the whole stuff and reajust for alignment
    return details::adjust_pointer
            ( std::realloc( oldHeader.pBlockBase
                          , sz + align + sizeof(details::aligned_block_header)
                          )
            , sz
            , align
            , oldSize
            , static_cast<char const *>(ptr)
            - static_cast<char const *>( oldHeader.pBlockBase )
            );
  }

#endif

} } }

#if defined(BOOST_INTEL)
#pragma warning pop
#endif

#endif
