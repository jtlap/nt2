//==============================================================================
//         Copyright 2003 - 2012 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_SDK_UNIT_TESTS_ULP_HPP_INCLUDED
#define NT2_SDK_UNIT_TESTS_ULP_HPP_INCLUDED

/*!
  @file
  @brief Precision testing macros
**/

#include <iomanip>
#include <nt2/sdk/unit/stats.hpp>
#include <nt2/sdk/unit/details/smallest_type.hpp>
#include <nt2/sdk/unit/details/through_volatile.hpp>
#include <nt2/include/functions/scalar/ulpdist.hpp>

/*!
  @brief Check for absolute precsion

  For two given values @c A and @c B, consider the test successful if and only
  if the absolute difference between @c A and @b is less or equal to @c N.

  @usage
  @include test_ulp.cpp
**/
#define NT2_TEST_ULP_EQUAL(A, B, N)                           \
{                                                             \
  nt2::unit::test_count()++;                                  \
  double ulpd = nt2::ulpdist( nt2::details::smallest_a(A, B)  \
                            , nt2::details::smallest_b(A, B)  \
                            );                                \
                                                              \
  std::cout << " * Test `"                                    \
            << "ulpdist(" << #A << ", " << #B << ")"          \
            << " <= " << N                                    \
            << "` ";                                          \
  if( ulpd <= nt2::details::through_volatile((N)) )           \
  {                                                           \
    ::nt2::unit::pass("ulpdist(" #A ", " #B ") <= " #N);      \
  }                                                           \
  else                                                        \
  {                                                           \
    ::nt2::unit::fail ( "ulpdist(" #A ", " #B ") > " #N       \
                      , __LINE__, BOOST_CURRENT_FUNCTION      \
                      );                                      \
    std::cout << std::setprecision(20)                        \
              << "because ulpdist("                           \
              << nt2::details::smallest_a(A, B) << ","        \
              << nt2::details::smallest_b(A, B) << ") = "     \
              << ulpd << "." << std::endl;                    \
  }                                                           \
}                                                             \
/**/

#endif
