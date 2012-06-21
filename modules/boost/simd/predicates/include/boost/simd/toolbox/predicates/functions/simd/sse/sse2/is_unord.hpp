//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II         
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI         
//                                                                              
//          Distributed under the Boost Software License, Version 1.0.          
//                 See accompanying file LICENSE.txt or copy at                 
//                     http://www.boost.org/LICENSE_1_0.txt                     
//==============================================================================
#ifndef BOOST_SIMD_TOOLBOX_PREDICATES_FUNCTIONS_SIMD_SSE_SSE2_IS_UNORD_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_PREDICATES_FUNCTIONS_SIMD_SSE_SSE2_IS_UNORD_HPP_INCLUDED
#ifdef BOOST_SIMD_HAS_SSE2_SUPPORT
#include <boost/simd/toolbox/predicates/functions/is_unord.hpp>
#include <boost/simd/sdk/simd/logical.hpp>
#include <boost/simd/include/constants/false.hpp>

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::is_unord_, boost::simd::tag::sse2_, (A0)
                            , ((simd_<arithmetic_<A0>,boost::simd::tag::sse_>))
                              ((simd_<arithmetic_<A0>,boost::simd::tag::sse_>))
                            )
  {
    typedef typename meta::as_logical<A0>::type result_type;
    inline result_type operator()(const A0&, const A0&)const
    {
      return boost::simd::False<A0>();
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::is_unord_, boost::simd::tag::sse2_,(A0)
                            , ((simd_<double_<A0>,boost::simd::tag::sse_>))
                              ((simd_<double_<A0>,boost::simd::tag::sse_>))
                            )
  {
    typedef typename meta::as_logical<A0>::type result_type;

    BOOST_SIMD_FUNCTOR_CALL_REPEAT(2)
    {
      result_type that = _mm_cmpunord_pd(a0,a1);
      return that;
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::is_unord_, boost::simd::tag::sse2_, (A0)
                            , ((simd_<single_<A0>,boost::simd::tag::sse_>))
                              ((simd_<single_<A0>,boost::simd::tag::sse_>))
                            )
  {
    typedef typename meta::as_logical<A0>::type result_type;

    BOOST_SIMD_FUNCTOR_CALL_REPEAT(2)
    {
      result_type that = _mm_cmpunord_ps(a0,a1);
      return that;
    }
  };
} } }

#endif
#endif
