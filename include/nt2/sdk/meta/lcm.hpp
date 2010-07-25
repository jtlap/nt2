/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_SDK_META_LCM_HPP_INCLUDED
#define NT2_SDK_META_LCM_HPP_INCLUDED

////////////////////////////////////////////////////////////////////////////////
// Compute the LCM of a list of integers at compile-time
//* TODO :  Documentation: http://nt2.lri.fr/sdk/meta/lcm.html
////////////////////////////////////////////////////////////////////////////////
#include <nt2/sdk/meta/gcd.hpp>

namespace nt2 { namespace meta
{
  //////////////////////////////////////////////////////////////////////////////
  // Recursive variadics
  //////////////////////////////////////////////////////////////////////////////
  #if defined(BOOST_HAS_VARIADIC_TMPL)
  template<int... As> struct lcm;

  template<int A0, int... As>
  struct  lcm<A0,As...> : lcm<A0, lcm<As...>::value > {};

  template<int A0, int A1>
  struct  lcm<A0,A1>  : boost::mpl::int_<(A*B)/gcd<A,B>::value>{};

  template<int A0> struct  lcm<A0> : boost::mpl::int_<A0> {};
  #else
  //////////////////////////////////////////////////////////////////////////////
  // Recursive macro
  //////////////////////////////////////////////////////////////////////////////
  template<BOOST_PP_ENUM_BINARY_PARAMS( NT2_MAX_META_ARITY
                                      , int A
                                      , = 1 BOOST_PP_INTERCEPT
                                      )
          >
  struct lcm;

  template<int A0, int A1>
  struct  lcm<A0,A1> : boost::mpl::int_<(A0*A1)/gcd<A0,A1>::value>{};

  template<> struct  lcm<0,0> : boost::mpl::int_<0>{};

  template<int A0> struct lcm<A0>: boost::mpl::int_<A0> {};

  #define M0(z,n,t)                                               \
  template<BOOST_PP_ENUM_PARAMS(n,int A)>                         \
  struct  lcm<BOOST_PP_ENUM_PARAMS(n,A)>                          \
        : lcm<A0, lcm<BOOST_PP_ENUM_SHIFTED_PARAMS(n,A)>::value > \
  {};                                                             \
  /**/

  BOOST_PP_REPEAT_FROM_TO(3,NT2_MAX_META_ARITY,M0,~)

  #undef M0
  #endif
} }

#endif
