//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#define NT2_UNIT_MODULE "nt2 complex.arithmetic toolbox - round/scalar Mode"

//////////////////////////////////////////////////////////////////////////////
// unit test behavior of boost.simd.arithmetic components in scalar mode
//////////////////////////////////////////////////////////////////////////////
/// created by jt the 01/12/2010
///
#include <nt2/toolbox/arithmetic/include/functions/round.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/include/constants/one.hpp>
#include <nt2/include/constants/zero.hpp>
#include <nt2/include/constants/half.hpp>
#include <nt2/include/constants/mhalf.hpp>
#include <nt2/include/constants/inf.hpp>
#include <nt2/include/constants/minf.hpp>
#include <nt2/include/constants/mone.hpp>
#include <nt2/include/constants/nan.hpp>
#include <nt2/toolbox/constant/common.hpp>


NT2_TEST_CASE_TPL ( round_real__1_0,  BOOST_SIMD_REAL_TYPES)
{

  using nt2::round;
  using nt2::tag::round_;
  typedef typename std::complex<T> cT;

  // specific values tests
  NT2_TEST_EQUAL(round(cT(T(-1.1))), cT(-1));
  NT2_TEST_EQUAL(round(cT(T(1.1))), cT(1));
  NT2_TEST_EQUAL(round(cT(T(-1.1), T(1.1))), cT(-1, 1));
  NT2_TEST_EQUAL(round(cT(T(1.4))), cT(1));
  NT2_TEST_EQUAL(round(cT(T(1.5))), cT(2));
  NT2_TEST_EQUAL(round(cT(T(1.6))), cT(2));
  NT2_TEST_EQUAL(round(cT(T(2.5))), cT(2));
  NT2_TEST_EQUAL(round(nt2::Half<cT>()), nt2::Zero<cT>());
  NT2_TEST_EQUAL(round(nt2::Inf<cT>()), nt2::Inf<cT>());
  NT2_TEST_EQUAL(round(nt2::Mhalf<cT>()), nt2::Zero<cT>());
  NT2_TEST_EQUAL(round(nt2::Minf<cT>()), nt2::Minf<cT>());
  NT2_TEST_EQUAL(round(nt2::Mone<cT>()), nt2::Mone<cT>());
  NT2_TEST_EQUAL(round(nt2::Nan<cT>()), nt2::Nan<cT>());
  NT2_TEST_EQUAL(round(nt2::One<cT>()), nt2::One<cT>());
  NT2_TEST_EQUAL(round(nt2::Zero<cT>()), nt2::Zero<cT>());
} // end of test for floating_
