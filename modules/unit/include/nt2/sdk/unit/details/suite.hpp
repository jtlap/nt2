/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_SDK_UNIT_DETAILS_SUITE_HPP_INCLUDED
#define NT2_SDK_UNIT_DETAILS_SUITE_HPP_INCLUDED

#include <cstdio>
#include <nt2/sdk/unit/details/register.hpp>

/// TODO: Make this runtime
#ifndef NT2_UNIT_MODULE
#define NT2_UNIT_MODULE "unnamed module"
#endif

namespace nt2 { namespace details
{
  /// INTERNAL ONLY
  /// RAII class for reporting error at end of modules
  struct suite
  {
    /// INTERNAL ONLY
    /// Display the count of test/pass/fail
    void report() const
    {
      int t = nt2::unit::test_count();

      if(t)
      {
        int e = nt2::unit::error_count();
        printf( "Results:\n"
              "----------------------------------------------------------------\n"
              "%d test - %d pass - %d fail.\n"
              , t, (t-e), e
              );
      }
      else
      {
        nt2::unit::error_count() = 1;
        printf(
              "----------------------------------------------------------------\n"
              "NO TEST REGISTERED -- FORCED FAILURE.\n"
              );
      }
    }

    /// INTERNAL ONLY
    /// Run the embedded tests
    void process() const
    {
      /// TODO: Make this runtime
      #if !defined(NT2_TEST_SILENT)
      printf("[%s]\n",NT2_UNIT_MODULE);
      puts("===============================================================");
      #endif

      if(tests) tests->process();

      /// TODO: Make this runtime
      #if !defined(NT2_TEST_SILENT)
      report();
      #endif
    }

    /// INTERNAL ONLY
    /// Chains tests in the suite
    test_registration const* link(test_registration const* n) const
    {
      return tests->link(n);
    }

    /// INTERNAL ONLY
    /// List of registered test functions
    mutable test_registration const*  tests;
  };

  /// INTERNAL ONLY
  /// Initial seed for a test suite
  suite const main_suite  = { &dummy };
} }

#endif
