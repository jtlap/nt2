//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012 - 2013   MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_MEMORY_ALIGNED_FREE_HPP_INCLUDED
#define BOOST_SIMD_MEMORY_ALIGNED_FREE_HPP_INCLUDED

#include <boost/simd/memory/config.hpp>
#include <boost/simd/memory/details/aligned_stash.hpp>
#include <boost/dispatch/attributes.hpp>
#include <new>

namespace boost { namespace simd
{
  /*!
    @brief Low level aligned memory deallocation

    Wraps system specific code for deallocating an aligned memory block.

    @param ptr Pointer referencing the memory to deallocate
  **/
  BOOST_FORCEINLINE void aligned_free( void * const ptr )
  {
#if     defined( _MSC_VER )                                                    \
    &&  defined( BOOST_SIMD_MEMORY_USE_BUILTINS )

    if(ptr)  ::_aligned_free( ptr );

#elif   defined( __APPLE__ )                                                   \
    ||  defined( BOOST_SIMD_CONFIG_SUPPORT_POSIX_MEMALIGN )                    \
    || (defined( _GNU_SOURCE ) && !defined( __ANDROID__ ))

    if(ptr)  std::free( ptr );

#else

    if(ptr) std::free( details::get_block_header( ptr ).pBlockBase );

#endif
  }
} }

#endif
