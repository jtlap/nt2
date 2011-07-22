//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_TOOLBOX_CONSTANT_CONSTANTS_EPS_RELATED_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_CONSTANT_CONSTANTS_EPS_RELATED_HPP_INCLUDED

#include <boost/simd/include/simd.hpp>
#include <boost/simd/sdk/constant/constant.hpp>
#include <boost/simd/toolbox/constant/include.hpp>
#include <boost/simd/sdk/constant/common.hpp>

namespace boost { namespace dispatch { namespace tag
{
  struct eps__            {};
  struct half_eps__       {};
  struct _3_x_eps_        {};
  struct sqrt_eps_        {};
  struct forth_root_eps_  {};
  struct third_root_eps_  {};
  struct mlog_eps_2_      {};
  struct min_denormal_    {};
  struct smallest_pos_val_{};
} } }

namespace boost { namespace simd
{
  BOOST_SIMD_CONSTANT_IMPLEMENTATION(boost::dispatch::tag::eps__            , Eps           )
  BOOST_SIMD_CONSTANT_IMPLEMENTATION(boost::dispatch::tag::half_eps__       , Halfeps       )
  BOOST_SIMD_CONSTANT_IMPLEMENTATION(boost::dispatch::tag::_3_x_eps_        , Threeeps      )
  BOOST_SIMD_CONSTANT_IMPLEMENTATION(boost::dispatch::tag::sqrt_eps_        , Sqrteps       )
  BOOST_SIMD_CONSTANT_IMPLEMENTATION(boost::dispatch::tag::forth_root_eps_  , Fourthrooteps  )
  BOOST_SIMD_CONSTANT_IMPLEMENTATION(boost::dispatch::tag::third_root_eps_  , Thirdrooteps  )
  BOOST_SIMD_CONSTANT_IMPLEMENTATION(boost::dispatch::tag::mlog_eps_2_      , Mlogeps2      )
  BOOST_SIMD_CONSTANT_IMPLEMENTATION(boost::dispatch::tag::min_denormal_    , Mindenormal   )
  BOOST_SIMD_CONSTANT_IMPLEMENTATION(boost::dispatch::tag::smallest_pos_val_, Smallestposval)
} }

#include <boost/simd/toolbox/constant/constants/scalar/eps_related.hpp>
#include <boost/simd/toolbox/constant/constants/simd/all/eps_related.hpp>

#endif
