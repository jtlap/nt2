/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#include <nt2/core/utility/config.hpp>
#include <nt2/core/utility/randstream.hpp>
#include <cstring>

namespace nt2
{
  randstream_::~randstream_() {}

  nt2::randstream_* current_randstream = mt19937stream();

  NT2_CORE_UTILITY_DECL void randstream(const char* choice)
  {
    if(strcmp(choice,"mt19937ar") == 0)
    {
      current_randstream = mt19937stream();
    }
    else if(strcmp(choice,"mlfg6331_64") == 0)
    {
      current_randstream = lagged_fibonacci2281stream();
    }
  }

  NT2_CORE_UTILITY_DECL void randstream(const char* choice, int s)
  {
    randstream(choice);
    current_randstream->seed(s);
  }
}
