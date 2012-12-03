//==============================================================================
//         Copyright 2003 - 2012 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012        MetaScale SAS
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
#include <iostream>
#include <nt2/sdk/unit/stats.hpp>
#include <nt2/sdk/unit/details/ulp.hpp>
#include <boost/current_function.hpp>

/*!
  @brief Check for absolute precision

  For two given values @c A and @c B, consider the test successful if and only
  if the absolute difference between @c A and @b is less or equal to @c N.

  @usage
  @include test_ulp.cpp
**/
#define NT2_TEST_ULP_EQUAL(A, B, N)                               \
do                                                                \
{                                                                 \
  nt2::unit::test_count()++;                                      \
  double ulpd = nt2::unit::max_ulp(A, B);                         \
  if( ulpd <= N )                                                 \
  {                                                               \
    ::nt2::unit::pass("max(ulpdist(" #A ", " #B ")) <= " #N);     \
  }                                                               \
  else                                                            \
  {                                                               \
    ::nt2::unit::fail( "max(ulpdist(" #A ", " #B ")) <= " #N      \
                     , __LINE__, BOOST_CURRENT_FUNCTION           \
                     );                                           \
    std::cout << std::setprecision(20);                           \
    std::cout << "max ulpdist is " << ulpd << "\n";               \
    std::cout << std::flush;                                      \
  }                                                               \
}                                                                 \
while(0)                                                          \
/**/

#endif
