//==============================================================================
//         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_SDK_ERROR_WARNING_HPP_INCLUDED
#define BOOST_SIMD_SDK_ERROR_WARNING_HPP_INCLUDED

/*!
 * \file
 * \brief Defines macros to output custom warning messages at compile time
 */

#include <boost/config.hpp>
#include <boost/preprocessor/stringize.hpp>

//==============================================================================
// Activate only in VERBOSE MODE
//==============================================================================
#if defined(BOOST_SIMD_VERBOSE)
#if defined(BOOST_MSVC)
//==============================================================================
// #pragma message on MSVC is very light so we add some info
//==============================================================================
#define BOOST_SIMD_WARNING_LOCATION __FILE__ "(" BOOST_PP_STRINGIZE(__LINE__) ") :"
#define BOOST_SIMD_WARN(exp) ( BOOST_SIMD_WARNING_LOCATION "[Boost.simd WARNING] -- "  BOOST_PP_STRINGIZE(exp) )
#define BOOST_SIMD_WARNING(X) __pragma( message BOOST_SIMD_WARN(X) )

#elif defined(__GNUC__)
//==============================================================================
// #pragma message on g++ just need a call to _Pragma
//==============================================================================
#define BOOST_SIMD_WARN(exp) "[Boost.simd WARNING] -- " #exp
#define BOOST_SIMD_WARNING(X) _Pragma( BOOST_PP_STRINGIZE(message BOOST_SIMD_WARN(X)) )
#endif
#else
//==============================================================================
/*!
 * \ingroup error
 * Emits a custom warning message at compile by displaying \c X in a file/line
 * localized message.
 *
 * \param MESSAGE Custom warning message
 *
 * \usage
 *
 * \include ../local.hpp
 */
//==============================================================================
#define BOOST_SIMD_WARNING(MESSAGE)
#endif

#endif
