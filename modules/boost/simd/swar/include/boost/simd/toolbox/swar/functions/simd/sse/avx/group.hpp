//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II         
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI         
//                                                                              
//          Distributed under the Boost Software License, Version 1.0.          
//                 See accompanying file LICENSE.txt or copy at                 
//                     http://www.boost.org/LICENSE_1_0.txt                     
//==============================================================================
#ifndef BOOST_SIMD_TOOLBOX_SWAR_FUNCTIONS_SIMD_SSE_AVX_GROUP_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_SWAR_FUNCTIONS_SIMD_SSE_AVX_GROUP_HPP_INCLUDED
#ifdef BOOST_SIMD_HAS_AVX_SUPPORT

#include <boost/simd/toolbox/swar/functions/group.hpp>
#include <boost/simd/sdk/simd/native_cast.hpp>
#include <boost/simd/sdk/meta/scalar_of.hpp>
#include <boost/dispatch/meta/downgrade.hpp>

namespace boost { namespace simd { namespace ext
{
  /////////////////////////////////////////////////////////////////////////////
  // Implementation when type A0 is double
  /////////////////////////////////////////////////////////////////////////////
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION(boost::simd::tag::group_, boost::simd::tag::avx_,
                        (A0),
                        ((simd_<double_<A0>,boost::simd::tag::avx_>))
                        ((simd_<double_<A0>,boost::simd::tag::avx_>))
                       )
  {
    typedef typename dispatch::meta::downgrade<A0>::type result_type;
    
    BOOST_SIMD_FUNCTOR_CALL_REPEAT(2)
    {
      typedef result_type rtype;
      typedef simd::native<float,boost::simd::tag::sse_ >   htype;
      htype r0 = {_mm256_cvtpd_ps(a0)};
      htype r1 = {_mm256_cvtpd_ps(a1)};
      rtype r  = {_mm256_insertf128_ps(r, r0, 0)};
      r = _mm256_insertf128_ps(r, r1, 1);
      return r;
    }
  };

/////////////////////////////////////////////////////////////////////////////
  // Implementation when type A0 is ints32
  /////////////////////////////////////////////////////////////////////////////
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION(boost::simd::tag::group_, boost::simd::tag::avx_,
                        (A0),
                        ((simd_<ints32_<A0>,boost::simd::tag::avx_>))
                        ((simd_<ints32_<A0>,boost::simd::tag::avx_>))
                       )
  {
    typedef typename dispatch::meta::downgrade<A0>::type result_type;
    
    BOOST_SIMD_FUNCTOR_CALL_REPEAT(2)
    {
      typedef result_type rtype;
      //     typedef typename meta::same<A0,boost::simd::tag::sse_>::type htype;
      typedef simd::native<typename meta::scalar_of<A0>::type,boost::simd::tag::sse_ >   htype;
      typedef simd::native<typename meta::scalar_of<rtype>::type,boost::simd::tag::sse_ >   type;
      //      typedef typename meta::same<rtype,boost::simd::tag::sse_>::type type;
      htype a00 = {_mm256_extractf128_si256(a0, 0)};
      htype a01 = {_mm256_extractf128_si256(a0, 1)};
      type v0 = {_mm_packs_epi32(a00, a01)};
      //     std::cout  << "v0 "<< v0 << std::endl;
      htype a10 = {_mm256_extractf128_si256(a1, 0)};
      htype a11 = {_mm256_extractf128_si256(a1, 1)};
      type v1 = {_mm_packs_epi32(a10, a11)};
      //      std::cout  << "v1 "<< v1 << std::endl;
      rtype r = {_mm256_insertf128_si256(r, v0, 0)};
      r = simd::native_cast<rtype>(_mm256_insertf128_si256(r, v1, 1));
      return r;
    }
  };

  /////////////////////////////////////////////////////////////////////////////
  // Implementation when type A0 is ints16_
  /////////////////////////////////////////////////////////////////////////////
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION(boost::simd::tag::group_, boost::simd::tag::avx_,
                        (A0),
                        ((simd_<ints16_<A0>,boost::simd::tag::avx_>))
                        ((simd_<ints16_<A0>,boost::simd::tag::avx_>))
                       )
  {
    typedef typename dispatch::meta::downgrade<A0>::type result_type;
    
    BOOST_SIMD_FUNCTOR_CALL_REPEAT(2)
    {
      typedef result_type rtype;
      //     typedef typename meta::same<A0,boost::simd::tag::sse_>::type htype;
      typedef simd::native<typename meta::scalar_of<A0>::type,boost::simd::tag::sse_ >   htype;
      typedef simd::native<typename meta::scalar_of<rtype>::type,boost::simd::tag::sse_ >   type;
      //      typedef typename meta::same<rtype,boost::simd::tag::sse_>::type type;
      htype a00 = {_mm256_extractf128_si256(a0, 0)};
      htype a01 = {_mm256_extractf128_si256(a0, 1)};
      type v0   = {_mm_packs_epi16(a00, a01)};
      htype a10 = {_mm256_extractf128_si256(a1, 0)};
      htype a11 = {_mm256_extractf128_si256(a1, 1)};
      type v1   = {_mm_packs_epi16(a10, a11)};
      rtype r   = {_mm256_insertf128_si256(r, v0, 0)};
      r = simd::native_cast<rtype>(_mm256_insertf128_si256(r, v1, 1));
      return r;
    }
  };
} } }
#endif
#endif
