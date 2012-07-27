/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_SDK_UNIT_STATS_HPP_INCLUDED
#define NT2_SDK_UNIT_STATS_HPP_INCLUDED

/*!
  @file
  @brief Basic building blocks for test macros
**/

#include <cstdio>

namespace nt2 { namespace unit
{
  /*!
    @brief Global error counter accessor

    Give a mutable access to the current test error counter.

    @return a non-const reference to the current error counter
  **/
  inline int& error_count()
  {
    static int x = 0;
    return x;
  }

  /*!
    @brief Global test counter accessor

    Give a mutable access to the current test counter.

    @return a non-const reference to the current test counter
  **/
  inline int& test_count()
  {
    static int x = 0;
    return x;
  }

  /*!
    @brief Report a passed test

    Report a test as a successand display a message about this success.

    @param msg Message to display when test passes
  **/
  inline void pass(char const* msg)
  {
    printf(" * Test `%s` **passed**\n",msg);
  }

  /*!
    @brief Report a failed test

    Report a test as a failure and display a message about this failure.

    @param msg  Message to display when test fails
    @param ln   Line number at which test failed
    @param fn   Name of the function in which the test failed
  **/
  inline void fail(char const* msg, int ln, char const* fn)
  {
    printf(" * Test `%s` **failed** in function `%s (%d)`\n",msg,fn,ln);
    ++nt2::unit::error_count();
  }

  /*!
    @brief Report a forced failure

    Report a test as a forced failure and display a message about this failure.

    @param msg  Message to display when test fails
    @param ln   Line number at which test failed
    @param fn   Name of the function in which the test failed
  **/
  inline void error(char const* msg, int ln, char const* fn)
  {
    printf(" * %s in function `%s (%d)\n`",msg,fn,ln);
    ++nt2::unit::error_count();
  }
} }

#endif
