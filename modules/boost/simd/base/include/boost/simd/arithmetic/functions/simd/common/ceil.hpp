//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_ARITHMETIC_FUNCTIONS_SIMD_COMMON_CEIL_HPP_INCLUDED
#define BOOST_SIMD_ARITHMETIC_FUNCTIONS_SIMD_COMMON_CEIL_HPP_INCLUDED
#include <boost/simd/arithmetic/functions/ceil.hpp>
#include <boost/simd/include/constants/one.hpp>
#include <boost/simd/include/functions/simd/round.hpp>
#include <boost/simd/include/functions/simd/seladd.hpp>
#include <boost/simd/include/functions/simd/is_less.hpp>

namespace boost { namespace simd { namespace ext
{
// It seems that mapping the scalar version outperform this common version
// with double_ with a gain of 2 in no sse4.1 systems. So we only define it
// for single_ in which case it is 1.5 better.
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::ceil_, tag::cpu_
                            , (A0)(X)
                            , ((simd_<single_<A0>,X>))
                            )
  {
    typedef A0 result_type;
    BOOST_SIMD_FUNCTOR_CALL(1)
    {
      const A0 d0 = round(a0);
      return seladd(lt(d0,a0),d0,One<A0>());
    }
  };
} } }


#endif
