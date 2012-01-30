//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_TOOLBOX_OPERATOR_FUNCTIONS_SIMD_SSE_AVX_DIVIDES_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_OPERATOR_FUNCTIONS_SIMD_SSE_AVX_DIVIDES_HPP_INCLUDED
#ifdef BOOST_SIMD_HAS_AVX_SUPPORT

#include <boost/simd/toolbox/operator/functions/divides.hpp>
#include <boost/simd/include/functions/is_eqz.hpp>
#include <boost/simd/include/functions/logical_and.hpp>
#include <boost/simd/include/functions/if_allbits_else.hpp>
#include <boost/simd/include/constants/nan.hpp>
#include <boost/simd/sdk/config/compiler.hpp>

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::divides_, boost::simd::tag::avx_
                            , (A0)
                            , ((simd_<double_<A0>,boost::simd::tag::avx_>))
                              ((simd_<double_<A0>,boost::simd::tag::avx_>))
                            )
  {
    typedef A0 result_type;

    BOOST_SIMD_FUNCTOR_CALL_REPEAT(2)
    {
      A0 const that = { _mm256_div_pd(a0,a1) };
#if defined(BOOST_SIMD_COMPILER_GCC) && __GNUC__ <= 4 && __GNUC_MINOR__ <= 6 && __GNUC_PATCHLEVEL__ < 3
      // workaround for GCC bug #50396 fixed in 4.6.3
      return if_nan_else(logical_and(is_eqz(a0), is_eqz(a1)), that);
#else
      return that;
#endif
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::divides_, boost::simd::tag::avx_
                            , (A0)
                            , ((simd_<single_<A0>,boost::simd::tag::avx_>))
                              ((simd_<single_<A0>,boost::simd::tag::avx_>))
                            )
  {
    typedef A0 result_type;

    BOOST_SIMD_FUNCTOR_CALL_REPEAT(2)
    {
      A0 const that = { _mm256_div_ps(a0,a1) };
#if defined(BOOST_SIMD_COMPILER_GCC) && __GNUC__ <= 4 && __GNUC_MINOR__ <= 6 && __GNUC_PATCHLEVEL__ < 3
      // workaround for GCC bug #50396 fixed in 4.6.3
      return if_nan_else(logical_and(is_eqz(a0), is_eqz(a1)), that);
#else
      return that;
#endif
    }
  };

} } }

#endif
#endif
