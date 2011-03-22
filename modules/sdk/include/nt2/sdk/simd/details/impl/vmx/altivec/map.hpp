/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_SDK_SIMD_DETAILS_IMPL_VMX_ALTIVEC_MAP_HPP_INCLUDED
#define NT2_SDK_SIMD_DETAILS_IMPL_VMX_ALTIVEC_MAP_HPP_INCLUDED

#include <nt2/sdk/simd/category.hpp>
#include <nt2/extension/parameters.hpp>
#include <boost/preprocessor/tuple/elem.hpp>
#include <boost/preprocessor/repetition/enum.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/repetition/repeat_from_to.hpp>

////////////////////////////////////////////////////////////////////////////////
// Implement a SIMD map that apply a given function to any Altivec vector types
// This is done by enumerating all cases of function calls over the different
// vector cardinal and function arity.
////////////////////////////////////////////////////////////////////////////////
#define M4(z,n,t) BOOST_PP_CAT(a,BOOST_PP_INC(n))[t]
#define M3(z,n,t) (typename A1::value_type)(a0(BOOST_PP_ENUM(t,M4,n)))
#define M2(z,n,t) ((simd_< BOOST_PP_TUPLE_ELEM(2,0,t) <A0>,tag::altivec_>))
#define M1(z,n,t) tag::simd_<tag::BOOST_PP_TUPLE_ELEM(2,0,t),tag::altivec_>

#define M0(z,n,t)                                                       \
NT2_REGISTER_DISPATCH ( tag::map_,tag::cpu_                             \
                      , (Func)(A0)                                      \
                      , (unspecified_<Func>)BOOST_PP_REPEAT(n,M2,t)     \
                      )                                                 \
namespace nt2 { namespace ext                                           \
{                                                                       \
  template<class Dummy>                                                 \
  struct call < tag::map_(tag::unspecified_,BOOST_PP_ENUM(n,M1,t))      \
              , tag::cpu_ , Dummy> : callable                           \
  {                                                                     \
    template<class Sig> struct result;                                  \
    template<class This,class F,class A>                                \
    struct result<This(F,NT2_PP_ENUM_VALUE(n,A))> : meta::strip<A> {};  \
    NT2_FUNCTOR_CALL(BOOST_PP_INC(n))                                   \
    {                                                                   \
      A1 that = {{BOOST_PP_ENUM(BOOST_PP_TUPLE_ELEM(2,1,t),M3,n)}};     \
      return that;                                                      \
    }                                                                   \
  };                                                                    \
} }                                                                     \
/**/

#define NT2_SIMD_MAP_CALL(T,C)                      \
BOOST_PP_REPEAT_FROM_TO(1,NT2_MAX_ARITY,M0, (T,C) ) \
/**/

NT2_SIMD_MAP_CALL(float_  ,  4 )
NT2_SIMD_MAP_CALL(ints32_ ,  4 )
NT2_SIMD_MAP_CALL(ints16_ ,  8 )
NT2_SIMD_MAP_CALL(ints8_  , 16 )

#undef NT2_SIMD_MAP_CALL
#undef MN64
#undef M64
#undef M4
#undef M3
#undef M2
#undef M1
#undef M0

#endif
