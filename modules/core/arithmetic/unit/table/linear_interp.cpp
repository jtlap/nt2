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
#include <nt2/include/functions/linear_interp.hpp>
#include <nt2/include/functions/linspace.hpp>
#include <nt2/include/functions/rif.hpp>
#include <nt2/include/constants/one.hpp>
#include <nt2/include/constants/half.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/basic.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/ulp.hpp>

NT2_TEST_CASE_TPL( linear_interp_scalar, NT2_REAL_TYPES )
{
  T x = nt2::linear_interp(nt2::Half<T>(), T(42), T(43));
  NT2_TEST_EQUAL( x, T(42.5) );

}

NT2_TEST_CASE_TPL( linear_interp, (float)(double))//NT2_TYPES )
{
  using nt2::_;
  nt2::table<T> dx, a, b;
  a = nt2::rif(5, 3, nt2::meta::as_<T>());
  b =  a+nt2::One<T>();
  dx = nt2::reshape(nt2::linspace(T(0), T(1), 15), 5, 3);
  NT2_DISPLAY(a);
  NT2_DISPLAY(b);
  NT2_DISPLAY(dx);
  NT2_TEST_EQUAL(nt2::linear_interp(nt2::Half<T>(), a, b), a+nt2::Half<T>());
  nt2::table<T> z = nt2::linear_interp(dx, a, b);
  NT2_TEST_ULP_EQUAL(nt2::linear_interp(dx, a, b), a+dx, 0.5);
  NT2_TEST_ULP_EQUAL(z, a+dx, 0.5);
  nt2::table<T> z1 = a+dx;
  NT2_TEST_EQUAL(z1, a+dx);
}

