//==============================================================================
//         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_SDK_FUNCTOR_FUNCTOR_HPP_INCLUDED
#define NT2_SDK_FUNCTOR_FUNCTOR_HPP_INCLUDED

/*!
 * \file
 * \brief Implements NT2 main functor handler
 */

/*!
 * \defgroup functors Functor system
 * \ingroup sdk
 * This module gathers macros, classes and functions to define, implement
 * and specialize polymorphic functors.
 */

#include <boost/config.hpp>
#include <nt2/sdk/meta/arithmetic.hpp>
#include <nt2/sdk/meta/floating.hpp>
#include <nt2/sdk/functor/forward.hpp>
#include <nt2/sdk/error/static_assert.hpp>
#include <nt2/sdk/functor/details/call.hpp>
#include <nt2/sdk/functor/meta/enable_call.hpp>
#include <nt2/sdk/functor/details/dispatch.hpp>
#include <nt2/sdk/functor/meta/make_functor.hpp>
#include <nt2/sdk/functor/preprocessor/dispatch.hpp>
#include <nt2/sdk/meta/result_of.hpp>

#if !defined(BOOST_HAS_VARIADIC_TMPL) || !defined(NT2_DONT_USE_PREPROCESSED_FILES) || (defined(__WAVE__) && defined(NT2_CREATE_PREPROCESSED_FILES))
#include <nt2/extension/parameters.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/repetition/enum_binary_params.hpp>
#include <boost/preprocessor/repetition/enum_trailing_params.hpp>
#include <boost/preprocessor/repetition/repeat.hpp>
#include <boost/preprocessor/repetition/repeat_from_to.hpp>
#include <boost/preprocessor/punctuation/comma_if.hpp>
#include <boost/preprocessor/seq/for_each_i.hpp>
#include <boost/preprocessor/seq/for_each_product.hpp>
#include <boost/preprocessor/seq/size.hpp>
#endif

namespace nt2
{
  //============================================================================
  /*!
   * \ingroup functors
   * \ref functor is a generic, concept-dispatched polymorphic function object.
   * Every function in NT2 are defined in term of implementing a call strategy
   * for \ref functor. The main rationale is to centralize and homogenize the way
   * functions with multiple possible implementation with respect to types,
   * architectures and compilation phases are handled.
   *
   * \tparam Tag Function tag to dispatch to.
   * \tparam EvalContext Tag defining how to perform said function call with
   * respect to architecture or phase settings.
   *
   * \par Models:
   * \dco
   *
   * \see call
   * \see hierarchy
   * \see enable_call
   * \see make_functor
   */
  //============================================================================
  template<class Tag, class EvalContext> struct functor
  {
    template<class Sig> struct result;

    #if (defined(BOOST_HAS_VARIADIC_TMPL) && !defined(__WAVE__)) || defined(DOXYGEN_ONLY)
    template<class This, class... Args>
    struct  result<This(Args...)>
    {
      typedef typename meta::dispatch_call<Tag(Args...),EvalContext>::type callee;
      typedef typename meta::result_of<callee(Args...)>::type   type;
    };

    //==========================================================================
    /*!
     * Polymorphic variadic function call operator. This catch-all operators
     * dispatches its arguments to the proper type and architecture based
     * implementation using the \ref hierarchy system.
     *
     * \params args Arguments of function \c Tag implementation
     * \return The result of the calculation of function \c Tag
     */
    //==========================================================================
    template<class... Args> inline typename result<functor(Args...)>::type
    operator()( Args const& ...args ) const
    {
      typename meta::dispatch_call<Tag(Args...),EvalContext>::type callee;
      return callee( args... );
    }
    #else

#if !defined(NT2_DONT_USE_PREPROCESSED_FILES)
#include <nt2/sdk/functor/preprocessed/functor.hpp>
#else
#if defined(__WAVE__) && defined(NT2_CREATE_PREPROCESSED_FILES)
#pragma wave option(preserve: 2, line: 0, output: "preprocessed/functor.hpp")
#endif

    #define param(r,_,i,b) BOOST_PP_COMMA_IF(i)                               \
    BOOST_PP_CAT(A,i) BOOST_PP_CAT(c,b) & BOOST_PP_CAT(a,i)
               
    #define c0
    #define c1 const
    #define bits(z, n, _) ((0)(1))
    #define n_size(seq) BOOST_PP_SEQ_SIZE(seq)
    
    #define call_operator(r, constness)                                       \
    template<BOOST_PP_ENUM_PARAMS(n_size(constness),class A)> inline          \
    typename meta::enable_call< Tag(BOOST_PP_ENUM_PARAMS(n_size(constness),A))\
                              , EvalContext>::type                            \
    operator()(BOOST_PP_SEQ_FOR_EACH_I_R(r,param,~,constness)) const          \
    {                                                                         \
      typename                                                                \
      meta::dispatch_call<Tag(BOOST_PP_ENUM_PARAMS(n_size(constness),A))      \
                         ,EvalContext                                         \
                         >::type                                              \
      callee;                                                                 \
      return callee( BOOST_PP_ENUM_PARAMS(n_size(constness),a) );             \
    }                                                                         \
    /**/

    #define M0(z,n,t)                                                         \
    template<class This, BOOST_PP_ENUM_PARAMS(n,class A) >                    \
    struct result<This(BOOST_PP_ENUM_PARAMS(n,A))>                            \
    {                                                                         \
      typedef typename                                                        \
      meta::dispatch_call<Tag(BOOST_PP_ENUM_PARAMS(n,A)),EvalContext>::type   \
                                                                    callee;   \
      typedef typename                                                        \
      meta::result_of<callee(BOOST_PP_ENUM_PARAMS(n,A))>::type  type;         \
    };                                                                        \
                                                                              \
    BOOST_PP_SEQ_FOR_EACH_PRODUCT_R(                                          \
        z,                                                                    \
        call_operator                                                         \
      , BOOST_PP_REPEAT(n, bits, ~)                                           \
    )                                                                         \
    /**/

    BOOST_PP_REPEAT_FROM_TO(1,BOOST_PP_INC(NT2_MAX_ARITY),M0,~)    
    #undef M0
    #undef bits
    #undef n_size
    #undef c1
    #undef c0
    #undef param
    #undef call_operator
    
#if defined(__WAVE__) && defined(NT2_CREATE_PREPROCESSED_FILES)
#pragma wave option(output: null)
#endif
#endif

    #endif
    };
}

#endif
