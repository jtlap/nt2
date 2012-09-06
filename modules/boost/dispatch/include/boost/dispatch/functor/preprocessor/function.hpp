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
#include <boost/dispatch/functor/meta/call.hpp>
#include <boost/dispatch/functor/meta/make_functor.hpp>
#include <boost/dispatch/attributes.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/repetition/enum_binary_params.hpp>
#include <boost/preprocessor/facilities/intercept.hpp>
#include <boost/preprocessor/seq/elem.hpp>
#include <boost/preprocessor/seq/size.hpp>
#include <boost/preprocessor/seq/enum.hpp>
#include <boost/preprocessor/cat.hpp>

////////////////////////////////////////////////////////////////////////////////
// Generate a function prototype from NAME, TAG and Number of parameters
////////////////////////////////////////////////////////////////////////////////
#define BOOST_DISPATCH_FUNCTION_INTERFACE(Tag, Name, N)                        \
template<BOOST_PP_ENUM_PARAMS(N,class A)>                                      \
BOOST_FORCEINLINE                                                              \
typename boost::dispatch::meta::                                               \
call<Tag(BOOST_PP_ENUM_BINARY_PARAMS(N, A, const& BOOST_PP_INTERCEPT))>::type  \
Name( BOOST_PP_ENUM_BINARY_PARAMS(N, A, const& a) )                            \
/**/

////////////////////////////////////////////////////////////////////////////////
// Generate a function body from TAG and Number of parameters
////////////////////////////////////////////////////////////////////////////////
#define BOOST_DISPATCH_FUNCTION_BODY(Tag, N)                                   \
return typename boost::dispatch::make_functor<Tag, A0>::type()                 \
(BOOST_PP_ENUM_PARAMS(N, a));                                                  \
/**/

////////////////////////////////////////////////////////////////////////////////
// Generate a complete function implementation
////////////////////////////////////////////////////////////////////////////////
#ifdef NT2_DOXYGEN_ONLY
#define BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(Tag, Name, N)      \
template<BOOST_PP_ENUM_PARAMS(N,class A)>                         \
unspecified Name( BOOST_PP_ENUM_BINARY_PARAMS(N, A, const& a) );  \
/**/
#else
#define BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(Tag, Name, N)                   \
template<BOOST_PP_ENUM_PARAMS(N,class A)>                                      \
BOOST_FORCEINLINE                                                              \
typename boost::dispatch::meta::                                               \
call<Tag(BOOST_PP_ENUM_BINARY_PARAMS(N, A, const& BOOST_PP_INTERCEPT))>::type  \
Name( BOOST_PP_ENUM_BINARY_PARAMS(N, A, const& a) )                            \
{                                                                              \
  BOOST_DISPATCH_FUNCTION_BODY(Tag, N)                                         \
}                                                                              \
/**/
#endif

#define BOOST_DISPATCH_FN_ARGS(z,n,t) BOOST_PP_SEQ_ELEM(n,t) a##n

////////////////////////////////////////////////////////////////////////////////
// Generate a complete function implementation with a specific prototype
////////////////////////////////////////////////////////////////////////////////
#ifdef NT2_DOXYGEN_ONLY
#define BOOST_DISPATCH_FUNCTION_IMPLEMENTATION_TPL(Tag, Name, Args, N)  \
template<BOOST_PP_ENUM_PARAMS(N, class A)>                              \
unspecified Name( BOOST_PP_ENUM ( BOOST_PP_SEQ_SIZE(Args                \
                                , BOOST_DISPATCH_FN_ARGS, Args          \
                                )                                       \
                );                                                      \
/**/
#else
#define BOOST_DISPATCH_FUNCTION_IMPLEMENTATION_TPL(Tag, Name, Args, N)         \
template<BOOST_PP_ENUM_PARAMS(N, class A)>                                     \
BOOST_FORCEINLINE                                                              \
typename boost::dispatch::meta::                                               \
call<Tag(BOOST_PP_SEQ_ENUM(Args))>::type                                       \
Name( BOOST_PP_ENUM(BOOST_PP_SEQ_SIZE(Args), BOOST_DISPATCH_FN_ARGS, Args) )   \
{                                                                              \
  BOOST_DISPATCH_FUNCTION_BODY(Tag, BOOST_PP_SEQ_SIZE(Args))                   \
}                                                                              \
/**/
#endif

////////////////////////////////////////////////////////////////////////////////
// Generate a complete function implementation for self modifying operator
////////////////////////////////////////////////////////////////////////////////
#define BOOST_DISPATCH_FN_REF(z,n,t) (BOOST_PP_CAT(A,BOOST_PP_INC(n)) const&)
#define BOOST_DISPATCH_FUNCTION_IMPLEMENTATION_SELF(Tag, Name, N)              \
BOOST_DISPATCH_FUNCTION_IMPLEMENTATION_TPL(Tag, Name,                          \
  (A0&)BOOST_PP_REPEAT(BOOST_PP_DEC(N), BOOST_DISPATCH_FN_REF, ~), N)          \
/**/

#endif
