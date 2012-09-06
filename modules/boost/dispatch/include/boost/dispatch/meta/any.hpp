//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_DISPATCH_META_ANY_HPP_INCLUDED
#define BOOST_DISPATCH_META_ANY_HPP_INCLUDED

/*!
 * @file
 * @brief Define the boost::dispatch::meta::any @metafunction.
 **/

#include <boost/config.hpp>
#include <boost/dispatch/meta/details/any.hpp>

#if !defined(BOOST_HAS_VARIADIC_TMPL)
#include <boost/preprocessor/facilities/intercept.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/repetition/enum_binary_params.hpp>
#endif

namespace boost { namespace dispatch { namespace meta
{
  //============================================================================
  // Recursive variadics
  //============================================================================
#if defined(BOOST_HAS_VARIADIC_TMPL) || defined(NT2_DOXYGEN_ONLY)
  /*!
   * @brief
   * Evaluates if a given meta-predicate is true for at least one type in a type
   * sequence. @c any can either work on a @metasequence or a classic enumeration
   * of template parameters.
   *
   * @tparam Pred Boolean @metafunction
   * @tparam Args List of types to assert
   *
   * @par Models:
   *
   * @metafunction
   *
   * @par Semantic:
   *
   * For any types @c Pred and @c T0,...,Tn
   *
   * @code
   * typedef any<Pred,T0,...,Tn>::type type;
   * @endcode
   *
   * is equivalent to :
   *
   * @code
   * typedef not_<is_same< boost::mpl::find_if<T0,Pred>::type
   *                     , boost::mpl::end<T0>::type>
   *             >::type                                           type;
   * @endcode
   *
   * if @c T0 is a @metasequence. Otherwise, it evaluates to @true_
   * if it exists a type @c T in @c T0,...,Tn for which @c apply1<Pred,T>::type
   * evaluates to @true_. Otherwise, it evaluates to @false_.
   *
   * @par Usage:
   *
   * @include any.cpp
   **/
  template< class Pred, class... Args>
  struct any : details::any_impl<Pred, Args...> {};
#else
  //============================================================================
  // Recursive macro
  //============================================================================
  template< class Pred
          , BOOST_PP_ENUM_BINARY_PARAMS ( BOOST_DISPATCH_MAX_META_ARITY
                                        , class A
                                        , = dispatch::meta::na_
                                            BOOST_PP_INTERCEPT
                                        )
          >
  struct  any
        : details::any_impl
                        < Pred
                        , BOOST_PP_ENUM_PARAMS(BOOST_DISPATCH_MAX_META_ARITY, A)
                        >
  {};
#endif
} } }

#endif
