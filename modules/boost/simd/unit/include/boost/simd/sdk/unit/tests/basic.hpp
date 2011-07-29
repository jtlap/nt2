//==============================================================================
//         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_SDK_UNIT_TESTS_BASIC_HPP_INCLUDED
#define BOOST_SIMD_SDK_UNIT_TESTS_BASIC_HPP_INCLUDED

/*!
 * \file
 * \brief Unit Test macros for basic checks and forced failure
 */

#include <boost/simd/sdk/unit/details/stats.hpp>

//==============================================================================
/*!
 * \ingroup utests
 * Checks if an expression to true and then raise the failure count if not.
 * \param X Expression to check
 */
//==============================================================================
#define BOOST_SIMD_TEST(X)                                                 \
( ::boost::simd::details::test_count()++                                    \
, (X) ? ::boost::simd::details::pass(#X)                                    \
      : ::boost::simd::details::fail(#X, __LINE__, BOOST_CURRENT_FUNCTION)  \
)                                                                   \
/**/

//==============================================================================
/*!
 * \ingroup utests
 * Emit a strong error message and raise the failure count
 * \param X Error message to display
 */
//==============================================================================
#define BOOST_SIMD_TEST_ERROR(X)                                   \
::boost::simd::details::error(X, __LINE__, BOOST_CURRENT_FUNCTION)  \
/**/

#endif
