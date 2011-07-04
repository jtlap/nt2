//==============================================================================
//         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_SDK_ERROR_ERROR_HPP_INCLUDED
#define BOOST_SIMD_SDK_ERROR_ERROR_HPP_INCLUDED

/*!
 * \file
 * \brief Implements NT2 exception handling system
 */

/*!
 * \defgroup error Error handling
 * \ingroup sdk
 * This module gathers macros, classes and functions to perform error handling
 * in NT2, beign at runtime or at compile-time.
 */

/*!
 * \defgroup error_config Error handling configuration
 * \ingroup error
 * This module gathers macros controling the configuration of error handling
 */

#include <boost/simd/sdk/error/details/error.hpp>

#if defined(DOXYGEN_ONLY)
//==============================================================================
/*!
 * \ingroup error_config
 * If defined, all NT2 exceptions handling code is disabled. This macro can be
 * defined manually and is triggered automatically if \c BOOST_NO_EXCEPTIONS is
 * defined or if exceptions are disabled by the compiler options.
 *
 * \see BOOST_SIMD_DISABLE_ASSERTS
 * \see BOOST_SIMD_ASSERTS_AS_EXCEPTIONS
 */
//==============================================================================
#define BOOST_SIMD_DISABLE_ERROR

//==============================================================================
/*!
 * \ingroup error
 * Throws an exception and its associated information carriers.
 *
 * \param EXCEPTION Exception to throw.
 */
//==============================================================================
#define BOOST_SIMD_THROW(EXCEPTION)

#endif

//==============================================================================
// No exception means no error unless they got requalified
//==============================================================================
#include <boost/config.hpp>

#if defined(BOOST_SIMD_DISABLE_ERROR) || defined(BOOST_NO_EXCEPTIONS)
#define BOOST_SIMD_NO_EXCEPTIONS
#endif

//==============================================================================
// Enabled errors
//==============================================================================
#if !defined(BOOST_SIMD_NO_EXCEPTIONS)
#include <boost/simd/sdk/error/details/exception.hpp>
#define BOOST_SIMD_THROW(EXP) BOOST_THROW_EXCEPTION( (EXP) ) \
/**/

//==============================================================================
// Disabled errors
//==============================================================================
#else
#define BOOST_SIMD_THROW(EXP)
#endif

#endif
