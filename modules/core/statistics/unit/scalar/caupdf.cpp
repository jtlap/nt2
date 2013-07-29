//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/include/functions/caupdf.hpp>
#include <nt2/include/constants/invpi.hpp>
#include <nt2/include/functions/repnum.hpp>
#include <nt2/include/functions/transpose.hpp>
#include <nt2/include/functions/cons.hpp>
#include <nt2/sdk/unit/tests/ulp.hpp>
#include <nt2/sdk/unit/module.hpp>

#include <nt2/constant/constant.hpp>
#include <nt2/table.hpp>


NT2_TEST_CASE_TPL ( caupdf_real__2_0,  NT2_REAL_TYPES)
{

  using nt2::caupdf;
  using nt2::tag::caupdf_;
  // specific values tests
  NT2_TEST_ULP_EQUAL(caupdf(nt2::Nan<T>()), nt2::Nan<T>(), 0);
  NT2_TEST_ULP_EQUAL(caupdf(nt2::One<T>()), nt2::Invpi<T>()/2, 0);
  NT2_TEST_ULP_EQUAL(caupdf(nt2::Zero<T>()), nt2::Invpi<T>(), 0);
  NT2_TEST_ULP_EQUAL(caupdf(nt2::Inf<T>()), nt2::Zero<T>(), 0);
  NT2_TEST_ULP_EQUAL(caupdf(nt2::Minf<T>()), nt2::Zero<T>(), 0);
} // end of test for floating_

NT2_TEST_CASE_TPL ( caupdf_2,  NT2_REAL_TYPES)
{

  using nt2::caupdf;
  using nt2::tag::caupdf_;
  using nt2::_;


  // specific values tests
  NT2_TEST_ULP_EQUAL(caupdf(nt2::Nan<T>(), nt2::One<T>()), nt2::Nan<T>(), 0);
  NT2_TEST_ULP_EQUAL(caupdf(nt2::Zero<T>(), nt2::One<T>() ), nt2::Invpi<T>()/2, 0);
  NT2_TEST_ULP_EQUAL(caupdf(nt2::One<T>(), nt2::One<T>()), nt2::Invpi<T>(), 0);
  NT2_TEST_ULP_EQUAL(caupdf(nt2::Inf<T>(), nt2::One<T>()), nt2::Zero<T>(), 0);
  NT2_TEST_ULP_EQUAL(caupdf(nt2::Minf<T>(), nt2::One<T>()), nt2::Zero<T>(), 0);
  std::cout << std::setprecision(20);
  nt2::table<T> a = _(T(-5), T(1), T(5));
  nt2::table<T> r1 = nt2::cons<T>(0.0086029698968592086677, 0.012242687930145795816, 0.018724110951987688739,
                                  0.031830988618379067734, 0.063661977236758135468, 0.15915494309189534561,
                                  0.31830988618379069122, 0.15915494309189534561, 0.063661977236758135468,
                                  0.031830988618379067734, 0.018724110951987688739);
  NT2_TEST_ULP_EQUAL(caupdf(a, nt2::One<T>()), r1, 1); //nt2::repnum(T( 0.318309886183790691223809), 4, 4));
  a = nt2::reshape(_(T(1), T(16)), 4, 4);
  NT2_DISPLAY(a);
  nt2::table<T> r2 = nt2::trans(nt2::cons<T>(nt2::of_size(4, 4),
                                             0.15915494309189534561, 0.031830988618379067734, 0.0093620554759938443695, 0.0043014849484296043339,
                                             0.12732395447351627094, 0.021952405943709701885, 0.0074896443807950753221, 0.0036798830772692566436,
                                             0.079577471545947672804, 0.015915494309189533867, 0.006121343965072897908, 0.0031830988618379071203,
                                             0.048970751720583183264, 0.012011693818256253055, 0.0050929581789406512191, 0.0027799990059719711932));
  NT2_TEST_ULP_EQUAL(caupdf(a, a, nt2::Two<T>()), nt2::repnum(T(0.15915494309189534561), 4, 4), 1);
  NT2_TEST_ULP_EQUAL(caupdf(a, nt2::One<T>(), nt2::Two<T>()), r2, 1);
  NT2_TEST_ULP_EQUAL(caupdf(a, a), nt2::repnum(T(0.31830988618379069122), 4, 4), 1);
  nt2::table<T> r3 = nt2::trans(nt2::cons<T>(nt2::of_size(4, 4),
                                             0.31830988618379069122, 0.063661977236758135468, 0.035367765131532294398, 0.024485375860291588163,
                                             0.15915494309189534561, 0.053051647697298448536, 0.031830988618379067734, 0.022736420441699337069,
                                             0.10610329539459689707, 0.045472840883398674139, 0.028937262380344608292, 0.021220659078919380802,
                                             0.079577471545947672804, 0.039788735772973836402, 0.026525823848649224268, 0.019894367886486918201
                                            ));
  NT2_TEST_ULP_EQUAL(caupdf(a, a, a), r3, 1);
} // end of test for floating_
