//==============================================================================
//         Copyright 2003 - 2013   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/include/functions/hypot.hpp>

#include <boost/dispatch/functor/meta/call.hpp>
#include <nt2/sdk/functor/meta/call.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>
#include <complex>
#include <nt2/sdk/complex/complex.hpp>
#include <nt2/sdk/unit/tests/ulp.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <boost/simd/sdk/config.hpp>

#include <nt2/include/constants/one.hpp>
#include <nt2/include/constants/sqrt_2.hpp>
#include <nt2/include/constants/zero.hpp>
#include <nt2/include/constants/inf.hpp>

NT2_TEST_CASE_TPL ( hypot_real,  BOOST_SIMD_REAL_TYPES)
{
  using nt2::hypot;
  using nt2::tag::hypot_;
  typedef typename std::complex<T> cT;

  // specific values tests
#ifndef BOOST_SIMD_NO_INVALIDS
  NT2_TEST_EQUAL(hypot(cT(nt2::Inf<T>()), cT(nt2::Inf<T>())), (nt2::Inf<T>()));
#endif
  NT2_TEST_EQUAL(hypot(cT(nt2::One<T>()), cT(nt2::Zero<T>())), (nt2::One<T>()));
  NT2_TEST_EQUAL(hypot(cT(nt2::Zero<T>()), cT(nt2::Zero<T>())),(nt2::Zero<T>()));
  NT2_TEST_ULP_EQUAL(hypot(cT(0, 1), cT(1, 0)), nt2::Sqrt_2<T>(), 0.5);
  NT2_TEST_ULP_EQUAL(hypot(cT(1, 0), cT(1, 0)), nt2::Sqrt_2<T>(), 0.5);
}
