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
#include <nt2/sdk/bench/args.hpp>
#include <nt2/sdk/bench/metric/speedup.hpp>
#include <boost/foreach.hpp>
#include <iostream>
#include <iomanip>

namespace nt2 { namespace bench
{
  struct benchmark_suite
  {
    // RUN ALL THE EXPERIMENTS !!!
    void run()
    {
      std::cout <<  std::string(100,'-') << std::endl;
      std::cout << "Benchmark\tSize\t" << std::endl;
      std::cout <<  std::string(100,'-') << std::endl;

      // Run every registered experiments
      for(std::size_t i=0;i<experiments_.size();++i)
      {
        details::current_benchmark = ids_[i];
        experiments_[i]();
      }
    }

    void register_benchmark ( std::string const&              name
                            , boost::function<void()> const&  fn
                            )
    {
      ids_.push_back(name);
      experiments_.push_back(fn);
    }

    std::vector< boost::function<void()> > experiments_;
    std::vector< std::string >             ids_;
  };
} }

namespace nt2 { namespace details
{
  // Text ID of current benchmark being run
  NT2_TEST_BENCHMARK_DECL std::string current_benchmark;

  // Global benchmark_suite
  bench::benchmark_suite benchmarker_;

  // Put an experiment in the benchmark suite
  NT2_TEST_BENCHMARK_DECL
  bool register_benchmark ( std::string const&              name
                          , boost::function<void()> const&  fn
                          )
  {
    if(fn) benchmarker_.register_benchmark(name, fn);
    return fn;
  }

} }

// Prebuilt main
NT2_TEST_BENCHMARK_DECL int main(int argc, const char** argv)
{
  std::cout << "CTEST_FULL_OUTPUT" << std::endl;

  // process option commands
  nt2::details::fill_args_map(argc,argv);

  // run all registered experiments
  nt2::details::benchmarker_.run();
}
