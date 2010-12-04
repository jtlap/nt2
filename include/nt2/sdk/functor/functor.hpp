/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_SDK_FUNCTOR_FUNCTOR_HPP_INCLUDED
#define NT2_SDK_FUNCTOR_FUNCTOR_HPP_INCLUDED

////////////////////////////////////////////////////////////////////////////////
// Main generic functor class
// Documentation: http://nt2.lri.fr/sdk/functor/entity/functor.html
////////////////////////////////////////////////////////////////////////////////
#include <boost/config.hpp>
#include <boost/tr1/functional.hpp>
#include <nt2/sdk/meta/floating.hpp>
#include <nt2/sdk/meta/arithmetic.hpp>
#include <nt2/sdk/functor/forward.hpp>
#include <nt2/sdk/error/static_assert.hpp>
#include <nt2/sdk/functor/details/call.hpp>
#include <nt2/sdk/functor/details/dispatch.hpp>
#include <nt2/sdk/functor/meta/enable_call.hpp>

#if !defined(BOOST_HAS_VARIADIC_TMPL)
#include <nt2/extension/parameters.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/repetition/enum_binary_params.hpp>
#include <boost/preprocessor/repetition/repeat_from_to.hpp>
#endif

namespace nt2
{
  template<class Tag, class Site> struct functor
  {
    template<class Sig> struct result;

    #if defined(BOOST_HAS_VARIADIC_TMPL)
    template<class This, class... Args>
    struct  result<This(Args...)>
    {
      typedef typename meta::dispatch_call<Tag(Args...),Site>::type callee;
      typedef typename std::tr1::result_of<callee(Args...)>::type   type;
    };

    template<class... Args> inline typename result<functor(Args...)>::type
    operator()( Args const& ...args ) const
    {
      typename meta::dispatch_call<Tag(Args...),Site>::type callee;
      return callee( args... );
    }
    #else

    #define M0(z,n,t)                                                         \
    template<class This, BOOST_PP_ENUM_PARAMS(n,class A) >                    \
    struct result<This(BOOST_PP_ENUM_PARAMS(n,A))>                            \
    {                                                                         \
      typedef typename                                                        \
      meta::dispatch_call<Tag(BOOST_PP_ENUM_PARAMS(n,A)),Site>::type callee;  \
      typedef typename                                                        \
      std::tr1::result_of<callee(BOOST_PP_ENUM_PARAMS(n,A))>::type  type;     \
    };                                                                        \
                                                                              \
    template<BOOST_PP_ENUM_PARAMS(n,class A)> inline                          \
    typename meta::enable_call<Tag(BOOST_PP_ENUM_PARAMS(n,A))>::type          \
    operator()( BOOST_PP_ENUM_BINARY_PARAMS(n,A,const& a)  ) const            \
    {                                                                         \
      typename                                                                \
      meta::dispatch_call<Tag(BOOST_PP_ENUM_PARAMS(n,A)),Site>::type callee;  \
      return callee( BOOST_PP_ENUM_PARAMS(n,a) );                             \
    }                                                                         \
    /**/

    BOOST_PP_REPEAT_FROM_TO(1,BOOST_PP_INC(NT2_MAX_ARITY),M0,~)
    #undef M0

    #endif
  };
}

#endif
