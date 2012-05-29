//==============================================================================
//         Copyright 2003 - 2012 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_SDK_UNIT_TESTS_RELATION_HPP_INCLUDED
#define NT2_SDK_UNIT_TESTS_RELATION_HPP_INCLUDED

/*!
  @file
  @brief Logical comparison testing macros
**/

#include <nt2/sdk/unit/stats.hpp>
#include <nt2/sdk/unit/details/test_func.hpp>
#include <nt2/include/functions/compare_equal.hpp>
#include <nt2/include/functions/compare_not_equal.hpp>
#include <nt2/include/functions/compare_less.hpp>
#include <nt2/include/functions/compare_less_equal.hpp>
#include <nt2/include/functions/compare_greater.hpp>
#include <nt2/include/functions/compare_greater_equal.hpp>

/*!
  @brief Check the equality of two values

  For any two given expressions @c A and @c B, consider the test successful if
  and only if @c A @c == @c B evaluates to @c true.

  @usage
  @include test_equal.cpp
**/
#define NT2_TEST_EQUAL(A,B)                                                   \
( ::nt2::details::test_eq(#A, #B , __LINE__, BOOST_CURRENT_FUNCTION, A, B) )  \
/**/


/*!
  @brief Check the inequality of two values

  For any two given expressions @c A and @c B, consider the test successful if
  and only if @c A @c != @c B evaluates to @c true.

  @usage
  @include test_not_equal.cpp
**/
#define NT2_TEST_NOT_EQUAL(A,B)                                               \
( ::nt2::details::test_neq(#A, #B , __LINE__, BOOST_CURRENT_FUNCTION, A, B) ) \
/**/

/*!
  @brief Check the ordering of two values

  For any two given expressions @c A and @c B, consider the test successful if
  and only if @c A @c < @c B evaluates to @c true.

  @usage
  @include test_lesser.cpp
**/
#define NT2_TEST_LESSER(A,B)                                                  \
( ::nt2::details::test_lt(#A, #B , __LINE__, BOOST_CURRENT_FUNCTION, A, B) )  \
/**/

/*!
  @brief Check the ordering of two values

  For any two given expressions @c A and @c B, consider the test successful if
  and only if @c A @c > @c B evaluates to @c true.

  @usage
  @include test_greater.cpp
**/
#define NT2_TEST_GREATER(A,B)                                                 \
( ::nt2::details::test_gt(#A, #B , __LINE__, BOOST_CURRENT_FUNCTION, A, B) )  \
/**/

/*!
  @brief Check the ordering of two values

  For any two given expressions @c A and @c B, consider the test successful if
  and only if @c A @c <= @c B evaluates to @c true.

  @usage
  @include test_lesser_equal.cpp
**/
#define NT2_TEST_LESSER_EQUAL(A,B)                                           \
( ::nt2::details::test_le(#A, #B , __LINE__, BOOST_CURRENT_FUNCTION, A, B) ) \
/**/


/*!
  @brief Check the ordering of two values

  For any two given expressions @c A and @c B, consider the test successful if
  and only if @c A @c >= @c B evaluates to @c true.

  @usage
  @include test_greater_equal.cpp
**/
#define NT2_TEST_GREATER_EQUAL(A,B)                                           \
( ::nt2::details::test_ge(#A, #B , __LINE__, BOOST_CURRENT_FUNCTION, A, B) )  \
/**/

#endif
