/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_SDK_UNIT_DETAILS_STATS_HPP_INCLUDED
#define NT2_SDK_UNIT_DETAILS_STATS_HPP_INCLUDED

#include <cstdio>
#include <boost/current_function.hpp>

namespace nt2 { namespace details
{
  //////////////////////////////////////////////////////////////////////////////
  // Init-on-first-call value for error count
  //////////////////////////////////////////////////////////////////////////////
  inline int& error_count() { static int x = 0; return x; }

  //////////////////////////////////////////////////////////////////////////////
  // Init-on-first-call value for test count
  //////////////////////////////////////////////////////////////////////////////
  inline int& test_count() { static int x = 0; return x; }

  //////////////////////////////////////////////////////////////////////////////
  // Report a passed test
  //////////////////////////////////////////////////////////////////////////////
  inline void pass(char const* x) { printf(" * Test `%s` **passed**\n",x); }

  //////////////////////////////////////////////////////////////////////////////
  // Report a failed test & increment error count
  //////////////////////////////////////////////////////////////////////////////
  inline void fail(char const* x, int ln, char const* fn)
  {
    printf(" * Test `%s` **failed** in function `%s (%d)\n`", x,fn,ln);
    ++error_count();
  }

  inline void error(char const* m, int ln, char const* fn)
  {
    printf(" * %s in function `%s (%d)\n`",m,fn,ln);
    ++error_count();
  }
} }

#endif
