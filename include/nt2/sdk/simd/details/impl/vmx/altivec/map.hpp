/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_SDK_SIMD_DETAILS_IMPL_VMX_ALTIVEC__MAP_HPP_INCLUDED
#define NT2_SDK_SIMD_DETAILS_IMPL_VMX_ALTIVEC_MAP_HPP_INCLUDED

#include <nt2/sdk/meta/strip.hpp>
#include <nt2/extension/parameters.hpp>
#include <boost/preprocessor/tuple/elem.hpp>

#define NT2_MAP_INTERFACE(z,n,t)									\
template<class This,class F,class A>								\
struct result<This(F,NT2_PP_ENUM_VALUE(n,A))> : meta::strip<A> {};	\
NT2_FUNCTOR_CALL_DISPATCH( BOOST_PP_INC(n)							\
                         , typename nt2::meta::scalar_of<A1>::type	\
                         , (4,(float,int8_,int16_,int32_))  		\
                         )											\
/**/

#define NT2_MAP_ARGS(z,n,t) BOOST_PP_CAT(a,BOOST_PP_INC(n))[t] \
/**/

#define NT2_MAP_CALL(z,n,t) a0(BOOST_PP_ENUM(t, NT2_MAP_ARGS, n)) \
/**/

#define NT2_MAP_IMPL(z,n,t)                                           \
NT2_FUNCTOR_CALL_EVAL_IF(BOOST_PP_INC(n),BOOST_PP_TUPLE_ELEM(2,0,t))  \
{                                                                     \
  A1 that = {{ BOOST_PP_ENUM( BOOST_PP_TUPLE_ELEM(2,1,t)              \
                            , NT2_MAP_CALL                            \
                            , n                                       \
                            )                                         \
            }};                                                       \
  return that;                                                        \
}                                                                     \
/**/

namespace nt2 { namespace functors
{
  template<class Info>
  struct call<map_,tag::simd_(tag::arithmetic_,tag::altivec_),Info>
  {
    template<class Sig> struct result;
    BOOST_PP_REPEAT_FROM_TO(1,NT2_MAX_ARITY,NT2_MAP_INTERFACE,~)

    BOOST_PP_REPEAT_FROM_TO(1,NT2_MAX_ARITY,NT2_MAP_IMPL,(float ,4  )    )
    BOOST_PP_REPEAT_FROM_TO(1,NT2_MAX_ARITY,NT2_MAP_IMPL,(int32_,4  ) )
    BOOST_PP_REPEAT_FROM_TO(1,NT2_MAX_ARITY,NT2_MAP_IMPL,(int16_,8  ) )
    BOOST_PP_REPEAT_FROM_TO(1,NT2_MAX_ARITY,NT2_MAP_IMPL,(int8_ ,16 ) )
  };
} }

#undef NT2_MAP_INTERFACE
#undef NT2_MAP_ARGS
#undef NT2_MAP_CALL
#undef NT2_MAP_IMPL

#endif
