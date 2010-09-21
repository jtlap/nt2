//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef NT2_TOOLBOX_BITWISE_FUNCTION_SIMD_SSE_AVX_BITWISE_NOTAND_HPP_INCLUDED
#define NT2_TOOLBOX_BITWISE_FUNCTION_SIMD_SSE_AVX_BITWISE_NOTAND_HPP_INCLUDED
#include <nt2/sdk/meta/strip.hpp>

#include <nt2/include/functions/details/simd/sse/sse4_1/bitwise_notand.hpp>

namespace nt2 { namespace functors
{
  //  no special validate for bitwise_notand

  template<class Extension,class Info>
  struct call<bitwise_notand_,tag::simd_(tag::arithmetic_,Extension),Info>
  {
    template<class Sig> struct result;
    template<class This,class A0, class A1>
    struct result<This(A0, A1)> : meta::strip<A0>{};//

    NT2_FUNCTOR_CALL_DISPATCH(
      2,
      typename nt2::meta::scalar_of<A0>::type,
      (3, (double,float,arithmetic_))
    )
    NT2_FUNCTOR_CALL_EVAL_IF(2,double)
    {
      A0 that;
      that = a1;
      that =  _mm256_andnot_pd(a0, that);
      return that;
    }
    NT2_FUNCTOR_CALL_EVAL_IF(2,float ) 
    {
      A0 that;
      that = a1; 
      that = _mm256_andnot_ps(a0,that);
      return that;
    }
    NT2_FUNCTOR_CALL_EVAL_IF(2,arithmetic_)
    {
      typedef typename meta::double_<A0>::type dtype; 
      return simd::native_cast<A0>(b_notand(simd::native_cast<simd::native<dtype, simd::avx_> >(a0),
					 simd::native_cast<simd::native<dtype, simd::avx_> >(a1))); 
    }

  };
} }

#endif