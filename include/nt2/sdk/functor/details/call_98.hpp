/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/

////////////////////////////////////////////////////////////////////////////////
// This file is supposed to be included inside functors::functor code
////////////////////////////////////////////////////////////////////////////////
#define M0(z,n,t)                                                               \
template<class This, BOOST_PP_ENUM_PARAMS(n,class A) >                          \
struct  result<This(BOOST_PP_ENUM_PARAMS(n,A))>                                 \
{                                                                               \
  typedef typename                                                              \
  std::tr1::result_of<meta::dominant(BOOST_PP_ENUM_PARAMS(n,A))>::type::tag dom;   \
  typedef call<Function,dom,Info>                  callee;                      \
  typedef typename                                                              \
  std::tr1::result_of<callee(BOOST_PP_ENUM_PARAMS(n,A))>::type  type;              \
};                                                                              \
                                                                                \
template<BOOST_PP_ENUM_PARAMS(n,class A)> inline                                \
typename meta::enable_call<Function(BOOST_PP_ENUM_PARAMS(n,A))>::type           \
operator()( BOOST_PP_ENUM_BINARY_PARAMS(n,A,const& a)  )                        \
{                                                                               \
  typedef typename                                                              \
  std::tr1::result_of<meta::dominant(BOOST_PP_ENUM_PARAMS(n,A))>::type::tag dom;   \
  call<Function,dom,Info>                  callee;                              \
  return callee( BOOST_PP_ENUM_PARAMS(n,a) );                                   \
}                                                                               \
/**/

BOOST_PP_REPEAT_FROM_TO(1,BOOST_PP_INC(NT2_MAX_ARITY),M0,~)
#undef M0
