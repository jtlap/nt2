/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_SDK_FUNCTOR_DETAILS_DOMINANT_HPP_INCLUDED
#define NT2_SDK_FUNCTOR_DETAILS_DOMINANT_HPP_INCLUDED

#include <boost/config.hpp>
#include <boost/mpl/eval_if.hpp>
#include <boost/utility/result_of.hpp>
#include <nt2/sdk/meta/category_of.hpp>
#include <nt2/extension/parameters.hpp>
#include <nt2/sdk/details/preprocessor.hpp>
#include <boost/preprocessor/repetition/repeat_from_to.hpp>

#if !defined(BOOST_HAS_VARIADIC_TMPL)
#include <nt2/sdk/meta/na.hpp>
#include <boost/preprocessor/facilities/intercept.hpp>
#include <boost/preprocessor/repetition/enum_binary_params.hpp>
#endif

namespace nt2 { namespace details
{
  //////////////////////////////////////////////////////////////////////////////
  // Recursive variadics implementation
  //////////////////////////////////////////////////////////////////////////////
  #if defined(BOOST_HAS_VARIADIC_TMPL)
  template<class... Args> struct dominant;

  template<class Head, class... Tails>
  struct  dominant<Head,Tails...>
        : boost::mpl::eval_if_c<  ( meta::category_of<Head>::type::rank
                                  < dominant<Tails...>::type::rank
                                  )
                                , dominant<Tails...>
                                , meta::category_of<Head>
                                >
  {};

  template<class Head>  struct dominant<Head> : meta::category_of<Head> {};
  #else
  //////////////////////////////////////////////////////////////////////////////
  // Macro based implementation
  //////////////////////////////////////////////////////////////////////////////
  template< BOOST_PP_ENUM_BINARY_PARAMS ( NT2_MAX_ARITY
                                        , class A
                                        , = meta::na_ BOOST_PP_INTERCEPT
                                        )
          >
  struct dominant;

  template<class A> struct dominant<A> : meta::category_of<A> {};

  #define M0(z,n,t)                                                                   \
  template<BOOST_PP_ENUM_PARAMS(n,class A)>                                           \
  struct  dominant<BOOST_PP_ENUM_PARAMS(n,A)>                                         \
  : boost::mpl::eval_if_c<  ( meta::category_of<A0>::type::rank                       \
                            < dominant<BOOST_PP_ENUM_SHIFTED_PARAMS(n,A)>::type::rank \
                            )                                                         \
                          , dominant<BOOST_PP_ENUM_SHIFTED_PARAMS(n,A)>               \
                          , meta::category_of<A0>                                     \
                          >                                                           \
  {};                                                                                 \
  /**/

  BOOST_PP_REPEAT_FROM_TO(2,NT2_MAX_ARITY,M0,~)

  template< BOOST_PP_ENUM_PARAMS(NT2_MAX_ARITY, class A)>
  struct dominant
  : boost::mpl::eval_if_c<  ( meta::category_of<A0>::type::rank
                            < dominant<BOOST_PP_ENUM_SHIFTED_PARAMS(NT2_MAX_ARITY,A)>::type::rank
                            )
                          , dominant<BOOST_PP_ENUM_SHIFTED_PARAMS(NT2_MAX_ARITY,A)>
                          , meta::category_of<A0>
                          >
  {};

  #undef M0
  #endif

  //////////////////////////////////////////////////////////////////////////////
  // Some specialization for improving compile-time
  //////////////////////////////////////////////////////////////////////////////
  #define M0(z,n,t)                                               \
  template<class A>                                               \
  struct dominant<NT2_PP_ENUM_VALUE(n,A)> : meta::category_of<A>  \
  {};                                                             \
  /**/

  BOOST_PP_REPEAT_FROM_TO(2,BOOST_PP_INC(NT2_MAX_ARITY),M0,~)

  #undef M0
} }

#endif
