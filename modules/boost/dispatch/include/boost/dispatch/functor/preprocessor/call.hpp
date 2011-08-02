/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef BOOST_DISPATCH_FUNCTOR_PREPROCESSOR_CALL_HPP_INCLUDED
#define BOOST_DISPATCH_FUNCTOR_PREPROCESSOR_CALL_HPP_INCLUDED

/*!
 * \file
 * \brief Defines macros for building a \ref boost::dispatch::ext::call specialization
 */

#include <boost/dispatch/meta/result_of.hpp>
#include <boost/dispatch/functor/preprocessor/dispatch.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/repetition/enum_binary_params.hpp>

//==============================================================================
/*!
 * Generates a \ref boost::dispatch::ext::call specialization \c operator() prototype.
 * In this function, arguments are defined as \c a0,...,an-1.
 *
 * \param N Number of parameters for the current \ref boost::dispatch::ext::call
 *
 * \usage
 *
 * \code
 * BOOST_DISPATCH_FUNCTOR_CALL(3)
 * {
 *   return a0 + a1/a2;
 * }
 * \endcode
 */
//==============================================================================
#define BOOST_DISPATCH_FUNCTOR_CALL(N)                                                       \
inline result_type operator()( BOOST_PP_ENUM_BINARY_PARAMS(N,A,const& a) ) const  \
/**/

//==============================================================================
/*!
 * Generates a \ref boost::dispatch::ext::call specialization \c operator() prototype.
 * In this function, arguments are defined as \c a0,...,an-1 of the same type
 * \c A0.
 *
 * \param N Number of parameters for the current \ref boost::dispatch::ext::call
 *
 * \usage
 *
 * \code
 * BOOST_DISPATCH_FUNCTOR_CALL_REPEAT(3)
 * {
 *   return a0 + a1/a2;
 * }
 * \endcode
 */
//==============================================================================
#define BOOST_DISPATCH_FUNCTOR_CALL_REPEAT(N)                                          \
inline result_type operator()( BOOST_PP_ENUM_PARAMS(N,A0 const& a) ) const  \
/**/

#define BOOST_DISPATCH_FUNCTOR_IMPLEMENTATION(NS,Tag,Site,Types,Seq)                 \
BOOST_DISPATCH_REGISTER_DISPATCH(NS,Tag,Site,Types,Seq)                              \
template< BOOST_PP_ENUM(BOOST_PP_SEQ_SIZE(Types),BOOST_DISPATCH_DISPATCH_TYPE,Types) \
        , class Dummy                                                     \
        >                                                                 \
struct  implement                                                         \
        < BOOST_DISPATCH_PP_STRIP(Tag)(BOOST_PP_ENUM ( BOOST_PP_SEQ_SIZE(Seq)        \
                                      , BOOST_DISPATCH_DISPATCH_TAG,Seq)             \
                                      )                                   \
        , Site, Dummy                                                     \
        >                                                                 \
/**/

#define BOOST_DISPATCH_FUNCTOR_IMPLEMENTATION_TPL(NS,Tag,Site,Types,Seq)                 \
BOOST_DISPATCH_REGISTER_DISPATCH_TPL(NS,Tag,Site,Types,Seq)                              \
template< BOOST_PP_ENUM(BOOST_PP_SEQ_SIZE(Types),BOOST_DISPATCH_DISPATCH_TYPE_TPL,Types) \
        , class Dummy                                                         \
        >                                                                     \
struct  implement                                                             \
        < BOOST_DISPATCH_PP_STRIP(Tag)(BOOST_PP_ENUM ( BOOST_PP_SEQ_SIZE(Seq)            \
                                          , BOOST_DISPATCH_DISPATCH_TAG,Seq)             \
                                          )                                   \
        , Site, Dummy                                                         \
        >                                                                     \
/**/

#define BOOST_DISPATCH_FUNCTOR_IMPLEMENTATION_IF(NS,Tag,Site,Types,Cond,Ret,Seq)     \
BOOST_DISPATCH_REGISTER_DISPATCH_IF(NS,Tag,Site,Types,Cond,Ret,Seq)                  \
template< BOOST_PP_ENUM(BOOST_PP_SEQ_SIZE(Types),BOOST_DISPATCH_DISPATCH_TYPE,Types) \
        , class Dummy                                                     \
        >                                                                 \
struct  implement<BOOST_DISPATCH_PP_STRIP(Ret),Site,Dummy>                           \
/**/

#endif
