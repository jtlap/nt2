//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/include/functions/contfrac.hpp>
#include <nt2/include/functions/eye.hpp>
#include <nt2/include/functions/ones.hpp>
#include <nt2/include/functions/cons.hpp>
#include <nt2/include/functions/real.hpp>
#include <nt2/sdk/unit/tests/ulp.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/table.hpp>

NT2_TEST_CASE_TPL ( contfrac,  (float))//NT2_REAL_TYPES)
{

  using nt2::contfrac;
  using nt2::tag::contfrac_;
  nt2::table<T> p =  nt2::_(T(1), T(3));
  nt2::table<T> q =  p;
  nt2::table<T> cf = contfrac(p, q);

  NT2_TEST_ULP_EQUAL(cf(1), T(3)/T(5), 0.5);
}

NT2_TEST_CASE_TPL ( contfracx,  (float))//NT2_REAL_TYPES)
{

  using nt2::contfrac;
  using nt2::tag::contfrac_;
  nt2::table<T> p =  nt2::_(T(1), T(3));
  nt2::table<T> q =  p;
  nt2::table<T> x =  nt2::_(T(0), T(5));
  nt2::table<T> cf = contfrac(p, q, x);
  nt2::table<T> res = nt2::cons<T>(nt2::of_size(1, 6),
                                   6.00000000000000e-01,   3.94736842105263e-01,   2.91139240506329e-01,
                                   2.29166666666667e-01,   1.88284518828452e-01,   1.59459459459459e-01);
  nt2::table<T> res2 = nt2::cons<T>(nt2::of_size(1, 6),
                                   6.00000000000000e-01,   1.05263157894737e+00,   1.43478260869565e+00,
                                   1.77777777777778e+00,   2.09677419354839e+00,   2.40000000000000e+00);

  nt2::table<T> res3 = nt2::cons<T>(nt2::of_size(1, 6),
                                    6.00000000000000e-01,   7.80487804878049e-01,   8.51851851851852e-01,
                                    8.88888888888889e-01,   9.11330049261084e-01,   9.26315789473684e-01);
  NT2_DISPLAY(cf);
  NT2_TEST_ULP_EQUAL(cf, res, 1);
  cf = contfrac(p, q, x, nt2::lower_);
  NT2_TEST_ULP_EQUAL(cf, res, 1);
  cf = contfrac(p, q, x, nt2::upper_);
  NT2_TEST_ULP_EQUAL(cf, res2, 1);
  cf = contfrac(p, q, x, nt2::both_);
  NT2_TEST_ULP_EQUAL(cf, res3, 1);


}






