//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_SDK_UNIT_PERFORM_BENCHMARK_HPP_INCLUDED
#define NT2_SDK_UNIT_PERFORM_BENCHMARK_HPP_INCLUDED

#include <nt2/sdk/timing/now.hpp>

#include <utility>

namespace nt2 { namespace unit
{
  typedef std::pair<nt2::details::cycles_t, nt2::details::microseconds_t> benchmark_result_t;

  class benchmark_t;

  NT2_SDK_TIMING_DECL benchmark_result_t perform_benchmark( benchmark_t & test, nt2::details::seconds_t total_duration_in_seconds );
} }

#endif
