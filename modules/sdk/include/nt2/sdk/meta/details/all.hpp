/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_SDK_META_DETAILS_ALL_HPP_INCLUDED
#define NT2_SDK_META_DETAILS_ALL_HPP_INCLUDED

////////////////////////////////////////////////////////////////////////////////
// Internals for meta::all_
////////////////////////////////////////////////////////////////////////////////
#include <boost/mpl/end.hpp>
#include <boost/mpl/not.hpp>
#include <nt2/sdk/meta/na.hpp>
#include <boost/mpl/apply.hpp>
#include <boost/mpl/find_if.hpp>
#include <boost/mpl/is_sequence.hpp>
#include <boost/type_traits/is_same.hpp>

#if !defined(BOOST_HAS_VARIADIC_TMPL)
#include <nt2/extension/parameters.hpp>
#include <boost/preprocessor/repetition/enum.hpp>
#include <boost/preprocessor/facilities/intercept.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/repetition/repeat_from_to.hpp>
#include <boost/preprocessor/repetition/enum_binary_params.hpp>
#endif

namespace nt2 { namespace details
{
  //////////////////////////////////////////////////////////////////////////////
  // Recursive variadic version
  //////////////////////////////////////////////////////////////////////////////
  #if defined(BOOST_HAS_VARIADIC_TMPL)
  template< class Predicate, class... Args> struct all_impl;

  template< class Pred, class Head, class... Tails>
  struct  all_impl<Pred,Head,Tails...>
        : boost::mpl::and_ < boost::mpl::apply1<Pred,Head>
                          , all_impl<Pred,Tails...>
                          >
  {};

  template< class Pred, class T>
  struct  all_impl<Pred, T>
        : boost::mpl::eval_if_c < boost::mpl::is_sequence<T>::value
                                , boost::is_same< typename boost::mpl::find_if<  T
                                                                              ,  boost::mpl::not_<Pred>
                                                                              >::type
                                                , typename boost::mpl::end<T>::type
                                                >
                                , boost::mpl::apply1<Pred,T>
                                >::type
  {};
  #else
  //////////////////////////////////////////////////////////////////////////////
  // Macro based version
  //////////////////////////////////////////////////////////////////////////////
  #define M1(z,n,t)                                           \
  && boost::mpl::apply1<Pred,BOOST_PP_CAT(A,n)>::type::value  \
  /**/

  template< class Pred
          , BOOST_PP_ENUM_BINARY_PARAMS ( NT2_MAX_META_ARITY
                                        , class A
                                        , = meta::na_ BOOST_PP_INTERCEPT
                                        )
          >
  struct  all_impl
        : boost::mpl::bool_<true BOOST_PP_REPEAT(NT2_MAX_META_ARITY,M1,~)>
  {};

  template< class Pred, class T>
  struct  all_impl<Pred, T>
        : boost::mpl::eval_if_c < boost::mpl::is_sequence<T>::value
                                ,  boost::is_same< typename boost::mpl::find_if<  T
                                                                              ,  boost::mpl::not_<Pred>
                                                                              >::type
                                                , typename boost::mpl::end<T>::type
                                                >
                                , boost::mpl::apply1<Pred,T>
                                >::type
  {};

  #define M0(z,n,t)                                         \
  template<class Pred, BOOST_PP_ENUM_PARAMS(n,class A)>     \
  struct  all_impl<Pred,BOOST_PP_ENUM_PARAMS(n,A)>          \
        : boost::mpl::bool_<true BOOST_PP_REPEAT(n,M1,~)>    \
  {};                                                       \
  /**/

  BOOST_PP_REPEAT_FROM_TO(2,NT2_MAX_META_ARITY,M0,~)

  #undef M1
  #undef M0

  #endif

} }

#endif
