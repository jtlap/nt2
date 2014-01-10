//==============================================================================
//         Copyright 2009 - 2013 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012 - 2013 MetaScale SAS
//         Copyright 2012        Domagoj Saric, Little Endian Ltd.
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_SDK_BENCH_SUITE_HPP_INCLUDED
#define NT2_SDK_BENCH_SUITE_HPP_INCLUDED

#include <nt2/sdk/bench/config.hpp>
#include <nt2/sdk/error/throw_exception.hpp>
#include <boost/function.hpp>
#include <string>
#include <vector>

namespace nt2
{
  namespace details
  {
    // Text ID of current benchmark being run
    extern NT2_TEST_BENCHMARK_DECL std::string current_benchmark;

    // Structure holding all the benchmarks
    struct BOOST_SYMBOL_VISIBLE benchmark_suite
    {
      // RUN ALL THE EXPERIMENTS !!!
      void NT2_TEST_BENCHMARK_DECL run();

      void NT2_TEST_BENCHMARK_DECL
      register_benchmark( std::string const&              name
                        , boost::function<void()> const&  fn
                        );

      std::vector< boost::function<void()> > experiments_;
      std::vector< std::string >             ids_;
    };
  }
}

#endif
