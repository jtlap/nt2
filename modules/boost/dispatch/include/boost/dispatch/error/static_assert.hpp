//==============================================================================
//         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_DISPATCH_ERROR_STATIC_ASSERT_HPP_INCLUDED
#define BOOST_DISPATCH_ERROR_STATIC_ASSERT_HPP_INCLUDED

/*!
 * \file
 * \brief Defines macros controlling the handling of compile-time assertions
 */

#include <boost/mpl/bool.hpp>
#include <boost/mpl/assert.hpp>
#include <boost/preprocessor/stringize.hpp>

#if defined(DOXYGEN_ONLY)
//==============================================================================
/*!
 * \ingroup error
 * If the static boolean expression \c COND evaluates to false, the compilation
 * is stopped and an error message is displayed by the compiler. This message
 * is built from the static error \c ID and the static error \c REASON message.
 *
 * \param COND Compile-time boolean condition to assert.
 * \param ID   A unique symbol identifying the error.
 * \param REASON a quoted string describing the reason of the error in details.
 */
//==============================================================================
#define BOOST_DISPATCH_STATIC_ASSERT(COND,ID,REASON)

//==============================================================================
/*!
 * \ingroup error
 * If the static boolean expression \c COND evaluates to true, the compilation
 * is stopped and an error message is displayed by the compiler. This message
 * is built from the static error \c ID and the static error \c REASON message.
 *
 * \param COND Compile-time boolean condition to assert.
 * \param ID   A unique symbol identifying the error.
 * \param REASON a quoted string describing the reason of the error in details.
 */
//==============================================================================
#define BOOST_DISPATCH_STATIC_ASSERT_NOT(COND,ID,REASON)
#endif

#if defined(BOOST_HAS_STATIC_ASSERT) && !defined(DOXYGEN_ONLY)
//==============================================================================
// C++0x maps over static_assert and display ID: REASON
//==============================================================================
#define BOOST_DISPATCH_STATIC_ASSERT(COND,ID,REASON)                 \
static_assert(COND, BOOST_PP_STRINGIZE(ID) ": " REASON )  \
/**/
#define BOOST_DISPATCH_STATIC_ASSERT_NOT(COND,ID,REASON)                   \
static_assert( (!(COND)), BOOST_PP_STRINGIZE(ID) ": " REASON )  \
/**/
#elif !defined(DOXYGEN_ONLY)
//==============================================================================
// C++03 maps over MPL_ASSERT_MSG and display the assert ID
//==============================================================================
#define BOOST_DISPATCH_STATIC_ASSERT(COND,ID,REASON) \
BOOST_MPL_ASSERT_MSG((COND),ID,())        \
/**/
#define BOOST_DISPATCH_STATIC_ASSERT_NOT(COND,ID,REASON) \
BOOST_MPL_ASSERT_MSG( (!(COND)),ID,())        \
/**/
#endif

#endif
