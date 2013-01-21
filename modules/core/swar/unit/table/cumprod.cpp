/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#define NT2_UNIT_MODULE "nt2 function cumprod"

#include <nt2/table.hpp>
#include <nt2/include/functions/of_size.hpp>
#include <nt2/include/functions/cumprod.hpp>
#include <nt2/include/functions/reshape.hpp>
#include <nt2/include/functions/colon.hpp>
#include <nt2/include/functions/cons.hpp>
#include <nt2/include/functions/rowvect.hpp>
#include <nt2/include/functions/isequal.hpp>

#include <nt2/include/functions/sb2b.hpp>
#include <nt2/include/functions/ones.hpp>
#include <nt2/include/constants/two.hpp>
#include <nt2/include/constants/zero.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/basic.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>
#include <nt2/sdk/unit/tests/exceptions.hpp>

NT2_TEST_CASE( cumprod_inner )
{
  using nt2::table;
  using nt2::of_size;
  using nt2::cumprod;
  using nt2::reshape;
  typedef double T;
  using nt2::_;

  table<T> a = nt2::ones( 3, 5, 2, nt2::meta::as_<T>());
  table<T> b = cumprod(a);
  table<T> c = cumprod(a, 2);
  NT2_TEST_EQUAL(b, a);
  NT2_TEST_EQUAL(c, a);

  table<T> aa = nt2::_(T(1), T(5));
  table<T> bb = nt2::rowvect(nt2::cons(T(1), T(2), T(6), T(24), T(120)));
  table<T> cc =cumprod(aa);
  NT2_TEST_EQUAL(bb, cc);
  table<T> dd =cumprod(aa, 2);
  NT2_TEST_EQUAL(bb, dd);
  table<T> ee =cumprod(aa, 1);
  NT2_TEST_EQUAL(ee, aa);
  NT2_TEST_EQUAL(120, cumprod(aa, 2)(5));
}

