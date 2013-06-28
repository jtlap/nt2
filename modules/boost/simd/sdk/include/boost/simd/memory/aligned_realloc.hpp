//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012 - 2013   MetaScale SAS
//         Copyright 2013          Domagoj Saric, Little Endian Ltd.
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_MEMORY_ALIGNED_REALLOC_HPP_INCLUDED
#define BOOST_SIMD_MEMORY_ALIGNED_REALLOC_HPP_INCLUDED

#include <boost/simd/memory/details/posix.hpp>
#include <boost/simd/memory/details/aligned_stash.hpp>
#include <boost/simd/memory/aligned_free.hpp>
#include <boost/simd/memory/aligned_malloc.hpp>
#include <boost/dispatch/attributes.hpp>
#include <boost/config.hpp>
#include <malloc.h>
#include <new>

// ICC warns about combination of inline and noinline
#if defined(BOOST_INTEL)
#pragma warning push
#pragma warning disable 2196
#endif

namespace boost { namespace simd
{
  /*!
    @brief Low level aligned memory reallocation

    Wraps system specific code for reallocating an aligned memory block of
    @c size bytes with an address aligned on @c alignment.

    @par Semantic:

    For any given pointer @c ptr, integral @c size and @c alignment constraint,

    @code
    void* r = aligned_realloc(ptr,size,alignment);
    @endcode

    is equivalent to :

      - a aligned memory allocation is @c ptr is equal to 0;
      - a no-op if the requested @c size is equal to the old size of the memory
        block referenced by @c ptr;
      - a call to the system specific reallocation function followed by an
        alignment fix-up.

    followed by a potential copy of the original data in the new memory block
    (contrary to aligned_reuse).

    @pre   @c alignment is a non-zero power of two.
    @param ptr      Pointer to reallocate
    @param sz       Number of bytes to allocate
    @param align    Alignment boundary to respect
    @return Pointer referencing the newly allocated memory block.
  **/
  BOOST_FORCEINLINE
  void* aligned_realloc(void* const ptr, std::size_t sz, std::size_t align)
  {
#if defined( _MSC_VER ) && defined( BOOST_SIMD_MEMORY_USE_BUILTINS )

    return ::_aligned_realloc( ptr, sz, align );

#elif defined( __APPLE__ )

    return std::realloc( ptr, sz );

#elif     defined( BOOST_SIMD_CONFIG_SUPPORT_POSIX_MEMALIGN )                  \
      || (defined( _GNU_SOURCE ) && !defined( __ANDROID__ ))

    // Resizing to 0 free the pointer data and return
    if(sz == 0)
    {
      aligned_free( ptr );
      return 0;
    }

    // Reallocating empty pointer performs allocation
    if(ptr == 0) return aligned_malloc( sz, align );

#ifdef __ANDROID__
    // https://groups.google.com/forum/?fromgroups=#!topic/android-ndk/VCEUpMfSh_o
    std::size_t const oldSize( ::dlmalloc_usable_size( ptr ) );
#else
    std::size_t const oldSize( ::malloc_usable_size( ptr ) );
#endif


    if( simd::is_aligned(ptr,align ) )
    {
      if ( ( oldSize - sz ) < 32 )
      {
        return ptr;
      }
      else
      {
        void* BOOST_DISPATCH_RESTRICT  const new_ptr = std::realloc(ptr, sz);
        if( simd::is_aligned(new_ptr,align ) ) return new_ptr;
        std::free(new_ptr);
      }
    }

    void * BOOST_DISPATCH_RESTRICT const fresh_ptr = aligned_malloc(sz,align);

    if( !fresh_ptr ) return 0;

    std::memcpy( fresh_ptr, ptr, std::min( sz, oldSize ) );
    aligned_free( ptr );

    return fresh_ptr;
#else

    // Resizing to 0 free the pointer data and return
    if(sz == 0)
    {
      aligned_free( ptr );
      return 0;
    }

    // Reallocating empty pointer performs allocation
    if(ptr == 0) return aligned_malloc( sz, align );

    details::aligned_block_header const oldHeader( details::get_block_header( ptr ) );
    std::size_t const oldSize( oldHeader.userBlockSize );

    // Return if idempotent reallocation is performed
    if( oldSize == sz ) return ptr;

    // Else actually realloc the whole stuff and readjust for alignment
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
#endif
  }

} }

#if defined(BOOST_INTEL)
#pragma warning pop
#endif

#endif
