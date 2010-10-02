/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_SDK_FUNCTOR_META_FIND_TYPE_HPP_INCLUDED
#define NT2_SDK_FUNCTOR_META_FIND_TYPE_HPP_INCLUDED

////////////////////////////////////////////////////////////////////////////////
// For a given type and a list of hierarchy, find the first hierarchy in which
// the type can be found. Used in internal call<> tag dispatching
//* TODO : Documentation:http://nt2.lri.fr/sdk/functor/meta/find_type.html
////////////////////////////////////////////////////////////////////////////////
#include <boost/mpl/end.hpp>
#include <boost/mpl/find.hpp>
#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/identity.hpp>
#include <nt2/sdk/functor/meta/belong_to.hpp>

#if !defined(BOOST_HAS_VARIADIC_TMPL)
#include <nt2/extension/parameters.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/repetition/repeat_from_to.hpp>
#include <boost/preprocessor/repetition/enum_shifted_params.hpp>
#endif

namespace nt2 { namespace details
{
  template<class T, class Seq, class Default>
  struct find_type
  {
    typedef typename boost::mpl::find_if< Seq
                                        , meta::belong_to<T,boost::mpl::_1>
                                        >::type                           iter;
    typedef typename boost::mpl::end<Seq>::type                           end_;
    typedef boost::mpl::eval_if_c < boost::is_same<iter,end_>::value
                                  , boost::mpl::identity<Default>
                                  , boost::mpl::deref<iter>
                                  >                                       base;
    typedef typename base::type type;
  };
} }

namespace nt2 { namespace meta
{
  //////////////////////////////////////////////////////////////////////////////
  // Recursive variadic implementation
  //////////////////////////////////////////////////////////////////////////////
  #if defined(BOOST_HAS_VARIADIC_TMPL)
  template<class Type, class... Sets> struct  find_type;

  template<class Type, class Head, class... Sets>
  struct  find_type<Type,Head,Sets...>
        : boost::mpl::eval_if_c< nt2::meta::belong_to<Type,Head>::value
                          , boost::mpl::identity<Head>
                          , find_type<Type,Sets...>
                          >
  {};

  template<class Type, class Set>
  struct  find_type<Type,Set>
        : boost::mpl::if_c< nt2::meta::belong_to<Type,Set>::value
                          , Set
                          , nt2::functors::empty_
                          >
  {};

  #else
  //////////////////////////////////////////////////////////////////////////////
  // Macros based implementation
  //////////////////////////////////////////////////////////////////////////////
  template< class Type
          , BOOST_PP_ENUM_BINARY_PARAMS ( NT2_MAX_META_ARITY
                                        , class A
                                        , = meta::na_ BOOST_PP_INTERCEPT
                                        )
          >
  struct find_type;

  template<class Type, class Set>
  struct  find_type<Type,Set>
        : boost::mpl::eval_if_c < boost::mpl::is_sequence<Set>::value
                                , details::find_type<Type,Set,nt2::functors::empty_>
                                , boost::mpl::if_c< nt2::meta::belong_to<Type,Set>::value
                                                  , Set
                                                  , nt2::functors::empty_
                                                  >
                                >
  {};

  #define M0(z,n,t)                                                           \
  template<class Type,BOOST_PP_ENUM_PARAMS(n,class A)>                        \
  struct find_type<Type,BOOST_PP_ENUM_PARAMS(n,A)>                            \
        : boost::mpl::eval_if_c< nt2::meta::belong_to<Type,A0>::value         \
                          , boost::mpl::identity<A0>                          \
                          , find_type<Type,BOOST_PP_ENUM_SHIFTED_PARAMS(n,A)> \
                          >                                                   \
  {};                                                                         \
  /**/

  BOOST_PP_REPEAT_FROM_TO(2,NT2_MAX_META_ARITY,M0,~)

  template<class Type, BOOST_PP_ENUM_PARAMS(NT2_MAX_META_ARITY, class A)>
  struct find_type
  : boost::mpl::eval_if_c< nt2::meta::belong_to<Type,A0>::value
                    , boost::mpl::identity<A0>
                    , find_type<Type,BOOST_PP_ENUM_SHIFTED_PARAMS(NT2_MAX_META_ARITY,A)>
                    >
  {};

  #undef M0
  #endif
} }

#endif
