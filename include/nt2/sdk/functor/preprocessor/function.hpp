/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_SDK_FUNCTOR_PREPROCESSOR_FUNCTION_HPP_INCLUDED
#define NT2_SDK_FUNCTOR_PREPROCESSOR_FUNCTION_HPP_INCLUDED

////////////////////////////////////////////////////////////////////////////////
// Various macro for boilerplating function code writing
// Documentation: http://nt2.lri.fr/sdk/functor/macros/function.html
////////////////////////////////////////////////////////////////////////////////
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/repetition/enum_binary_params.hpp>

////////////////////////////////////////////////////////////////////////////////
// Generate a function prototype from NAME, TAG and Number of parameters
////////////////////////////////////////////////////////////////////////////////
#define NT2_FUNCTION_INTERFACE(TAG,NAME,N)                                      \
template<BOOST_PP_ENUM_PARAMS(N,class A)> inline                                \
typename nt2::meta::enable_call<TAG (                                           \
                    BOOST_PP_ENUM_BINARY_PARAMS(N,A, const& BOOST_PP_INTERCEPT) \
                                    )>::type                                    \
NAME ( BOOST_PP_ENUM_BINARY_PARAMS(N,A, const& a) )                             \
/**/

////////////////////////////////////////////////////////////////////////////////
// Generate a function body from TAG and Number of parameters
////////////////////////////////////////////////////////////////////////////////
#define NT2_FUNCTION_BODY(TAG,N)          \
nt2::functor<TAG> callee;       \
return callee(BOOST_PP_ENUM_PARAMS(N,a)); \
/**/

////////////////////////////////////////////////////////////////////////////////
// Generate a complete function implementation
////////////////////////////////////////////////////////////////////////////////
#define NT2_FUNCTION_IMPLEMENTATION(TAG,NAME,N)                   \
NT2_FUNCTION_INTERFACE(TAG,NAME,N) { NT2_FUNCTION_BODY(TAG,N); }  \
/**/

////////////////////////////////////////////////////////////////////////////////
// Generate a complete function implementation for self modifying operator
////////////////////////////////////////////////////////////////////////////////
#define NT2_FUNCTION_IMPLEMENTATION_SELF_1(NAME,TAG)  \
template<class A0> inline                             \
typename nt2::meta::enable_call<TAG(A0&)>::type       \
NAME( A0& a0 )  { NT2_FUNCTION_BODY(TAG,1) }          \
/**/

#define NT2_FUNCTION_IMPLEMENTATION_SELF_2(NAME,TAG)        \
template<class A0,class A1> inline                          \
typename nt2::meta::enable_call<TAG(A0&,A1 const&)>::type   \
NAME( A0& a0, A1 const& a1 )  { NT2_FUNCTION_BODY(TAG,2) }  \
/**/

#define NT2_FUNCTION_IMPLEMENTATION_SELF(TAG,NAME,N)        \
BOOST_PP_CAT(NT2_FUNCTION_IMPLEMENTATION_SELF_,N)(NAME,TAG) \
/**/

////////////////////////////////////////////////////////////////////////////////
// Generate a method for self-operator overload
////////////////////////////////////////////////////////////////////////////////
#define NT2_FUNCTION_METHOD_SELF(NAME,TAG,SELF)             \
template<class A0> inline                                   \
typename nt2::meta::enable_call<TAG(SELF&,A0 const&)>::type \
NAME( A0 const& a0 )                                        \
{                                                           \
  nt2::functor<TAG> callee;                                 \
  return callee(*this,a0);                                  \
}                                                           \
/**/

#endif
