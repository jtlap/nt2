//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_DISPATCH_FUNCTOR_FUNCTOR_HPP_INCLUDED
#define BOOST_DISPATCH_FUNCTOR_FUNCTOR_HPP_INCLUDED

/*!
 * \file
 * \brief Implements Boost.Dispatch main functor handler
 */

/*!
 * \defgroup functors Functor system
 * \ingroup sdk
 * This module gathers macros, classes and functions to define, implement
 * and specialize polymorphic functors.
 */

#include <boost/config.hpp>
#include <boost/dispatch/meta/arithmetic.hpp>
#include <boost/dispatch/meta/floating.hpp>
#include <boost/dispatch/meta/as_ref.hpp>
#include <boost/dispatch/functor/forward.hpp>
#include <boost/dispatch/functor/details/call.hpp>
#include <boost/dispatch/functor/details/dispatch.hpp>
#include <boost/dispatch/functor/meta/make_functor.hpp>
#include <boost/dispatch/functor/preprocessor/dispatch.hpp>
#include <boost/dispatch/functor/meta/call.hpp>
#include <boost/dispatch/attributes.hpp>

#if ((defined(BOOST_NO_VARIADIC_TEMPLATES) || defined(BOOST_NO_RVALUE_REFERENCES)) \
 && defined(BOOST_DISPATCH_DONT_USE_PREPROCESSED_FILES)) || defined(BOOST_DISPATCH_CREATE_PREPROCESSED_FILES)
#include <boost/dispatch/details/parameters.hpp>
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

namespace boost { namespace dispatch
{
  //============================================================================
  /*!
   * \ingroup functors
   * \ref functor is a generic, concept-dispatched polymorphic function object.
   * Every function in Boost.Dispatch are defined in term of implementing a call strategy
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
   * \see make_functor
   */
  //============================================================================
  template<class Tag, class EvalContext> struct functor
  {
    template<class Sig> struct result;

    #if (   !defined(BOOST_NO_VARIADIC_TEMPLATES)   \
        &&  !defined(BOOST_NO_RVALUE_REFERENCES)    \
        &&  !defined(BOOST_DISPATCH_CREATE_PREPROCESSED_FILES) \
        )                                           \
        || defined(DOXYGEN_ONLY)
    template<class This, class... Args>
    struct result<This(Args...)>
      : meta::
        result_of< typename meta::
                   dispatch_call< Tag(Args...)
                                , EvalContext
                                >::type(Args...)
                 >
    {};

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
    template<class... Args> BOOST_FORCEINLINE
    typename result<functor(Args...)>::type
    operator()( Args&& ...args ) const
    {
      return meta::dispatch( Tag(), EvalContext()
                           , static_cast<typename meta::as_ref<Args>::type>(args)... )
                           ( static_cast<typename meta::as_ref<Args>::type>(args)... );
    }
    #elif !defined(BOOST_NO_RVALUE_REFERENCES) && !defined(BOOST_DISPATCH_CREATE_PREPROCESSED_FILES_NO_0X)
    
#if !defined(BOOST_DISPATCH_DONT_USE_PREPROCESSED_FILES)
#include <boost/dispatch/functor/preprocessed/functor0x.hpp>
#else
#if defined(__WAVE__) && defined(BOOST_DISPATCH_CREATE_PREPROCESSED_FILES) && __INCLUDE_LEVEL__ == 0
#pragma wave option(preserve: 2, line: 0, output: "preprocessed/functor0x.hpp")
#undef BOOST_FORCEINLINE
#endif

    #define M1(z,n,t) static_cast<typename meta::as_ref<A##n>::type>(a##n)

    #define M0(z,n,t)                                                         \
    template<class This, BOOST_PP_ENUM_PARAMS(n,class A) >                    \
    struct result<This(BOOST_PP_ENUM_PARAMS(n,A))>                            \
      : meta::                                                                \
        result_of< typename meta::                                            \
                   dispatch_call< Tag(BOOST_PP_ENUM_PARAMS(n,A))              \
                                , EvalContext                                 \
                                >::type(BOOST_PP_ENUM_PARAMS(n,A))            \
                 >                                                            \
    {};                                                                       \
                                                                              \
    template<BOOST_PP_ENUM_PARAMS(n,class A)> BOOST_FORCEINLINE               \
    typename result<functor(BOOST_PP_ENUM_PARAMS(n,A))>::type                 \
    operator()(BOOST_PP_ENUM_BINARY_PARAMS(n, A, && a)) const                 \
    {                                                                         \
      return meta::dispatch( Tag(), EvalContext()                             \
                           , BOOST_PP_ENUM(n, M1, ~) )                        \
                           ( BOOST_PP_ENUM(n, M1, ~) );                       \
    }                                                                         \
    /**/

    BOOST_PP_REPEAT_FROM_TO(1,BOOST_PP_INC(BOOST_DISPATCH_MAX_ARITY),M0,~)
    #undef M0
    #undef M1

#if defined(__WAVE__) && defined(BOOST_DISPATCH_CREATE_PREPROCESSED_FILES)
#pragma wave option(output: null)
#endif
#endif
    
#else

#if !defined(BOOST_DISPATCH_DONT_USE_PREPROCESSED_FILES)
#include <boost/dispatch/functor/preprocessed/functor.hpp>
#else
#if defined(__WAVE__) && defined(BOOST_DISPATCH_CREATE_PREPROCESSED_FILES) && __INCLUDE_LEVEL__ == 0
#pragma wave option(preserve: 2, line: 0, output: "preprocessed/functor.hpp")
#undef BOOST_FORCEINLINE
#endif

    #define param(r,_,i,b) BOOST_PP_COMMA_IF(i)                               \
    BOOST_PP_CAT(A,i) BOOST_PP_CAT(c,b) & BOOST_PP_CAT(a,i)                   \
    /**/

    #define arg_type(r,_,i,b) BOOST_PP_COMMA_IF(i) BOOST_PP_CAT(A,i) BOOST_PP_CAT(c,b) &
               
    #define c0
    #define c1 const
    #define bits(z, n, _) ((0)(1))
    #define n_size(seq) BOOST_PP_SEQ_SIZE(seq)
    
    #define call_operator(r, constness)                                       \
    template<BOOST_PP_ENUM_PARAMS(n_size(constness),class A)> BOOST_FORCEINLINE \
    typename result < functor                                                 \
                      (BOOST_PP_SEQ_FOR_EACH_I_R(r,arg_type,~,constness))     \
                    >::type                                                   \
    operator()(BOOST_PP_SEQ_FOR_EACH_I_R(r,param,~,constness)) const          \
    {                                                                         \
      return meta::dispatch ( Tag(),EvalContext()                             \
                            , BOOST_PP_ENUM_PARAMS(n_size(constness),a)       \
                            )                                                 \
                            ( BOOST_PP_ENUM_PARAMS(n_size(constness),a) );    \
    }                                                                         \
    /**/

    #define M0(z,n,t)                                                         \
    template<class This, BOOST_PP_ENUM_PARAMS(n,class A) >                    \
    struct result<This(BOOST_PP_ENUM_PARAMS(n,A))>                            \
      : meta::                                                                \
        result_of< typename meta::                                            \
                   dispatch_call< Tag(BOOST_PP_ENUM_PARAMS(n,A))              \
                                , EvalContext                                 \
                                >::type(BOOST_PP_ENUM_PARAMS(n,A))            \
                 >                                                            \
    {};                                                                       \
                                                                              \
    BOOST_PP_SEQ_FOR_EACH_PRODUCT_R(                                          \
        z,                                                                    \
        call_operator                                                         \
      , BOOST_PP_REPEAT(n, bits, ~)                                           \
    )                                                                         \
    /**/

    BOOST_PP_REPEAT_FROM_TO(1,BOOST_PP_INC(BOOST_DISPATCH_MAX_ARITY),M0,~)    

    #undef M0
    #undef bits
    #undef n_size
    #undef c1
    #undef c0
    #undef param2
    #undef param
    #undef call_operator
    
#if defined(__WAVE__) && defined(BOOST_DISPATCH_CREATE_PREPROCESSED_FILES)
#pragma wave option(output: null)
#endif
#endif

    #endif
    };
} }

#endif
