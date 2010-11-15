//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef NT2_TOOLBOX_BITWISE_FUNCTION_SIMD_SSE_AVX_SHRAI_HPP_INCLUDED
#define NT2_TOOLBOX_BITWISE_FUNCTION_SIMD_SSE_AVX_SHRAI_HPP_INCLUDED

#include <nt2/sdk/meta/strip.hpp>

#include <nt2/include/functions/details/simd/sse/sse4_1/shrai.hpp>

namespace nt2 { namespace functors
{
  //  no special validate for shrai


  /////////////////////////////////////////////////////////////////////////////
  // Implementation when type  is fundamental_
  /////////////////////////////////////////////////////////////////////////////
  template<class Info>
  struct  call<shrai_,tag::simd_(tag::arithmetic_),fundamental_,Info> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0, class A1>
    struct result<This(A0,A1)> : meta::strip<A0>{};//

    NT2_FUNCTOR_CALL(2)
    {
      typedef typename meta::scalar_of<A0>::type sctype;			
      typedef typename simd::native<sctype, tag::sse_ >  svtype;		
      svtype a00 = { _mm256_extractf128_si256(a0, 0)};			
      svtype a01 = { _mm256_extractf128_si256(a0, 1)};			
      A0 that = { _mm256_insertf128_si256(that,nt2::shrai( a00, a1), 0)};	
      that =  _mm256_insertf128_si256(that, nt2::shrai(a01, a1), 1); 		
      return that; 
     }

  };
} }

#endif
/// Revised by jt the 15/11/2010
