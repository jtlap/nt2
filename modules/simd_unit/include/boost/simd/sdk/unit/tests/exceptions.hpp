//==============================================================================
//         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_SDK_UNIT_TESTS_EXCEPTIONS_HPP_INCLUDED
#define BOOST_SIMD_SDK_UNIT_TESTS_EXCEPTIONS_HPP_INCLUDED

/*!
 * \file
 * \brief Unit Test macros for exception conformance checks
 */

#include <boost/simd/sdk/unit/details/stats.hpp>

//==============================================================================
/*!
 * \ingroup utests
 * Checks if an expression throws a given exception at evaluation and raise the
 * failure count if not.
 * \param X Expression to check
 * \param E Exception expected to be caught
 */
//==============================================================================
#define BOOST_SIMD_TEST_THROW(X,E)                                                 \
do {                                                                        \
  ::boost::simd::details::test_count()++;                                           \
  bool catched = false;                                                     \
  try             { X; }                                                    \
  catch( E& ex )  { ::boost::simd::details::pass(#X); catched = true; }             \
  catch(...)      {}                                                        \
  if(!catched) ::boost::simd::details::fail(#X, __LINE__, BOOST_CURRENT_FUNCTION);  \
} while(0)                                                                  \
/**/


//==============================================================================
/*!
 * \ingroup utests
 * Checks if an expression evaluates without throwing any exception and raise
 * the failure count if not.
 * \param X Expression to check
 */
//==============================================================================
#define BOOST_SIMD_TEST_NO_THROW(X)                                                \
do {                                                                        \
  ::boost::simd::details::test_count()++;                                           \
  try         { X; }                                                        \
  catch(...)  { ::boost::simd::details::fail(#X, __LINE__, BOOST_CURRENT_FUNCTION); \
  ::boost::simd::details::pass(#X);                                                 \
} while(0)                                                                  \
/**/

#endif
