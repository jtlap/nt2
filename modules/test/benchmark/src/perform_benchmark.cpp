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
#include <nt2/sdk/bench/details/median.hpp>
#include <nt2/sdk/bench/details/overheads.hpp>
#include <nt2/sdk/bench/perform_benchmark.hpp>
#include <nt2/sdk/timing/now.hpp>
#include <vector>

namespace nt2
{
  namespace details
  {
    static std::vector<nt2::cycles_t      > individual_measurement_cycles;
    static std::vector<nt2::time_quantum_t> individual_measurement_time_quantums;

    NT2_TEST_BENCHMARK_DECL benchmark_result_t reference_timing_value;

    BOOST_DISPATCH_NOINLINE intermediate_result_t
    perform_benchmark_impl( base_experiment const& test, nt2::seconds_t const d )
    {
      individual_measurement_cycles       .clear();
      individual_measurement_time_quantums.clear();

      time_quantum_t const total_duration( to_timequantums( d * 1000000 ) );
      time_quantum_t       duration      (0);

      test.reset();
      while ( duration < total_duration )
      {
        /// \todo Consider flushing the CPU cache(s) here (the pipeline
        /// presumably gets flushed this loop's code).
        ///                                   (05.11.2012.) (Domagoj Saric)

        time_quantum_t const time_start  ( time_quantum() );
        cycles_t       const cycles_start( read_cycles() );
        test.run();
        cycles_t       const cycles_end( read_cycles() );
        time_quantum_t const time_end  ( time_quantum() );

        cycles_t       const burned_cycles( cycles_end - cycles_start );
        time_quantum_t const elapsed_time ( time_end   - time_start   );

        duration += elapsed_time;

        individual_measurement_cycles       .push_back( burned_cycles );
        individual_measurement_time_quantums.push_back( elapsed_time  );

        test.reset();
      }

      return intermediate_result_t( median(individual_measurement_cycles)
                                  , median(individual_measurement_time_quantums)
                                  );
    }
  }

  NT2_TEST_BENCHMARK_DECL BOOST_DISPATCH_NOINLINE
  benchmark_result_t perform_benchmark( details::base_experiment const& test
                                      , nt2::seconds_t const duration
                                      )
  {
    intermediate_result_t const
    irs( details::perform_benchmark_impl( test, duration ) );

    return  benchmark_result_t
            ( irs.first - details::cycles_overhead
            , to_microseconds(irs.second - details::quantums_overhead)
            );
  }

  NT2_TEST_BENCHMARK_DECL BOOST_DISPATCH_NOINLINE
  benchmark_result_t& reference_timing()
  {
    return details::reference_timing_value;
  }
}
