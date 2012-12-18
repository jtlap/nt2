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
#include <cstdio>
#include <nt2/sdk/bench/config.hpp>
#include <nt2/sdk/bench/details/overheads.hpp>
#include <nt2/sdk/bench/perform_benchmark.hpp>

namespace nt2 { namespace details
{
  // Overhead offsets:
  // http://www.motherboardpoint.com/rdtsc-performance-different-x86-archs-t166722.html
  static std::pair<unsigned int, unsigned int> calculate_overhead()
  {
    struct null_benchmark_t : base_experiment
    {
      null_benchmark_t() {}
      BOOST_DISPATCH_NOTHROW void run() const BOOST_DISPATCH_OVERRIDE {}
    } null_benchmark;

    volatile null_benchmark_t& owb( null_benchmark );

    nt2::intermediate_result_t const
    result( perform_benchmark_impl(const_cast<null_benchmark_t&>( owb ), 0.25) );

    return std::make_pair ( static_cast<unsigned int>( result.first  )
                          , static_cast<unsigned int>( result.second )
                          );
  }

  static std::pair<unsigned int,unsigned int> const ior(calculate_overhead());

  unsigned int const cycles_overhead(ior.first);
  unsigned int const quantums_overhead(ior.second);
} }
