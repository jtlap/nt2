//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#define NT2_UNIT_MODULE "nt2::cdiff function"

#include <nt2/table.hpp>
#include <nt2/include/functions/cdiff.hpp>
#include <nt2/include/functions/sum.hpp>
#include <nt2/include/functions/abs.hpp>
#include <nt2/include/functions/size.hpp>
#include <nt2/include/functions/rec.hpp>
#include <nt2/include/functions/is_eqz.hpp>
#include <nt2/include/functions/if_else.hpp>
#include <nt2/include/functions/isequal.hpp>
#include <nt2/include/functions/ones.hpp>
#include <nt2/include/functions/sqr.hpp>
#include <nt2/include/functions/zeros.hpp>
#include <nt2/include/constants/two.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/basic.hpp>

// NT2_TEST_CASE_TPL( cdiff_scalar, (float)(double))//NT2_TYPES )
// {
//   T x = nt2::cdiff(T(42));
//   NT2_TEST_EQUAL( x, T(42) );

//   x = nt2::cdiff(T(42),1);
//   NT2_TEST_EQUAL( x, T(42) );

//   x = nt2::cdiff(T(42),0);
//   NT2_TEST_EQUAL( x, T(42) );

// }

NT2_TEST_CASE_TPL( cdiff, (float)(double))//NT2_TYPES )
{
  using nt2::_;
  using nt2::end_;

  nt2::table<T> y( nt2::of_size(5,3) );
  nt2::table<T> sy, zy;
  nt2::table<T> sy1, sy2;
  nt2::table<T> zy1, zy2;


  for(size_t j=1;j<=size(y, 2);j++)
    for(size_t i=1;i<=size(y, 1);i++)
      y(i,j) = nt2::sqr(i + j);

  NT2_DISPLAY(y);

  sy = nt2::cdiff(y);
  zy1= y(_(3, end_), _)-y(_(1, end_-2), _);
  NT2_TEST(nt2::isequal(sy, zy1));
  NT2_TEST(nt2::isequal(nt2::cdiff(y), y(_(3, end_), _)-y(_(1, end_-2), _)));
  NT2_TEST(nt2::isequal(sy,  y(_(3, end_), _)-y(_(1, end_-2), _)));
  NT2_TEST(nt2::isequal(nt2::cdiff(y), zy1));
  NT2_DISPLAY(sy);
  NT2_DISPLAY(zy1);
  sy1 = nt2::cdiff(y, 2);
  zy2 =  y(_, _(3, end_))-y(_, _(1, end_-2));
  NT2_TEST(nt2::isequal(sy1, zy2));
  NT2_TEST(nt2::isequal(nt2::cdiff(y, 2),  y(_, _(3, end_))-y(_, _(1, end_-2))));
  NT2_TEST(nt2::isequal(sy1,  y(_, _(3, end_))-y(_, _(1, end_-2))));
  NT2_TEST(nt2::isequal(nt2::cdiff(y, 2),  zy2));
  NT2_DISPLAY(sy1);
  NT2_DISPLAY(zy2);
  sy2 = nt2::cdiff(y, 3);
  NT2_DISPLAY(sy2);




}

