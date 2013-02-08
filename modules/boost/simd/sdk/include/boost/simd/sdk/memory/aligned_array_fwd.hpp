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
#include <boost/simd/sdk/memory/meta/next_power_of_2.hpp>

namespace boost { namespace simd { namespace memory
{
  /* Default alignment is BOOST_SIMD_ARCH_ALIGNMENT or the largest power of 2
   * smaller than N*sizeof(T), whichever is smaller */
  template< class T
          , std::size_t N
          , std::size_t Align = (BOOST_SIMD_ARCH_ALIGNMENT > (N*sizeof(T)))
                              ? meta::prev_power_of_2_c< N*sizeof(T) >::value
                              : BOOST_SIMD_ARCH_ALIGNMENT
          >
  struct aligned_array;
} } }

#endif
