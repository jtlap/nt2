//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II         
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI         
//                                                                              
//          Distributed under the Boost Software License, Version 1.0.          
//                 See accompanying file LICENSE.txt or copy at                 
//                     http://www.boost.org/LICENSE_1_0.txt                     
//==============================================================================
#ifndef BOOST_SIMD_TOOLBOX_OPERATOR_FUNCTIONS_SIMD_SSE_SSE2_COMPARE_EQUAL_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_OPERATOR_FUNCTIONS_SIMD_SSE_SSE2_COMPARE_EQUAL_HPP_INCLUDED
#ifdef BOOST_SIMD_HAS_SSE2_SUPPORT
#include <boost/simd/include/functions/is_equal.hpp>
#include <boost/simd/toolbox/boolean/as_logical.hpp>
#include <boost/dispatch/meta/scalar_of.hpp>

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::compare_equal_, boost::simd::tag::sse2_
                            , (A0)
                            , ((simd_<double_<A0>,boost::simd::tag::sse_>))
                              ((simd_<double_<A0>,boost::simd::tag::sse_>))
                            )
  {
    typedef typename meta::scalar_of<A0>::type  sA0; 
    typedef typename meta::as_logical<sA0>::type result_type;
    BOOST_SIMD_FUNCTOR_CALL_REPEAT(2) { return _mm_movemask_pd(eq(a0,a1)) == 0X03; }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::compare_equal_, boost::simd::tag::sse2_
                            , (A0)
                            , ((simd_<single_<A0>,boost::simd::tag::sse_>))
                              ((simd_<single_<A0>,boost::simd::tag::sse_>))
                            )
  {
    typedef typename meta::scalar_of<A0>::type  sA0; 
    typedef typename meta::as_logical<sA0>::type result_type;
    BOOST_SIMD_FUNCTOR_CALL_REPEAT(2) { return _mm_movemask_ps(eq(a0,a1)) == 0X0F; }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::compare_equal_, boost::simd::tag::sse2_
                            , (A0)
                            , ((simd_<integer_<A0>,boost::simd::tag::sse_>))
                              ((simd_<integer_<A0>,boost::simd::tag::sse_>))
                            )
  {
    typedef typename meta::scalar_of<A0>::type  sA0; 
    typedef typename meta::as_logical<sA0>::type result_type;
    BOOST_SIMD_FUNCTOR_CALL_REPEAT(2)
    {
      return _mm_movemask_epi8(eq(a0,a1)) == 0X0FFFF;
    }
  };
} } }

#endif
#endif
