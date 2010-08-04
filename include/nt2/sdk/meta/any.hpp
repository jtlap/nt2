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

////////////////////////////////////////////////////////////////////////////////
// Check if any elements of a sequence matches some lambda function
// Documentation: http://nt2.lri.fr/sdk/meta/algo/any.html
////////////////////////////////////////////////////////////////////////////////
#include <boost/config.hpp>
#include <nt2/sdk/meta/details/any.hpp>

#if !defined(BOOST_HAS_VARIADIC_TMPL)
#include <boost/preprocessor/facilities/intercept.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/repetition/enum_binary_params.hpp>
#endif

namespace nt2 { namespace meta
{
  //////////////////////////////////////////////////////////////////////////////
  // Recursive variadics
  //////////////////////////////////////////////////////////////////////////////
  #if defined(BOOST_HAS_VARIADIC_TMPL)
  template< class Pred, class... Args>
  struct  any : details::any_impl<Pred, Args...> {};
  #else
  //////////////////////////////////////////////////////////////////////////////
  // Recursive macro
  //////////////////////////////////////////////////////////////////////////////
  template< class Pred
          , BOOST_PP_ENUM_BINARY_PARAMS ( NT2_MAX_META_ARITY
                                        , class A
                                        , = na_ BOOST_PP_INTERCEPT
                                        )
          >
  struct  any
        : details::any_impl<Pred,BOOST_PP_ENUM_PARAMS(NT2_MAX_META_ARITY, A)>
  {};
  #endif
} }

#endif
