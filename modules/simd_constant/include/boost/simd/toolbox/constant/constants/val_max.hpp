//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_TOOLBOX_CONSTANT_CONSTANTS_VAL_MAX_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_CONSTANT_CONSTANTS_VAL_MAX_HPP_INCLUDED

////////////////////////////////////////////////////////////////////////////////
// Make some real based constants
////////////////////////////////////////////////////////////////////////////////
#include <boost/simd/include/simd.hpp>
#include <boost/simd/sdk/constant/constant.hpp>
#include <boost/simd/toolbox/constant/include.hpp>
#include <boost/simd/sdk/constant/common.hpp>

namespace boost { namespace dispatch
{
  namespace tag { struct val_max_ {};}
} }

namespace boost { namespace simd
{
  BOOST_SIMD_CONSTANT_IMPLEMENTATION(boost::dispatch::tag::val_max_, Valmax)
} }

#include <boost/simd/toolbox/constant/constants/scalar/val_max.hpp>
#include <boost/simd/toolbox/constant/constants/simd/all/val_max.hpp>

#endif
