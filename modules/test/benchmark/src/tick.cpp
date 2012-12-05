//==============================================================================
//         Copyright 2003 - 2012 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012        MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/sdk/timing/now.hpp>
#include <nt2/sdk/bench/details/tick.hpp>

namespace nt2 { namespace details
{
  double      second_::call()  { return ::nt2::details::now();               }
  const char* second_::unit()  { return "s"; }

  double      cycle_::call()  { return static_cast<double>(read_cycles());  }
  const char* cycle_::unit()  { return "c/e"; }
} }
