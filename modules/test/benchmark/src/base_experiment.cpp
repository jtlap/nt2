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
  base_experiment::base_experiment( double d
                                  , const std::string& n
                                  , const std::string& u
                                  , test_suite const* x
                                  )
                  : unit_test(x,0,0), duration(d), name(n), unit(u)
  {}
  /// Benchmark process
  NT2_TEST_BENCHMARK_DECL void base_experiment::process() const
  {
    std::cout << name << "\t";
    this->info(std::cout);
    std::cout << "\t" << std::flush;

    benchmark_result_t r = perform_benchmark(*this,duration);

    std::cout << compute(r) << " " << unit << std::endl;
    base_experiment::advance();
  }
} }

