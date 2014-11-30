//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/include/functions/evcdf.hpp>
#include <nt2/include/functions/eye.hpp>
#include <nt2/include/functions/ones.hpp>
#include <nt2/include/functions/abs.hpp>
#include <nt2/include/functions/cons.hpp>
#include <nt2/include/functions/repnum.hpp>
#include <nt2/include/functions/linspace.hpp>
#include <nt2/sdk/unit/tests.hpp>
#include <nt2/sdk/unit/module.hpp>

#include <nt2/constant/constant.hpp>
#include <nt2/table.hpp>

NT2_TEST_CASE_TPL ( evcdf_1,  NT2_REAL_TYPES)
{
  using nt2::evcdf;
  using nt2::tag::evcdf_;
  using nt2::_;
  // specific values tests
  NT2_TEST_ULP_EQUAL(evcdf(nt2::Nan<T>()), nt2::Nan<T>(), 0.5);
  NT2_TEST_ULP_EQUAL(evcdf(nt2::One<T>()), T(9.340119641546875e-01), 0.5);
  NT2_TEST_ULP_EQUAL(evcdf(nt2::Mone<T>()), T(3.077993724446537e-01), 0.75);
  NT2_TEST_ULP_EQUAL(evcdf(nt2::Zero<T>()), T(6.321205588285577e-01), 0.5);
  NT2_TEST_ULP_EQUAL(evcdf(nt2::Inf<T>()), nt2::One<T>(), 0.5);
  NT2_TEST_ULP_EQUAL(evcdf(nt2::Minf<T>()), nt2::Zero<T>(), 0.5);
  nt2::table<T> a = nt2::_(T(-5), T(1), T(5));
  nt2::table<T> r, plo, pup;
  nt2::table<T> cov = nt2::eye(2, nt2::meta::as_<T>());
  nt2::tie(r, plo, pup) = nt2::evcdf(a, T(1), T(1), cov, T(0.05));
  nt2::table<T> rr = nt2::cons<T>(
     2.475682607247459e-03,     6.715297932158510e-03,     1.814892693833351e-02,     4.856800709954660e-02,     1.265769815068834e-01,
     3.077993724446537e-01,     6.321205588285577e-01,     9.340119641546875e-01,     9.993820210106689e-01,     9.999999981078213e-01,
     1.000000000000000e+00
  );


 nt2::table<T> pplo = nt2::cons<T>(
     1.646555038460669e-08,     3.077756412240543e-07,     5.665352941264714e-06,     1.012415870823350e-04,     1.689271456668030e-03,
     2.274770989563399e-02,     1.313921262892844e-01,     1.563565824722985e-01,     8.817672578646583e-02,     4.002289043877510e-02,
     1.674642024412162e-02
 );


 nt2::table<T> ppup = nt2::cons<T>(
     1.000000000000000e+00,     1.000000000000000e+00,     1.000000000000000e+00,     9.999999999766938e-01,     9.999802660444745e-01,
     9.972093351090986e-01,     9.991741285154262e-01,     1.000000000000000e+00,     1.000000000000000e+00,     1.000000000000000e+00,
     1.000000000000000e+00
 );
  NT2_TEST_ULP_EQUAL(r, rr, 0.5);
  NT2_TEST_ULP_EQUAL(plo, pplo, 10.5);
  NT2_TEST_ULP_EQUAL(pup, ppup, 1);
} // end of test for floating_

