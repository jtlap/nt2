//==============================================================================
//         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_SDK_FUNCTOR_META_CALL_HPP_INCLUDED
#define NT2_SDK_FUNCTOR_META_CALL_HPP_INCLUDED

/*!
 * \file
 */

#include <boost/config.hpp>
#include <boost/tr1/functional.hpp>
#include <nt2/sdk/functor/functor.hpp>

#if !defined(BOOST_HAS_VARIADIC_TMPL)
#include <nt2/extension/parameters.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/repetition/repeat_from_to.hpp>
#endif

namespace nt2 { namespace meta
{
  //============================================================================
  /*!
   * \ref call is a \metafunction that, for a given \c Tag, \c EvalContext and
   * argument lists \c ...Args, computes the return type of
   * functor<Tag,EvalContext>::operator()(Args...).
   *
   * \param Signature function type build from Tag(Args...)
   * \param EvalContext evaluation context to use for type deduction
   *
   * \par Models:
   * \metafunction
   *
   * \par Semantics:
   * For a given \c Tag, \c EvalContext and argument lists \c ...Args,
   *
   * \code
   * typedef call<Tag(Args...),EvalContext>::type type;
   * \endcode
   *
   * is equivalent to:
   * \code
   * typedef decltype(functor<Tag,EvalContext>(declval<Args...>())) type;
   * \endcode
   */
  //============================================================================
  template<class Signature, class EvalContext = tag::cpu_> struct call {};

#if defined(BOOST_HAS_VARIADIC_TMPL)
  template<class Tag, class... Args, class Site>
  struct call<Tag(Args...),Site>
        : std::tr1::result_of<functor<Tag,Site>(Args...)>
  {};
#else
#define M0(z,n,t) \
template<class Tag, BOOST_PP_ENUM_PARAMS(n,class A), class Site> \
struct call<Tag(BOOST_PP_ENUM_PARAMS(n,A)),Site> \
: std::tr1::result_of<functor<Tag,Site>(BOOST_PP_ENUM_PARAMS(n,A))> \
{}; \
/**/

  BOOST_PP_REPEAT_FROM_TO(1,BOOST_PP_INC(NT2_MAX_ARITY),M0,~)
#undef M0
#endif
} }

#endif

