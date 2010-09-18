/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_SDK_SIMD_NATIVE_DETAILS_IMPL_VMX_ALTIVEC_MULTIPLIES_HPP_INCLUDED
#define NT2_SDK_SIMD_NATIVE_DETAILS_IMPL_VMX_ALTIVEC_MULTIPLIES_HPP_INCLUDED

#include <nt2/sdk/meta/strip.hpp>
#include <nt2/sdk/meta/scalar_of.hpp>

namespace nt2 { namespace functors
{
  template<class Info>
  struct call<multiplies_,tag::simd_(tag::arithmetic_,tag::altivec_),Info>
  {
    template<class Sig> struct result;
    template<class This,class A>
    struct result<This(A,A)> : meta::strip<A> {};

    NT2_FUNCTOR_CALL_DISPATCH ( 2
                              , typename nt2::meta::scalar_of<A0>::type
                              , (5, ( float, int32_t, uint32_t, types16_, types8_ ) )
                              )

    NT2_FUNCTOR_CALL_EVAL_IF(2,float )
    {
      A0 that = { vec_madd(a0,a1,vec_xor(a0,a0)) };
      return that;
    }

    NT2_FUNCTOR_CALL_EVAL_IF(2,types16_ )
    {
      A0 that = { vec_mladd(a0,a1,vec_xor(a0,a0)); };
      return that;
    }

    NT2_FUNCTOR_CALL_EVAL_IF(2,types8_ )
    {
      A0 l = { vec_mule(a0,a1); }; // replace A0 by upgrade<A0>
      A0 r = { vec_mulo(a0,a1); };
      A0 that  = { vec_mergel(vec_pack(l,l),vec_pack(r,r)) };
      return that;
    }

    NT2_FUNCTOR_CALL_EVAL_IF(2,int32_t )
    {
/*
      static inline type_t Multiply( const type_t& a, const type_t& b, const ttt::boxed<2>&, const true_t&  )
      {
        typedef __vu32_4 cast_t;
        type_t r  = type_t( av_multiply<__vu32_4>::Multiply(cast_t(a),cast_t(b), ttt::boxed<2>(), false_t()) );
        return vec_sel(r,vec_sub(vec_splat_u32(0), r),vec_cmpgt(vec_splat_u32(0), vec_xor(a, b)));
      }  
      */
    }

    NT2_FUNCTOR_CALL_EVAL_IF(2,uint32_t )
    {

/*
      static inline type_t Multiply( const type_t& a, const type_t& b, const ttt::boxed<2>&, const false_t&  )
      {
        typedef __vu16_8 short_t;
        type_t sixteen = type_t(vec_vspltisw (-16));
        type_t low = vec_mulo (short_t(a),short_t(b));										
        type_t high = vec_msum (short_t(a),short_t(vec_rl(b, sixteen)),vec_splat_u32(0));
        return vec_add(vec_sl(high, sixteen),low);
      }  

*/
    }
  };
} }

#endif


