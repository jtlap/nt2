//==============================================================================
//         Copyright 2003 - 2012 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012        MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/sdk/unit/details/suite.hpp>
#include <nt2/sdk/unit/stats.hpp>
#include <cstdio>

namespace nt2 { namespace details
{
  test_suite::~test_suite() {}

  void test_suite::report() const
  {
    int t = nt2::unit::test_count();
    int e = nt2::unit::error_count();

    printf( "Results:\n"
            "----------------------------------------------------------------\n"
            "%d test - %d pass - %d fail.\n"
            , t, (t-e), e
          );
  }

  void test_suite::process() const
  {
    if(tests) tests->process();
    report();
  }

  NT2_TEST_UNIT_DECL unit_test const* test_suite::link(unit_test const* n) const
  {
    return tests->link(n);
  }
} }
