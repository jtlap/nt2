//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II         
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI         
//                                                                              
//          Distributed under the Boost Software License, Version 1.0.          
//                 See accompanying file LICENSE.txt or copy at                 
//                     http://www.boost.org/LICENSE_1_0.txt                     
//==============================================================================
#ifndef BOOST_SIMD_TOOLBOX_BITWISE_FUNCTIONS_SIMD_SSE_AVX_SHRAI_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_BITWISE_FUNCTIONS_SIMD_SSE_AVX_SHRAI_HPP_INCLUDED
#ifdef BOOST_SIMD_HAS_AVX_SUPPORT

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::shrai_, boost::simd::tag::avx_
                            , (A0)(A1)
                            , ((simd_<signed_<A0>,boost::simd::tag::avx_>))
                              (scalar_< integer_<A1> >)
                            )
  {
    typedef A0 result_type; 
    BOOST_SIMD_FUNCTOR_CALL(2)
    {
      typedef typename meta::scalar_of<A0>::type             sctype;
      typedef simd::native<sctype, boost::simd::tag::sse_ >  svtype;
      svtype a00 = { _mm256_extractf128_si256(a0, 0)};
      svtype a01 = { _mm256_extractf128_si256(a0, 1)};
      A0 that= { _mm256_insertf128_si256(that,boost::simd::shrai( a00, a1), 0)};
         that =  _mm256_insertf128_si256(that, boost::simd::shrai(a01, a1), 1);
      return that;
     }
  };
  
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::shrai_, boost::simd::tag::avx_
                            , (A0)(A1)
                            , ((simd_<unsigned_<A0>,boost::simd::tag::avx_>))
                              (scalar_< integer_<A1> >)
                            )
  {
    typedef A0 result_type; 
    BOOST_SIMD_FUNCTOR_CALL(2)
    {
      typedef typename meta::scalar_of<A0>::type             sctype;
      typedef simd::native<sctype, boost::simd::tag::sse_ >  svtype;
      svtype a00 = { _mm256_extractf128_si256(a0, 0)};
      svtype a01 = { _mm256_extractf128_si256(a0, 1)};
      A0 that= { _mm256_insertf128_si256(that,boost::simd::shrai( a00, a1), 0)};
         that =  _mm256_insertf128_si256(that, boost::simd::shrai(a01, a1), 1);
      return that;
     }
  };  
} } }

#endif
#endif
