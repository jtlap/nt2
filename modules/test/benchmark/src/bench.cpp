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
#include <nt2/sdk/bench/details/bench.hpp>
#include <iostream>
#include <string>

namespace nt2 { namespace details
{
  NT2_TEST_BENCHMARK_DECL std::string current_benchmark;

  NT2_TEST_BENCHMARK_DECL
  bench::bench (test_suite const* s, ptr_fun_t c, const char* n)
        : unit_test(s,c,n)
  {}

  NT2_TEST_BENCHMARK_DECL bench::~bench() {}

  NT2_TEST_BENCHMARK_DECL void bench::process() const
  {
    if(name) current_benchmark = name;
    if(call) call();
    advance();
  }
} }
