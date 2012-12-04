//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_TOOLBOX_ARITHMETIC_FUNCTIONS_SIMD_COMMON_REC_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_ARITHMETIC_FUNCTIONS_SIMD_COMMON_REC_HPP_INCLUDED
#include <boost/simd/toolbox/arithmetic/functions/rec.hpp>
#include <boost/dispatch/meta/as_floating.hpp>
#include <boost/simd/sdk/simd/meta/is_real_convertible.hpp>
#include <boost/simd/include/constants/digits.hpp>
#include <boost/simd/include/functions/simd/tofloat.hpp>

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::rec_, tag::cpu_
                            , (A0)(X)
                            , ((simd_<arithmetic_<A0>,X>))
                            )
  {
    typedef typename dispatch::meta::as_floating<A0>::type result_type;
    BOOST_SIMD_FUNCTOR_CALL(1)
    {
      return One<result_type>()/boost::simd::tofloat(a0);
    }
  };
} } }

#endif
