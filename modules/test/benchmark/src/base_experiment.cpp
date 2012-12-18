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
#include <nt2/sdk/bench/details/base_experiment.hpp>
#include <nt2/sdk/bench/perform_benchmark.hpp>

#include <nt2/sdk/timing/now.hpp>
#include <iostream>
#include <iomanip>

namespace nt2 { namespace details
{
  NT2_TEST_BENCHMARK_DECL
  base_experiment::base_experiment() : unit_test(0,0,0) {}

  NT2_TEST_BENCHMARK_DECL
  base_experiment::base_experiment( std::size_t sz
                                  , double d
                                  , const std::string& n
                                  , const std::string& u
                                  , test_suite const* x
                                  )
                  : unit_test(x,0,0), size(sz), duration(d), name(n), unit(u)
  {}

  /// Benchmark process
  NT2_TEST_BENCHMARK_DECL
  void base_experiment::preprocess(std::size_t sz) const
  {
    std::cout << std::setiosflags(std::ios::fixed)
              << std::setw(40) << std::left   << name
              << std::setw(10) << std::right  << sz;
  }

  /// Benchmark process
  NT2_TEST_BENCHMARK_DECL void base_experiment::process() const
  {
    preprocess(size);

    benchmark_result_t r = perform_benchmark(*this,duration);

    std::cout << std::setiosflags(std::ios::fixed)  << std::setprecision(2)
              << std::setw(20)    << std::right
              << compute(r)
              << " " << unit
              << std::endl;

    base_experiment::advance();
  }
} }

