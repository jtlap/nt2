//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II         
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI         
//                                                                              
//          Distributed under the Boost Software License, Version 1.0.          
//                 See accompanying file LICENSE.txt or copy at                 
//                     http://www.boost.org/LICENSE_1_0.txt                     
//==============================================================================
#ifndef BOOST_SIMD_TOOLBOX_REDUCTION_FUNCTIONS_SIMD_SSE_SSE3_SUM_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_REDUCTION_FUNCTIONS_SIMD_SSE_SSE3_SUM_HPP_INCLUDED
#ifdef BOOST_SIMD_HAS_SSE3_SUPPORT

#include <boost/simd/toolbox/reduction/functions/sum.hpp>
#include <boost/simd/include/functions/simd/plus.hpp>
#include <boost/simd/include/constants/zero.hpp>
#include <boost/simd/sdk/meta/scalar_of.hpp>
#include <boost/fusion/algorithm/iteration/fold.hpp>

namespace boost { namespace simd { namespace ext
{
  /////////////////////////////////////////////////////////////////////////////
  // Implementation when type A0 is double
  /////////////////////////////////////////////////////////////////////////////
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION(boost::simd::tag::sum_, boost::simd::tag::sse3_,
                      (A0),
                      ((simd_<double_<A0>,boost::simd::tag::sse_>))
                     )
  {
      typedef typename meta::scalar_of<A0>::type                 result_type;
    
    BOOST_SIMD_FUNCTOR_CALL_REPEAT(1) {
      A0 b1 = _mm_hadd_pd (a0, Zero<A0>());
      double r;
      _mm_store_sd(&r, b1);
      return r;
    }
  };

  /////////////////////////////////////////////////////////////////////////////
  // Implementation when type A0 is float
  /////////////////////////////////////////////////////////////////////////////
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION(boost::simd::tag::sum_, boost::simd::tag::sse3_,
                      (A0),
                      ((simd_<single_<A0>,boost::simd::tag::sse_>))
                     )
  {
      typedef typename meta::scalar_of<A0>::type   result_type;
    
    BOOST_SIMD_FUNCTOR_CALL_REPEAT(1)
    {
      A0 b1 = _mm_hadd_ps (a0, Zero<A0>());
      b1 = _mm_hadd_ps (b1, Zero<A0>());
      float r;
      _mm_store_ss(&r, b1);
      return r;
    }
  };
} } }
#endif
#endif
