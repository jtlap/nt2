//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/include/functions/acosh.hpp>
#include <nt2/exponential/constants.hpp>
#include <nt2/sdk/functor/meta/call.hpp>
#include <nt2/sdk/unit/tests/ulp.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/complex/meta/as_complex.hpp>
#include <complex>
#include <nt2/include/functions/splat.hpp>


NT2_TEST_CASE_TPL ( acosh_real__1_0, NT2_REAL_TYPES)
{
  using nt2::acosh;
  using nt2::tag::acosh_;
  using boost::simd::native;
  typedef NT2_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef std::complex<T>                cT;
  typedef native<T,ext_t>                vT;
  typedef native<cT,ext_t>              cvT;
  typedef typename nt2::meta::call<acosh_(cvT)>::type r_t;


  // specific values tests
  NT2_TEST_ULP_EQUAL(nt2::acosh(cvT(nt2::One<vT>(), nt2::Zero<vT>())),  cvT(nt2::Zero<vT>(), nt2::Zero<vT>()), 0.75);
  NT2_TEST_ULP_EQUAL(nt2::acosh(cvT(nt2::Zero<vT>(), nt2::Zero<vT>())),  cvT(nt2::Zero<vT>(), nt2::Pio_2<vT>()), 0.75);
  NT2_TEST_ULP_EQUAL(nt2::acosh(cvT(nt2::Mzero<vT>(), nt2::Zero<vT>())), cvT(nt2::Zero<vT>(), nt2::Pio_2<vT>()), 0.75);
#ifndef BOOSvT_SIMD_NO_INVALIDS
  NT2_TEST_ULP_EQUAL(nt2::acosh(cvT(nt2::One  <vT>(), nt2::Nan <vT>())), cvT(nt2::Nan<vT>(),  nt2::Nan<vT>()), 0.75);
  NT2_TEST_ULP_EQUAL(nt2::acosh(cvT(nt2::Minf <vT>(), nt2::Nan<vT>())),  cvT(nt2::Inf<vT>(), nt2::Nan<vT>()), 0.75);
  NT2_TEST_ULP_EQUAL(nt2::acosh(cvT(nt2::Inf  <vT>(), nt2::Nan<vT>())),  cvT(nt2::Inf <vT>(), nt2::Nan<vT>()), 0.75);
  NT2_TEST_ULP_EQUAL(nt2::acosh(cvT(nt2::Nan  <vT>(), nt2::One<vT>())),  cvT(nt2::Nan <vT>(), nt2::Nan<vT>()), 0.75);
  NT2_TEST_ULP_EQUAL(nt2::acosh(cvT(nt2::Nan  <vT>(), nt2::Inf<vT>())),  cvT(nt2::Inf <vT>(), nt2::Nan<vT>()), 0.75);
  NT2_TEST_ULP_EQUAL(nt2::acosh(cvT(nt2::Nan  <vT>(), nt2::Nan<vT>())),  cvT(nt2::Nan <vT>(), nt2::Nan<vT>()), 0.75);
  // cacosh(+inf + iy) returns +inf + i0, for positive-signed finite y. --- matlab : Inf
  NT2_TEST_ULP_EQUAL(nt2::acosh(cvT(nt2::Inf  <vT>(), nt2::One <vT>())), cvT(nt2::Inf <vT>(), nt2::Zero<vT>()), 0.75);
  // cacosh(~inf + iy) returns +inf + i pi , for positive-signed finite y. --- matlab :  Inf + 3.1416i
  NT2_TEST_ULP_EQUAL(nt2::acosh(cvT(nt2::Minf <vT>(), nt2::One <vT>())), cvT(nt2::Inf<vT>(), nt2::Pi<vT>()), 0.75);
  // cacosh(x + i inf) returns +inf + i pi /2, for finite x.               --- matlab : Inf +    NaNi
  NT2_TEST_ULP_EQUAL(nt2::acosh(cvT(nt2::One  <vT>(), nt2::Inf <vT>())), cvT(nt2::Inf<vT>(),  nt2::Pio_2<vT>()), 0.75);
  NT2_TEST_ULP_EQUAL(nt2::acosh(cvT(nt2::One <vT>(), nt2::Inf<vT>())),  nt2::acosh(cvT(nt2::One <vT>(), nt2::Inf<vT>())), 0.75);
  // cacosh(~inf + i inf) returns +inf + i3 pi /4.                         --- matlab : Inf +    NaNi
  NT2_TEST_ULP_EQUAL(nt2::acosh(cvT(nt2::Minf <vT>(), nt2::Inf<vT>())),  cvT(nt2::Inf<vT>(), 3*nt2::Pi<vT>()/4), 0.75);
  NT2_TEST_ULP_EQUAL(nt2::acosh(cvT(nt2::Minf <vT>(), nt2::Inf<vT>())),  nt2::acosh(cvT(nt2::Minf <vT>(), nt2::Inf<vT>())), 0.75);
  //  cacosh(+inf + i inf) returns +inf + i pi /4.
  NT2_TEST_ULP_EQUAL(nt2::acosh(cvT(nt2::Inf  <vT>(), nt2::Inf<vT>())),  cvT(nt2::Inf <vT>(),  nt2::Pi<vT>()/4), 0.75);
  //  cacosh(NaN + i0) returns NaN + iNan.
  NT2_TEST_ULP_EQUAL(nt2::acosh(cvT(nt2::Nan  <vT>(), nt2::Zero<vT>())), cvT(nt2::Nan <vT>(), nt2::Nan<vT>()), 0.75);
#endif
  NT2_TEST_ULP_EQUAL(nt2::acosh(nt2::splat<cvT>(cT(0.5, -0.5))), nt2::splat<cvT>(nt2::acosh(cT(0.5, -0.5))), 0.75);
  NT2_TEST_ULP_EQUAL(nt2::acosh(nt2::splat<cvT>(cT(1, 1))),      nt2::splat<cvT>(nt2::acosh(cT(1, 1))), 0.75);
  NT2_TEST_ULP_EQUAL(nt2::acosh(nt2::splat<cvT>(cT(1, 10))),     nt2::splat<cvT>(nt2::acosh(cT(1, 10))), 0.75);
  NT2_TEST_ULP_EQUAL(nt2::acosh(nt2::splat<cvT>(cT(10, 10))),    nt2::splat<cvT>(nt2::acosh(cT(10, 10))), 0.75);
  NT2_TEST_ULP_EQUAL(nt2::acosh(nt2::splat<cvT>(cT(10, 1))),     nt2::splat<cvT>(nt2::acosh(cT(10, 1))), 0.75);
} // end of test for floating_


