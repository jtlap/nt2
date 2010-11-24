/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_SDK_SIMD_DETAILS_IMPL_SSE_SSE2_SPLAT_HPP_INCLUDED
#define NT2_SDK_SIMD_DETAILS_IMPL_SSE_SSE2_SPLAT_HPP_INCLUDED

#include <nt2/sdk/simd/category.hpp>
#include <nt2/sdk/meta/scalar_of.hpp>
#include <nt2/sdk/functor/preprocessor/call.hpp>

namespace nt2 { namespace functors
{
  template<class T, class Info>
  struct  call< splat_<T> , tag::simd_(tag::arithmetic_,tag::sse_)
              , double    , Info
              >
        : callable
  {
    typedef T result_type;

    NT2_FUNCTOR_CALL(1)  { T that = { _mm_set1_pd(a0)    };  return that;  }
  };

  template<class T, class Info>
  struct  call< splat_<T> , tag::simd_(tag::arithmetic_,tag::sse_)
              , float     , Info
              >
        : callable
  {
    typedef T result_type;

    NT2_FUNCTOR_CALL(1)   { T that = { _mm_set1_ps(a0)    };  return that;  }
  };

  template<class T, class Info>
  struct  call< splat_<T> , tag::simd_(tag::arithmetic_,tag::sse_)
              , int8_     , Info
              >
        : callable
  {
    typedef T result_type;

    NT2_FUNCTOR_CALL(1)   { T that = { _mm_set1_epi8(a0)  };  return that;  }
  };

  template<class T, class Info>
  struct  call< splat_<T> , tag::simd_(tag::arithmetic_,tag::sse_)
              , int16_    , Info
              >
        : callable
  {
    typedef T result_type;

    NT2_FUNCTOR_CALL(1)  { T that = { _mm_set1_epi16(a0) };  return that;  }
  };

  template<class T, class Info>
  struct  call< splat_<T> , tag::simd_(tag::arithmetic_,tag::sse_)
              , int32_    , Info
              >
        : callable
  {
    typedef T result_type;

    NT2_FUNCTOR_CALL(1)  { T that = { _mm_set1_epi32(a0) };  return that;  }
  };

  template<class T, class Info>
  struct  call< splat_<T> , tag::simd_(tag::arithmetic_,tag::sse_)
              , int64_    , Info
              >
        : callable
  {
    typedef T result_type;

    NT2_FUNCTOR_CALL(1)  { T that = {{ a0, a0 }};  return that;  }
  };
} }

#endif
