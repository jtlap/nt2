//==============================================================================
//         Copyright 2015 J.T. Lapreste
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/table.hpp>
#include <nt2/include/functions/ishess.hpp>
#include <nt2/include/functions/ones.hpp>
#include <nt2/include/functions/triu.hpp>
#include <nt2/include/functions/tril.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/basic.hpp>

NT2_TEST_CASE( fundamental_ishess )
{
  NT2_TEST( nt2::ishess('e') );
  NT2_TEST( nt2::ishess(1)   );
  NT2_TEST( nt2::ishess(1.)  );
  NT2_TEST( nt2::ishess(1.f) );
}

NT2_TEST_CASE( table_ishess )
{
  nt2::table<float> a(nt2::of_size(3, 4));

  for(std::ptrdiff_t j=1; j <= 4; j++)
    for(std::ptrdiff_t i=1; i <= 3; i++)
      a(i, j) = (i <= j+1) ? (i+j) : 0;

  NT2_TEST( nt2::ishess(a) );

  a(3,1) = 25;
  NT2_TEST( !nt2::ishess(a) );

  for(std::ptrdiff_t j=1; j <= 4; j++)
    for(std::ptrdiff_t i=1; i <= 3; i++)
      a(i, j) = (i >=  j) ? (i+j) : 0;

  NT2_TEST( !nt2::ishess(a) );
}

