//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II         
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI         
//                                                                              
//          Distributed under the Boost Software License, Version 1.0.          
//                 See accompanying file LICENSE.txt or copy at                 
//                     http://www.boost.org/LICENSE_1_0.txt                     
//==============================================================================
#ifndef BOOST_SIMD_TOOLBOX_ARITHMETIC_FUNCTIONS_SIMD_SSE_AVX_ISQRT_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_ARITHMETIC_FUNCTIONS_SIMD_SSE_AVX_ISQRT_HPP_INCLUDED
#ifdef BOOST_SIMD_HAS_AVX_SUPPORT

#include <boost/simd/toolbox/arithmetic/functions/isqrt.hpp>

namespace boost { namespace simd { namespace ext
{
//   /////////////////////////////////////////////////////////////////////////////
//   // Implementation when type A0 is integer
//   /////////////////////////////////////////////////////////////////////////////
//   BOOST_SIMD_FUNCTOR_IMPLEMENTATION(boost::simd::tag::isqrt_, boost::simd::tag::avx_,
//                        (A0),
//                        ((simd_<integer_<A0>,boost::simd::tag::avx_>))
//                       )
//   {
//     typedef A0 result_type;
//     BOOST_SIMD_FUNCTOR_CALL_REPEAT(1)
//     {
//       typedef typename meta::scalar_of<A0>::type             sctype;
//       typedef simd::native<sctype, boost::simd::tag::sse_ >  svtype;
//       svtype a00 = { _mm256_extractf128_si256(a0, 0)};
//       svtype  r0 = isqrt(a00);
//       result_type that  = {_mm256_insertf128_si256(that, r0, 0)};
//       svtype a01 = { _mm256_extractf128_si256(a0, 1)};
//       svtype r1 = isqrt(a01);
//       that = _mm256_insertf128_si256(that, r1, 1);
//       return that; 
//     }
//   };

} } }
#endif
#endif
