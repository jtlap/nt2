//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef NT2_TOOLBOX_SWAR_FUNCTION_SIMD_SSE_AVX_GROUP_HPP_INCLUDED
#define NT2_TOOLBOX_SWAR_FUNCTION_SIMD_SSE_AVX_GROUP_HPP_INCLUDED
#include <nt2/sdk/meta/templatize.hpp>
#include <nt2/sdk/meta/downgrade.hpp>
#include <nt2/sdk/meta/strip.hpp>


namespace nt2 { namespace functors
{
  //  no special validate for group

  template<class Extension,class Info>
  struct call<group_,tag::simd_(tag::arithmetic_,Extension),Info>
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0, A0)>
    {
      typedef typename meta::scalar_of<A0>::type                                      stype;
      typedef typename meta::downgrade<stype>::type                          utype;
      typedef simd::native<utype,simd::avx_>                                          type1;
      typedef simd::native<typename meta::float_<A0>::type,simd::avx_>                type2;
      typedef typename boost::mpl::if_c < boost::is_same<stype,double>::value
                                        , type2
                                        , type1
                                        >::type type;
    };

    NT2_FUNCTOR_CALL_DISPATCH(
      2,
      typename nt2::meta::scalar_of<A0>::type,
      (7, (int16_t,uint16_t,int32_t,uint32_t,int64_t,uint64_t,double))
    )

    NT2_FUNCTOR_CALL_EVAL_IF(2,       double)
    {
      typedef typename NT2_CALL_RETURN_TYPE(2)::type rtype;
      typedef simd::native<float,tag::sse_ >   htype;
      htype r0 = {_mm256_cvtpd_ps(a0)};
      htype r1 = {_mm256_cvtpd_ps(a1)};
      rtype r  = {_mm256_insertf128_ps(r, r0, 0)};
      r = _mm256_insertf128_ps(r, r1, 1);
      return r; 
    }
    NT2_FUNCTOR_CALL_EVAL_IF(2,       int16_t)
    {
      typedef typename NT2_CALL_RETURN_TYPE(2)::type rtype;
      //     typedef typename meta::same<A0,tag::sse_>::type htype;
      typedef simd::native<typename meta::scalar_of<A0>::type,tag::sse_ >   htype;
      typedef simd::native<typename meta::scalar_of<rtype>::type,tag::sse_ >   type;
      //      typedef typename meta::same<rtype,tag::sse_>::type type;
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
     NT2_FUNCTOR_CALL_EVAL_IF(2,       uint16_t)
    {
      typedef typename NT2_CALL_RETURN_TYPE(2)::type rtype;
      //     typedef typename meta::same<A0,tag::sse_>::type htype;
      typedef simd::native<typename meta::scalar_of<A0>::type,tag::sse_ >   htype;
      typedef simd::native<typename meta::scalar_of<rtype>::type,tag::sse_ >   type;
      //      typedef typename meta::same<rtype,tag::sse_>::type type;
      htype a00 = {_mm256_extractf128_si256(a0, 0)}; 
      htype a01 = {_mm256_extractf128_si256(a0, 1)};
      type v0   = {_mm_packus_epi16(a00, a01)}; 
      htype a10 = {_mm256_extractf128_si256(a1, 0)}; 
      htype a11 = {_mm256_extractf128_si256(a1, 1)};
      type v1   = {_mm_packus_epi16(a10, a11)}; 
      rtype r   = {_mm256_insertf128_si256(r, v0, 0)};
      r = simd::native_cast<rtype>(_mm256_insertf128_si256(r, v1, 1)); 
      return r; 
    }
    NT2_FUNCTOR_CALL_EVAL_IF(2,       int32_t)
    {
      typedef typename NT2_CALL_RETURN_TYPE(2)::type rtype;
      //     typedef typename meta::same<A0,tag::sse_>::type htype;
      typedef simd::native<typename meta::scalar_of<A0>::type,tag::sse_ >   htype;
      typedef simd::native<typename meta::scalar_of<rtype>::type,tag::sse_ >   type;
      //      typedef typename meta::same<rtype,tag::sse_>::type type;
      htype a00 = {_mm256_extractf128_si256(a0, 0)}; 
      htype a01 = {_mm256_extractf128_si256(a0, 1)};
      type v0 = {_mm_packs_epi32(a00, a01)}; 
      std::cout  << "v0 "<< v0 << std::endl; 
      htype a10 = {_mm256_extractf128_si256(a1, 0)}; 
      htype a11 = {_mm256_extractf128_si256(a1, 1)};
      type v1 = {_mm_packs_epi32(a10, a11)}; 
      std::cout  << "v1 "<< v1 << std::endl; 
      rtype r = {_mm256_insertf128_si256(r, v0, 0)};
      r = simd::native_cast<rtype>(_mm256_insertf128_si256(r, v1, 1)); 
      return r; 
    }
    NT2_FUNCTOR_CALL_EVAL_IF(2,       uint32_t)
    {
      typedef typename NT2_CALL_RETURN_TYPE(2)::type rtype;
      //     typedef typename meta::same<A0,tag::sse_>::type htype;
      typedef simd::native<typename meta::scalar_of<A0>::type,tag::sse_ >   htype;
      typedef simd::native<typename meta::scalar_of<rtype>::type,tag::sse_ >   type;
      //      typedef typename meta::same<rtype,tag::sse_>::type type;
      htype a00 = {_mm256_extractf128_si256(a0, 0)}; 
      htype a01 = {_mm256_extractf128_si256(a0, 1)};
      type v0 = {_mm_packus_epi32(a00, a01)}; 
      std::cout  << "v0 "<< v0 << std::endl; 
      htype a10 = {_mm256_extractf128_si256(a1, 0)}; 
      htype a11 = {_mm256_extractf128_si256(a1, 1)};
      type v1 = {_mm_packus_epi32(a10, a11)}; 
      std::cout  << "v1 "<< v1 << std::endl; 
      rtype r = {_mm256_insertf128_si256(r, v0, 0)};
      r = simd::native_cast<rtype>(_mm256_insertf128_si256(r, v1, 1)); 
      return r; 
    }
//     NT2_FUNCTOR_CALL_EVAL_IF(2,       int64_t)
//     {
//       typedef typename NT2_CALL_RETURN_TYPE(2)::type rtype;
//       //     typedef typename meta::same<A0,tag::sse_>::type htype;
//       typedef simd::native<typename meta::scalar_of<A0>::type,tag::sse_ >   htype;
//       typedef simd::native<double,simd::avx_ >   ftype;
//       typedef simd::native<typename meta::scalar_of<rtype>::type,tag::sse_ >   type;
//       //      typedef typename meta::same<rtype,tag::sse_>::type type;
//       __m256i control = _mm256_set_epi32(0, 4, 1, 5, 2, 6, 3, 7); 
//       rtype r = {_mm256_castps_si256(_mm256_permute2f128_ps(_mm256_castsi256_ps(a0),
// 						     _mm256_castsi256_ps(a1),
// 						     control))}; 
//       return r; 
//     }
    
  };
} }

#endif
