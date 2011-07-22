//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_TOOLBOX_CONSTANT_CONSTANTS_IEEE_SPEC_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_CONSTANT_CONSTANTS_IEEE_SPEC_HPP_INCLUDED

////////////////////////////////////////////////////////////////////////////////
// Make some real based constants
////////////////////////////////////////////////////////////////////////////////
#include <boost/simd/include/simd.hpp>
#include <boost/simd/sdk/constant/constant.hpp>
#include <boost/simd/toolbox/constant/include.hpp>
#include <boost/simd/sdk/constant/common.hpp>

namespace boost { namespace dispatch
{
  namespace tag
  {
    struct ldexp_mask_        {}; struct nb_digits_         {};
    struct nb_mantissa_bits_  {}; struct nb_exponent_bits_  {};
    struct max_exponent_      {}; struct min_exponent_      {};
  }
} }

namespace boost { namespace simd
{  
  BOOST_SIMD_CONSTANT_IMPLEMENTATION(boost::dispatch::tag::ldexp_mask_       , Ldexpmask      )
  BOOST_SIMD_CONSTANT_IMPLEMENTATION(boost::dispatch::tag::nb_mantissa_bits_ , Nbmantissabits )
  BOOST_SIMD_CONSTANT_IMPLEMENTATION(boost::dispatch::tag::nb_exponent_bits_ , Nbexponentbits )
  BOOST_SIMD_CONSTANT_IMPLEMENTATION(boost::dispatch::tag::max_exponent_     , Maxexponent    )
  BOOST_SIMD_CONSTANT_IMPLEMENTATION(boost::dispatch::tag::min_exponent_     , Minexponent    )
  BOOST_SIMD_CONSTANT_IMPLEMENTATION(boost::dispatch::tag::nb_digits_        , Nbdigits       )
} }

#include <boost/simd/toolbox/constant/constants/scalar/ieee_spec.hpp>
#include <boost/simd/toolbox/constant/constants/simd/all/ieee_spec.hpp>

#endif
