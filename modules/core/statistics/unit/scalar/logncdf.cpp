//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/include/functions/logncdf.hpp>
#include <nt2/include/functions/cons.hpp>
#include <nt2/include/functions/eye.hpp>
#include <nt2/include/functions/ones.hpp>
#include <nt2/include/functions/abs.hpp>
#include <nt2/sdk/unit/tests.hpp>
#include <nt2/sdk/unit/module.hpp>

#include <nt2/constant/constant.hpp>
#include <nt2/table.hpp>

NT2_TEST_CASE_TPL ( logncdf_1,  (float)(double))//NT2_REAL_TYPES)
{

  using nt2::logncdf;
  using nt2::tag::logncdf_;
  using nt2::_;


  // specific values tests
  NT2_TEST_ULP_EQUAL(logncdf(nt2::Nan<T>()), nt2::Nan<T>(), 0.5);
  NT2_TEST_ULP_EQUAL(logncdf(nt2::One<T>()), nt2::Half<T>(), 1.5);
  NT2_TEST_ULP_EQUAL(logncdf(nt2::Mone<T>()), nt2::Zero<T>(), 6);
  NT2_TEST_ULP_EQUAL(logncdf(nt2::Zero<T>()), nt2::Zero<T>(), 0.5);
  NT2_TEST_ULP_EQUAL(logncdf(nt2::Inf<T>()), nt2::One<T>(), 0.5);
  NT2_TEST_ULP_EQUAL(logncdf(nt2::Minf<T>()), nt2::Zero<T>(), 0.5);
} // end of test for floating_

NT2_TEST_CASE_TPL ( logncdf_2,  NT2_REAL_TYPES)
{

  using nt2::logncdf;
  using nt2::tag::logncdf_;
  using nt2::_;


  // specific values tests
  NT2_TEST_ULP_EQUAL(logncdf(nt2::Nan<T>(), nt2::One<T>()), nt2::Nan<T>(), 0.5);
  NT2_TEST_ULP_EQUAL(logncdf(nt2::Zero<T>(), nt2::One<T>() ), nt2::Zero<T>(), 0.5);
  NT2_TEST_ULP_EQUAL(logncdf(nt2::Mone<T>(), nt2::One<T>()),  nt2::Zero<T>(), 25);
  NT2_TEST_ULP_EQUAL(logncdf(nt2::Inf<T>(), nt2::One<T>()), nt2::One<T>(), 0.5);
  NT2_TEST_ULP_EQUAL(logncdf(nt2::Minf<T>(), nt2::One<T>()), nt2::Zero<T>(), 0.5);
  nt2::table<T> a = _(T(0), T(1), T(4));
  nt2::table<T> r0 = nt2::cons<T>( 0,                         5.000000000000000e-01,
                                   7.558914042144173e-01,     8.640313923585755e-01,
                                   9.171714809983015e-01
                                 );

  NT2_TEST_ULP_EQUAL(logncdf(a), r0, 5);
  NT2_TEST_ULP_EQUAL(logncdf(a, nt2::Zero<T>()), r0, 5);
  NT2_TEST_ULP_EQUAL(logncdf(a, nt2::Zero<T>(), nt2::One<T>()), r0, 5);

  nt2::table<T> r1 =   nt2::cons<T>( 0,     1.586552539314571e-01,
                                     9.563135117897992e-02,     2.862562397124228e-02,
                                     4.478308308837837e-03
                                   );
  NT2_TEST_ULP_EQUAL(logncdf(a, a), r1, 10);

  nt2::table<T> r, plo, pup;
  nt2::table<T> cov = nt2::eye(2, nt2::meta::as_<T>());
  nt2::tie(r, plo, pup) = nt2::logncdf(a, T(1), T(1), cov, T(0.05));
  nt2::table<T> rr = nt2::cons<T>(0,                         1.586552539314571e-01,
                                  3.794777011200849e-01,     5.392769436822993e-01,
                                  6.503606618993090e-01
                                 );
  nt2::table<T> pplo = nt2::cons<T>(0,                         8.103458710481820e-05,
                                    9.211248673176946e-03,     3.068235790587167e-02,
                                    4.318884284369216e-02
                                   );
  nt2::table<T> ppup = nt2::cons<T>(nt2::Nan<T>(),             9.617867537625060e-01,
                                    9.593602138644935e-01,     9.806838876045809e-01,
                                    9.935661805604945e-01);
  NT2_TEST_ULP_EQUAL(r, rr, 10);
  NT2_TEST_ULP_EQUAL(plo, pplo, 10000);
  NT2_TEST_ULP_EQUAL(pup, ppup, 1);
//   nt2::tie(r, plo, pup) = nt2::logncdf(a, T(0), T(1), cov, T(0.05));
//   rr = nt2::cons<T>(2.8665157187948740877e-07, 3.1671241833184224292e-05, 0.0013498980316300926256, 0.022750131948179170421,
//                     0.15865525393145676891, 0.5, 0.84134474606854325884, 0.97724986805182079141, 0.99865010196836989653,
//                     0.999968328758166769, 0.99999971334842807646
//                    );
//   pplo = nt2::cons<T>(4.0245808925994784484e-51, 6.6433555372421765656e-34, 1.8242118763224949552e-20, 8.7045905576395988544e-11,
//                                     8.1034587105013216376e-05, 0.025000000000000008327, 0.038213246237494107038, 0.0085951345568521120982,
//                                     0.00069204060577546125475, 2.2407816472484755717e-05, 2.9586849442854012488e-07
//                                    );
//   ppup = nt2::cons<T>(0.99999970413150551796, 0.99997759218352755273, 0.99930795939422456531, 0.99140486544314787576,
//                                    0.96178675376250588602, 0.9749999999999999778, 0.99991896541289493339, 0.99999999991295407398,
//                                    1.0, 1.0, 1.0
//                                   );
//   NT2_TEST_ULP_EQUAL(r, rr, 5);
//   NT2_TEST_ULP_EQUAL(plo, pplo, 600);
//   NT2_TEST_ULP_EQUAL(pup, ppup, 1);
} // end of test for floating_

