//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/include/functions/csch.hpp>
#include <nt2/constant/constant.hpp>
#include <nt2/sdk/functor/meta/call.hpp>
#include <nt2/sdk/unit/tests/ulp.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/complex/meta/as_complex.hpp>
#include <nt2/include/functions/sinh.hpp>
#include <nt2/include/functions/rec.hpp>
#include <complex>

NT2_TEST_CASE_TPL (csch_real__1_0, NT2_REAL_TYPES)
{

  using nt2::csch;
  using nt2::tag::csch_;
  typedef std::complex<T> cT;
  typedef typename nt2::meta::call<csch_(cT)>::type r_t;
  typedef typename nt2:: meta::as_complex<T>::type wished_r_t;

  NT2_TEST_TYPE_IS(r_t, wished_r_t);

  // specific values tests
  NT2_TEST_ULP_EQUAL(nt2::csch(cT(nt2::One<T>(), nt2::Zero<T>())),   nt2::rec(nt2::sinh(cT(nt2::One<T>(), nt2::Zero<T>()))), 0.75);
  NT2_TEST_ULP_EQUAL(nt2::csch(cT(nt2::Zero<T>(), nt2::Zero<T>())),  cT(nt2::Inf<T>(), nt2::Zero<T>()), 0.75);
  NT2_TEST_ULP_EQUAL(nt2::csch(cT(nt2::Mzero<T>(), nt2::Zero<T>())), cT(nt2::Minf<T>(), nt2::Zero<T>()), 0.75);
  NT2_TEST_ULP_EQUAL(nt2::csch(cT(1, 1)),   nt2::rec(nt2::sinh(cT(1, 1))), 0.75);
  NT2_TEST_ULP_EQUAL(nt2::csch(cT(1, 10)),  nt2::rec(nt2::sinh(cT(1, 10))), 0.75);
  NT2_TEST_ULP_EQUAL(nt2::csch(cT(10, 10)), nt2::rec(nt2::sinh(cT(10, 10))), 1);
  NT2_TEST_ULP_EQUAL(nt2::csch(cT(10, 1)),  nt2::rec(nt2::sinh(cT(10, 1))), 1);


} // end of test for floating_

