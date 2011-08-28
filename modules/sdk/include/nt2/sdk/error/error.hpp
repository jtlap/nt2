//==============================================================================
//         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_SDK_ERROR_ERROR_HPP_INCLUDED
#define NT2_SDK_ERROR_ERROR_HPP_INCLUDED

/*!
 * \file
 * \brief Implements Boost.Dispatch exception handling system
 */

/*!
 * \defgroup error Error handling
 * \ingroup sdk
 * This module gathers macros, classes and functions to perform error handling
 * in Boost.Dispatch, beign at runtime or at compile-time.
 */

/*!
 * \defgroup error_config Error handling configuration
 * \ingroup error
 * This module gathers macros controling the configuration of error handling
 */

#include <nt2/sdk/error/details/error.hpp>

#if defined(DOXYGEN_ONLY)
//==============================================================================
/*!
 * \ingroup error_config
 * If defined, all Boost.Dispatch exceptions handling code is disabled. This macro can be
 * defined manually and is triggered automatically if \c BOOST_NO_EXCEPTIONS is
 * defined or if exceptions are disabled by the compiler options.
 *
 * \see NT2_DISABLE_ASSERTS
 * \see NT2_ASSERTS_AS_EXCEPTIONS
 */
//==============================================================================
#define NT2_DISABLE_ERROR
#endif

//==============================================================================
// No exception means no error unless they got requalified
//==============================================================================
#include <boost/config.hpp>

#if defined(NT2_DISABLE_ERROR) || defined(BOOST_NO_EXCEPTIONS)
#define NT2_NO_EXCEPTIONS
#endif

//==============================================================================
// Enabled errors
//==============================================================================
#if !defined(NT2_NO_EXCEPTIONS)
#include <nt2/sdk/error/details/exception.hpp>
#endif

#endif
