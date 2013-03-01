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
#ifndef NT2_SDK_BENCH_DETAILS_SUITE_HPP_INCLUDED
#define NT2_SDK_BENCH_DETAILS_SUITE_HPP_INCLUDED

#include <cstdio>
#include <nt2/sdk/bench/config.hpp>
#include <nt2/sdk/unit/details/suite.hpp>
#include <nt2/sdk/bench/details/base_experiment.hpp>

namespace nt2 { namespace details
{
  /// INTERNAL ONLY - RAII class for benchmarks handling
  struct benchmark_suite : public test_suite
  {
    NT2_TEST_BENCHMARK_DECL benchmark_suite(unit_test const* t_);
    NT2_TEST_BENCHMARK_DECL virtual ~benchmark_suite();
    NT2_TEST_BENCHMARK_DECL virtual void report()   const;
    NT2_TEST_BENCHMARK_DECL virtual void process()  const;
  };

  // Dummy experiment do nothing really useful
  struct dummy_experiment : unit_test
  {
    dummy_experiment() : unit_test()    {}
    virtual ~dummy_experiment()         {}
    virtual void process() const  { unit_test::advance(); }
    virtual void run() const  {}
  };

  dummy_experiment  const dummy_bench;
  benchmark_suite   const main_bench_suite(&dummy_bench);
} }

#endif
