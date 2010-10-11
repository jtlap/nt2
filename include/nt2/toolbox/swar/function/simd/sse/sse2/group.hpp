//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef NT2_TOOLBOX_SWAR_FUNCTION_SIMD_SSE_SSE2_GROUP_HPP_INCLUDED
#define NT2_TOOLBOX_SWAR_FUNCTION_SIMD_SSE_SSE2_GROUP_HPP_INCLUDED
#include <nt2/sdk/meta/templatize.hpp>
#include <nt2/sdk/meta/downgrade.hpp>
#include <nt2/sdk/meta/as_integer.hpp>
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
      typedef simd::native<utype,tag::sse_>                                          type1;
      typedef simd::native<typename meta::float_<A0>::type,tag::sse_>                type2;
      typedef typename boost::mpl::if_c < boost::is_same<stype,double>::value
                                        , type2
                                        , type1
                                        >::type type;
    };

    NT2_FUNCTOR_CALL_DISPATCH(
      2,
      typename nt2::meta::scalar_of<A0>::type,
      (7, (int16_t, uint16_t,int32_t, uint32_t,int64_, float, double))
    )

    NT2_FUNCTOR_CALL_EVAL_IF(2,       double)
    {
      typedef typename NT2_CALL_RETURN_TYPE(2)::type rtype;
      typedef typename meta::as_integer<rtype>::type itype;
      rtype r = simd::native_cast<rtype>(_mm_slli_si128(simd::native_cast<itype >(_mm_cvtpd_ps(a1)), 8));
      return b_or(r, simd::native_cast<rtype>(_mm_cvtpd_ps(a0)));
    }
#define NT2_SH(a, b, c, d) (_MM_SHUFFLE(d, c, b, a))
      NT2_FUNCTOR_CALL_EVAL_IF(2,       int64_)
    {
      typedef typename NT2_CALL_RETURN_TYPE(2)::type rtype;
      rtype b = {_mm_slli_si128(simd::native_cast<rtype>(a1),4)};// works only for int64 that are int32 representable
      b = b_or(b, a0);
      return simd::native_cast<rtype>(_mm_shuffle_epi32(b, NT2_SH(0, 2, 1, 3)));
    }
#undef NT2_SH

    NT2_FUNCTOR_CALL_EVAL_IF(2,       int32_t)
    {
      typedef typename NT2_CALL_RETURN_TYPE(2)::type rtype;
      return simd::native_cast<rtype>(_mm_packs_epi32(a0, a1));
    }
    NT2_FUNCTOR_CALL_EVAL_IF(2,       uint32_t)
    {
      typedef typename NT2_CALL_RETURN_TYPE(2)::type rtype;
      return simd::native_cast<rtype>(_mm_packs_epi32(a0, a1)); //_mm_packus_epi32 pas existe avant sse4.1
    }
    NT2_FUNCTOR_CALL_EVAL_IF(2,       int16_t)
    {
      typedef typename NT2_CALL_RETURN_TYPE(2)::type rtype;
      return simd::native_cast<rtype>(_mm_packs_epi16(a0, a1));
    }
    NT2_FUNCTOR_CALL_EVAL_IF(2,       uint16_t)
    {
      typedef typename NT2_CALL_RETURN_TYPE(2)::type rtype;
      return simd::native_cast<rtype>(_mm_packus_epi16(a0, a1));
    }
//     NT2_FUNCTOR_CALL_EVAL_IF(2,       int8_t)
//     {
//       typedef typename NT2_CALL_RETURN_TYPE(2)::type rtype;
//       return simd::native_cast<rtype>(_mm_packs_epi8(a0, a1));
//     }
//     NT2_FUNCTOR_CALL_EVAL_IF(2,       uint8_t)
//     {
//       typedef typename NT2_CALL_RETURN_TYPE(2)::type rtype;
//       return simd::native_cast<rtype>(_mm_packus_epi8(a0, a1));
//     }


  };
} }

#endif
