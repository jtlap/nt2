//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_SDK_MEMORY_ALIGNED_ARRAY_FWD_HPP_INCLUDED
#define BOOST_SIMD_SDK_MEMORY_ALIGNED_ARRAY_FWD_HPP_INCLUDED

#include <boost/simd/sdk/config/arch.hpp>

namespace boost { namespace simd { namespace memory
{
  /* Default alignment is BOOST_SIMD_ARCH_ALIGNMENT or the largest power of 2
   * smaller than N*sizeof(T), whichever is smaller */
  template< class T
          , std::size_t N
          , std::size_t Align = (BOOST_SIMD_ARCH_ALIGNMENT > (N*sizeof(T)))
                              ? (  ( ( (N*sizeof(T))
                                     | (N*sizeof(T)) >> 1
                                     | (N*sizeof(T)) >> 2
                                     | (N*sizeof(T)) >> 4
                                     | (N*sizeof(T)) >> 8
                                     | (N*sizeof(T)) >> 16
                                     )
                                     >> 1
                                   ) + 1
                                )
                              : BOOST_SIMD_ARCH_ALIGNMENT
          >
  struct aligned_array;
} } }

#endif
