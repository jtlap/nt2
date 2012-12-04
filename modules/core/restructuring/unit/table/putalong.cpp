/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#define NT2_UNIT_MODULE "nt2::sum1 function"

#include <nt2/table.hpp>
#include <nt2/include/functions/putalong.hpp>
#include <nt2/include/functions/sum.hpp>
#include <nt2/include/functions/abs.hpp>
#include <nt2/include/functions/size.hpp>
#include <nt2/include/functions/rec.hpp>
#include <nt2/include/functions/is_eqz.hpp>
#include <nt2/include/functions/if_else.hpp>
#include <nt2/include/functions/isequal.hpp>
#include <nt2/include/functions/ones.hpp>
#include <nt2/include/functions/zeros.hpp>
#include <nt2/include/constants/two.hpp>
#include <nt2/include/functions/isequal.hpp>
#include <nt2/include/functions/reshape.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/basic.hpp>

NT2_TEST_CASE_TPL( putalong_scalar, (float)(double))//NT2_TYPES )
{
  nt2::table<T> x = nt2::putalong(T(42), 1);  NT2_DISPLAY( x );
  x = nt2::putalong(T(42),1);  NT2_DISPLAY( x );
  NT2_TEST_EQUAL(x, T(42));
  x = nt2::putalong(T(42),2);  NT2_DISPLAY( x );
  NT2_TEST_EQUAL(x, T(42));

}

NT2_TEST_CASE_TPL( putalong, (float)(double))//NT2_TYPES )
{
  using nt2::_;
  nt2::table<T> y( nt2::of_size(2,3) );
  nt2::table<T> sy;

  int k = 0;
  for(size_t j=1;j<=size(y, 2);j++)
    for(size_t i=1;i<=size(y, 1);i++)
      y(i,j) = k++;


  sy = nt2::putalong(y, 1);
  display(sy);
  NT2_TEST_EQUAL(sy, reshape(y, nt2::of_size(numel(y), 1)));
  sy = nt2::putalong(y, 2);
  NT2_TEST_EQUAL(sy, reshape(y, nt2::of_size(1, numel(y))));
  display(sy);
  sy = nt2::putalong(y, 3);
  NT2_TEST_EQUAL(sy, reshape(y, nt2::of_size(1, 1, numel(y))));
  display(sy);



}

