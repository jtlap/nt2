/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef BOOST_DISPATCH_FUNCTOR_PREPROCESSOR_FUNCTION_HPP_INCLUDED
#define BOOST_DISPATCH_FUNCTOR_PREPROCESSOR_FUNCTION_HPP_INCLUDED

////////////////////////////////////////////////////////////////////////////////
// Various macro for boilerplating function code writing
// Documentation: http://nt2.lri.fr/sdk/functor/macros/function.html
////////////////////////////////////////////////////////////////////////////////
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/repetition/enum_binary_params.hpp>
#include <boost/dispatch/attributes.hpp>

////////////////////////////////////////////////////////////////////////////////
// Generate a function prototype from NAME, TAG and Number of parameters
////////////////////////////////////////////////////////////////////////////////
#define BOOST_DISPATCH_FUNCTION_INTERFACE(TAG,NAME,N)                           \
template<BOOST_PP_ENUM_PARAMS(N,class A)> BOOST_DISPATCH_FORCE_INLINE               \
typename boost::dispatch::meta::call<TAG(                                       \
                    BOOST_PP_ENUM_BINARY_PARAMS(N,A, const& BOOST_PP_INTERCEPT) \
                                    )>::type                                    \
NAME ( BOOST_PP_ENUM_BINARY_PARAMS(N,A, const& a) )                             \
/**/

////////////////////////////////////////////////////////////////////////////////
// Generate a function body from TAG and Number of parameters
////////////////////////////////////////////////////////////////////////////////
#define BOOST_DISPATCH_FUNCTION_BODY(TAG,N)                   \
typename boost::dispatch::make_functor<TAG, A0>::type callee; \
return callee(BOOST_PP_ENUM_PARAMS(N,a));                     \
/**/

////////////////////////////////////////////////////////////////////////////////
// Generate a complete function implementation
////////////////////////////////////////////////////////////////////////////////
#define BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(TAG,NAME,N)                             \
BOOST_DISPATCH_FUNCTION_INTERFACE(TAG,NAME,N) { BOOST_DISPATCH_FUNCTION_BODY(TAG,N); } \
/**/

#define BOOST_DISPATCH_FN_TYPES(z,n,t) BOOST_PP_SEQ_ELEM(n,t)
#define BOOST_DISPATCH_FN_ARGS(z,n,t)  BOOST_PP_SEQ_ELEM(n,t) BOOST_PP_CAT(a,n)

////////////////////////////////////////////////////////////////////////////////
// Generate a complete function implementation with a specific prototype
////////////////////////////////////////////////////////////////////////////////
#define BOOST_DISPATCH_FUNCTION_IMPLEMENTATION_TPL(TAG,NAME,ARGS,N)                  \
template<BOOST_PP_ENUM_PARAMS(N, class A)> BOOST_DISPATCH_FORCE_INLINE                   \
typename boost::dispatch::meta::                                                     \
call<TAG(BOOST_PP_ENUM(BOOST_PP_SEQ_SIZE(ARGS),BOOST_DISPATCH_FN_TYPES,ARGS))>::type \
NAME( BOOST_PP_ENUM(BOOST_PP_SEQ_SIZE(ARGS),BOOST_DISPATCH_FN_ARGS,ARGS) )           \
{                                                                                    \
  BOOST_DISPATCH_FUNCTION_BODY(TAG, BOOST_PP_SEQ_SIZE(ARGS) )                        \
}                                                                                    \
/**/

////////////////////////////////////////////////////////////////////////////////
// Generate a complete function implementation for self modifying operator
////////////////////////////////////////////////////////////////////////////////
#define BOOST_DISPATCH_FUNCTION_IMPLEMENTATION_SELF_1(NAME,TAG) \
template<class A0> BOOST_DISPATCH_FORCE_INLINE                      \
typename boost::dispatch::meta::call<TAG(A0&)>::type            \
NAME( A0& a0 )  { BOOST_DISPATCH_FUNCTION_BODY(TAG,1) }         \
/**/

#define BOOST_DISPATCH_FUNCTION_IMPLEMENTATION_SELF_2(NAME,TAG)       \
template<class A0,class A1> BOOST_DISPATCH_FORCE_INLINE                   \
typename boost::dispatch::meta::call<TAG(A0&,A1 const&)>::type        \
NAME( A0& a0, A1 const& a1 )  { BOOST_DISPATCH_FUNCTION_BODY(TAG,2) } \
/**/

#define BOOST_DISPATCH_FN_REF(z,n,t) (BOOST_PP_CAT(A,BOOST_PP_INC(n)) const&)
#define BOOST_DISPATCH_FUNCTION_IMPLEMENTATION_SELF(TAG,NAME,N)        \
BOOST_DISPATCH_FUNCTION_IMPLEMENTATION_TPL(TAG,NAME, \
    (A0&)BOOST_PP_REPEAT(BOOST_PP_DEC(N),BOOST_DISPATCH_FN_REF,~),N) \
/**/

////////////////////////////////////////////////////////////////////////////////
// Generate a method for self-operator overload
////////////////////////////////////////////////////////////////////////////////
#define BOOST_DISPATCH_FUNCTION_METHOD_SELF(NAME,TAG,SELF)       \
template<class A0>  BOOST_DISPATCH_FORCE_INLINE                      \
typename boost::dispatch::meta::call<TAG(SELF&,A0 const&)>::type \
NAME( A0 const& a0 )                                             \
{                                                                \
  typename boost::dispatch::make_functor<TAG, A0>::type callee;  \
  return callee(*this,a0);                                       \
}                                                                \
/**/

#endif
