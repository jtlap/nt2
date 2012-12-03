//==============================================================================
//         Copyright 2003 - 2012 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012        MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
// Usually defined on command line
#define NT2_ASSERTS_AS_EXCEPTIONS
#define BOOST_ENABLE_ASSERT_HANDLER

#include <boost/assert.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/exceptions.hpp>

void f(bool b)
{
  BOOST_ASSERT_MSG( b
                  , "Some condition was not met."
                  );
}

NT2_TEST_CASE(nt2_test_no_assert)
{
  NT2_TEST_NO_ASSERT(f(true));
  NT2_TEST_NO_ASSERT(f(false));
}
