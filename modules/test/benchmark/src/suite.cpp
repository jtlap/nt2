//==============================================================================
//         Copyright 2003 - 2012 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012 - 2013 MetaScale SAS
//         Copyright 2012        Domagoj Saric, Little Endian Ltd.
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/sdk/bench/config.hpp>
#include <nt2/sdk/bench/details/suite.hpp>
#include <iostream>
#include <iomanip>

namespace nt2 { namespace details
{
  NT2_TEST_BENCHMARK_DECL
  benchmark_suite::benchmark_suite(unit_test const* t_) : test_suite(t_) {}

  NT2_TEST_BENCHMARK_DECL benchmark_suite::~benchmark_suite()  {}

  NT2_TEST_BENCHMARK_DECL void benchmark_suite::report() const {}
  NT2_TEST_BENCHMARK_DECL void benchmark_suite::process() const
  {
    std::cout << std::setiosflags(std::ios::fixed)
              << std::setw(40) << std::left   << "[Benchmark]"
              << std::setw(10) << std::left   << "[Info]"
              << std::setw(20) << std::right  << "[Result]"
              << std::endl;

    std::cout <<  "--------------------------------------------"
                  "------------------------------------------\n";
    test_suite::process();
  }
} }

