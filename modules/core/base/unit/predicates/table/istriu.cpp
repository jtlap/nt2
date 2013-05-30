//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#define NT2_UNIT_MODULE "nt2::istriu function"

#include <nt2/table.hpp>
#include <nt2/include/functions/istriu.hpp>
#include <nt2/include/functions/ones.hpp>
#include <nt2/include/functions/triu.hpp>
#include <nt2/include/functions/tril.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/basic.hpp>

NT2_TEST_CASE( fundamental_istriu )
{
  NT2_TEST( nt2::istriu('e') );
  NT2_TEST( nt2::istriu(1)   );
  NT2_TEST( nt2::istriu(1.)  );
  NT2_TEST( nt2::istriu(1.f) );
}

NT2_TEST_CASE( table_istriu )
{
  nt2::table<float> a(nt2::of_size(3, 4));

  for(std::ptrdiff_t j=1; j <= 4; j++)
    for(std::ptrdiff_t i=1; i <= 3; i++)
      a(i, j) = (i <= j) ? (i+j) : 0;

  NT2_TEST( nt2::istriu(a) );

  a(2,1) = 25;
  NT2_TEST( !nt2::istriu(a) );

  for(std::ptrdiff_t j=1; j <= 4; j++)
    for(std::ptrdiff_t i=1; i <= 3; i++)
      a(i, j) = (i >=  j) ? (i+j) : 0;

  NT2_TEST( !nt2::istriu(a) );
}

NT2_TEST_CASE( expr_istril )
{
  NT2_TEST( !nt2::istriu( nt2::tril(nt2::ones(4,3)) ) );
  NT2_TEST( nt2::istriu( nt2::triu(nt2::ones(4,3)) ) );
}
