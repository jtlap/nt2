//==============================================================================
//         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_DISPATCH_DETAILS_PREPROCESSOR_HPP_INCLUDED
#define BOOST_DISPATCH_DETAILS_PREPROCESSOR_HPP_INCLUDED

#include <boost/preprocessor/stringize.hpp>
#include <boost/preprocessor/repetition/enum.hpp>
#include <boost/preprocessor/repetition/enum_shifted.hpp>
#include <boost/preprocessor/detail/is_unary.hpp>
#include <boost/preprocessor/control/iif.hpp>
#include <boost/preprocessor/tuple/eat.hpp>
#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/expand.hpp>

/*!
 * \file
 * \brief Defines some short-cut for frequently used PP macros
 */

/*!
 * \defgroup preprocessor Preprocessor Utilities
 * \ingroup sdk
 *
 * This module gathers frequently used preprocessor macros and macros functions
 * that extend Boost.Preprocessor features in Boost.Dispatch context.
 */

//==============================================================================
/*!
 * \ingroup preprocessor
 * Evaluates a macros into a printable string for debugging purpose.
 *
 * \param MACRO Macro to expand
 */
//==============================================================================
#define BOOST_DISPATCH_PP_DEBUG(MACRO) BOOST_PP_STRINGIZE( (MACRO) )

//==============================================================================
// Enumeration macro for index and value. Used internally
//==============================================================================
#define BOOST_DISPATCH_PP_INDEX(z,n,t)             n
#define BOOST_DISPATCH_PP_TEXT(z,n,t)              t

//==============================================================================
/*!
 * \ingroup preprocessor
 * Evaluates as the comma separated enumeration of \c N times the symbol \c V.
 *
 * \param N Number of iterations to generate
 * \param V Symbol to replicate
 *
 * \par Example Usage:
 *
 * \include pp_enum_value.cpp
 *
 * This produces the folowing output
 * \code (6 , 6 , 6 , 6 , 6) \endcode
 */
//==============================================================================
#define BOOST_DISPATCH_PP_ENUM_VALUE(N,V)          BOOST_PP_ENUM(N,BOOST_DISPATCH_PP_TEXT,V)

//==============================================================================
/*!
 * \ingroup preprocessor
 * Evaluates as a string usuable as a valid include directive.by concatenating
 * a base root \c PATH to a \c FILE. Both \c PATH and \c FILE can actually be
 * macros, thus creating the effect of a programmable include directive.
 *
 * \param PATH Root path to the file to include
 * \param FILE File to include
 *
 * \par Example Usage:
 *
 * \include pp_include.cpp
 */
//==============================================================================
#define BOOST_DISPATCH_PP_INCLUDE(PATH,FILE) BOOST_PP_STRINGIZE(PATH()FILE)

#endif
