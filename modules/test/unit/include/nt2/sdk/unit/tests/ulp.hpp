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
#include <nt2/sdk/unit/details/eval.hpp>
#include <nt2/sdk/unit/details/ulp.hpp>
#include <boost/current_function.hpp>

namespace nt2 { namespace details
{
  template<typename A, typename B>
  void test_ulp_equal ( const char* desc
                      , const char* func, int line
                      , A const& a, B const& b
                      , double N
                      )
  {
    typedef BOOST_TYPEOF(nt2::unit::eval(a))                        a_t;
    typedef BOOST_TYPEOF(nt2::unit::eval(b))                        b_t;
    typedef typename nt2::details::max_ulp_<a_t,b_t>::failure_type  f_t;

    std::vector< f_t > ulps;
    double ulpd = nt2::unit::max_ulp( nt2::unit::eval(a)
                                    , nt2::unit::eval(b)
                                    , N, ulps
                                    );
    if( ulps.empty() )
    {
      ::nt2::details::ulp_pass( desc, ulpd, N );
    }
    else
    {
      ::nt2::details::ulp_fail( desc, func, line, ulps.size(),N);

      std::cout << std::setprecision(20);

      BOOST_FOREACH ( f_t const & f, ulps )
      {
        std::cout << "\tlhs: "  << f.value
                  << ", rhs: "  << f.desired_value
                  << ", ULP: "  << f.ulp_error
                  << ", @( "    << f.index << " )";
        std::cout << std::endl;
      }

      std::cout << std::endl;
    }
  }
} }

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
                                                                  \
  nt2::details::test_ulp_equal( #A " == " #B                      \
                              , BOOST_CURRENT_FUNCTION, __LINE__  \
                              , A, B, N                           \
                              );                                  \
}                                                                 \
while(0)                                                          \
/**/

#endif
