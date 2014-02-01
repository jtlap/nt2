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
#include <nt2/sdk/bench/metric/speedup.hpp>
#include <iostream>
#include <iomanip>

namespace nt2 { namespace details
{
  // RUN ALL THE EXPERIMENTS !!!
  NT2_TEST_BENCHMARK_DECL
  void benchmark_suite::run()
  {
    std::cout <<  std::string(100,'-') << std::endl;
    std::cout << "Benchmark\tSize\tResult\tUnit\tSamples #" << std::endl;
    std::cout <<  std::string(100,'-') << std::endl;

    // Run every registered experiments
    for(std::size_t i=0;i<experiments_.size();++i)
    {
      details::current_benchmark = ids_[i];
      experiments_[i]();
      std::cout <<  std::string(100,'-') << std::endl;
    }
  }

  NT2_TEST_BENCHMARK_DECL
  void benchmark_suite::register_benchmark( std::string const& name
                                          , boost::function<void()> const& fn
                                          )
  {
    ids_.push_back(name);
    experiments_.push_back(fn);
  }

  // Text ID of current benchmark being run
  NT2_TEST_BENCHMARK_DECL std::string current_benchmark;
} }
