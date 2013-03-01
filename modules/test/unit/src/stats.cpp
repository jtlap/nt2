//==============================================================================
//         Copyright 2003 - 2012 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012        MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <cstdio>
#include <nt2/sdk/unit/stats.hpp>
#include <nt2/sdk/unit/config.hpp>

namespace nt2 { namespace unit
{
  NT2_TEST_UNIT_DECL int& error_count()
  {
    static int x = 0;
    return x;
  }

  NT2_TEST_UNIT_DECL int& test_count()
  {
    static int x = 0;
    return x;
  }

  NT2_TEST_UNIT_DECL void pass(char const* msg)
  {
    printf(" * Test `%s` **passed**\n",msg);
  }

  NT2_TEST_UNIT_DECL void fail(char const* msg, int ln, char const* fn)
  {
    printf(" * Test `%s` **failed** in function `%s (%d)`\n",msg,fn,ln);
    ++nt2::unit::error_count();
  }

  NT2_TEST_UNIT_DECL void error(char const* msg, int ln, char const* fn)
  {
    printf(" * %s in function `%s (%d)\n`",msg,fn,ln);
    ++nt2::unit::error_count();
  }
} }
