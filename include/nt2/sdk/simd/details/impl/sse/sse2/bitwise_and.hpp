/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_SDK_SIMD_DETAILS_IMPL_SSE_SSE2_BITWISE_AND_HPP_INCLUDED
#define NT2_SDK_SIMD_DETAILS_IMPL_SSE_SSE2_BITWISE_AND_HPP_INCLUDED
#include <nt2/sdk/meta/size.hpp>

namespace nt2 { namespace functors
{
  //////////////////////////////////////////////////////////////////////////////
  // Bitwise operators requires same bits size
  //////////////////////////////////////////////////////////////////////////////
  template<class Info>
  struct validate<bitwise_and_,tag::simd_(tag::arithmetic_,tag::sse_),Info>
  {
    template<class Sig> struct result;
    template<class This,class A0,class A1>
      struct  result<This(A0,A1)> : meta::has_same_size < A0, A1 >{}; 
      //          : boost::mpl::bool_< sizeof(A0) == sizeof(A1) > {};
  };

  template<class Info,class C>
  struct call<bitwise_and_,tag::simd_(C,tag::sse_),Info>
  {
    template<class Sig> struct result;
    template<class This,class A0,class A1>
    struct result<This(A0,A1)> : meta::strip<A0> {};
    
    NT2_FUNCTOR_CALL_DISPATCH ( 2
                              , typename nt2::meta::scalar_of<A0>::type
                              , (3,(double,float,arithmetic_))
                              )

    NT2_FUNCTOR_CALL_EVAL_IF(2,double)
    {
      A0 that = { a1 };
      that    =  _mm_and_pd(a0, that);
      return that;
    }

    NT2_FUNCTOR_CALL_EVAL_IF(2,float )
    {
      A0 that = { a1 };
      that    =  _mm_and_ps(a0, that);
      return that;
    }

    NT2_FUNCTOR_CALL_EVAL_IF(2,arithmetic_)
    {
      A0 that = { a1 };
      that    =  _mm_and_si128(a0,that);
      return that;
    }
  };
} }

#endif
