//==============================================================================
//         Copyright 2003 - 2012 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_SDK_UNIT_DETAILS_REGISTER_HPP_INCLUDED
#define NT2_SDK_UNIT_DETAILS_REGISTER_HPP_INCLUDED

#include <cstdio>

namespace nt2 { namespace details
{
  /// INTERNAL ONLY
  /// RAII class for registering a test function into the system
  struct test_registration
  {
    typedef void (*ptr_fun_t)();

            ptr_fun_t                 call;
            char              const*  name;
    mutable test_registration const*  next;

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

    test_registration const* link(test_registration const* n) const
    {
      if(next != 0 )  return next->link(n);
      else            next = n;
      return 0;
    }
  };

  /// INTERNAL ONLY
  /// Base registration point for test functions
  test_registration const dummy   = {0,0,0};
} }

#endif
