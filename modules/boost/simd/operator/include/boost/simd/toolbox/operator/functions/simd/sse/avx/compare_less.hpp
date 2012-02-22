//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II         
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI         
//                                                                              
//          Distributed under the Boost Software License, Version 1.0.          
//                 See accompanying file LICENSE.txt or copy at                 
//                     http://www.boost.org/LICENSE_1_0.txt                     
//==============================================================================
#ifndef BOOST_SIMD_TOOLBOX_OPERATOR_FUNCTIONS_SIMD_SSE_AVX_COMPARE_LESS_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_OPERATOR_FUNCTIONS_SIMD_SSE_AVX_COMPARE_LESS_HPP_INCLUDED
#ifdef BOOST_SIMD_HAS_AVX_SUPPORT

#include <boost/simd/toolbox/operator/functions/compare_less.hpp>
#include <boost/simd/include/constants/true.hpp>
#include <boost/simd/include/constants/false.hpp>
#include <boost/simd/include/functions/is_less.hpp>
#include <boost/simd/include/functions/is_greater.hpp>
#include <boost/simd/include/functions/reversebits.hpp>
#include <boost/simd/toolbox/operator/functions/simd/common/details/compare_less_helper.hpp>
#include <boost/simd/sdk/simd/logical.hpp>
#include <boost/dispatch/meta/scalar_of.hpp>

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::compare_less_, boost::simd::tag::avx_
                            , (A0)
                            , ((simd_<double_<A0>,boost::simd::tag::avx_>))
                              ((simd_<double_<A0>,boost::simd::tag::avx_>))
                            )
  {
    typedef typename meta::scalar_of<A0>::type  sA0; 
    typedef typename meta::as_logical<sA0>::type result_type;
    BOOST_SIMD_FUNCTOR_CALL_REPEAT(2)
    {
      unsigned int mask_a_lt_b =  _mm256_movemask_pd(lt(a0,a1));
      unsigned int mask_a_gt_b =  _mm256_movemask_pd(gt(a0,a1));
      return result_type(boost::simd::details::compare_less_helper(mask_a_lt_b,mask_a_gt_b));
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::compare_less_, boost::simd::tag::avx_
                            , (A0)
                            , ((simd_<single_<A0>,boost::simd::tag::avx_>))
                              ((simd_<single_<A0>,boost::simd::tag::avx_>))
                            )
  {
    typedef typename meta::scalar_of<A0>::type  sA0; 
    typedef typename meta::as_logical<sA0>::type result_type;
    BOOST_SIMD_FUNCTOR_CALL_REPEAT(2)
    {
      unsigned int mask_a_lt_b =  _mm256_movemask_ps(lt(a0,a1));
      unsigned int mask_a_gt_b =  _mm256_movemask_ps(gt(a0,a1));
      return result_type(boost::simd::details::compare_less_helper(mask_a_lt_b,mask_a_gt_b));
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::compare_less_, boost::simd::tag::avx_
                            , (A0)
                            , ((simd_<integer_<A0>,boost::simd::tag::avx_>))
                              ((simd_<integer_<A0>,boost::simd::tag::avx_>))
                            )
  {
    typedef typename meta::scalar_of<A0>::type  sA0; 
    typedef typename meta::as_logical<sA0>::type result_type;
    BOOST_SIMD_FUNCTOR_CALL_REPEAT(2)
    {
      typedef typename dispatch::meta::scalar_of<A0>::type      stype;
      typedef native < stype,  boost::simd::tag::sse_>          htype;
      htype a00 = {_mm256_extractf128_si256(a0, 0)}; 
      htype a10 = {_mm256_extractf128_si256(a1, 0)};
      if (compare_less(a00, a10))
      {
        return True<result_type>();
      } 
      else if (compare_equal(a00, a10))
      {
        htype a01 = {_mm256_extractf128_si256(a0, 1)};  
        htype a11 = {_mm256_extractf128_si256(a1, 1)}; 
        return  compare_less(a01, a11);
      }
      else
      {
        return False<result_type>(); 
      }
    }
  };
} } }

#endif
#endif
