//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_ARITHMETIC_FUNCTIONS_SCALAR_SQRT_HPP_INCLUDED
#define BOOST_SIMD_ARITHMETIC_FUNCTIONS_SCALAR_SQRT_HPP_INCLUDED
#include <boost/simd/arithmetic/functions/sqrt.hpp>
#include <boost/simd/include/constants/nan.hpp>
#include <boost/simd/include/functions/scalar/is_ltz.hpp>
#include <math.h>

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::sqrt_, tag::cpu_
                            , (A0)
                            , (scalar_< double_<A0> >)
                            )
  {
    typedef typename boost::dispatch::meta::as_floating<A0>::type result_type;
    BOOST_SIMD_FUNCTOR_CALL(1)
    {
      #ifdef BOOST_SIMD_NO_DOMAIN_CHECK
      return ::sqrt(a0);
      #else
      return (is_ltz(a0)) ?  Nan<A0>() : ::sqrt(a0);
      #endif
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::sqrt_, tag::cpu_
                            , (A0)
                            , (scalar_< single_<A0> >)
                            )
  {
    typedef A0 result_type;
    BOOST_SIMD_FUNCTOR_CALL(1)
    {
      #ifdef BOOST_SIMD_NO_DOMAIN_CHECK
      return ::sqrtf(a0);
      #else
      // libc has a very poor treatment of exceptions regarding performance
      // this test is at almost no cost but improve drastically performances
      // in case negative arguments are common.
      return (is_ltz(a0)) ?  Nan<A0>() : ::sqrtf(a0);
      #endif
    }
  };
} } }


#endif
