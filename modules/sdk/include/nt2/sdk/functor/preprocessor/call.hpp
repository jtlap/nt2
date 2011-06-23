/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_SDK_FUNCTOR_PREPROCESSOR_CALL_HPP_INCLUDED
#define NT2_SDK_FUNCTOR_PREPROCESSOR_CALL_HPP_INCLUDED

/*!
 * \file
 * \brief Defines macros for building a \ref nt2::ext::call specialization
 */

#include <nt2/sdk/meta/result_of.hpp>
#include <nt2/sdk/functor/preprocessor/dispatch.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/repetition/enum_binary_params.hpp>

//==============================================================================
/*!
 * Generates a \ref nt2::ext::call specialization \c operator() prototype.
 * In this function, arguments are defined as \c a0,...,an-1.
 *
 * \param N Number of parameters for the current \ref nt2::ext::call
 *
 * \usage
 *
 * \code
 * NT2_FUNCTOR_CALL(3)
 * {
 *   return a0 + a1/a2;
 * }
 * \endcode
 */
//==============================================================================
#define NT2_FUNCTOR_CALL(N)                                                       \
inline result_type operator()( BOOST_PP_ENUM_BINARY_PARAMS(N,A,const& a) ) const  \
/**/

//==============================================================================
/*!
 * Generates a \ref nt2::ext::call specialization \c operator() prototype.
 * In this function, arguments are defined as \c a0,...,an-1 of the same type
 * \c A0.
 *
 * \param N Number of parameters for the current \ref nt2::ext::call
 *
 * \usage
 *
 * \code
 * NT2_FUNCTOR_CALL_REPEAT(3)
 * {
 *   return a0 + a1/a2;
 * }
 * \endcode
 */
//==============================================================================
#define NT2_FUNCTOR_CALL_REPEAT(N)                                          \
inline result_type operator()( BOOST_PP_ENUM_PARAMS(N,A0 const& a) ) const  \
/**/

#define NT2_FUNCTOR_IMPLEMENTATION(Tag,Site,Types,Seq)                    \
NT2_REGISTER_DISPATCH(Tag,Site,Types,Seq)                                 \
template< BOOST_PP_ENUM(BOOST_PP_SEQ_SIZE(Types),NT2_DISPATCH_TYPE,Types) \
        , class Dummy                                                     \
        >                                                                 \
struct  implement                                                         \
        < NT2_PP_STRIP(Tag)(BOOST_PP_ENUM ( BOOST_PP_SEQ_SIZE(Seq)        \
                                      , NT2_DISPATCH_TAG,Seq)             \
                                      )                                   \
        , Site, Dummy                                                     \
        >                                                                 \
/**/

#define NT2_FUNCTOR_IMPLEMENTATION_TPL(Tag,Site,Types,Seq)                    \
NT2_REGISTER_DISPATCH_TPL(Tag,Site,Types,Seq)                                 \
template< BOOST_PP_ENUM(BOOST_PP_SEQ_SIZE(Types),NT2_DISPATCH_TYPE_TPL,Types) \
        , class Dummy                                                         \
        >                                                                     \
struct  implement                                                             \
        < NT2_PP_STRIP(Tag)(BOOST_PP_ENUM ( BOOST_PP_SEQ_SIZE(Seq)            \
                                          , NT2_DISPATCH_TAG,Seq)             \
                                          )                                   \
        , Site, Dummy                                                         \
        >                                                                     \
/**/

#define NT2_FUNCTOR_IMPLEMENTATION_IF(Tag,Site,Types,Cond,Ret,Seq)        \
NT2_REGISTER_DISPATCH_IF(Tag,Site,Types,Cond,Ret,Seq)                     \
template< BOOST_PP_ENUM(BOOST_PP_SEQ_SIZE(Types),NT2_DISPATCH_TYPE,Types) \
        , class Dummy                                                     \
        >                                                                 \
struct  implement<NT2_PP_STRIP(Ret),Site,Dummy>                           \
/**/

#endif
