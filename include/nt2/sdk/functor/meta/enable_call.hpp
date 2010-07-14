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
#include <boost/utility/result_of.hpp>
#include <boost/utility/enable_if.hpp>
#include <nt2/sdk/functor/meta/validate.hpp>

#if !defined(BOOST_HAS_VARIADIC_TMPL)
#include <nt2/extension/parameters.hpp>
#include <boost/preprocessor/repetition/repeat_from_to.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#endif

namespace nt2 { namespace meta
{
  template<class Sig, class Enable = void>
  struct enable_call;

  #if defined(BOOST_HAS_VARIADIC_TMPL)
  template<class F, class... Args>
  struct enable_call< F(Args...)
                    , typename boost::
                      enable_if_c < boost::
                                    result_of<validate<F>(Args...)>::type::value
                                  >::type
                    >
    : boost::result_of<functors::functor<F>(Args...)>
  {};
  #else

  #define M0(z,n,t)                                                           \
  template<class F, BOOST_PP_ENUM_PARAMS(n,class A)>                          \
  struct enable_call< F(BOOST_PP_ENUM_PARAMS(n,A))                            \
                    , typename boost::                                        \
                      enable_if_c < boost::result_of<validate<F>              \
                                    (BOOST_PP_ENUM_PARAMS(n,A))>::type::value \
                                  >::type                                     \
                    >                                                         \
    : boost::result_of<functors::functor<F>(BOOST_PP_ENUM_PARAMS(n,A))>       \
  {};                                                                         \
  /**/

  BOOST_PP_REPEAT_FROM_TO(1,BOOST_PP_INC(NT2_MAX_ARITY),M0,~)
  #undef M0

  #endif
} }

#endif
