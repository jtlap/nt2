/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_SDK_FUNCTOR_META_DOMINANT_HPP_INCLUDED
#define NT2_SDK_FUNCTOR_META_DOMINANT_HPP_INCLUDED

////////////////////////////////////////////////////////////////////////////////
// Compute the dominant category of a list of types
// Documentation:http://nt2.lri.fr/sdk/functor/meta/dominant.html
////////////////////////////////////////////////////////////////////////////////
#include <boost/config.hpp>
#include <nt2/sdk/functor/details/dominant.hpp>

#if !defined(BOOST_HAS_VARIADIC_TMPL)
#include <nt2/extension/parameters.hpp>
#include <boost/preprocessor/facilities/intercept.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/repetition/repeat_from_to.hpp>
#include <boost/preprocessor/repetition/enum_binary_params.hpp>
#endif

namespace nt2 { namespace meta
{
  struct dominant
  {
    template<class Sig> struct result;

    #if defined(BOOST_HAS_VARIADIC_TMPL)
    template<class This, class... Args>
    struct  result<This(Args...)> : details::dominant< Args... >
    {};

    template<class... Args>
    typename result<dominant(Args...)>::type
    operator()(Args&& ... ) const
    {
      typename result<dominant(Args...)>::type that;
      return that;
    };

    #else
    #define M0(z,n,t)                                                     \
    template<class This, BOOST_PP_ENUM_PARAMS(n,class A) >                \
    struct  result<This(BOOST_PP_ENUM_PARAMS(n,A))>                       \
          : details::dominant<BOOST_PP_ENUM_PARAMS(n,A)>                  \
    {};                                                                   \
                                                                          \
    template<BOOST_PP_ENUM_PARAMS(n,class A) >                            \
    typename result<dominant(BOOST_PP_ENUM_PARAMS(n,A))>::type            \
    operator()                                                            \
    (BOOST_PP_ENUM_BINARY_PARAMS(n,A, const & BOOST_PP_INTERCEPT)) const  \
    {                                                                     \
      typename result<dominant(BOOST_PP_ENUM_PARAMS(n,A))>::type that;    \
      return that;                                                        \
    }                                                                     \
    /**/
    BOOST_PP_REPEAT_FROM_TO(1,BOOST_PP_INC(NT2_MAX_ARITY),M0,~)
    #undef M0
    #endif
  };
} }

#endif
