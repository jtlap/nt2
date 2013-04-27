//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_MEMORY_ALIGNED_MALLOC_HPP_INCLUDED
#define BOOST_SIMD_MEMORY_ALIGNED_MALLOC_HPP_INCLUDED

#include <boost/simd/memory/config.hpp>
#include <boost/simd/memory/details/aligned_stash.hpp>
#include <boost/dispatch/meta/ignore_unused.hpp>
#include <boost/dispatch/attributes.hpp>
#include <new>

namespace boost { namespace simd { namespace memory
{
  BOOST_FORCEINLINE BOOST_SIMD_MALLOC
  void* BOOST_DISPATCH_RESTRICT
  aligned_malloc( std::size_t const size, std::size_t const alignment)
  {
#if     defined( _MSC_VER )                                                    \
    &&  defined( BOOST_SIMD_MEMORY_USE_BUILTINS )                              \

    return ::_aligned_malloc(size, alignment);

#elif defined( __APPLE__ )

    boost::dispatch::ignore_unused(alignment);
    return std::malloc( size );

#elif defined( BOOST_SIMD_CONFIG_SUPPORT_POSIX_MEMALIGN )

    void* result(0);

    BOOST_VERIFY(   ( ::posix_memalign( &result, alignment, size ) == 0 )
                ||  ( result == 0 )
                );

    return static_cast<void* BOOST_DISPATCH_RESTRICT>(result);

#elif defined( _GNU_SOURCE ) && !defined( __ANDROID__ )
    /**
      @note Inexplicable yet consistently reproducible SIGSEGVs encountered on
            Android (4.1.3 emulator) with memalign (as if it actually allocates
            only  a part of the requested memory).

      @todo Harvest:
      https://groups.google.com/a/chromium.org/forum/?fromgroups=#!msg/chromium-reviews/uil2eVbovQM/9slPSDkBvX8J
      http://codereview.chromium.org/10796020/diff/5018/base/memory/aligned_memory.h

                                           (25.10.2012.) (Domagoj Saric)
    **/
    return ::memalign( size, alignment );

#else
    /// manual "metadata" stashing
    return  details::adjust_pointer
            ( std::malloc( size + alignment
                         + sizeof( details::aligned_block_header )
                         )
            , size
            , alignment
            );
#endif
  }
} } }

#endif
