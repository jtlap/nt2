/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_TOOLBOX_OPERATOR_FUNCTION_SIMD_COMMON_MAP_HPP_INCLUDED
#define NT2_TOOLBOX_OPERATOR_FUNCTION_SIMD_COMMON_MAP_HPP_INCLUDED

#include <nt2/sdk/simd/category.hpp>
#include <nt2/toolbox/operator/specific/details/maybe_genmask.hpp>
#include <nt2/include/functions/load.hpp>
#include <nt2/sdk/memory/aligned_type.hpp>

#if !defined(NT2_DONT_USE_PREPROCESSED_FILES)
#include <nt2/toolbox/operator/function/simd/common/preprocessed/map.hpp>
#else
#include <nt2/extension/parameters.hpp>
#include <nt2/sdk/functor/preprocessor/call.hpp>
#include <boost/preprocessor/tuple/elem.hpp>
#include <boost/preprocessor/repetition/enum.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/repetition/repeat_from_to.hpp>
#if defined(__WAVE__) && defined(NT2_CREATE_PREPROCESSED_FILES)
#pragma wave option(preserve: 2, line: 0, output: "preprocessed/map.hpp")
#endif

#define M0(z,n,t) ((simd_< unspecified_<A0>, X >))
#define M1(z,n,t) tag::simd_<tag::unspecified_, X>                                  
#define M2(z,n,t) typename meta::scalar_of<A##n>::type
#define M3(z,n,t) a##n[i]

#define M4(z,n,t)                                                            \
NT2_REGISTER_DISPATCH ( tag::map_, tag::cpu_, (Func)(A0)(X)                  \
                      , (unspecified_<Func>)BOOST_PP_REPEAT(n,M0,~)          \
                      )                                                      \
namespace nt2 { namespace ext                                                \
{                                                                            \
  template<class X, class Dummy>                                             \
  struct  call<tag::map_( tag::unspecified_                                  \
                        , BOOST_PP_ENUM(n,M1,~)                              \
                        )                                                    \
              , tag::cpu_, Dummy                                             \
              >                                                              \
    : callable                                                               \
  {                                                                          \
                                                                             \
    template<class Sig> struct result;                                       \
    template<class This,class Func,BOOST_PP_ENUM_PARAMS(n,class A)>          \
    struct result<This(Func, BOOST_PP_ENUM_PARAMS(n,A))>                     \
    {                                                                        \
      typedef typename meta::                                                \
      result_of< typename meta::                                             \
                 strip<Func>::type const( BOOST_PP_ENUM(n,M2,~) )            \
               >::type                                                       \
      rtype;                                                                 \
      typedef typename details::                                             \
      as_native< Func                                                        \
               , rtype                                                       \
               , typename meta::scalar_of<A0>::type                          \
               >::type                                                       \
      stype;                                                                 \
      typedef simd::native<stype, X> type;                                   \
    };                                                                       \
                                                                             \
    template<class Func, BOOST_PP_ENUM_PARAMS(n,class A)>                    \
    typename result<call(Func, BOOST_PP_ENUM_PARAMS(n, A))>::type            \
    operator()(Func const& f, BOOST_PP_ENUM_BINARY_PARAMS(n, A, const& a))   \
    {                                                                        \
      typedef typename result<call(Func, BOOST_PP_ENUM_PARAMS(n, A))>::type ntype;\
      typedef typename result<call(Func, BOOST_PP_ENUM_PARAMS(n, A))>::stype stype;\
                                                                             \
      NT2_ALIGNED_TYPE(stype) tmp[meta::cardinal_of<A0>::value];             \
                                                                             \
      for(int i = 0; i != meta::cardinal_of<A0>::value; ++i)                 \
        tmp[i] = details::maybe_genmask<stype>(f(BOOST_PP_ENUM(n, M3, ~)));  \
                                                                             \
      return load<ntype>(&tmp[0], 0);                                        \
    }                                                                        \
  };                                                                         \
} }                                                                          \
/**/

BOOST_PP_REPEAT_FROM_TO(1,BOOST_PP_INC(NT2_MAX_ARITY),M4,~)

#undef M4
#undef M3
#undef M2
#undef M1
#undef M0

#if defined(__WAVE__) && defined(NT2_CREATE_PREPROCESSED_FILES)
#pragma wave option(output: null)
#endif
#endif

#endif
