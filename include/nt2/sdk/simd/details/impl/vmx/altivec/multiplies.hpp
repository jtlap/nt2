//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef NT2_SDK_SIMD_DETAILS_IMPL_VMX_ALTIVEC_MULTIPLIES_HPP_INCLUDED
#define NT2_SDK_SIMD_DETAILS_IMPL_VMX_ALTIVEC_MULTIPLIES_HPP_INCLUDED

#include <nt2/sdk/meta/strip.hpp>
#include <nt2/sdk/meta/scalar_of.hpp>

////////////////////////////////////////////////////////////////////////////////
// Overload registration
////////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH ( tag::multiplies_, tag::cpu_, (A0)
                      , ((simd_<float_<A0>,tag::altivec_>))
                        ((simd_<float_<A0>,tag::altivec_>))
                      );

////////////////////////////////////////////////////////////////////////////////
// Overloads implementation
////////////////////////////////////////////////////////////////////////////////
namespace nt2 { namespace ext
{
  template<class Dummy>
  struct  call< tag::multiplies_( tag::simd_<tag::float_,tag::altivec_>
                                , tag::simd_<tag::float_,tag::altivec_>
                                )
              , tag::cpu_, Dummy
              >
        : callable
  {
    template<class Sig>           struct result;
    template<class This,class A0>
    struct result<This(A0,A0)> : meta::strip<A0> {};

    NT2_FUNCTOR_CALL(2)
    {
      A0 that = { vec_madd(a0(),a1(),Zero<A0>()()) };
      return that;
    }
  };
} }

////////////////////////////////////////////////////////////////////////////////
// Overload registration
////////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH ( tag::multiplies_, tag::cpu_, (A0)
                      , ((simd_<type16_<A0>,tag::altivec_>))
                        ((simd_<type16_<A0>,tag::altivec_>))
                      );

////////////////////////////////////////////////////////////////////////////////
// Overloads implementation
////////////////////////////////////////////////////////////////////////////////
namespace nt2 { namespace ext
{
  template<class Dummy>
  struct  call< tag::multiplies_( tag::simd_<tag::type16_,tag::altivec_>
                                , tag::simd_<tag::type16_,tag::altivec_>
                                )
              , tag::cpu_, Dummy
              >
        : callable
  {
    template<class Sig>           struct result;
    template<class This,class A0>
    struct result<This(A0,A0)> : meta::strip<A0> {};

    NT2_FUNCTOR_CALL(2)
    {
      A0 that = { vec_mladd(a0(),a1(),Zero<A0>()()) };
      return that;
    }
  };
} }

/*
    NT2_FUNCTOR_CALL_EVAL_IF(2,type8_ )
    {
      A0 l = { vec_mule(a0,a1); }; // replace A0 by upgrade<A0>
      A0 r = { vec_mulo(a0,a1); };
      A0 that  = { vec_mergel(vec_pack(l,l),vec_pack(r,r)) };
      return that;
    }

    NT2_FUNCTOR_CALL_EVAL_IF(2,int32_t )
    {
      static inline type_t Multiply( const type_t& a, const type_t& b, const ttt::boxed<2>&, const true_t&  )
      {
        typedef __vu32_4 cast_t;
        type_t r  = type_t( av_multiply<__vu32_4>::Multiply(cast_t(a),cast_t(b), ttt::boxed<2>(), false_t()) );
        return vec_sel(r,vec_sub(vec_splat_u32(0), r),vec_cmpgt(vec_splat_u32(0), vec_xor(a, b)));
      }
    }

    NT2_FUNCTOR_CALL_EVAL_IF(2,uint32_t )
    {

      static inline type_t Multiply( const type_t& a, const type_t& b, const ttt::boxed<2>&, const false_t&  )
      {
        typedef __vu16_8 short_t;
        type_t sixteen = type_t(vec_vspltisw (-16));
        type_t low = vec_mulo (short_t(a),short_t(b));
        type_t high = vec_msum (short_t(a),short_t(vec_rl(b, sixteen)),vec_splat_u32(0));
        return vec_add(vec_sl(high, sixteen),low);
      }

*/

#endif


