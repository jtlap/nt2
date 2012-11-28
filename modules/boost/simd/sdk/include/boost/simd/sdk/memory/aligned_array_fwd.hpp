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

namespace boost { namespace simd { namespace memory
{
  template<class T, std::size_t N, std::size_t Align = 0>
  struct aligned_array;

  template<std::size_t N>
  struct max_alignment;
} } }

#endif
