/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_SDK_FUNCTOR_META_ENABLE_CALL_HPP_INCLUDED
#define NT2_SDK_FUNCTOR_META_ENABLE_CALL_HPP_INCLUDED

////////////////////////////////////////////////////////////////////////////////
// SFINAE based functor return type computation
//* TODO : Documentation:http://nt2.lri.fr/sdk/functor/meta/enable_call.html
////////////////////////////////////////////////////////////////////////////////
#include <boost/config.hpp>
#include <boost/tr1/functional.hpp>
#include <boost/utility/result_of.hpp>
#include <nt2/sdk/meta/enable_if_type.hpp>

#if !defined(BOOST_HAS_VARIADIC_TMPL)
#include <nt2/extension/parameters.hpp>
#include <boost/preprocessor/repetition/repeat_from_to.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#endif

namespace nt2 { namespace details
{
  template<typename T> struct callable_type
  {
    typedef typename T::callable_type type;
  };
} }

namespace nt2 { namespace meta
{

  template<class Sig, class Site = tag::cpu_, class Enable = void>
  struct enable_call;

  #if defined(BOOST_HAS_VARIADIC_TMPL)
  template<class F, class Site, class... Args>
  struct enable_call< F(Args...), Site
                    , typename
                      enable_if_type< typename details::callable_type< typename
                                                                       dispatch_call < F(Args...)
                                                                                     , Site
                                                                                     >::type
                                                                     >::type
                                    >::type
                    >
    : std::tr1::result_of<functor<F>(Args...)>
  {};
  #else

  #define M0(z,n,t)                                                                                                    \
  template<class F, class Site, BOOST_PP_ENUM_PARAMS(n,class A)>                                                       \
  struct  enable_call < F(BOOST_PP_ENUM_PARAMS(n,A))                                                                   \
                      , Site                                                                                           \
                      , typename                                                                                       \
                        enable_if_type< typename details::callable_type< typename                                      \
                                                                         dispatch_call < F(BOOST_PP_ENUM_PARAMS(n,A))  \
                                                                                       , Site                          \
                                                                                       >::type                         \
                                                                       >::type                                         \
                                      >::type                                                                          \
                    >                                                                                                  \
        : std::tr1::result_of<functor<F>(BOOST_PP_ENUM_PARAMS(n,A))>                                                   \
  {};                                                                                                                  \
  /**/

  BOOST_PP_REPEAT_FROM_TO(1,BOOST_PP_INC(NT2_MAX_ARITY),M0,~)
  #undef M0

  #endif
} }

#endif
