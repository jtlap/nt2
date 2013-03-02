/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#define NT2_UNIT_MODULE "nt2 function cumtrapz"

#include <nt2/table.hpp>
#include <nt2/include/functions/of_size.hpp>
#include <nt2/include/functions/cumtrapz.hpp>
#include <nt2/include/functions/reshape.hpp>
#include <nt2/include/functions/rowvect.hpp>
#include <nt2/include/functions/cons.hpp>
#include <nt2/include/functions/colon.hpp>
#include <nt2/include/functions/zeros.hpp>
#include <nt2/include/functions/ones.hpp>
#include <nt2/include/functions/transpose.hpp>
#include <nt2/include/constants/half.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/basic.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>
#include <nt2/sdk/unit/tests/exceptions.hpp>

NT2_TEST_CASE_TPL( cumtrapz_inner, NT2_REAL_TYPES)
{
  using nt2::table;
  using nt2::of_size;
  using nt2::cumtrapz;
  using nt2::reshape;
  using nt2::_;
  using nt2::_2D;
  table<T, _2D> r2 = nt2::rowvect(nt2::cons(T(0), T(1.5), T(4), T(7.5), T(12)));
  table<T, _2D> r1 = nt2::zeros(1, 5, nt2::meta::as_<T>());
  table<T, _2D> a = nt2::_(T(1), T(5));
  table<T, _2D> b0 = nt2::cumtrapz(a);
  NT2_TEST_EQUAL(b0, r2);
  table<T, _2D> b1 = nt2::cumtrapz(a, 1);
  NT2_TEST_EQUAL(b1, r1);
  table<T, _2D> b2= nt2::cumtrapz(a, 2);
  NT2_TEST_EQUAL(b2, r2);
}

NT2_TEST_CASE_TPL( cumtrapz_outer, NT2_REAL_TYPES )
{
  using nt2::table;
  using nt2::of_size;
  using nt2::cumtrapz;
  using nt2::reshape;
  using nt2::_;
  using nt2::_2D;
  table<T, _2D> r2 = nt2::rowvect(nt2::cons(T(0), T(1.5), T(4), T(7.5), T(12)));
  table<T, _2D> r1 = nt2::zeros(1, 5, nt2::meta::as_<T>());
  table<T, _2D> a = nt2::_(T(1), T(5));
  table<T, _2D> b0 = nt2::cumtrapz(a, a);
  NT2_TEST_EQUAL(b0, r2);
  table<T, _2D> b2= nt2::cumtrapz(a, a, 2);
  NT2_TEST_EQUAL(b2, r2);
  table<T, _2D> b1 = nt2::cumtrapz(nt2::ones(1, 1, nt2::meta::as_<T>()),a, 1);
  NT2_TEST_EQUAL(b1, r1);
}

NT2_TEST_CASE_TPL( cumtrapz_mat, NT2_REAL_TYPES )
{
  using nt2::table;
  using nt2::of_size;
  using nt2::cumtrapz;
  using nt2::reshape;
  using nt2::trans;
  using nt2::cons;
  using nt2::_;
  using nt2::_2D;
  using nt2::meta::as_;
  table<T> y = reshape(_(T(1), T(15)), 3, 5); // test fails if y is _2D
  table<T, _2D> r1= trans(reshape(cons(
                                    T(0  ),  T(0  ),  T(0  ), T(0   ),T( 0  ),
                                    T(1.5),  T(4.5),  T(7.5), T(10.5),T( 13.5),
                                    T(4.0),  T(10.),  T(16.0),T(22.0),T( 28.0)
                                    ), 5, 3));

  table<T, _2D> r2= trans(reshape(cons(
                                    T(0),  T(2.5), T( 8.0), T(16.5), T(28.0),
                                    T(0),  T(3.5), T(10.0), T(19.5), T(32.0),
                                    T(0),  T(4.5), T(12.0), T(22.5), T(36.0)
                                    ), 5, 3));
  table<T, _2D> r3 =  nt2::zeros(3, 5, as_<T>());

  table<T, _2D> v1 =  cumtrapz(y, 1);
  NT2_TEST_EQUAL(v1, r1);
  table<T, _2D> v2 =  cumtrapz(y, 2);
  NT2_TEST_EQUAL(v2, r2);
  table<T, _2D> v3 =  cumtrapz(y, 3);
  NT2_TEST_EQUAL(v3, r3);
}
NT2_TEST_CASE_TPL( cumtrapz_scal, NT2_REAL_TYPES )
{
  using nt2::table;
  using nt2::of_size;
  using nt2::cumtrapz;
  using nt2::reshape;
  using nt2::trans;
  using nt2::cons;
  using nt2::_;
  using nt2::_2D;

  table<T, _2D> y = _(T(1), T(15));
  table<T, _2D> x = y*nt2::Half<T>();
  table<T, _2D> v1 =  cumtrapz(x, y);
  table<T, _2D> v2 =  cumtrapz(nt2::Half<T>(), y);
  table<T, _2D> v3 =  cumtrapz(y)*nt2::Half<T>();
  NT2_TEST_EQUAL(v1, v2);
  NT2_TEST_EQUAL(v1, v3);
}
