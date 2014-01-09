//==============================================================================
//         Copyright 2009 - 2013 LRI  UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2013             MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/sdk/bench/config.hpp>
#include <nt2/sdk/bench/metric/speedup.hpp>
#include <string>

namespace nt2
{
  namespace details
  {
    NT2_TEST_BENCHMARK_DECL std::map<std::string, double> measures_map;
  }
}
