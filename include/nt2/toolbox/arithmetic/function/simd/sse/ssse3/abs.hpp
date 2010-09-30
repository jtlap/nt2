//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef NT2_TOOLBOX_ARITHMETIC_FUNCTION_SIMD_SSE_SSSE3_ABS_HPP_INCLUDED
#define NT2_TOOLBOX_ARITHMETIC_FUNCTION_SIMD_SSE_SSSE3_ABS_HPP_INCLUDED
#include <nt2/sdk/constant/real.hpp>
#include <nt2/sdk/meta/strip.hpp>

#include <nt2/include/functions/select.hpp>
#include <nt2/include/functions/is_lez.hpp>
#include <nt2/include/functions/bitwise_notand.hpp>

namespace nt2 { namespace functors
{
  //  no special validate for abs

  template<class Extension,class Info>
  struct call<abs_,tag::simd_(tag::arithmetic_,Extension),Info>
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0)> : meta::strip<A0>{};

    NT2_FUNCTOR_CALL_DISPATCH(
      1,
      typename nt2::meta::scalar_of<A0>::type,
      (6, (real_,int64_t,int32_t,int16_t,int8_t,unsigned_))
    )

    NT2_FUNCTOR_CALL_EVAL_IF(1,real_)     { return b_notand(Mzero<A0>(),a0);   }
    NT2_FUNCTOR_CALL_EVAL_IF(1,int64_t)   { return select(is_lez(a0),neg(a0),a0); }
    NT2_FUNCTOR_CALL_EVAL_IF(1,int32_t)   { A0 that = {_mm_abs_epi32(a0)};return that;}
    NT2_FUNCTOR_CALL_EVAL_IF(1,int16_t)   { A0 that = {_mm_abs_epi16(a0)};return that;}
    NT2_FUNCTOR_CALL_EVAL_IF(1,int8_t)    { A0 that = {_mm_abs_epi8(a0) };return that;}
    NT2_FUNCTOR_CALL_EVAL_IF(1,unsigned_) { return a0;                           }
  };
} }

#endif
