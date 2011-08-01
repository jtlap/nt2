//==============================================================================
//         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_SDK_ERROR_ASSERT_HPP_INCLUDED
#define BOOST_SIMD_SDK_ERROR_ASSERT_HPP_INCLUDED

/*!
 * \file
 * \brief Defines macros and functions controlling runtime assertions
 */
#include <boost/simd/sdk/error/debug.hpp>

#if defined(DOXYGEN_ONLY)
//==============================================================================
/*!
 * \ingroup error_config
 * If \c BOOST_SIMD_DISABLE_ASSERTS is defined, all runtime assertion are disabled.
 * Note than defining \c BOOST_DISABLE_ASSERTS triggers this definition.
 *
 * \see BOOST_SIMD_DISABLE_ERROR
 * \see BOOST_SIMD_ASSERTS_AS_EXCEPTIONS
 */
//==============================================================================
#define BOOST_SIMD_DISABLE_ASSERTS
#endif

//==============================================================================
// Include assert and forward the macro
//==============================================================================
#ifndef BOOST_SIMD_DISABLE_ASSERTS

#include <boost/assert.hpp>

//==============================================================================
/*!
 * \ingroup error
 * If BOOST_SIMD_DISABLE_ASSERTS is not defined, evaluates \c XPR and, if \c XPR
 * evaluates to \c false, trigger a runtime assertion failure. If not, no
 * operationsa re performed.
 *
 * \param XPR Expression to assert.
 */
//==============================================================================
#define BOOST_SIMD_ASSERT(XPR) BOOST_ASSERT(XPR)

//==============================================================================
/*!
 * \ingroup error
 * Evaluates \c XPR and, if \c XPR evaluates to \c false, trigger a runtime
 * assertion failure if and only if BOOST_SIMD_DISABLE_ASSERTS is not defined
 *
 * \param XPR Expression to verify.
 */
//==============================================================================
#define BOOST_SIMD_VERIFY(XPR) BOOST_VERIFY(XPR)
#else

#define BOOST_SIMD_ASSERT(XPR)
#define BOOST_SIMD_VERIFY(XPR)

#endif

#endif
