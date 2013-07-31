//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/include/functions/normcdf.hpp>
#include <nt2/include/functions/cons.hpp>
#include <nt2/include/functions/eye.hpp>
#include <nt2/include/functions/ones.hpp>
#include <nt2/include/functions/abs.hpp>
#include <nt2/sdk/unit/tests.hpp>
#include <nt2/sdk/unit/module.hpp>

#include <nt2/constant/constant.hpp>
#include <nt2/table.hpp>

NT2_TEST_CASE_TPL ( normcdf_1,  (float)(double))//NT2_REAL_TYPES)
{

  using nt2::normcdf;
  using nt2::tag::normcdf_;
  using nt2::_;


  // specific values tests
  NT2_TEST_ULP_EQUAL(normcdf(nt2::Nan<T>()), nt2::Nan<T>(), 0.5);
  NT2_TEST_ULP_EQUAL(normcdf(nt2::One<T>()), T(0.841344746068542948585232545632), 1.5);
  NT2_TEST_ULP_EQUAL(normcdf(nt2::Mone<T>()), T(0.158655253931457051414767454368), 5.5);
  NT2_TEST_ULP_EQUAL(normcdf(nt2::Zero<T>()), nt2::Half<T>(), 0.5);
  NT2_TEST_ULP_EQUAL(normcdf(nt2::Inf<T>()), nt2::One<T>(), 0.5);
  NT2_TEST_ULP_EQUAL(normcdf(nt2::Minf<T>()), nt2::Zero<T>(), 0.5);
} // end of test for floating_

NT2_TEST_CASE_TPL ( normcdf_2,  NT2_REAL_TYPES)
{

  using nt2::normcdf;
  using nt2::tag::normcdf_;
  using nt2::_;


  // specific values tests
  NT2_TEST_ULP_EQUAL(normcdf(nt2::Nan<T>(), nt2::One<T>()), nt2::Nan<T>(), 0.5);
  NT2_TEST_ULP_EQUAL(normcdf(nt2::Zero<T>(), nt2::One<T>() ), T(0.158655253931457051414767454368), 5.5);
  NT2_TEST_ULP_EQUAL(normcdf(nt2::Mone<T>(), nt2::One<T>()),  T(0.0227501319481792072002826371665), 25);
  NT2_TEST_ULP_EQUAL(normcdf(nt2::Inf<T>(), nt2::One<T>()), nt2::One<T>(), 0.5);
  NT2_TEST_ULP_EQUAL(normcdf(nt2::Minf<T>(), nt2::One<T>()), nt2::Zero<T>(), 0.5);
  nt2::table<T> a = _(T(-5), T(1), T(5));
  nt2::table<T> r0 = nt2::cons<T>( 2.8665157187948740877e-07, 3.1671241833184224292e-05, 0.0013498980316300926256, 0.022750131948179170421,
                                  0.15865525393145676891, 0.5, 0.84134474606854325884, 0.97724986805182079141, 0.99865010196836989653,
                                  0.999968328758166769, 0.99999971334842807646
                                );

  NT2_TEST_ULP_EQUAL(normcdf(a), r0, 3);
  NT2_TEST_ULP_EQUAL(normcdf(a, nt2::Zero<T>()), r0, 3);
  NT2_TEST_ULP_EQUAL(normcdf(a, nt2::Zero<T>(), nt2::One<T>()), r0, 3);
  nt2::table<T> r1 =  nt2::repnum(T(0.5), 1, 11);
  NT2_TEST_ULP_EQUAL(normcdf(a, a), r1, 1);
  NT2_TEST_ULP_EQUAL(normcdf(a, a, T(2)),r1, 1);
  r1(6) = nt2::Nan<T>();
  NT2_TEST_ULP_EQUAL(normcdf(a, a, nt2::abs(a)), r1, 1);
  nt2::table<T> r, plo, pup;
  nt2::table<T> cov = nt2::eye(2, nt2::meta::as_<T>());
  nt2::tie(r, plo, pup) = nt2::normcdf(a, nt2::ones(size(a), nt2::meta::as_<T>()), T(1), cov, T(0.05));
  nt2::table<T> rr = nt2::cons<T>(9.8658764503824527049e-10, 2.8665157187948740877e-07, 3.1671241833184224292e-05,
                                  0.0013498980316300926256, 0.022750131948179170421, 0.15865525393145676891, 0.5,
                                  0.84134474606854325884, 0.97724986805182079141, 0.99865010196836989653, 0.999968328758166769
                                 );
  nt2::table<T> pplo = nt2::cons<T>(3.9713608935672806662e-72, 4.0245808925994784484e-51, 6.6433555372421765656e-34, 1.8242118763224949552e-20,
                                    8.7045905576395988544e-11, 8.1034587105013216376e-05, 0.025000000000000008327, 0.038213246237494107038,
                                    0.0085951345568521120982, 0.00069204060577546125475, 2.2407816472484755717e-05
                                   );
  nt2::table<T> ppup = nt2::cons<T>(0.99999999840970821285, 0.99999970413150551796, 0.99997759218352755273, 0.99930795939422456531,
                                   0.99140486544314787576, 0.96178675376250588602, 0.9749999999999999778, 0.99991896541289493339,
                                   0.99999999991295407398, 1.0, 1.0);
  NT2_TEST_ULP_EQUAL(r, rr, 10);
  NT2_TEST_ULP_EQUAL(plo, pplo, 600);
  NT2_TEST_ULP_EQUAL(pup, ppup, 1);
  nt2::tie(r, plo, pup) = nt2::normcdf(a, T(0), T(1), cov, T(0.05));
  rr = nt2::cons<T>(2.8665157187948740877e-07, 3.1671241833184224292e-05, 0.0013498980316300926256, 0.022750131948179170421,
                    0.15865525393145676891, 0.5, 0.84134474606854325884, 0.97724986805182079141, 0.99865010196836989653,
                    0.999968328758166769, 0.99999971334842807646
                   );
  pplo = nt2::cons<T>(4.0245808925994784484e-51, 6.6433555372421765656e-34, 1.8242118763224949552e-20, 8.7045905576395988544e-11,
                                    8.1034587105013216376e-05, 0.025000000000000008327, 0.038213246237494107038, 0.0085951345568521120982,
                                    0.00069204060577546125475, 2.2407816472484755717e-05, 2.9586849442854012488e-07
                                   );
  ppup = nt2::cons<T>(0.99999970413150551796, 0.99997759218352755273, 0.99930795939422456531, 0.99140486544314787576,
                                   0.96178675376250588602, 0.9749999999999999778, 0.99991896541289493339, 0.99999999991295407398,
                                   1.0, 1.0, 1.0
                                  );
  NT2_TEST_ULP_EQUAL(r, rr, 3);
  NT2_TEST_ULP_EQUAL(plo, pplo, 600);
  NT2_TEST_ULP_EQUAL(pup, ppup, 1);
} // end of test for floating_

