//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_TOOLBOX_REDUCTION_FUNCTIONS_SIMD_COMMON_DETAILS_COMPARE_LESS_HELPER_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_REDUCTION_FUNCTIONS_SIMD_COMMON_DETAILS_COMPARE_LESS_HELPER_HPP_INCLUDED

#include <boost/simd/toolbox/bitwise/functions/reversebits.hpp>

////////////////////////////////////////////////////////////////////////////////
// shared helper
////////////////////////////////////////////////////////////////////////////////
namespace boost { namespace simd { namespace details
{
  template<class T>
  inline bool compare_less_helper(T mask_lt, T mask_gt)
  {
    unsigned int mlt = boost::simd::reversebits(mask_lt);
    unsigned int mgt = boost::simd::reversebits(mask_gt);
    return (mlt > mgt) && mlt;
  }
} } }

#include <boost/simd/include/functions/simd/reversebits.hpp>

#endif
