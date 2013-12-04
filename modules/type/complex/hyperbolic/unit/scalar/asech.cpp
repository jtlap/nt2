//==============================================================================
//         Copyright 2003 - 2013   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/include/functions/asech.hpp>

#include <boost/dispatch/functor/meta/call.hpp>
#include <nt2/sdk/functor/meta/call.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>
#include <complex>
#include <nt2/sdk/complex/complex.hpp>
#include <nt2/sdk/unit/tests/ulp.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <boost/simd/sdk/config.hpp>

#include <nt2/include/constants/mzero.hpp>
#include <nt2/include/constants/one.hpp>
#include <nt2/include/constants/zero.hpp>
#include <nt2/include/constants/inf.hpp>
#include <nt2/include/constants/minf.hpp>
#include <nt2/include/constants/i.hpp>

#include <nt2/include/functions/rec.hpp>
#include <nt2/include/functions/acosh.hpp>

NT2_TEST_CASE_TPL ( asech_real, NT2_REAL_TYPES)
{
  using nt2::asech;
  using nt2::tag::asech_;
  typedef typename std::complex<T> cT;
  typedef typename nt2::meta::call<asech_(cT)>::type r_t;

  // return type conformity test
  NT2_TEST_TYPE_IS(r_t, cT);

  // specific values tests
#ifndef BOOST_SIMD_NO_INVALIDS
  NT2_TEST_ULP_EQUAL(nt2::asech(cT(nt2::Zero<T>(), nt2::Zero<T>())),  nt2::acosh(cT(nt2::Inf<T>(), nt2::Zero<T>())), 0.75);
  NT2_TEST_ULP_EQUAL(nt2::asech(cT(nt2::Mzero<T>(), nt2::Zero<T>())), nt2::acosh(cT(nt2::Minf<T>(), nt2::Zero<T>())), 0.75);
#endif
  NT2_TEST_ULP_EQUAL(nt2::asech(cT(nt2::One<T>(), nt2::Zero<T>())),   nt2::acosh(nt2::rec(cT(nt2::One<T>(), nt2::Zero<T>()))), 0.75);
  NT2_TEST_ULP_EQUAL(nt2::asech(cT(1, 1)),   nt2::acosh(nt2::rec(cT(1, 1))), 1);
  NT2_TEST_ULP_EQUAL(nt2::asech(cT(1, 10)),  nt2::acosh(nt2::rec(cT(1, 10))), 1);
  NT2_TEST_ULP_EQUAL(nt2::asech(cT(10, 10)), nt2::acosh(nt2::rec(cT(10, 10))), 1);
  NT2_TEST_ULP_EQUAL(nt2::asech(cT(10, 1)),  nt2::acosh(nt2::rec(cT(10, 1))), 1);
}
