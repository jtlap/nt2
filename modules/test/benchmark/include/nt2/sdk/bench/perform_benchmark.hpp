//==============================================================================
//         Copyright 2003 - 2012 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012          Domagoj Saric, Little Endian Ltd.
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_SDK_BENCH_PERFORM_BENCHMARK_HPP_INCLUDED
#define NT2_SDK_BENCH_PERFORM_BENCHMARK_HPP_INCLUDED

#include <nt2/sdk/bench/config.hpp>
#include <nt2/sdk/bench/details/base_experiment.hpp>
#include <nt2/sdk/error/exception.hpp>
#include <nt2/sdk/timing/now.hpp>
#include <boost/dispatch/attributes.hpp>

namespace nt2
{
  typedef std::pair<nt2::cycles_t, nt2::time_quantum_t> intermediate_result_t;

  namespace details
  {
    BOOST_DISPATCH_NOINLINE intermediate_result_t
    perform_benchmark_impl( base_experiment const& test, nt2::seconds_t const d );

    NT2_TEST_BENCHMARK_DECL extern benchmark_result_t reference_timing_value;
  }

  NT2_TEST_BENCHMARK_DECL BOOST_DISPATCH_NOINLINE
  benchmark_result_t perform_benchmark( details::base_experiment const& test
                                      , nt2::seconds_t const duration
                                      );

  NT2_TEST_BENCHMARK_DECL BOOST_DISPATCH_NOINLINE
  benchmark_result_t& reference_timing();
}

#endif
