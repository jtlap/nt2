//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_TOOLBOX_ARITHMETIC_FUNCTIONS_SIMD_COMMON_ARG_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_ARITHMETIC_FUNCTIONS_SIMD_COMMON_ARG_HPP_INCLUDED
#include <boost/simd/toolbox/arithmetic/functions/arg.hpp>
#include <boost/dispatch/meta/as_floating.hpp>
#include <boost/simd/sdk/simd/meta/is_real_convertible.hpp>
#include <boost/simd/include/constants/real.hpp>
#include <boost/dispatch/meta/strip.hpp>
#include <boost/simd/include/functions/simd/is_nan.hpp>
#include <boost/simd/include/functions/simd/is_ltz.hpp>
#include <boost/simd/include/functions/simd/if_else_zero.hpp>
#include <boost/simd/include/functions/simd/if_allbits_else.hpp>
// No implementation for integer types

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION(boost::simd::tag::arg_, tag::cpu_,
                      (A0)(X),
                      ((simd_<floating_<A0>,X>))
                     )
  {
    typedef A0 result_type;
    BOOST_SIMD_FUNCTOR_CALL_REPEAT(1)
    {
      // a0 >= 0 -> 0, a0 < 0 ->Pi, a0 Nan -> Nan
      return if_nan_else(is_nan(a0), if_else_zero(is_ltz(a0), Pi<result_type>()));
    }
  };
} } }
#endif
