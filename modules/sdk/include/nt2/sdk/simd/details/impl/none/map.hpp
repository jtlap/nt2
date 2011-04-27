/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_SDK_SIMD_DETAILS_IMPL_NONE_MAP_HPP_INCLUDED
#define NT2_SDK_SIMD_DETAILS_IMPL_NONE_MAP_HPP_INCLUDED

#include <nt2/sdk/simd/category.hpp>
#include <nt2/sdk/functor/preprocessor/call.hpp>

#define M0(z,n,t) ((simd_< unspecified_<A0>, tag::none_>))
#define M1(z,n,t) tag::simd_<tag::unspecified_, tag::none_>                                  
#define M2(z,n,t) typename meta::scalar_of<A##n>::type

#define M3(z,n,t)                                                         \
NT2_REGISTER_DISPATCH ( tag::map_, tag::cpu_, (Func)(A0)                  \
                      , (unspecified_<Func>)BOOST_PP_REPEAT(n,M0,~)       \
                      )                                                   \
namespace nt2 { namespace ext                                             \
{                                                                         \
  template<class Dummy>                                                   \
  struct  call<tag::map_( tag::unspecified_                               \
                        , BOOST_PP_ENUM(n,M1,~)                           \
                        )                                                 \
              , tag::cpu_, Dummy                                          \
              >                                                           \
    : callable                                                            \
  {                                                                       \
    template<class Sig> struct result;                                    \
    template<class This,class Func,BOOST_PP_ENUM_PARAMS(n,class A)>       \
    struct result<This(Func, BOOST_PP_ENUM_PARAMS(n,A))>                  \
    {                                                                     \
      typedef simd::                                                      \
      native< typename std::tr1::                                         \
              result_of< typename meta::                                  \
                         strip<Func>::type const( BOOST_PP_ENUM(n,M2,~) ) \
                       >::type                                            \
            , tag::none_                                                  \
            > type;                                                       \
    };                                                                    \
                                                                          \
    template<class Func, BOOST_PP_ENUM_PARAMS(n,class A)>                 \
    typename result<call(Func, BOOST_PP_ENUM_PARAMS(n, A))>::type         \
    operator()(Func const& f, BOOST_PP_ENUM_BINARY_PARAMS(n, A, const& a))\
    {                                                                     \
      typename result<call(Func, BOOST_PP_ENUM_PARAMS(n, A))>::type that = {\
        f(BOOST_PP_ENUM_BINARY_PARAMS(n, a, () BOOST_PP_INTERCEPT))       \
      };                                                                  \
      return that;                                                        \
    }                                                                     \
  };                                                                      \
} }                                                                       \
/**/

BOOST_PP_REPEAT_FROM_TO(1,BOOST_PP_INC(NT2_MAX_ARITY),M3,~)

#undef M3
#undef M2
#undef M1
#undef M0

#endif
