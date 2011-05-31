//==============================================================================
//         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_SDK_FUNCTOR_META_ENABLE_CALL_HPP_INCLUDED
#define NT2_SDK_FUNCTOR_META_ENABLE_CALL_HPP_INCLUDED

/*!
 * \file
 * \brief Defiens and implements functor conformance checking \metafunction
 */

#include <boost/config.hpp>
#include <boost/tr1/functional.hpp>
#include <boost/utility/result_of.hpp>
#include <nt2/sdk/meta/enable_if_type.hpp>
#include <boost/function_types/result_type.hpp>

#if !defined(BOOST_HAS_VARIADIC_TMPL)
#include <nt2/extension/parameters.hpp>
#include <boost/preprocessor/repetition/repeat_from_to.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#endif

namespace nt2 { namespace details
{
  //==============================================================================
  // This helper structure is here to make MSVC compile our code
  //==============================================================================
  template<typename T> struct callable_type
  {
    typedef typename T::callable_type type;
  };
} }

namespace nt2 { namespace meta
{
  //==============================================================================
  /*!
   * \ref enable_call is a Boolean \metafunction that, for a given \c Tag,
   * \c EvalContext and argument lists \c ...Args, computes the if the call to
   * functor<Tag,EvalContext>::operator()(Args...) is supported.
   *
   * \param Sig  function type build from Tag(Args...)
   * \param EvalContext evaluation context to use for type deduction
   *
   * \par Models:
   * \metafunction
   *
   * \par Semantics:
   * For a given \c Tag, \c EvalContext and argument lists \c ...Args,
   *
   * \code
   * typedef enable_call<Tag(Args...),EvalContext>::type type;
   * \endcode
   *
   * is equivalent \c boost::mpl::true_ if an implementation of \c ext::call
   * for \c Tag(Args...) exists for said \c EvalContext
   */
  //==============================================================================
  template< class Sig
          , class EvalContext = typename
                                default_site< typename  boost::function_types::
                                                        result_type<Sig>::type
                                            >::type
          , class Enable  = void
          >
  struct enable_call
  {};

  #if defined(BOOST_HAS_VARIADIC_TMPL)
  template<class F, class Site, class... Args>
  struct enable_call< F(Args...), Site
                    , typename
                      enable_if_type<
                        typename details::
                        callable_type< typename
                                       dispatch_call < F(Args...)
                                                     , Site
                                                     >::type
                                     >::type
                                    >::type
                    >
    : std::tr1::result_of<functor<F,Site>(Args...)>
  {};
  #else

  #define M0(z,n,t)                                                                   \
  template<class F, class Site, BOOST_PP_ENUM_PARAMS(n,class A)>                      \
  struct  enable_call < F(BOOST_PP_ENUM_PARAMS(n,A))                                  \
                      , Site                                                          \
                      , typename                                                      \
                        enable_if_type<                                               \
                          typename details::                                          \
                          callable_type < typename                                    \
                                          dispatch_call< F(BOOST_PP_ENUM_PARAMS(n,A)) \
                                                       , Site                         \
                                                       >::type                        \
                                        >::type                                       \
                                      >::type                                         \
                      >                                                               \
        : std::tr1::result_of<functor<F,Site>(BOOST_PP_ENUM_PARAMS(n,A))>             \
  {};                                                                                 \
  /**/

  BOOST_PP_REPEAT_FROM_TO(1,BOOST_PP_INC(NT2_MAX_ARITY),M0,~)
  #undef M0

  #endif
} }

#endif
