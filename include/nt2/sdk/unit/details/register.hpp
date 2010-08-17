/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_SDK_UNIT_DETAILS_REGISTER_HPP_INCLUDED
#define NT2_SDK_UNIT_DETAILS_REGISTER_HPP_INCLUDED

#include <cstdio>

namespace nt2 { namespace details
{
  //////////////////////////////////////////////////////////////////////////////
  // RAII class for registering a test function
  //////////////////////////////////////////////////////////////////////////////
  struct test
  {
    ////////////////////////////////////////////////////////////////////////////
    // Status function have a void() type
    ////////////////////////////////////////////////////////////////////////////
    typedef void (*ptr_fun_t)();

    ////////////////////////////////////////////////////////////////////////////
    // Store current status function
    ////////////////////////////////////////////////////////////////////////////
    ptr_fun_t      call;
    char const*    name;

    ////////////////////////////////////////////////////////////////////////////
    // Next reporter
    ////////////////////////////////////////////////////////////////////////////
    mutable test const* next;

    ////////////////////////////////////////////////////////////////////////////
    // Run the embedded test
    ////////////////////////////////////////////////////////////////////////////
    void process() const
    {
      if(name)
      {
        #if !defined(NT2_TEST_SILENT)
        printf("Running: %s\n",name);
        puts("---------------------------------------------------------------");
        #endif
      }
      if(call) call();
      puts("");
      if(next) next->process();
    }

    ////////////////////////////////////////////////////////////////////////////
    // Called by the reporter registration to build the chain of reporting
    ////////////////////////////////////////////////////////////////////////////
    test const* link(test const* n) const
    {
      if(next != 0 )  return next->link(n);
      else            next = n;
      return 0;
    }
  };

  //////////////////////////////////////////////////////////////////////////////
  // Base registration point
  //////////////////////////////////////////////////////////////////////////////
  test const dummy   = {0,0,0};
} }

#endif
