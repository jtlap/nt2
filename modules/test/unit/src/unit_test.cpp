//==============================================================================
//         Copyright 2003 - 2012 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012        MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/sdk/unit/stats.hpp>
#include <nt2/sdk/unit/details/unit_test.hpp>
#include <nt2/sdk/unit/details/suite.hpp>
#include <cstdio>

namespace nt2 { namespace details
{
  unit_test::unit_test (test_suite const* s, ptr_fun_t c, const char* n)
            : call(c), name(n)
  {
    if(s) next = s->link(this);
  }

  unit_test::~unit_test() {}

  void unit_test::process() const
  {
    if(name)
    {
      printf("Running: %s\n",name);
      puts("---------------------------------------------------------------");
    }

    if(call)
    {
      int n = nt2::unit::test_count();
      call();
      if(nt2::unit::test_count() == n)
      {
        nt2::unit::error_count()++;
        nt2::unit::test_count()++;
        printf
        ( "----------------------------------------------------------------\n"
          "NO TEST REGISTERED -- FORCED FAILURE.\n"
        );
      }
    }
    puts("");
    advance();
  }

  unit_test const* unit_test::link(unit_test const* n) const
  {
    if(next != 0 )  return next->link(n);
    else            next = n;
    return 0;
  }

  void unit_test::advance() const
  {
    if(next) next->process();
  }
} }
