//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II         
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI         
//                                                                              
//          Distributed under the Boost Software License, Version 1.0.          
//                 See accompanying file LICENSE.txt or copy at                 
//                     http://www.boost.org/LICENSE_1_0.txt                     
//==============================================================================
#ifndef BOOST_SIMD_TOOLBOX_REDUCTION_FUNCTION_SIMD_SSE_SSE3_SUM_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_REDUCTION_FUNCTION_SIMD_SSE_SSE3_SUM_HPP_INCLUDED
#include <boost/simd/include/constants/digits.hpp>
#include <boost/fusion/tuple.hpp>
#include <boost/fusion/include/fold.hpp>
#include <boost/simd/sdk/meta/strip.hpp>
/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is arithmetic_
/////////////////////////////////////////////////////////////////////////////
namespace boost { namespace simd { namespace meta
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION(tag::sum_, tag::cpu_,
                      (A0),
                      ((simd_<arithmetic_<A0>,tag::sse_>))
                     )
  {
      typedef typename meta::scalar_of<A0>::type                 base;
      typedef typename meta::result_of<meta::arithmetic(base)>::type  result_type;
    
    BOOST_SIMD_FUNCTOR_CALL_REPEAT(1)
    {
      return boost::fusion::fold(a0,0,functor<tag::plus_>());
    }
  };

/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is double
/////////////////////////////////////////////////////////////////////////////


  BOOST_SIMD_FUNCTOR_IMPLEMENTATION(tag::sum_, tag::cpu_,
                      (A0),
                      ((simd_<double_<A0>,tag::sse_>))
                     )
  {
      typedef typename meta::scalar_of<A0>::type                 result_type;
    
    BOOST_SIMD_FUNCTOR_CALL_REPEAT(1) {
      A0 b1 = {_mm_hadd_pd (a0, Zero<A0>())};
      double r;
      _mm_store_sd(&r, b1);
      return r;
    }
  };

/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is float
/////////////////////////////////////////////////////////////////////////////


  BOOST_SIMD_FUNCTOR_IMPLEMENTATION(tag::sum_, tag::cpu_,
                      (A0),
                      ((simd_<float_<A0>,tag::sse_>))
                     )
  {
      typedef typename meta::scalar_of<A0>::type   result_type;
    
    BOOST_SIMD_FUNCTOR_CALL_REPEAT(1)
    {
      A0 b1 = {_mm_hadd_ps (a0, Zero<A0>())};
      b1 = _mm_hadd_ps (b1, Zero<A0>());
      float r;
      _mm_store_ss(&r, b1);
      return r;
    }
  };
} } }
#endif
