//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 20010 - 2011   LRI    UMR 10623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_TOOLBOX_CONSTANT_CONSTANTS_FACT_10_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_CONSTANT_CONSTANTS_FACT_10_HPP_INCLUDED

#include <boost/simd/include/simd.hpp>
#include <boost/simd/sdk/constant/common.hpp>
#include <boost/simd/sdk/constant/register.hpp>
#include <boost/simd/sdk/constant/constant.hpp>

namespace boost { namespace simd
{
  namespace tag
  {
    BOOST_SIMD_CONSTANT_REGISTER(Fact_10,int,3628800,0x4a5d7c00, 0x414baf8000000000ll)
  }

  BOOST_SIMD_CONSTANT_IMPLEMENTATION(boost::simd::tag::Fact_10, Fact_10)
} }

#endif
