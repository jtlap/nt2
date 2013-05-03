//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012 - 2013   MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_MEMORY_ALIGNED_REUSE_HPP_INCLUDED
#define BOOST_SIMD_MEMORY_ALIGNED_REUSE_HPP_INCLUDED

#include <boost/simd/memory/details/posix.hpp>
#include <boost/simd/memory/aligned_realloc.hpp>
#include <boost/simd/memory/details/aligned_stash.hpp>
#include <boost/dispatch/attributes.hpp>
#include <boost/config.hpp>
#include <malloc.h>
#include <new>

// ICC warns about combination of inline and noinline,
#if defined(BOOST_INTEL)
#pragma warning push
#pragma warning disable 2196
#endif

namespace boost { namespace simd
{
  /*!
    @brief Low level aligned memory reuse

    Wraps system specific code for reusing an aligned memory block of
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

    Note that data are not preserved during reusing (contrary to aligned_realloc).

    @pre   @c alignment is a non-zero power of two.
    @param ptr      Pointer to reuse
    @param sz       Number of bytes to allocate
    @param align    Alignment boundary to respect
    @return Pointer referencing the newly allocated memory block.
  **/
  BOOST_DISPATCH_NOINLINE inline
  void* aligned_reuse( void * const ptr, std::size_t sz, std::size_t align )
  {

#if     defined( BOOST_SIMD_CONFIG_SUPPORT_POSIX_MEMALIGN )                    \
    || (defined( _GNU_SOURCE ) && !defined( __ANDROID__ ))                     \
    || (defined( _MSC_VER ) && defined( BOOST_SIMD_MEMORY_USE_BUILTINS ))

    /// Resizing to 0 free the pointer data and return
    if(sz == 0)
    {
      aligned_free( ptr );
      return 0;
    }

    /// Reallocating empty pointer performs allocation
    if(ptr == 0) return aligned_malloc( sz, align );

#ifdef __ANDROID__
    std::size_t const oldSize( ::dlmalloc_usable_size( ptr ) );
#else
    std::size_t const oldSize( ::malloc_usable_size( ptr ) );
#endif

    if ( ( oldSize - sz ) < 32 ) return ptr;

    void* BOOST_DISPATCH_RESTRICT const new_ptr = std::realloc(ptr, sz);

    if(!new_ptr) return 0;

    if( simd::is_aligned(new_ptr,align ) ) return new_ptr;
    void * BOOST_DISPATCH_RESTRICT const fresh_ptr = aligned_malloc(sz,align);

    if( !fresh_ptr ) return 0;
    aligned_free( new_ptr );

    return fresh_ptr;
#else
    return aligned_realloc(ptr, sz, align);
#endif
  }

} }

#if defined(BOOST_INTEL)
#pragma warning pop
#endif

#endif
