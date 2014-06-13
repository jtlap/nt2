//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/include/functions/length.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>

////////////////////////////////////////////////////////////////////////////////
// length of arithmetic types
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE( fundamental_length )
{
  using nt2::length;

  NT2_TEST_EQUAL( length('4'), 1U  );
  NT2_TEST_EQUAL( length(4)  , 1U  );
  NT2_TEST_EQUAL( length(4.) , 1U  );
  NT2_TEST_EQUAL( length(4.f), 1U  );
}
