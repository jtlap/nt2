//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef NT2_TOOLBOX_SWAR_FUNCTION_SIMD_SSE_SSE2_SORT_HPP_INCLUDED
#define NT2_TOOLBOX_SWAR_FUNCTION_SIMD_SSE_SSE2_SORT_HPP_INCLUDED
#include <nt2/sdk/meta/as_real.hpp>
#include <nt2/sdk/meta/strip.hpp>

#include <nt2/include/functions/minimum.hpp>
#include <nt2/include/functions/maximum.hpp>

namespace nt2 { namespace functors
{
  //  no special validate for sort


  /////////////////////////////////////////////////////////////////////////////
  // Implementation when type A0 is types32_
  /////////////////////////////////////////////////////////////////////////////
  template<class Info>
  struct call<sort_,tag::simd_(tag::arithmetic_,tag::sse_),types32_,Info> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0)>
      : meta::strip<A0>{};//

    NT2_FUNCTOR_CALL(1)
    {
      typedef typename meta::as_real<A0>::type flt;
      A0 a =  {a0};  
      A0 b =  {NT2_CAST(A0, _mm_movehl_ps(NT2_CAST(flt, a0), NT2_CAST(flt, a0)))};
      comp(a, b); 
      a = NT2_CAST(A0, _mm_movelh_ps(NT2_CAST(flt, a), NT2_CAST(flt, b)));
      b = NT2_CAST(A0, _mm_shuffle_ps(NT2_CAST(flt, a), NT2_CAST(flt, b), NT2_SH(1, 3, 1, 3))); 
      comp(a, b); 
      A0 c = {NT2_CAST(A0, _mm_movelh_ps(NT2_CAST(flt, b), NT2_CAST(flt, b)))};
      A0 d = {a};
      comp(c, d); 
      a = NT2_CAST(A0, _mm_shuffle_ps(NT2_CAST(flt, c), NT2_CAST(flt, a), NT2_SH(3, 2, 0, 0)));
      b = NT2_CAST(A0, _mm_movehl_ps(NT2_CAST(flt, b), NT2_CAST(flt, d)));
      b = NT2_CAST(A0, _mm_shuffle_ps(NT2_CAST(flt, a), NT2_CAST(flt, b), NT2_SH(3, 1, 0, 2))); 
      return b; 
    }
  };


  /////////////////////////////////////////////////////////////////////////////
  // Implementation when type A0 is types64_
  /////////////////////////////////////////////////////////////////////////////
  template<class Info>
  struct call<sort_,tag::simd_(tag::arithmetic_,tag::sse_),types64_,Info> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0)>
      : meta::strip<A0>{};//

    NT2_FUNCTOR_CALL(1)
    {
      A0 that = {minimum(a0), maximum(a0)};
      return that; 
    }
  };

} }

#endif
/// Revised by jt the 15/11/2010
