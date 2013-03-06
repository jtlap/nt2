//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#define NT2_UNIT_MODULE "nt2 polynom toolbox - polyadd/e"

//////////////////////////////////////////////////////////////////////////////
// unit test behavior of polynom components
//////////////////////////////////////////////////////////////////////////////
/// created  by jt the 06/03/2011
///
#include <nt2/include/functions/polyadd.hpp>
#include <nt2/sdk/unit/tests.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/table.hpp>

NT2_TEST_CASE_TPL ( polyadd_real__1_0,  NT2_REAL_TYPES)
{

  using nt2::polyadd;
  using nt2::tag::polyadd_;
  nt2::table<T, nt2::_2D> a =  nt2::_(T(1), T(4));
  nt2::table<T, nt2::_2D> b =  nt2::_(T(1), T(2));
  nt2::table<T, nt2::_2D> c;
  T aab[] = { 1, 2, 4, 6};
  nt2::table<T> d(nt2::of_size(1, 4), &aab[0], &aab[4]);
  c = polyadd(a, b);

  NT2_DISPLAY(a);
  NT2_DISPLAY(b);
  NT2_DISPLAY(c);
  NT2_DISPLAY(polyadd(a, b));
  NT2_DISPLAY(polyadd(b, a));
  NT2_TEST_EQUAL(d,polyadd(a, b));
  NT2_TEST_EQUAL(d,polyadd(b, a));
} // end of test for floating_


