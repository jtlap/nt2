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
#include <boost/simd/memory/details/aligned_stash.hpp>
#include <boost/simd/memory/aligned_malloc.hpp>
#include <boost/simd/memory/aligned_realloc.hpp>
#include <boost/dispatch/attributes.hpp>
#include <boost/config.hpp>

#include <stdlib.h>

#if !defined(__APPLE__)
#include <malloc.h>
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
    void* r = aligned_reuse(ptr,size,alignment);
    @endcode

    is equivalent to :

      - a aligned memory allocation is @c ptr is equal to 0;
      - a no-op if the requested @c size is equal to the old size of the memory
        block referenced by @c ptr;
      - a call to the system specific reallocation function followed by an
        alignment fix-up.

    Note that data is not preserved during reusing (contrary to aligned_realloc).

    @pre   @c alignment is a non-zero power of two.
    @param ptr        Pointer to reuse
    @param size       Number of bytes to allocate
    @param alignment  Alignment boundary to respect
    @return Pointer referencing the newly allocated memory block.
  **/
  inline void* aligned_reuse(void* ptr, std::size_t size, std::size_t alignment)
  {
    // Do we want to use built-ins special aligned free/alloc ?
    #if defined( _MSC_VER ) && !defined(BOOST_SIMD_MEMORY_NO_BUILTINS)

    std::size_t* const oldptr = static_cast<std::size_t*>(ptr)-1;

    if(ptr && !size)
    {
      ::_aligned_free(oldptr);
      return 0;
    }

    std::size_t* fresh_ptr;
    if(ptr && alignment == *oldptr)
      fresh_ptr = static_cast<std::size_t*>(::_aligned_offset_realloc(oldptr, size+sizeof(std::size_t), alignment, sizeof(std::size_t)));
    else
      fresh_ptr = static_cast<std::size_t*>(::_aligned_offset_malloc(size+sizeof(std::size_t), alignment, sizeof(std::size_t)));

    *fresh_ptr++ = alignment;
    return fresh_ptr;

    #elif (     defined( BOOST_SIMD_CONFIG_SUPPORT_POSIX_MEMALIGN )            \
            ||  (defined( _GNU_SOURCE ) && !defined( __ANDROID__ ))            \
          )                                                                    \
       && !defined(BOOST_SIMD_MEMORY_NO_BUILTINS)

    // Resizing to 0 free the pointer data and return
    if(size == 0)
    {
      ::free(ptr);
      return 0;
    }

    #ifdef __ANDROID__
    // https://groups.google.com/forum/?fromgroups=#!topic/android-ndk/VCEUpMfSh_o
    std::size_t const oldSize( ::dlmalloc_usable_size( ptr ) );
    #else
    std::size_t const oldSize( ::malloc_usable_size( ptr ) );
    #endif

    if( simd::is_aligned(ptr, align) )
    {
      if( ( oldSize - size ) < BOOST_SIMD_REALLOC_SHRINK_THRESHOLD )
      {
        return ptr;
      }
      else
      {
        // FIXME: realloc will free the old memory if it moves.
        // if it moves to a non-aligned memory segment and the subsequent
        // memory allocation fails, we break the invariant
        ptr = ::realloc(ptr, size);
        if( simd::is_aligned(ptr, alignment) )
          return ptr;
      }
    }

    void* const fresh_ptr = aligned_malloc(size, alignment);
    if(!fresh_ptr)
      return 0;

    ::free(ptr);

    return fresh_ptr;

    #else

    return aligned_realloc(ptr, size, alignment);

    #endif
  }
} }

#endif
