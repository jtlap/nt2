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
#include <nt2/include/functions/idxy_bilinear.hpp>
#include <nt2/include/functions/linspace.hpp>
#include <nt2/include/functions/transpose.hpp>
#include <nt2/include/functions/isequal.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/basic.hpp>
#include <boost/fusion/include/make_vector.hpp>


// NT2_TEST_CASE_TPL( idxy_bilinear2, (float)(double))//NT2_TYPES )
// {
//   using nt2::_;
//   nt2::table<T> x =  nt2::reshape(nt2::linspace(T(1),  T(16), 16), 4, 4);
//   nt2::table<T> xi=  nt2::linspace(T(1),  T(4), 7);
//   nt2::table<T> yi=  nt2::linspace(T(0),  T(6), 11);
//   NT2_DISPLAY(x);
//   NT2_DISPLAY(xi);
//   nt2::table<T> r;
//   r =nt2::idxy_bilinear(x, xi, xi, true);
//   NT2_DISPLAY(r);
//   r =nt2::idxy_bilinear(x, xi, yi, true);
//   NT2_DISPLAY(r);
//   r =nt2::idxy_bilinear(x, xi, yi);
//   NT2_DISPLAY(r);
//   r =nt2::idxy_bilinear(x, xi, yi, _, 1, 2);
//   NT2_DISPLAY(r);

//  }
NT2_TEST_CASE_TPL( idxy_bilinear2b, (float))//(double))//NT2_TYPES )
{
  using nt2::_;
  nt2::table<T> x =  nt2::reshape(nt2::linspace(T(1),  T(16), 16), 4, 4);
  nt2::table<T> xi=  nt2::linspace(T(1),  T(4), 7);
  nt2::table<T> yi=  nt2::linspace(T(1),  T(4), 11);
  NT2_DISPLAY(x);
  NT2_DISPLAY(xi);
  NT2_DISPLAY(yi);
  nt2::table<T> r, r0;
  r =nt2::idxy_bilinear(x, xi, yi);
  NT2_DISPLAY(r);
  r0 =nt2::idxy_bilinear(x, xi, yi, true);
  NT2_DISPLAY(r0);
  NT2_TEST(isequal(r0, r));
  r =nt2::idxy_bilinear(x, xi, yi, _, 2, 1);
  NT2_DISPLAY(r);
  NT2_TEST(isequal(r0, r));
 }
NT2_TEST_CASE_TPL( idxy_bilinear2c, (float))//(double))//NT2_TYPES )
{
  using nt2::_;
  nt2::table<T> x =  nt2::reshape(nt2::linspace(T(1),  T(16), 16), 4, 4);
  nt2::table<T> xi=  nt2::linspace(T(0),  T(5), 7);
  nt2::table<T> yi=  nt2::linspace(T(0),  T(5), 11);
  NT2_DISPLAY(x);
  NT2_DISPLAY(xi);
  NT2_DISPLAY(yi);
  nt2::table<T> r, r0;
  r =nt2::idxy_bilinear(x, xi, yi);
  NT2_DISPLAY(r);
  r0 =nt2::idxy_bilinear(x, xi, yi, true);
  NT2_DISPLAY(r0);
  r =nt2::idxy_bilinear(x, xi, yi, _, 2, 1);
  NT2_DISPLAY(r);
  NT2_TEST_COMPLETE("idxy_bilinear2c");
 }
