//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef NT2_SDK_SIMD_DETAILS_IMPL_SSE_SSE2_IS_NOT_EQUAL_TO_HPP_INCLUDED
#define NT2_SDK_SIMD_DETAILS_IMPL_SSE_SSE2_IS_NOT_EQUAL_TO_HPP_INCLUDED

#include <nt2/sdk/meta/strip.hpp>
#include <nt2/sdk/meta/scalar_of.hpp>

namespace nt2 { namespace functors
{
  template<class Info>
  struct  call<is_not_equal_,tag::simd_(tag::arithmetic_,tag::sse_),double,Info>
        : callable
  {
    template<class Sig> struct result;
    template<class This,class A> struct result<This(A,A)> : meta::strip<A> {};

    NT2_FUNCTOR_CALL(2)
    {
      A0 that = { _mm_cmpneq_pd(a0,a1) };
      return that;
    }
  };

  template<class Info>
  struct  call<is_not_equal_,tag::simd_(tag::arithmetic_,tag::sse_),float,Info>
        : callable
  {
    template<class Sig> struct result;
    template<class This,class A> struct result<This(A,A)> : meta::strip<A> {};

    NT2_FUNCTOR_CALL(2)
    {
      A0 that = { _mm_cmpneq_ps(a0,a1) };
      return that;
    }
  };

  template<class Info>
  struct  call< is_not_equal_ , tag::simd_(tag::arithmetic_,tag::sse_)
              , integer_      , Info
              >
        : callable
  {
    template<class Sig> struct result;
    template<class This,class A> struct result<This(A,A)> : meta::strip<A> {};

    NT2_FUNCTOR_CALL(2)
    {
      return complement(eq(a0,a1));
    }
  };

  template<class Info>
  struct  call<is_not_equal_,tag::simd_(tag::arithmetic_,tag::sse_),int64_,Info>
        : callable
  {
    template<class Sig> struct result;
    template<class This,class A> struct result<This(A,A)> : meta::strip<A> {};

    NT2_FUNCTOR_CALL(2)
    {
      typedef typename meta::scalar_of<A0>::type stype;
      typedef typename meta::make_integer < 4, unsigned
                                            , simd::native< boost::mpl::_
                                                          , tag::sse_
                                                          >
                                            >::type type;
      type tmp      = { a0 - a1 };
           tmp      = neq(tmp,Zero<type>());
      type shuffled = { _mm_shuffle_epi32(tmp, _MM_SHUFFLE(2, 3, 0, 1)) };
      A0   that     = { tmp | shuffled };
      return that;
    }
  };
} }

#endif
