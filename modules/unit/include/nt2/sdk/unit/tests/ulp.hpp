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
#include <nt2/include/functions/ulpdist.hpp>
#include <nt2/include/functions/globalmax.hpp>
#include <nt2/include/functions/display.hpp>

/*!
  @brief Check for absolute precsion

  For two given values @c A and @c B, consider the test successful if and only
  if the absolute difference between @c A and @b is less or equal to @c N.

  @usage
  @include test_ulp.cpp
**/
#define NT2_TEST_ULP_EQUAL(A, B, N)                                            \
{                                                                              \
  nt2::unit::test_count()++;                                                   \
  double ulpd = nt2::globalmax( nt2::ulpdist( nt2::details::smallest_a(A, B)   \
                                            , nt2::details::smallest_b(A, B)   \
                                            )                                  \
                              );                                               \
  if( ulpd <= N )                                                              \
  {                                                                            \
    ::nt2::unit::pass("max(ulpdist(" #A ", " #B ")) <= " #N);                  \
  }                                                                            \
  else                                                                         \
  {                                                                            \
    ::nt2::unit::fail( "max(ulpdist(" #A ", " #B ")) <= " #N                   \
                     , __LINE__, BOOST_CURRENT_FUNCTION                        \
                     );                                                        \
    std::cout << std::setprecision(20);                                        \
    std::cout << "max ulpdist is " << ulpd << "\n";                            \
    nt2::display(#A, nt2::details::smallest_a(A, B));                          \
    nt2::display(#B, nt2::details::smallest_a(A, B));                          \
    std::cout << std::flush;                                                   \
  }                                                                            \
}                                                                              \
/**/

#endif
