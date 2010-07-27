/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_SDK_META_GCD_HPP_INCLUDED
#define NT2_SDK_META_GCD_HPP_INCLUDED

////////////////////////////////////////////////////////////////////////////////
// Compute the GCD of a list of integers at compile-time
//* TODO :  Documentation: http://nt2.lri.fr/sdk/meta/gcd.html
////////////////////////////////////////////////////////////////////////////////
#include <boost/config.hpp>
#include <boost/mpl/int.hpp>
#include <nt2/sdk/meta/details/gcd.hpp>

#if !defined(BOOST_HAS_VARIADIC_TMPL)
#include <nt2/extension/parameters.hpp>
#include <boost/preprocessor/facilities/intercept.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/repetition/repeat_from_to.hpp>
#include <boost/preprocessor/repetition/enum_binary_params.hpp>
#include <boost/preprocessor/repetition/enum_shifted_params.hpp>
#endif

namespace nt2 { namespace meta
{
  //////////////////////////////////////////////////////////////////////////////
  // Recursive variadics
  //////////////////////////////////////////////////////////////////////////////
  #if defined(BOOST_HAS_VARIADIC_TMPL)
  template<int... As> struct gcd;

  template<int A0, int... As>
  struct  gcd<A0,As...> : details::gcd_impl<A0, gcd<As...>::value > {};

  template<int A0, int A1>  struct  gcd<A0,A1>  : details::gcd_impl<A0,A1>  {};
  template<int A0>          struct  gcd<A0>     : boost::mpl::int_<A0>      {};
  #else
  //////////////////////////////////////////////////////////////////////////////
  // Recursive macro
  //////////////////////////////////////////////////////////////////////////////
  template<BOOST_PP_ENUM_BINARY_PARAMS( NT2_MAX_META_ARITY
                                      , int A
                                      , = 1 BOOST_PP_INTERCEPT
                                      )
          >
  struct gcd;

  template<int A0, int A1>  struct gcd<A0,A1>: details::gcd_impl<A0, A1> {};
  template<int A0>          struct gcd<A0>: boost::mpl::int_<A0> {};

  #define M0(z,n,t)                                                             \
  template<BOOST_PP_ENUM_PARAMS(n,int A)>                                       \
  struct  gcd<BOOST_PP_ENUM_PARAMS(n,A)>                                        \
        : details::gcd_impl<A0, gcd<BOOST_PP_ENUM_SHIFTED_PARAMS(n,A)>::value > \
  {};                                                                           \
  /**/

  BOOST_PP_REPEAT_FROM_TO(3,NT2_MAX_META_ARITY,M0,~)

  #undef M0
  #endif
} }

#endif
