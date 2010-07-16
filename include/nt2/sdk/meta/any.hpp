/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_SDK_META_ANY_HPP_INCLUDED
#define NT2_SDK_META_ANY_HPP_INCLUDED

//////////////////////////////////////////////////////////////////////////////
// Check if any elements of a sequence matches some lambda function
//* TODO :  Documentation: http://nt2.lri.fr/sdk/meta/any.html
////////////////////////////////////////////////////////////////////////////////
#include <boost/mpl/end.hpp>
#include <boost/mpl/not.hpp>
#include <nt2/sdk/meta/na.hpp>
#include <boost/mpl/is_sequence.hpp>
#include <boost/mpl/apply.hpp>
#include <boost/mpl/find_if.hpp>
#include <nt2/extension/parameters.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/preprocessor/facilities/intercept.hpp>
#include <boost/preprocessor/repetition/enum.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/repetition/enum_binary_params.hpp>
#include <boost/preprocessor/repetition/repeat_from_to.hpp>

namespace nt2 { namespace details
{
  template<class Pred,class Seq>
  struct  any_impl_sequence
        : boost::mpl::not_<
              boost::is_same< typename boost::mpl::find_if<Seq,Pred>::type
                            , typename boost::mpl::end<Seq>::type
                            >
                          >
  {};

  template<class Pred,class Seq>
  struct  any_impl_type : boost::mpl::apply1<Pred,Seq>::type
  {};

  #if defined(BOOST_HAS_VARIADIC_TMPL)
  template< class Predicate, int Size, class... Args>
  struct any_impl
  {};
  // TODO A FINIR

  template< class Predicate, class A>
  struct any_impl<Predicate,1,A>
  : boost::mpl::eval_if_c < boost::mpl::is_sequence<A>::value
                          , any_impl_sequence<Predicate,A>
                          , any_impl_type<Predicate,A>
                          >
  {};

  #else
  template< class Predicate
          , bool IsSequence
          , BOOST_PP_ENUM_BINARY_PARAMS ( NT2_MAX_META_ARITY
                                        , class A
                                        , = meta::na_ BOOST_PP_INTERCEPT
                                        )
          >
  struct  any_impl;

  template<class Predicate,class A0>
  struct  any_impl<Predicate,true,A0> : any_impl_sequence<Predicate,A0>
  {};

  template<class Predicate,class A0>
  struct  any_impl<Predicate,false,A0> : any_impl_type<Predicate,A0>
  {};

  #define M1(z,n,t) typename boost::mpl::apply1<Predicate,BOOST_PP_CAT(A,n)>::type
  /**/

  #define M0(z,n,t)                                                 \
  template< class Predicate, bool IsSequence                        \
          , BOOST_PP_ENUM_PARAMS(n, class A)                        \
          >                                                         \
  struct  any_impl<Predicate,IsSequence,BOOST_PP_ENUM_PARAMS(n, A)> \
        : boost::mpl::or_<BOOST_PP_ENUM(n,M1,~)> {};                \
  /**/

  BOOST_PP_REPEAT_FROM_TO(1,NT2_MAX_META_ARITY,M0,~)

  template< class Predicate, bool IsSequence
          , BOOST_PP_ENUM_PARAMS(NT2_MAX_META_ARITY, class A)
          >
  struct  any_impl : boost::mpl::or_<BOOST_PP_ENUM(NT2_MAX_META_ARITY,M1,~)>
  {};

  #undef M1
  #undef M0
  #endif
} }

namespace nt2 { namespace meta
{
  #if defined(BOOST_HAS_VARIADIC_TMPL)
  template< class Predicate, class... Args>
  struct  any : details::any_impl<Predicate, sizeof...(Args), Args...> {};
  #else
  template< class Predicate
          , BOOST_PP_ENUM_BINARY_PARAMS ( NT2_MAX_META_ARITY
                                        , class A
                                        , = na_ BOOST_PP_INTERCEPT
                                        )
          >
  struct  any
        : details::any_impl < Predicate
                            , boost::mpl::is_sequence<A0>::value
                            , BOOST_PP_ENUM_PARAMS(NT2_MAX_META_ARITY, A)
                            >
  {};
  #endif
} }

#endif
