//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef NT2_TOOLBOX_ARITHMETIC_FUNCTION_SIMD_SSE_AVX_ABS_HPP_INCLUDED
#define NT2_TOOLBOX_ARITHMETIC_FUNCTION_SIMD_SSE_AVX_ABS_HPP_INCLUDED

#include <nt2/sdk/constant/real.hpp>
#include <nt2/sdk/meta/strip.hpp>

#include <nt2/include/functions/details/simd/sse/sse4_1/abs.hpp>

namespace nt2 { namespace functors
{
  //  no special validate for abs


  /////////////////////////////////////////////////////////////////////////////
  // Implementation when type A0 is real_
  /////////////////////////////////////////////////////////////////////////////
  template<class Info>
  struct call<abs_,tag::simd_(tag::arithmetic_,tag::sse_),real_,Info> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0)> : meta::strip<A0>{};//

    NT2_FUNCTOR_CALL(1){ return b_notand(Mzero<A0>(),a0); }
  };


  /////////////////////////////////////////////////////////////////////////////
  // Implementation when type A0 is signed_
  /////////////////////////////////////////////////////////////////////////////
  template<class Info>
  struct call<abs_,tag::simd_(tag::arithmetic_,tag::sse_),signed_,Info> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0)> : meta::strip<A0>{};//

    NT2_FUNCTOR_CALL(1)
    {
      typedef typename meta::scalar_of<A0>::type sctype;		
      typedef typename simd::native<sctype, tag::sse_ >  svtype;	
      svtype a00 = { _mm256_extractf128_si256(a0, 0)};			
      svtype a01 = { _mm256_extractf128_si256(a0, 1)};			
      A0 that = { _mm256_insertf128_si256(that,nt2::abs(a00), 0)};		
      that =  _mm256_insertf128_si256(that,nt2::abs(a01), 1);
      //       NT2_AVX_JOIN128INT1(that, nt2::abs); 
      return that;
    }	
  };


  /////////////////////////////////////////////////////////////////////////////
  // Implementation when type A0 is unsigned_
  /////////////////////////////////////////////////////////////////////////////
  template<class Info>
  struct call<abs_,tag::simd_(tag::arithmetic_,tag::sse_),unsigned_,Info> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0)> : meta::strip<A0>{};//

    NT2_FUNCTOR_CALL(1){ return a0; }
  };

} }

#endif
/// Revised by jt the 15/11/2010
