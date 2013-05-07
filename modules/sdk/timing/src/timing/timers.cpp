//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================

#include <nt2/sdk/timing/tic.hpp>
#include <nt2/sdk/timing/ctic.hpp>
#include <nt2/sdk/timing/config.hpp>
#include <iostream>

namespace nt2 { namespace details
{
  NT2_SDK_TIMING_DECL void cycle_based_timer::Print(const cycles_t& val)
  {
    std::cout << "Elapsed time is " << val << " CPU cycle(s).\n";
  }

  NT2_SDK_TIMING_DECL void second_based_timer::Print(const double& val)
  {
    std::cout << "Elapsed time is " << val << " s.\n";
  }
} }
