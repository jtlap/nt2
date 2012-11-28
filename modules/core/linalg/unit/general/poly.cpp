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
#include <nt2/include/constants/one.hpp>
#include <nt2/include/constants/ten.hpp>
#include <nt2/include/constants/eps.hpp>
#include <nt2/include/constants/two.hpp>
#include <nt2/include/functions/rec.hpp>
#include <nt2/include/functions/ones.hpp>
#include <nt2/include/functions/ulpdist.hpp>
#include <nt2/include/functions/isulpequal.hpp>
#include <nt2/sdk/unit/tests.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/exceptions.hpp>


NT2_TEST_CASE_TPL(poly, NT2_REAL_TYPES)
{
  typedef T r_t;
  using nt2::poly;
  using nt2::tag::poly_;
//  nt2::table<T> n = nt2::eye(2, 2, nt2::meta::as_<T>());
  nt2::table<T> n = nt2::ones(1, 2,  nt2::meta::as_<T>());
  nt2::table<T> p = nt2::poly(n);
  nt2::table<T> pp(nt2::of_size(1, 3));
  pp(1) = pp(3) = T(1); pp(2) = T(-2);
  NT2_DISPLAY(n);
  NT2_DISPLAY(pp);
  NT2_DISPLAY(p);
  NT2_TEST(nt2::isulpequal(pp, p, 0.5));


  T z[] = { 1,   -10,    35,   -50,    24};
  nt2::table<T> n1 = nt2::_(T(1), T(4));
  nt2::table<T> p1 = nt2::poly(n1);
  nt2::table<T> pp1(nt2::of_size(1, 5), &z[0], &z[5]);
  NT2_DISPLAY(n1);
  NT2_DISPLAY(pp1);
  NT2_DISPLAY(p1);
  NT2_TEST(nt2::isulpequal(pp1, p1, 0.5));

}
