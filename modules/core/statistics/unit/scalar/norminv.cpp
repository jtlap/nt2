//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/include/functions/norminv.hpp>
#include <nt2/include/functions/eye.hpp>
#include <nt2/include/functions/cons.hpp>
#include <nt2/include/functions/linspace.hpp>
#include <nt2/include/functions/ones.hpp>
#include <nt2/include/functions/abs.hpp>
#include <nt2/include/functions/repnum.hpp>
#include <nt2/sdk/unit/tests.hpp>
#include <nt2/sdk/unit/module.hpp>

#include <nt2/constant/constant.hpp>
#include <nt2/table.hpp>

NT2_TEST_CASE_TPL ( norminv_1,  NT2_REAL_TYPES)
{
  using nt2::norminv;
  using nt2::tag::norminv_;
  using nt2::_;
  // specific values tests
  NT2_TEST_ULP_EQUAL(norminv(nt2::Nan<T>()), nt2::Nan<T>(), 0.5);
  NT2_TEST_ULP_EQUAL(norminv(T(0.841344746068542948585232545632)), nt2::One<T>(), 3);
  NT2_TEST_ULP_EQUAL(norminv(T(0.158655253931457051414767454368)), nt2::Mone<T>(), 6.5);
  NT2_TEST_ULP_EQUAL(norminv(nt2::Zero<T>()), nt2::Minf<T>(), 0.5);
  NT2_TEST_ULP_EQUAL(norminv(nt2::One<T>()), nt2::Inf<T>(), 0.5);
} // end of test for floating_

NT2_TEST_CASE_TPL ( norminv_2,  NT2_REAL_TYPES)
{
  using nt2::norminv;
  using nt2::tag::norminv_;
  using nt2::_;
  // specific values tests
  NT2_TEST_ULP_EQUAL(norminv(nt2::Nan<T>(), nt2::One<T>()), nt2::Nan<T>(), 0.5);
  NT2_TEST_ULP_EQUAL(norminv(T(0.841344746068542948585232545632), nt2::One<T>()), nt2::Two<T>(), 3);
  NT2_TEST_ULP_EQUAL(norminv(T(0.158655253931457051414767454368), nt2::One<T>()), nt2::Zero<T>(), 6.5);
  NT2_TEST_ULP_EQUAL(norminv(nt2::One<T>(), nt2::One<T>()), nt2::Inf<T>(), 0.5);
  NT2_TEST_ULP_EQUAL(norminv(nt2::Zero<T>(), nt2::One<T>()), nt2::Minf<T>(), 0.5);
} // end of test for floating_

NT2_TEST_CASE_TPL ( norminv_1v,  NT2_REAL_TYPES)
{
  using nt2::norminv;
  using nt2::tag::norminv_;
  using nt2::_;
  // specific values tests
  NT2_TEST_ULP_EQUAL(norminv(nt2::repnum(nt2::Nan<T>(), 10, 2)), nt2::repnum(nt2::Nan<T>(), 10, 2), 0.5);
  NT2_TEST_ULP_EQUAL(norminv(nt2::repnum(T(0.841344746068542948585232545632), 10, 2)), nt2::repnum(nt2::One<T>(), 10, 2), 3);
  NT2_TEST_ULP_EQUAL(norminv(nt2::repnum(T(0.158655253931457051414767454368), 10, 2)), nt2::repnum(nt2::Mone<T>(), 10, 2), 6.5);
  NT2_TEST_ULP_EQUAL(norminv(nt2::repnum(nt2::Zero<T>(), 10, 2)), nt2::repnum(nt2::Minf<T>(), 10, 2), 0.5);
  NT2_TEST_ULP_EQUAL(norminv(nt2::repnum(nt2::One<T>(), 10, 2)), nt2::repnum(nt2::Inf<T>(), 10, 2), 0.5);
}

NT2_TEST_CASE_TPL ( norminv_2v,  NT2_REAL_TYPES)
{
  using nt2::norminv;
  using nt2::tag::norminv_;
  using nt2::_;
  // specific values tests
  NT2_TEST_ULP_EQUAL(norminv(nt2::repnum(nt2::Nan<T>(), 10, 2), nt2::One<T>()),  nt2::repnum(nt2::Nan<T>(), 10, 2), 0.5);
  NT2_TEST_ULP_EQUAL(norminv(nt2::repnum(T(0.841344746068542948585232545632), 10, 2), nt2::One<T>()),  nt2::repnum(nt2::Two<T>(), 10, 2), 3);
  NT2_TEST_ULP_EQUAL(norminv(nt2::repnum(T(0.158655253931457051414767454368), 10, 2), nt2::One<T>()),  nt2::repnum(nt2::Zero<T>(), 10, 2), 6.5);
  NT2_TEST_ULP_EQUAL(norminv(nt2::repnum(nt2::One<T>(), 10, 2), nt2::One<T>()),  nt2::repnum(nt2::Inf<T>(), 10, 2), 0.5);
  NT2_TEST_ULP_EQUAL(norminv(nt2::repnum(nt2::Zero<T>(), 10, 2), nt2::One<T>()),  nt2::repnum(nt2::Minf<T>(), 10, 2), 0.5);
} // end of test for floating_

NT2_TEST_CASE_TPL ( norminv_conf,  NT2_REAL_TYPES)
{
  using nt2::norminv;
  using nt2::tag::norminv_;
  using nt2::_;
  // specific values tests
  nt2::table<T> a =  nt2::linspace(T(0), T(1), 5);
  nt2::table<T> r, plo, pup;
  nt2::table<T> cov = nt2::eye(2, nt2::meta::as_<T>());
  nt2::tie(r, plo, pup) = nt2::norminv(a, T(1), T(2), cov, T(0.05));
  nt2::table<T> rr = nt2::cons<T>( -nt2::Inf<T>(),    -3.489795003921636e-01,
                     1.000000000000000e+00,     2.348979500392164e+00,
                     nt2::Inf<T>()
                   );
  nt2::table<T> pplo = nt2::cons<T>(-nt2::Inf<T>(),     -2.713102668956324e+00,
                      -9.599639845400545e-01,    -1.514366817199697e-02,
                      nt2::Nan<T>()
                     );
  nt2::table<T> ppup = nt2::cons<T>(nt2::Nan<T>(),      2.015143668171997e+00,
                      2.959963984540054e+00,     4.713102668956324e+00,
                      nt2::Inf<T>()
                     );
  NT2_TEST_ULP_EQUAL(r, rr, 6);
  NT2_TEST_ULP_EQUAL(plo, pplo, 600);
  NT2_TEST_ULP_EQUAL(pup, ppup, 1);
} // end of test for floating_
