/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#include <time.h>
#include <nt2/sdk/sys/timestamp.hpp>

namespace nt2 { namespace sys
{
  //////////////////////////////////////////////////////////////////////////////
  // Return a string with time stamp in readable human format
  //////////////////////////////////////////////////////////////////////////////
  sys::string timestamp()
  {
    time_t rawtime;
    char buffer[64];

    time(&rawtime);
    strftime(buffer,64,"%c",localtime(&rawtime));

    return sys::string(buffer);
  }
} }
