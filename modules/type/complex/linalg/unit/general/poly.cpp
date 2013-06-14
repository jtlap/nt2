//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#define NT2_UNIT_MODULE "nt2 linalg toolbox - poly factorization"

#include <nt2/table.hpp>
#include <nt2/include/functions/poly.hpp>
#include <nt2/include/functions/eye.hpp>
#include <nt2/include/functions/ones.hpp>
#include <nt2/include/functions/cons.hpp>
#include <nt2/sdk/unit/tests.hpp>
#include <nt2/sdk/unit/tests/ulp.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/complex/meta/as_complex.hpp>

NT2_TEST_CASE_TPL(poly, NT2_REAL_TYPES)
{
 typedef typename nt2::meta::as_complex<T>::type  cT;
 typedef T r_t;
  using nt2::poly;
  using nt2::tag::poly_;
  nt2::table<cT> n = nt2::ones(1, 2,  nt2::meta::as_<cT>());
  nt2::table<cT> p = nt2::poly(n);
  nt2::table<cT> pp(nt2::of_size(1, 3));
  pp(1) = pp(3) = cT(1); pp(2) = cT(-2);
  NT2_TEST_ULP_EQUAL(pp, p, 0.5);


  nt2::table<cT> pp1 = nt2::cons(nt2::of_size(1, 5), 1,   -10,    35,   -50,    24);
  nt2::table<cT> n1 = nt2::_(T(1), T(4));
  nt2::table<cT> p1 = nt2::poly(n1);
  NT2_TEST_ULP_EQUAL(pp1, p1, 0.5);

}
NT2_TEST_CASE_TPL(poly2, NT2_REAL_TYPES)
{
 typedef typename nt2::meta::as_complex<T>::type  cT;
 typedef T r_t;
  using nt2::poly;
  using nt2::tag::poly_;

  nt2::table<cT> p = nt2::cons(nt2::of_size(1, 5), cT(1), cT(-6), cT(15), cT(-18),  cT(10));
  nt2::table<cT> z = nt2::cons(nt2::of_size(1, 4), cT(1, 1), cT(1, -1), cT(2, 1), cT(2, -1));
  nt2::table<cT> p1 = nt2::poly(z);
  NT2_TEST_ULP_EQUAL(p, p1, 0.5);

}
