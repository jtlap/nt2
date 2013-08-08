//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/include/functions/asinh.hpp>
#include <nt2/exponential/constants.hpp>
#include <nt2/sdk/functor/meta/call.hpp>
#include <nt2/sdk/unit/tests/ulp.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/complex/meta/as_complex.hpp>
#include <complex>
#include <boost/math/complex/asinh.hpp>

NT2_TEST_CASE_TPL ( asinh_real__1_0,  NT2_REAL_TYPES)
{

  using nt2::asinh;
  using nt2::tag::asinh_;
  typedef std::complex<T> cT;
  typedef typename nt2::meta::call<asinh_(cT)>::type r_t;
  typedef typename nt2:: meta::as_complex<T>::type wished_r_t;

  NT2_TEST_TYPE_IS(r_t, wished_r_t);

  // specific values tests
   NT2_TEST_ULP_EQUAL(nt2::asinh(cT(nt2::Zero<T>(),  nt2::Zero<T>())), cT(nt2::Zero<T>(), nt2::Zero<T>()), 0.75);
   NT2_TEST_ULP_EQUAL(nt2::asinh(cT(nt2::Nan  <T>(), nt2::Zero<T>())), cT(nt2::Nan <T>(), nt2::Zero<T>()), 0.75);
   NT2_TEST_ULP_EQUAL(nt2::asinh(cT(nt2::One  <T>(), nt2::Inf <T>())), cT(nt2::Inf<T>(),  nt2::Pio_2<T>()), 0.75);
   NT2_TEST_ULP_EQUAL(nt2::asinh(cT(nt2::One  <T>(), nt2::Nan <T>())), cT(nt2::Nan<T>(),  nt2::Nan<T>()), 0.75);

   NT2_TEST_ULP_EQUAL(nt2::asinh(cT(nt2::Inf  <T>(), nt2::One <T>())), cT(nt2::Inf <T>(), nt2::Zero<T>()), 0.75);
   NT2_TEST_ULP_EQUAL(nt2::asinh(cT(nt2::Inf  <T>(), nt2::Inf<T>())),  cT(nt2::Inf <T>(), nt2::Pi<T>()/4), 0.75);
   NT2_TEST_ULP_EQUAL(nt2::asinh(cT(nt2::Inf  <T>(), nt2::Nan<T>())),  cT(nt2::Inf <T>(), nt2::Nan<T>()), 0.75);
   NT2_TEST_ULP_EQUAL(nt2::asinh(cT(nt2::Nan  <T>(), nt2::One<T>())),  cT(nt2::Nan <T>(), nt2::Nan<T>()), 0.75);
   NT2_TEST_ULP_EQUAL(nt2::asinh(cT(nt2::Nan  <T>(), nt2::Inf<T>())),  cT(nt2::Minf <T>(), nt2::Nan<T>()), 0.75);
   NT2_TEST_ULP_EQUAL(nt2::asinh(cT(nt2::Nan  <T>(), nt2::Nan<T>())),  cT(nt2::Nan <T>(), nt2::Nan<T>()), 0.75);
#ifndef BOOST_SIMD_NO_INVALIDS
   NT2_TEST_ULP_EQUAL(nt2::asinh(cT(nt2::One  <T>(), -nt2::Inf <T>())), cT(nt2::Inf<T>(),  -nt2::Pio_2<T>()), 0.75);
   NT2_TEST_ULP_EQUAL(nt2::asinh(cT(nt2::One  <T>(), -nt2::Nan <T>())), cT(nt2::Nan<T>(),  -nt2::Nan<T>()), 0.75);
   NT2_TEST_ULP_EQUAL(nt2::asinh(cT(nt2::Inf  <T>(), -nt2::One <T>())), cT(nt2::Inf <T>(), -nt2::Zero<T>()), 0.75);
   NT2_TEST_ULP_EQUAL(nt2::asinh(cT(nt2::Inf  <T>(), -nt2::Inf<T>())),  cT(nt2::Inf <T>(), -nt2::Pi<T>()/4), 0.75);
   NT2_TEST_ULP_EQUAL(nt2::asinh(cT(nt2::Inf  <T>(), -nt2::Nan<T>())),  cT(nt2::Inf <T>(), -nt2::Nan<T>()), 0.75);
   NT2_TEST_ULP_EQUAL(nt2::asinh(cT(nt2::Nan  <T>(), -nt2::One<T>())),  cT(nt2::Nan <T>(), -nt2::Nan<T>()), 0.75);
   NT2_TEST_ULP_EQUAL(nt2::asinh(cT(nt2::Nan  <T>(), -nt2::Inf<T>())),  cT(nt2::Minf <T>(), -nt2::Nan<T>()), 0.75);
   NT2_TEST_ULP_EQUAL(nt2::asinh(cT(nt2::Nan  <T>(), -nt2::Nan<T>())),  cT(nt2::Nan <T>(), -nt2::Nan<T>()), 0.75);
#endif

} // end of test for floating_

//  casinh(conj(z)) = conj(casinh(z)) and casinh is odd.
//  casinh(+0 + i0) returns 0 + i0.
//  casinh(x + i inf) returns +inf + ipi /2 for positive-signed finite x.
//  casinh(x + iNaN) returns NaN + iNaN and optionally raises the invalid floating-point exception, for finite x.
//  casinh(+inf + iy) returns +inf + i0 for positive-signed finite y.
//  casinh(+inf + i inf) returns +inf + ipi /4.
//  casinh(+inf + iNaN) returns +inf + iNaN.
//  casinh(NaN + i0) returns NaN + i0.
//  casinh(NaN + iy) returns NaN + iNaN and optionally raises the invalid floating-point exception, for finite nonzero y.
//  casinh(NaN + i inf) returns ±inf + iNaN (where the sign of the real part of the result is unspecified).
//  casinh(NaN + iNaN) returns NaN + iNaN.
