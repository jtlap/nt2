//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_DISPATCH_META_ALL_HPP_INCLUDED
#define BOOST_DISPATCH_META_ALL_HPP_INCLUDED

/*!
 * @file
 * @brief Define the boost::dispatch::meta::all @metafunction.
 **/

#include <boost/config.hpp>
#include <boost/dispatch/meta/details/all.hpp>

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
   * @brief Checks a predicates over all elements of a types list
   *
   * Evaluates if a given Boolean @metafunction is true for all types in a type
   * sequence. all can either work on a @metasequence or a classic enumeration
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
   * typedef all<Pred,T0,...,Tn>::type type;
   * @endcode
   *
   * is equivalent to :
   *
   * @code
   * typedef is_same< find_if<T0, not_<Pred> >::type, end<T0>::type>::type type;
   * @endcode
   *
   * if @c T0 is a @metasequence. Otherwise, it evaluates to @true_
   * if @c apply1<Pred,T>::type evaluates to @true_  for all
   * @c T0,...,Tn. Otherwise, it evaluates to @false_.
   *
   * @par Usage:
   *
   * @include all.cpp
   **/
  template<class Pred, class... Args>
  struct all : details::all_impl<Pred, Args...> {};
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
  struct  all
        : details::all_impl
                        < Pred
                        , BOOST_PP_ENUM_PARAMS(BOOST_DISPATCH_MAX_META_ARITY, A)
                        >
  {};
#endif
} } }

#endif
