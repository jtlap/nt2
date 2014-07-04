//==============================================================================
//         Copyright 2009 - 2014   LRI UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012 - 2014   NumScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/include/functions/swap.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>

NT2_TEST_CASE_TPL(swap, NT2_TYPES )
{
  T x,y;

  x = T(42);
  y = T(69);

  nt2::swap(x,y);

  NT2_TEST_EQUAL( x, T(69));
  NT2_TEST_EQUAL( y, T(42));
}
