//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#define NT2_UNIT_MODULE "nt2 complex.exponential toolbox - acosh/scalar Mode"

//////////////////////////////////////////////////////////////////////////////
// unit test behavior of exponential components in scalar mode
//////////////////////////////////////////////////////////////////////////////
/// created by jt the 08/12/2010
///
#include <nt2/include/functions/acosh.hpp>
#include <boost/type_traits/is_same.hpp>
#include <nt2/sdk/functor/meta/call.hpp>
#include <nt2/sdk/meta/as_integer.hpp>
#include <nt2/sdk/meta/as_floating.hpp>
#include <nt2/sdk/meta/as_signed.hpp>
#include <nt2/sdk/meta/upgrade.hpp>
#include <nt2/sdk/meta/downgrade.hpp>
#include <nt2/sdk/meta/scalar_of.hpp>
#include <boost/dispatch/meta/as_floating.hpp>
#include <boost/type_traits/common_type.hpp>
#include <nt2/sdk/unit/tests.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/memory/buffer.hpp>
#include <nt2/toolbox/constant/constant.hpp>
#include <boost/math/complex/acosh.hpp>


NT2_TEST_CASE_TPL ( acosh_real__1_0,  (double))//NT2_REAL_TYPES)
{

  using nt2::acosh;
  using nt2::tag::acosh_;
  typedef std::complex<T> cT;
  typedef typename nt2::meta::call<acosh_(cT)>::type r_t;
  typedef typename nt2:: meta::as_complex<T>::type wished_r_t;


  // return type conformity test
//   NT2_TEST( (boost::is_same < r_t, wished_r_t >::value) );
  std::cout << std::endl;
  double ulpd;
  ulpd=0.0;


  // specific values tests
  NT2_TEST_ULP_EQUAL(nt2::acosh(cT(nt2::One<T>(), nt2::Zero<T>())),  cT(nt2::Zero<T>(), nt2::Zero<T>()), 0.75);
  NT2_TEST_ULP_EQUAL(nt2::acosh(cT(nt2::Zero<T>(), nt2::Zero<T>())),  cT(nt2::Zero<T>(), nt2::Pio_2<T>()), 0.75);
  NT2_TEST_ULP_EQUAL(nt2::acosh(cT(nt2::Mzero<T>(), nt2::Zero<T>())), cT(nt2::Zero<T>(), nt2::Pio_2<T>()), 0.75);
  NT2_TEST_ULP_EQUAL(nt2::acosh(cT(nt2::One  <T>(), nt2::Nan <T>())), cT(nt2::Nan<T>(),  nt2::Nan<T>()), 0.75);
  NT2_TEST_ULP_EQUAL(nt2::acosh(cT(nt2::Minf <T>(), nt2::Nan<T>())),  cT(nt2::Inf<T>(), nt2::Nan<T>()), 0.75);
  NT2_TEST_ULP_EQUAL(nt2::acosh(cT(nt2::Inf  <T>(), nt2::Nan<T>())),  cT(nt2::Inf <T>(), nt2::Nan<T>()), 0.75);
  NT2_TEST_ULP_EQUAL(nt2::acosh(cT(nt2::Nan  <T>(), nt2::One<T>())),  cT(nt2::Nan <T>(), nt2::Nan<T>()), 0.75);
  NT2_TEST_ULP_EQUAL(nt2::acosh(cT(nt2::Nan  <T>(), nt2::Inf<T>())),  cT(nt2::Inf <T>(), nt2::Nan<T>()), 0.75);
  NT2_TEST_ULP_EQUAL(nt2::acosh(cT(nt2::Nan  <T>(), nt2::Nan<T>())),  cT(nt2::Nan <T>(), nt2::Nan<T>()), 0.75);


// cacosh(+inf + iy) returns +inf + i0, for positive-signed finite y. --- matlab : Inf
  NT2_TEST_ULP_EQUAL(nt2::acosh(cT(nt2::Inf  <T>(), nt2::One <T>())), cT(nt2::Inf <T>(), nt2::Zero<T>()), 0.75);
  // cacosh(~inf + iy) returns +inf + i pi , for positive-signed finite y. --- matlab :  Inf + 3.1416i
  NT2_TEST_ULP_EQUAL(nt2::acosh(cT(nt2::Minf <T>(), nt2::One <T>())), cT(nt2::Inf<T>(), nt2::Pi<T>()), 0.75);
  // cacosh(x + i inf) returns +inf + i pi /2, for finite x.               --- matlab : Inf +    NaNi
  NT2_TEST_ULP_EQUAL(nt2::acosh(cT(nt2::One  <T>(), nt2::Inf <T>())), cT(nt2::Inf<T>(),  nt2::Pio_2<T>()), 0.75);
  NT2_TEST_ULP_EQUAL(nt2::acosh(cT(nt2::One <T>(), nt2::Inf<T>())),  boost::math::acosh(cT(nt2::One <T>(), nt2::Inf<T>())), 0.75);
  // cacosh(~inf + i inf) returns +inf + i3 pi /4.                         --- matlab : Inf +    NaNi
  NT2_TEST_ULP_EQUAL(nt2::acosh(cT(nt2::Minf <T>(), nt2::Inf<T>())),  cT(nt2::Inf<T>(), 3*nt2::Pi<T>()/4), 0.75);
  NT2_TEST_ULP_EQUAL(nt2::acosh(cT(nt2::Minf <T>(), nt2::Inf<T>())),  boost::math::acosh(cT(nt2::Minf <T>(), nt2::Inf<T>())), 0.75);

  //  cacosh(+inf + i inf) returns +inf + i pi /4.
  NT2_TEST_ULP_EQUAL(nt2::acosh(cT(nt2::Inf  <T>(), nt2::Inf<T>())),  cT(nt2::Inf <T>(),  nt2::Pi<T>()/4), 0.75);
  //  cacosh(NaN + i0) returns NaN + iNan.
  NT2_TEST_ULP_EQUAL(nt2::acosh(cT(nt2::Nan  <T>(), nt2::Zero<T>())), cT(nt2::Nan <T>(), nt2::Nan<T>()), 0.75);
  NT2_TEST_ULP_EQUAL(nt2::acosh(cT(1, 1)),  boost::math::acosh(cT(1, 1)), 0.75);
  NT2_TEST_ULP_EQUAL(nt2::acosh(cT(1, 10)),  boost::math::acosh(cT(1, 10)), 0.75);
  NT2_TEST_ULP_EQUAL(nt2::acosh(cT(10, 10)),  boost::math::acosh(cT(10, 10)), 0.75);
  NT2_TEST_ULP_EQUAL(nt2::acosh(cT(10, 1)),  boost::math::acosh(cT(10, 1)), 0.75);


} // end of test for floating_

// cacosh(conj(z)) = conj(cacosh(z)).
//  cacosh((+/-)0 + i0) returns +0 + i pi /2.
//  cacosh(x + i inf) returns +inf + i pi /2, for finite x.
//  cacosh(x + iNaN) returns NaN + iNaN and optionally raises the invalid floating-point exception, for finite x.
//  cacosh(~inf + iy) returns +inf + i pi , for positive-signed finite y.
//  cacosh(+inf + iy) returns +inf + i0, for positive-signed finite y.
//  cacosh(~inf + i inf) returns +inf + i3 pi /4.
//  cacosh(+inf + i inf) returns +inf + i pi /4.
//  cacosh((+/-)inf + iNaN) returns +inf + iNaN.
//  cacosh(NaN + iy) returns NaN + iNaN and optionally raises the invalid floating-point exception, for finite y.
//  cacosh(NaN + i inf) returns +inf + iNaN.
//  cacosh(NaN + iNaN) returns NaN + iNaN.


