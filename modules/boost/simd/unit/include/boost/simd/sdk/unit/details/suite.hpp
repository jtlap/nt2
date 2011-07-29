/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef BOOST_SIMD_SDK_UNIT_DETAILS_SUITE_HPP_INCLUDED
#define BOOST_SIMD_SDK_UNIT_DETAILS_SUITE_HPP_INCLUDED

#include <cstdio>
#include <boost/simd/sdk/details/type_id.hpp>
#include <boost/simd/sdk/config/type_lists.hpp>
#include <boost/simd/sdk/unit/details/stats.hpp>
#include <boost/simd/sdk/unit/details/register.hpp>

namespace boost { namespace simd { namespace details
{
  //////////////////////////////////////////////////////////////////////////////
  // RAII class for reporting error at end of modules
  //////////////////////////////////////////////////////////////////////////////
  struct suite
  {
    ////////////////////////////////////////////////////////////////////////////
    // Display the count of test/pass/fail
    ////////////////////////////////////////////////////////////////////////////
    ~suite()
    {
      #if !defined(BOOST_SIMD_TEST_SILENT)
      int t = details::test_count();
      int e = details::error_count();
      printf( "Results:\n"
              "----------------------------------------------------------------\n"
              "%d test - %d pass - %d fail.\n"
            , t, (t-e), e
            );
      #endif
    }

    ////////////////////////////////////////////////////////////////////////////
    // Run the embedded tests
    ////////////////////////////////////////////////////////////////////////////
    void process() const
    {
      #if !defined(BOOST_SIMD_TEST_SILENT)
      printf("[%s]\n",BOOST_SIMD_UNIT_MODULE);
      puts("===============================================================");
      #endif
      if(tests) tests->process();
    }

    ////////////////////////////////////////////////////////////////////////////
    // Chains tests in the suite
    ////////////////////////////////////////////////////////////////////////////
    test const* link(test const* n) const { return tests->link(n); }

    ////////////////////////////////////////////////////////////////////////////
    // List of registere test functions
    ////////////////////////////////////////////////////////////////////////////
    mutable test const*  tests;
  };

  suite const main_suite  = { &dummy };

} } }

#endif
