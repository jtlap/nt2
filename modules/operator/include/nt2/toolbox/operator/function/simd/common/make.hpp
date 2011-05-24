/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_TOOLBOX_OPERATOR_FUNCTION_SIMD_COMMON_MAKE_HPP_INCLUDED
#define NT2_TOOLBOX_OPERATOR_FUNCTION_SIMD_COMMON_MAKE_HPP_INCLUDED

////////////////////////////////////////////////////////////////////////////////
// make for SIMD types
////////////////////////////////////////////////////////////////////////////////
#include <nt2/sdk/meta/as.hpp>
#include <nt2/sdk/simd/category.hpp>
#include <nt2/sdk/functor/preprocessor/call.hpp>
#include <nt2/sdk/memory/aligned_type.hpp>
#include <nt2/include/functions/load.hpp>

#define M1(z,n,t) (fundamental_<A0>)
#define M0(n)                                                                              \
NT2_REGISTER_DISPATCH ( tag::make_, tag::cpu_, (A0)(A1)(X)                                 \
                      , BOOST_PP_REPEAT(n, M1, ~)                                          \
                       ((target_< simd_< arithmetic_<A1>, X> >))                           \
                      )                                                                    \
                                                                                           \
namespace nt2 { namespace ext                                                              \
{                                                                                          \
  template<class X, class Dummy>                                                           \
  struct  call< tag::make_ ( BOOST_PP_ENUM_PARAMS(n, tag::fundamental_ BOOST_PP_INTERCEPT) \
                           , tag::target_<tag::simd_<tag::arithmetic_, X> >                \
                           )                                                               \
              , tag::cpu_                                                                  \
              , Dummy                                                                      \
              >                                                                            \
        : callable                                                                         \
  {                                                                                        \
    template<class Sig> struct result;                                                     \
    template<class This, BOOST_PP_ENUM_PARAMS(n, class A), class Target>                   \
    struct result<This(BOOST_PP_ENUM_PARAMS(n, A), Target)> : meta::strip<Target>::type {};\
                                                                                           \
    NT2_FUNCTOR_CALL(BOOST_PP_INC(n))                                                      \
    {                                                                                      \
      ignore_unused(BOOST_PP_CAT(a, n));                                                   \
      typedef typename NT2_RETURN_TYPE(BOOST_PP_INC(n))::type type;                        \
      typedef typename meta::scalar_of<type>::type stype;                                  \
      NT2_ALIGNED_TYPE(stype) tmp[n] = {                                                   \
        BOOST_PP_ENUM_PARAMS(n, a)                                                         \
      };                                                                                   \
      return load(&tmp[0], 0);                                                             \
    }                                                                                      \
  };                                                                                       \
} }

  M0( 1)
  M0( 2)
  M0( 4)
  M0( 8)
  M0(16)
  M0(32)
#if NT2_MAX_ARITY >= 64
  M0(64)
#endif

#endif
