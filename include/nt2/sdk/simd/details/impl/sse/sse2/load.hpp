/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_SDK_SIMD_DETAILS_IMPL_SSE_SSE2_LOAD_HPP_INCLUDED
#define NT2_SDK_SIMD_DETAILS_IMPL_SSE_SSE2_LOAD_HPP_INCLUDED

#include <nt2/sdk/simd/category.hpp>
#include <nt2/sdk/meta/scalar_of.hpp>
#include <nt2/sdk/meta/cardinal_of.hpp>
#include <nt2/sdk/functor/preprocessor/call.hpp>

namespace nt2 { namespace functors
{
  //////////////////////////////////////////////////////////////////////////////
  // load with no offset
  //////////////////////////////////////////////////////////////////////////////
  template<class T,class Info>
  struct  call< load_<T,0>  , tag::simd_(tag::arithmetic_,tag::sse_)
              , double      , Info
              >
        : callable
  {
    typedef T result_type;

    NT2_FUNCTOR_CALL(2)
    {
      T that = { _mm_load_pd(a0+a1*meta::cardinal_of<T>::value) };
      return that;
    }
  };

  template<class T,class Info>
  struct  call< load_<T,0>  , tag::simd_(tag::arithmetic_,tag::sse_)
              , float       , Info
              >
        : callable
  {
    typedef T result_type;

    NT2_FUNCTOR_CALL(2)
    {
      T that = { _mm_load_ps(a0+a1*meta::cardinal_of<T>::value) };
      return that;
    }
  };

  template<class T,class Info>
  struct  call< load_<T,0>  , tag::simd_(tag::arithmetic_,tag::sse_)
              , integer_    , Info
              >
        : callable
  {
    typedef T result_type;

    NT2_FUNCTOR_CALL(2)
    {
      T that = { _mm_load_si128(reinterpret_cast<__m128i const*>(a0)+a1) };
      return that;
    }
  };
} }

#include <nt2/sdk/simd/details/impl/sse/sse2/load_offset.hpp>

#endif
