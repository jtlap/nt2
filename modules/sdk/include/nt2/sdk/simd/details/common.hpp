/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_SDK_SIMD_DETAILS_COMMON_HPP_INCLUDED
#define NT2_SDK_SIMD_DETAILS_COMMON_HPP_INCLUDED

////////////////////////////////////////////////////////////////////////////////
// By default, any SIMD implementation falls down to scalar map application if
// nothing is implemented for doing otherwise.
////////////////////////////////////////////////////////////////////////////////
#include <nt2/sdk/simd/category.hpp>
#include <nt2/extension/parameters.hpp>
#include <nt2/sdk/details/preprocessor.hpp>
#include <boost/preprocessor/repetition/enum.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/repetition/repeat_from_to.hpp>

////////////////////////////////////////////////////////////////////////////////
// Register all tag and extension agnostic call for common code sharing
////////////////////////////////////////////////////////////////////////////////
#define M0(z,n,t) ((simd_< unspecified_<A0>, X >))

#define M1(z,n,t)                                     \
NT2_REGISTER_DISPATCH ( Tag , tag::cpu_, (A0)(Tag)(X) \
                      , BOOST_PP_REPEAT(n,M0,~)       \
                      )                               \
/**/

BOOST_PP_REPEAT_FROM_TO(1,BOOST_PP_INC(NT2_MAX_ARITY),M1,~)

#undef M0
#undef M1

////////////////////////////////////////////////////////////////////////////////
// Generate all the common map calls over Tag using nt2::map
////////////////////////////////////////////////////////////////////////////////
#define M0(z,n,t) tag::simd_<tag::unspecified_,X>

#define M1(z,n,t)                                                         \
namespace nt2 { namespace ext                                             \
{                                                                         \
  template<class Tag, class X, class Dummy>                               \
  struct  call<Tag( BOOST_PP_ENUM(n,M0,~) ), tag::cpu_, Dummy> : callable \
  {                                                                       \
    template<class Sig> struct result;                                    \
    template<class This,BOOST_PP_ENUM_PARAMS(n,class A)>                  \
    struct  result<This(BOOST_PP_ENUM_PARAMS(n,A))> : meta::strip<A0> {}; \
                                                                          \
    NT2_FUNCTOR_CALL(n)                                                   \
    {                                                                     \
      return nt2::map( functor<Tag>(), BOOST_PP_ENUM_PARAMS(n,a));        \
    }                                                                     \
  };                                                                      \
} }                                                                       \
/**/

BOOST_PP_REPEAT_FROM_TO(1,BOOST_PP_INC(NT2_MAX_ARITY),M1,~)

#undef M1
#undef M0

#endif
