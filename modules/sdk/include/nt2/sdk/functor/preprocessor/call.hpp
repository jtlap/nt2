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
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/repetition/enum_binary_params.hpp>

//==============================================================================
/*!
 * Builds the call to result_of required to computes the return type of a
 * \ref nt2::ext::call specialization of \c N arguments.
 *
 * \param N Number of parameters for the current \ref nt2::ext::call
 *
 * \usage
 *
 * \code
 * typedef typename NT2_RETURN_TYPE(3)::type type;
 * \endcode
 */
//==============================================================================
#define NT2_RETURN_TYPE(N)                                                         \
meta::result_of<call(BOOST_PP_ENUM_BINARY_PARAMS(N,A, const& BOOST_PP_INTERCEPT))> \

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
 *   typedef typename NT2_RETURN_TYPE(3)::type type;
 *   return type(a0) + a1/a2;
 * }
 * \endcode
 */
//==============================================================================
#define NT2_FUNCTOR_CALL(N)                                     \
template<BOOST_PP_ENUM_PARAMS(N,class A)> inline                \
typename NT2_RETURN_TYPE(N)::type                               \
operator()( BOOST_PP_ENUM_BINARY_PARAMS(N,A, const& a) ) const  \
/**/

#endif
