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

#include <stdlib.h>
#include <new>

#if !defined(__APPLE__)
#include <malloc.h>
#endif

#if !defined(BOOST_SIMD_DEFAULT_REALLOC)
/// INTERNAL ONLY
#define BOOST_SIMD_DEFAULT_REALLOC std::realloc
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

      - a aligned memory allocation if @c ptr is equal to 0;
      - a no-op if the requested @c size is equal to the old size of the memory
        block referenced by @c ptr;
      - a call to the system specific reallocation function followed by a
        potential alignment fix-up.

    followed by a potential copy of the original data in the new memory block
    (contrary to aligned_reuse).

    @par Framework specific override

    By default, aligned_realloc use system specific functions to handle memory
    reallocation. One can specify a custom reallocation function to be used
    instead. This custom function must have a prototype equivalent to:

    @code
    void* f(void* ptr, std::size_t sz, std::size_t align);
    @endcode

    In this case, the following code:

    @code
    void* r = aligned_realloc(ptr,size,alignment, f);
    @endcode

    is equivalent to a call to @c f followed by an alignment fix-up.

    @pre   @c alignment is a non-zero power of two.

    @param ptr        Pointer to reallocate
    @param sz         Number of bytes to allocate
    @param align      Alignment boundary to respect
    @âram  realloc_fn Function to use for basic reallocation

    @return Pointer referencing the newly allocated memory block.
  **/
  template<typename ReallocFunction>
  inline void* aligned_realloc( void* ptr, std::size_t sz, std::size_t align
                              , ReallocFunction realloc_fn
                              )
  {
    details::aligned_block_header oldHeader = {0,0};

    if(ptr) oldHeader = details::get_block_header( ptr );

    std::size_t const oldSize( oldHeader.userBlockSize );

    sz = sz ? sz + align + sizeof(details::aligned_block_header)
            : 0u;

    // Else actually realloc the whole stuff and readjust for alignment
    return details::adjust_pointer
            ( realloc_fn( oldHeader.pBlockBase, sz )
            , sz, align, oldSize
            , static_cast<char const *>(ptr)
            - static_cast<char const *>( oldHeader.pBlockBase )
            );
  }

  /// @overload
  inline void* aligned_realloc(void* ptr, std::size_t sz, std::size_t align)
  {
    // Do we want to use built-ins special aligned free/alloc ?
    #if defined( _MSC_VER ) && !defined(BOOST_SIMD_MEMORY_NO_BUILTINS)

    if( simd::is_aligned(ptr,align ) )
    {
      return ::_aligned_realloc( ptr, sz, align );
    }
    else
    {
      void* const fresh_ptr = aligned_malloc(sz,align);
      std::size_t const oldSize( _msize( ptr ) );

      if( !fresh_ptr ) return 0;

      std::memcpy( fresh_ptr, ptr, std::min( sz, oldSize ) );
      aligned_free( ptr );
    }

    #elif (     defined( BOOST_SIMD_CONFIG_SUPPORT_POSIX_MEMALIGN )            \
            ||  (defined( _GNU_SOURCE ) && !defined( __ANDROID__ ))            \
          )                                                                    \
       && !defined(BOOST_SIMD_MEMORY_NO_BUILTINS)

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
        void* const new_ptr = std::realloc(ptr, sz);
        if( simd::is_aligned(new_ptr,align ) ) return new_ptr;
        std::free(new_ptr);
      }
    }

    void* const fresh_ptr = aligned_malloc(sz,align);

    if( !fresh_ptr ) return 0;

    std::memcpy( fresh_ptr, ptr, std::min( sz, oldSize ) );
    aligned_free( ptr );

    return fresh_ptr;

    #else

    return aligned_realloc(ptr, sz, align, &BOOST_SIMD_DEFAULT_REALLOC);

    #endif
  }
} }

#endif
