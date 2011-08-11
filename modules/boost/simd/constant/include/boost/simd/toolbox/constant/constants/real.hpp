//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_TOOLBOX_CONSTANT_CONSTANTS_REAL_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_CONSTANT_CONSTANTS_REAL_HPP_INCLUDED

////////////////////////////////////////////////////////////////////////////////
// Make some real based constants
////////////////////////////////////////////////////////////////////////////////
#include <boost/simd/include/simd.hpp>
#include <boost/simd/sdk/constant/constant.hpp>
#include <boost/simd/toolbox/constant/include.hpp>
#include <boost/simd/sdk/constant/common.hpp>
#include <boost/simd/toolbox/constant/constants/macros.hpp>
#include <boost/simd/toolbox/constant/constants/localgen.hpp>

// specially generated constants
#include <boost/simd/toolbox/constant/constants/scalar/val_max.hpp>
#include <boost/simd/toolbox/constant/constants/scalar/val_min.hpp>
#include <boost/simd/toolbox/constant/constants/scalar/signmask.hpp>
#include <boost/simd/toolbox/constant/constants/scalar/max_left_shift.hpp>  
#include <boost/simd/toolbox/constant/constants/false.hpp>
#include <boost/simd/toolbox/constant/constants/true.hpp>
#include <boost/simd/toolbox/constant/constants/scalar/ieee_spec.hpp>  

namespace boost { namespace simd
{
  // standard constants
  BOOST_SIMD_MAKE_STD_CONSTANT(Mhalf         ,0xBFE0000000000000ll, 0xBF000000, 0 )
  BOOST_SIMD_MAKE_STD_CONSTANT(Mzero         ,0x8000000000000000ll, 0x80000000, 0 )
  BOOST_SIMD_MAKE_STD_CONSTANT(Half          ,0x3FE0000000000000ll, 0x3F000000, 0 )
  BOOST_SIMD_MAKE_STD_CONSTANT(Third         ,0x3FD5555555555555ll, 0x3EAAAAAB, 0 )
  BOOST_SIMD_MAKE_STD_CONSTANT(Quarter       ,0x3FD0000000000000ll, 0x3E800000, 0 )
  BOOST_SIMD_MAKE_STD_CONSTANT(Twotom10      ,0x3F50000000000000ll, 0x3a800000, 0 )
  BOOST_SIMD_MAKE_STD_CONSTANT(Two2nmb       ,0x4330000000000000ll, 0x4b000000, 0 )
  BOOST_SIMD_MAKE_STD_CONSTANT(Pi            ,0x400921fb54442d18ll, 0x40490fdb, 3 )
  BOOST_SIMD_MAKE_STD_CONSTANT(Splitfactor   ,0x41a0000000000000ll, 0x46000000, 0 )
  BOOST_SIMD_MAKE_STD_CONSTANT(Sqrt_2o_2     ,0x3fe6a09e667f3bcdll, 0x3f3504f3, 0 )
  BOOST_SIMD_MAKE_STD_CONSTANT(Sqrt_2        ,0x3ff6a09e667f3bccll, 0x3fb504f3, 1 )
  BOOST_SIMD_MAKE_STD_CONSTANT(Gold          ,0x3ff9e3779b97f4a8ll, 0x3fcf1bbd, 1 )
  BOOST_SIMD_MAKE_STD_CONSTANT(Cgold         ,0x3fd8722191a02d61ll, 0x3ec3910d, 0 )
  BOOST_SIMD_MAKE_STD_CONSTANT(Eps           ,0x3cb0000000000000ll, 0X34000000, 1 )
  BOOST_SIMD_MAKE_STD_CONSTANT(Halfeps       ,0x3ca0000000000000ll, 0x33800000, 1 )
  BOOST_SIMD_MAKE_STD_CONSTANT(Threeeps      ,0x3CC8000000000000ll, 0x34c00000, 3 )
  BOOST_SIMD_MAKE_STD_CONSTANT(Sqrteps       ,0x3e50000000000000ll, 0x39b504f3, 1 )
  BOOST_SIMD_MAKE_STD_CONSTANT(Fourthrooteps ,0x3f20000000000000ll, 0x3c9837f0, 1 )
  BOOST_SIMD_MAKE_STD_CONSTANT(Thirdrooteps  ,0x3ed965fea53d6e42ll, 0x3ba14518, 1 )
  BOOST_SIMD_MAKE_STD_CONSTANT(Mlogeps2      ,0x403205966f2b4f13ll, 0x40ff1402, 0 )
  BOOST_SIMD_MAKE_STD_CONSTANT(Mindenormal   ,0x1ll               , 0x1       , 1 )
  BOOST_SIMD_MAKE_STD_CONSTANT(Smallestposval,0x0010000000000000ll, 0x00800000, 1 )
  BOOST_SIMD_MAKE_STD_CONSTANT(Inf           ,0x7FF0000000000000ll, 0x7F800000, boost::simd::Valmax<result_type>())
  BOOST_SIMD_MAKE_STD_CONSTANT(Minf          ,0xFFF0000000000000ll, 0xFF800000, boost::simd::Valmin<result_type>())
  BOOST_SIMD_MAKE_STD_CONSTANT(Nan           ,0xFFFFFFFFFFFFFFFFll, 0xFFFFFFFF, 0)
} }

#endif
