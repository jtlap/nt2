//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II         
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI         
//                                                                              
//          Distributed under the Boost Software License, Version 1.0.          
//                 See accompanying file LICENSE.txt or copy at                 
//                     http://www.boost.org/LICENSE_1_0.txt                     
//==============================================================================
#ifndef BOOST_SIMD_TOOLBOX_OPERATOR_FUNCTIONS_SIMD_SSE_SSE2_DIVIDES_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_OPERATOR_FUNCTIONS_SIMD_SSE_SSE2_DIVIDES_HPP_INCLUDED
#ifdef BOOST_SIMD_HAS_SSE2_SUPPORT
#include <boost/simd/toolbox/operator/functions/divides.hpp>
#include <boost/simd/sdk/config/compiler.hpp>
#include <boost/simd/include/functions/is_eqz.hpp>
#include <boost/simd/include/functions/logical_and.hpp>
#include <boost/simd/include/constants/nan.hpp>
#include <boost/simd/include/functions/if_nan_else.hpp>

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::divides_, boost::simd::tag::sse2_
                            , (A0)
                            , ((simd_<double_<A0>,boost::simd::tag::sse_>))
                              ((simd_<double_<A0>,boost::simd::tag::sse_>))
                            )
  {
    typedef A0 result_type;
    BOOST_SIMD_FUNCTOR_CALL_REPEAT(2)
    {
      A0 const that = { _mm_div_pd(a0,a1) };
#ifdef BOOST_SIMD_COMPILER_GCC
      //================================================================
      // this is a workaround for a possible gcc over-optimisation
      // that produce zero/zero -> zero instead of nan
      return if_nan_else(logical_and(is_eqz(a0), is_eqz(a1)), that);
      //================================================================
#else
      return that;
#endif
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::divides_, boost::simd::tag::sse2_
                            , (A0)
                            , ((simd_<single_<A0>,boost::simd::tag::sse_>))
                              ((simd_<single_<A0>,boost::simd::tag::sse_>))
                            )
  {
    typedef A0 result_type;
    BOOST_SIMD_FUNCTOR_CALL_REPEAT(2)
    {
      A0 const that = { _mm_div_ps(a0,a1) };
#ifdef BOOST_SIMD_COMPILER_GCC
      //================================================================
      // this is a workaround for a possible gcc over-optimisation
      // that produce zero/zero -> zero instead of nan
      if_nan_else(logical_and(is_eqz(a0), is_eqz(a1)), that);
      //================================================================
#else
      A0 const that = { _mm_div_ps(a0,a1) };
#endif
      return that;
    }
  };
} } }

#endif
#endif
