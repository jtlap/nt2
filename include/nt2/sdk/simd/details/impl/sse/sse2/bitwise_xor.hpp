/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_SDK_SIMD_DETAILS_IMPL_SSE_SSE2_BITWISE_XOR_HPP_INCLUDED
#define NT2_SDK_SIMD_DETAILS_IMPL_SSE_SSE2_BITWISE_XOR_HPP_INCLUDED

namespace nt2 { namespace functors
{
  //////////////////////////////////////////////////////////////////////////////
  // Bitwise operators requires same bits size
  //////////////////////////////////////////////////////////////////////////////
  template<class Info>
  struct validate<bitwise_xor_,tag::simd_(tag::arithmetic_,tag::sse_),Info>
  {
    template<class Sig> struct result;
    template<class This,class A0,class A1>
    struct  result<This(A0,A1)>
          : boost::mpl::bool_< sizeof(A0) == sizeof(A1) > {};
  };
  template<class Info>
  struct  call<bitwise_xor_,tag::simd_(tag::arithmetic_,tag::sse_),double,Info>
        : callable
  {
    template<class Sig> struct result;
    template<class This,class A0,class A1>
    struct result<This(A0,A1)> : meta::strip<A0> {};

    NT2_FUNCTOR_CALL(2)
    {
      A0 that = simd::native_cast<A0>( a1 );
      that    =  _mm_xor_pd(a0, that);
      return that;
    }
  };

  template<class Info>
  struct  call<bitwise_xor_,tag::simd_(tag::arithmetic_,tag::sse_),float,Info>
        : callable
  {
    template<class Sig> struct result;
    template<class This,class A0,class A1>
    struct result<This(A0,A1)> : meta::strip<A0> {};

    NT2_FUNCTOR_CALL(2)
    {
      A0 that = simd::native_cast<A0>( a1 );
      that    =  _mm_xor_ps(a0, that);
      return that;
    }
  };

  template<class Info>
  struct  call< bitwise_xor_, tag::simd_(tag::arithmetic_,tag::sse_)
              , arithmetic_ , Info
              >
        : callable
  {
    template<class Sig> struct result;
    template<class This,class A0,class A1>
    struct result<This(A0,A1)> : meta::strip<A0> {};

    NT2_FUNCTOR_CALL(2)
    {
      A0 that = simd::native_cast<A0>( a1 );
      that    =  _mm_xor_si128(a0,that);
      return that;
    }
  };
} }

#endif
