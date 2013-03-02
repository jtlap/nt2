//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#define NT2_UNIT_MODULE "nt2 linalg toolbox - house function"

#include <nt2/table.hpp>
#include <nt2/include/functions/house.hpp>
#include <nt2/include/functions/transpose.hpp>
#include <nt2/include/functions/cons.hpp>
#include <nt2/include/functions/mul_i.hpp>
#include <nt2/include/functions/diag_of.hpp>
#include <nt2/include/functions/ones.hpp>
#include <nt2/sdk/unit/tests.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/exceptions.hpp>
#include <nt2/include/functions/tie.hpp>

NT2_TEST_CASE_TPL ( house, NT2_REAL_TYPES)
{
  nt2::table<T> c;
  T d, e;
  nt2::tie(c, d, e) = nt2::house(nt2::ones(4, 1, nt2::meta::as_<T>()));
  nt2::table<T> v = nt2::ones(4, 1, nt2::meta::as_<T>());
  v(1)=T(3);
  T b = T(1.0/6.0);
  T s =  T(-2);
  NT2_TEST_ULP_EQUAL(c, v, 2);
  NT2_TEST_ULP_EQUAL(d, b, 2);
  NT2_TEST_ULP_EQUAL(e, s, 2);
  v(1) = T(-1);
  b = T(0.5);
  s = T(2);
  nt2::tie(c, d, e) = nt2::house(nt2::ones(4, 1, nt2::meta::as_<T>()), 1);
  NT2_TEST_ULP_EQUAL(c, v, 2);
  NT2_TEST_ULP_EQUAL(d, b, 2);
  NT2_TEST_ULP_EQUAL(e, s, 2);
  nt2::tie(c, d, e) = nt2::house(nt2::ones(4, 1, nt2::meta::as_<T>()), 2);
  NT2_TEST_ULP_EQUAL(c, v, 2);
  NT2_TEST_ULP_EQUAL(d, b, 2);
  NT2_TEST_ULP_EQUAL(e, s, 2);

}

NT2_TEST_CASE_TPL ( house_cplx, NT2_REAL_TYPES)
{
  typedef std::complex<T> cT;
  nt2::table<cT> c, v;
  cT d, e;
  nt2::table<cT> x = nt2::mul_i(nt2::ones(4, 1, nt2::meta::as_<cT>()));
  v = x;   v(1)=cT(0, 3);
  nt2::tie(c, d, e) = nt2::house(x);
  cT b = cT(1.0/6.0);
  cT s =  cT(0, -2);
  NT2_TEST_ULP_EQUAL(c, v, 2);
  NT2_TEST_ULP_EQUAL(d, b, 2);
  NT2_TEST_ULP_EQUAL(e, s, 2);
  nt2::tie(c, d, e) = nt2::house(x, 2);
  NT2_TEST_ULP_EQUAL(c, v, 2);
  NT2_TEST_ULP_EQUAL(d, b, 2);
  NT2_TEST_ULP_EQUAL(e, s, 2);
  v(1) = cT(0, -1);
  b = cT(0.5);
  s = cT(0, 2);
  nt2::tie(c, d, e) = nt2::house(x, 1);
  NT2_TEST_ULP_EQUAL(c, v, 2);
  NT2_TEST_ULP_EQUAL(d, b, 2);
  NT2_TEST_ULP_EQUAL(e, s, 2);

}

