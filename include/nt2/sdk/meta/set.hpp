/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_SDK_META_SET_HPP_INCLUDED
#define NT2_SDK_META_SET_HPP_INCLUDED

#include <boost/mpl/bool.hpp>
#include <nt2/sdk/meta/na.hpp>
#include <boost/preprocessor/facilities/intercept.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/repetition/repeat_from_to.hpp>
#include <boost/preprocessor/repetition/enum_binary_params.hpp>

////////////////////////////////////////////////////////////////////////////////
// Maximum of elements in a type hierarchy.
////////////////////////////////////////////////////////////////////////////////
#if !defined(NT2_META_SET_SIZE)
#define NT2_META_SET_SIZE 5
#endif

namespace nt2 { namespace meta
{
  //////////////////////////////////////////////////////////////////////////////
  // hierarchy of types - lightweight MPL set like class with minimal support
  //////////////////////////////////////////////////////////////////////////////
  template<BOOST_PP_ENUM_BINARY_PARAMS( NT2_META_SET_SIZE
                                      , class A
                                      , = meta::na_ BOOST_PP_INTERCEPT
                                      )
                                      >
  struct set
  {
    typedef void is_set_type;
    template<class T,class X=void> struct has_key : boost::mpl::false_ {};
  };

  #define M0(z,n,t)                                           \
  template<class X>                                           \
  struct has_key<BOOST_PP_CAT(A,n),X> : boost::mpl::true_ {}; \
  /**/

  #define M1(z,n,t)                             \
  template<BOOST_PP_ENUM_PARAMS(n,class A)>     \
  struct  set<BOOST_PP_ENUM_PARAMS(n,A)>        \
  {                                             \
    typedef void is_set_type;                   \
    template<class T,class X=void>              \
    struct has_key : boost::mpl::false_ {};     \
    BOOST_PP_REPEAT(n,M0,~)                     \
  };                                            \
  /**/

  //////////////////////////////////////////////////////////////////////////////
  // Generate all hierarchy specialization
  //////////////////////////////////////////////////////////////////////////////
  BOOST_PP_REPEAT_FROM_TO(1,NT2_META_SET_SIZE,M1,~)

  #undef M0
  #undef M1
} }

#endif
