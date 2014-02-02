//==============================================================================
//         Copyright 2009 - 2013 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012 - 2013 MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/sdk/bench/config.hpp>
#include <nt2/sdk/bench/suite.hpp>
#include <iostream>

namespace nt2 { namespace details
{
  NT2_TEST_BENCHMARK_DECL
  bench_suite::bench_suite(unit_test const* t_) : test_suite(t_) {}

  NT2_TEST_BENCHMARK_DECL bench_suite::~bench_suite() {}

  NT2_TEST_BENCHMARK_DECL void bench_suite::process() const
  {
    std::cout << "Benchmark\tSize\tResult\tUnit\tSamples #" << std::endl;
    std::cout <<  std::string(100,'-');

    if(test_suite::tests) test_suite::tests->process();
  }
} }
