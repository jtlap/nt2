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
#include <boost/simd/include/functions/none.hpp>
#include <boost/simd/include/functions/logical_or.hpp>
#include <boost/simd/include/constants/nan.hpp>

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
#ifdef BOOST_SIMD_COMPILER_GCC
      //================================================================
      // this is a workaround for a possible gcc over-optimisation
      // that produce zero/zero -> zero instead of nan
      if (logical_or(none(a0), none(a1))) return Nan<result_type>();
      //================================================================
#endif
      A0 const that = { _mm_div_pd(a0,a1) };
      return that;
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
#ifdef BOOST_SIMD_COMPILER_GCC
      //================================================================
      // this is a workaround for a possible gcc over-optimisation
      // that produce zero/zero -> zero instead of nan
      if  (logical_or(none(a0), none(a1))) return Nan<result_type>();
      //================================================================
#endif
      A0 const that = { _mm_div_ps(a0,a1) };
      return that;
    }
  };
} } }

#endif
#endif
