//==============================================================================
//         Copyright 2003 - 2012 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012        MetaScale SAS
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

#include <iomanip>
#include <iostream>
#include <nt2/sdk/unit/stats.hpp>
#include <nt2/sdk/unit/details/eval.hpp>
#include <nt2/sdk/unit/details/test_for_equality.hpp>
#include <boost/current_function.hpp>

/// INTERNAL ONLY - Base macro for relation checks
#define NT2_TEST_FUNC(A,B,OP)                         \
do                                                    \
{                                                     \
  nt2::unit::test_count()++;                          \
  if( nt2::unit::eval(A) OP nt2::unit::eval(B) )      \
  {                                                   \
    nt2::unit::pass(#A " " #OP " " #B);               \
  }                                                   \
  else                                                \
  {                                                   \
    nt2::unit::fail ( #A " " #OP " " #B               \
                    , __LINE__,BOOST_CURRENT_FUNCTION \
                    );                                \
    std::setprecision(20);                            \
    std::cout << #A << ": \n" << (A) << std::endl;    \
    std::cout << #B << ": \n" << (B) << std::endl;    \
  }                                                   \
} while(0)                                            \
/**/

/*!
  @brief Check the equality of two values

  For any two given expressions @c A and @c B, consider the test successful if
  and only if @c A @c == @c B evaluates to @c true.

  @usage
  @include test_equal.cpp
**/
#define NT2_TEST_EQUAL(A,B)                             \
do                                                      \
{                                                       \
  nt2::unit::test_count()++;                            \
  if( nt2::unit::test_for_equality( nt2::unit::eval(A)  \
                                  , nt2::unit::eval(B)  \
                                  )                     \
    )                                                   \
  {                                                     \
    nt2::unit::pass(#A " == " #B);                      \
  }                                                     \
  else                                                  \
  {                                                     \
    nt2::unit::fail ( #A " == " #B                      \
                    , __LINE__,BOOST_CURRENT_FUNCTION   \
                    );                                  \
    std::setprecision(20);                              \
    std::cout << #A << ": \n" << (A) << std::endl;      \
    std::cout << #B << ": \n" << (B) << std::endl;      \
  }                                                     \
} while(0)                                              \
/**/

/*!
  @brief Check the inequality of two values

  For any two given expressions @c A and @c B, consider the test successful if
  and only if @c A @c != @c B evaluates to @c true.

  @usage
  @include test_not_equal.cpp
**/
#define NT2_TEST_NOT_EQUAL(A,B)                           \
do                                                        \
{                                                         \
  nt2::unit::test_count()++;                              \
  if( !nt2::unit::test_for_equality ( nt2::unit::eval(A)  \
                                    , nt2::unit::eval(B)  \
                                    )                     \
    )                                                     \
  {                                                       \
    nt2::unit::pass(#A " != " #B);                        \
  }                                                       \
  else                                                    \
  {                                                       \
    nt2::unit::fail ( #A " != " #B                        \
                    , __LINE__,BOOST_CURRENT_FUNCTION     \
                    );                                    \
    std::setprecision(20);                                \
    std::cout << #A << ": \n" << (A) << std::endl;        \
    std::cout << #B << ": \n" << (B) << std::endl;        \
  }                                                       \
} while(0)                                                \
/**/

/*!
  @brief Check the ordering of two values

  For any two given expressions @c A and @c B, consider the test successful if
  and only if @c A @c < @c B evaluates to @c true.

  @usage
  @include test_lesser.cpp
**/
#define NT2_TEST_LESSER(A,B) NT2_TEST_FUNC(A,B,<)

/*!
  @brief Check the ordering of two values

  For any two given expressions @c A and @c B, consider the test successful if
  and only if @c A @c > @c B evaluates to @c true.

  @usage
  @include test_greater.cpp
**/
#define NT2_TEST_GREATER(A,B) NT2_TEST_FUNC(A,B,>)

/*!
  @brief Check the ordering of two values

  For any two given expressions @c A and @c B, consider the test successful if
  and only if @c A @c <= @c B evaluates to @c true.

  @usage
  @include test_lesser_equal.cpp
**/
#define NT2_TEST_LESSER_EQUAL(A,B) NT2_TEST_FUNC(A,B,<=)

/*!
  @brief Check the ordering of two values

  For any two given expressions @c A and @c B, consider the test successful if
  and only if @c A @c >= @c B evaluates to @c true.

  @usage
  @include test_greater_equal.cpp
**/
#define NT2_TEST_GREATER_EQUAL(A,B) NT2_TEST_FUNC(A,B,>=)

#endif
