//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II         
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI         
//                                                                              
//          Distributed under the Boost Software License, Version 1.0.          
//                 See accompanying file LICENSE.txt or copy at                 
//                     http://www.boost.org/LICENSE_1_0.txt                     
//==============================================================================
#ifndef BOOST_SIMD_TOOLBOX_ARITHMETIC_FUNCTIONS_SIMD_SSE_AVX_MAX_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_ARITHMETIC_FUNCTIONS_SIMD_SSE_AVX_MAX_HPP_INCLUDED
#ifdef BOOST_SIMD_HAS_AVX_SUPPORT
#include <boost/dispatch/meta/strip.hpp>
#include <boost/simd/include/functions/seladd.hpp>
#include <boost/simd/include/functions/details/simd/sse/sse4_1/max.hpp>
/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is uint8_t
/////////////////////////////////////////////////////////////////////////////
namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION(boost::simd::tag::max_, boost::simd::tag::avx_,
                      (A0),
                      ((simd_<uint8_<A0>,boost::simd::tag::avx_>))
                      ((simd_<uint8_<A0>,boost::simd::tag::avx_>))
                     )
  {
    typedef A0 result_type;
    BOOST_SIMD_FUNCTOR_CALL_REPEAT(2)
    {
      BOOST_SIMD_AVX_JOIN128INT(that, _mm_max_epu8); return that;
    }
  };

/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is arithmetic_
/////////////////////////////////////////////////////////////////////////////


  BOOST_SIMD_FUNCTOR_IMPLEMENTATION(boost::simd::tag::max_, boost::simd::tag::avx_,
                      (A0),
                      ((simd_<arithmetic_<A0>,boost::simd::tag::avx_>))
                      ((simd_<arithmetic_<A0>,boost::simd::tag::avx_>))
                     )
  {
    typedef A0 result_type;
    BOOST_SIMD_FUNCTOR_CALL_REPEAT(2)
    {
       return seladd( is_lt(a0,a1),a0,a1-a0);
    }
  };

/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is double
/////////////////////////////////////////////////////////////////////////////


  BOOST_SIMD_FUNCTOR_IMPLEMENTATION(boost::simd::tag::max_, boost::simd::tag::avx_,
                      (A0),
                      ((simd_<double_<A0>,boost::simd::tag::avx_>))
                      ((simd_<double_<A0>,boost::simd::tag::avx_>))
                     )
  {
    typedef A0 result_type;
    BOOST_SIMD_FUNCTOR_CALL_REPEAT(2)
    {
      A0 that =  {_mm256_max_pd(a0,a1)}; return that;
    }
  };

/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is int32_t
/////////////////////////////////////////////////////////////////////////////


  BOOST_SIMD_FUNCTOR_IMPLEMENTATION(boost::simd::tag::max_, boost::simd::tag::avx_,
                      (A0),
                      ((simd_<int32_<A0>,boost::simd::tag::avx_>))
                      ((simd_<int32_<A0>,boost::simd::tag::avx_>))
                     )
  {
    typedef A0 result_type;
    BOOST_SIMD_FUNCTOR_CALL_REPEAT(2)
    {
      BOOST_SIMD_AVX_JOIN128INT(that, _mm_max_epi32); return that;
    }
  };

/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is float
/////////////////////////////////////////////////////////////////////////////


  BOOST_SIMD_FUNCTOR_IMPLEMENTATION(boost::simd::tag::max_, boost::simd::tag::avx_,
                      (A0),
                      ((simd_<float_<A0>,boost::simd::tag::avx_>))
                      ((simd_<float_<A0>,boost::simd::tag::avx_>))
                     )
  {
    typedef A0 result_type;
    BOOST_SIMD_FUNCTOR_CALL_REPEAT(2)
    {
      A0 that =  {_mm256_max_ps(a0,a1)}; return that;
    }
  };

/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is int8_t
/////////////////////////////////////////////////////////////////////////////


  BOOST_SIMD_FUNCTOR_IMPLEMENTATION(boost::simd::tag::max_, boost::simd::tag::avx_,
                      (A0),
                      ((simd_<int8_<A0>,boost::simd::tag::avx_>))
                      ((simd_<int8_<A0>,boost::simd::tag::avx_>))
                     )
  {
    typedef A0 result_type;
    BOOST_SIMD_FUNCTOR_CALL_REPEAT(2)
    {
      BOOST_SIMD_AVX_JOIN128INT(that, _mm_max_epi8); return that;
    }
  };

/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is int16_t
/////////////////////////////////////////////////////////////////////////////


  BOOST_SIMD_FUNCTOR_IMPLEMENTATION(boost::simd::tag::max_, boost::simd::tag::avx_,
                      (A0),
                      ((simd_<int16_<A0>,boost::simd::tag::avx_>))
                      ((simd_<int16_<A0>,boost::simd::tag::avx_>))
                     )
  {
    typedef A0 result_type;
    BOOST_SIMD_FUNCTOR_CALL_REPEAT(2)
    {
      BOOST_SIMD_AVX_JOIN128INT(that, _mm_max_epi16); return that;
    }
  };

/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is uint32_t
/////////////////////////////////////////////////////////////////////////////


  BOOST_SIMD_FUNCTOR_IMPLEMENTATION(boost::simd::tag::max_, boost::simd::tag::avx_,
                      (A0),
                      ((simd_<uint32_<A0>,boost::simd::tag::avx_>))
                      ((simd_<uint32_<A0>,boost::simd::tag::avx_>))
                     )
  {
    typedef A0 result_type;
    BOOST_SIMD_FUNCTOR_CALL_REPEAT(2)
    {
      BOOST_SIMD_AVX_JOIN128INT(that, _mm_max_epu32); return that;
    }
  };

/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is uint16_t
/////////////////////////////////////////////////////////////////////////////


  BOOST_SIMD_FUNCTOR_IMPLEMENTATION(boost::simd::tag::max_, boost::simd::tag::avx_,
                      (A0),
                      ((simd_<uint16_<A0>,boost::simd::tag::avx_>))
                      ((simd_<uint16_<A0>,boost::simd::tag::avx_>))
                     )
  {
    typedef A0 result_type;
    BOOST_SIMD_FUNCTOR_CALL_REPEAT(2)
    {
      BOOST_SIMD_AVX_JOIN128INT(that, _mm_max_epu16); return that;
    }
  };
} } }
#endif
#endif
