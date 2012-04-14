/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#define NT2_UNIT_MODULE "nt2::istril function"

#include <nt2/table.hpp>
#include <nt2/include/functions/istril.hpp>
#include <nt2/include/functions/ones.hpp>
#include <nt2/include/functions/is_equal.hpp>
#include <nt2/include/functions/sin.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/basic.hpp>
#include <nt2/toolbox/operator/operator.hpp>
#include <nt2/include/functions/function.hpp>

NT2_TEST_CASE( fundamental_istril )
{
  NT2_TEST( nt2::istril('e') );
  NT2_TEST( nt2::istril(1)   );
  NT2_TEST( nt2::istril(1.)  );
  NT2_TEST( nt2::istril(1.f) );
}

NT2_TEST_CASE( table_istril )
{
  nt2::table<float> a(nt2::of_size(3, 4));
  nt2::container::table<float> aa(nt2::of_size(3, 4));

  for(std::ptrdiff_t i=1; i <= 3; i++)
    for(std::ptrdiff_t j=1; j <= 4; j++)
      a(i, j) = (i >= j) ? (i+j) : 0;
  NT2_TEST( nt2::istril(a) );

  a(1, 2) = 25;
  NT2_TEST( !nt2::istril(a) );

  for(std::ptrdiff_t i=1; i <= 3; i++)
    for(std::ptrdiff_t j=1; j <= 4; j++)
      a(i, j) = (i <=  j) ? (i+j) : 0;

  NT2_TEST( !nt2::istril(a) );
}
