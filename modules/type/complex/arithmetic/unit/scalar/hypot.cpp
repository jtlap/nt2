//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Hypotributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#define NT2_UNIT_MODULE "nt2 complex.operator toolbox - hypot/scalar Mode"

//////////////////////////////////////////////////////////////////////////////
// unit test behavior of boost.simd.operator components in scalar mode
//////////////////////////////////////////////////////////////////////////////
/// created  by jt the 18/02/2011
///
#include <nt2/toolbox/arithmetic/include/functions/hypot.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/ulp.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/include/constants/one.hpp>
#include <nt2/include/constants/zero.hpp>
#include <nt2/include/constants/inf.hpp>
#include <nt2/include/constants/sqrt_2.hpp>

NT2_TEST_CASE_TPL ( hypot_real__2_0,  BOOST_SIMD_REAL_TYPES)
{

  using nt2::hypot;
  using nt2::tag::hypot_;
  typedef std::complex<T> cT;

  // specific values tests
  NT2_TEST_EQUAL(hypot(cT(nt2::Inf<T>()), cT(nt2::Inf<T>())), (nt2::Inf<T>()));
  NT2_TEST_EQUAL(hypot(cT(nt2::One<T>()), cT(nt2::Zero<T>())), (nt2::One<T>()));
  NT2_TEST_EQUAL(hypot(cT(nt2::Zero<T>()), cT(nt2::Zero<T>())),(nt2::Zero<T>()));
  NT2_TEST_ULP_EQUAL(hypot(cT(0, 1), cT(1, 0)), nt2::Sqrt_2<T>(), 0.5);
  NT2_TEST_ULP_EQUAL(hypot(cT(1, 0), cT(1, 0)), nt2::Sqrt_2<T>(), 0.5);
} // end of test for floating_
