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
#ifndef BOOST_SIMD_MEMORY_ALIGNED_MALLOC_HPP_INCLUDED
#define BOOST_SIMD_MEMORY_ALIGNED_MALLOC_HPP_INCLUDED

#include <boost/simd/memory/details/posix.hpp>
#include <boost/simd/memory/details/aligned_stash.hpp>
#include <boost/simd/preprocessor/malloc.hpp>
#include <boost/dispatch/meta/ignore_unused.hpp>
#include <boost/dispatch/attributes.hpp>

#include <stdlib.h>
#include <new>

#if !defined(__APPLE__)
#include <malloc.h>
#endif

#if !defined(BOOST_SIMD_DEFAULT_MALLOC)
/// INTERNAL ONLY
#define BOOST_SIMD_DEFAULT_MALLOC std::malloc
#endif

namespace boost { namespace simd
{
  /*!
    @brief Low level aligned memory allocation

    Wraps system specific code for allocating an aligned memory block of
    @c size bytes with an address aligned on @c alignment.

    @par Semantic:

    For any given integral @c size and @c alignment constraint,

    @code
    void* r = aligned_alloc(size,alignment);
    @endcode

    is equivalent to a call to the system specific allocation function followed
    by a potential alignment fix-up.

    @par Framework specific override

    By default, aligned_malloc use system specific functions to handle memory
    allocation. One can specify a custom allocation function to be used
    instead. This custom function must have a prototype equivalent to:

    @code
    void* f(std::size_t sz, std::size_t align);
    @endcode

    In this case, the following code:

    @code
    void* r = aligned_realloc(ptr,size,alignment, f);
    @endcode

    is equivalent to a call to @c f followed by an alignment fix-up.

    @pre   @c alignment is a non-zero power of two.

    @param size       Number of bytes to allocate
    @param alignment  Alignment boundary to respect
    @param malloc_fn  Function object to use for allocation of the base pointer

    @return Pointer referencing the newly allocated memory block.
  **/
  template<typename AllocFunction>
  inline void* aligned_malloc ( std::size_t size, std::size_t alignment
                              , AllocFunction malloc_fn
                              )
  {
    return  details::adjust_pointer
            ( malloc_fn(size + alignment + sizeof(details::aligned_block_header))
            , size
            , alignment
            );
  }

  /// @overload
  inline void* aligned_malloc(std::size_t size, std::size_t alignment)
  {
    // Do we want to use built-ins special aligned free/alloc ?
    #if defined( _MSC_VER ) && !defined(BOOST_SIMD_MEMORY_NO_BUILTINS)

    return ::_aligned_malloc(size, alignment);

    #elif     defined( BOOST_SIMD_CONFIG_SUPPORT_POSIX_MEMALIGN )              \
          && !defined(BOOST_SIMD_MEMORY_NO_BUILTINS)

    alignment = std::max(alignment,sizeof(void*));

    void* result(0);

    BOOST_VERIFY(   (::posix_memalign(&result,alignment,size) == 0 )
                ||  ( result == 0 )
                );

    return result;

    #elif     defined( _GNU_SOURCE ) && !defined( __ANDROID__ )                \
          && !defined(BOOST_SIMD_MEMORY_NO_BUILTINS)
    /*
      Inexplicable yet consistently reproducible SIGSEGVs encountered on
      Android (4.1.3 emulator) with memalign (as if it actually allocates
      only a part of the requested memory).

      TODO:
      https://groups.google.com/a/chromium.org/forum/?fromgroups=#!msg/chromium-reviews/uil2eVbovQM/9slPSDkBvX8J
      http://codereview.chromium.org/10796020/diff/5018/base/memory/aligned_memory.h

                                       (25.10.2012.) (Domagoj Saric)
    */
    return ::memalign( size, alignment );

    #else

    return aligned_malloc( size, alignment, BOOST_SIMD_DEFAULT_MALLOC );

    #endif
  }
} }

#endif
