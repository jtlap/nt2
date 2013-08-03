//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/euler/include/functions/gamma.hpp>
#include <nt2/sdk/functor/meta/call.hpp>
#include <nt2/sdk/unit/tests/ulp.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>
#include <nt2/sdk/unit/module.hpp>

#include <nt2/constant/constant.hpp>

NT2_TEST_CASE_TPL ( gamma_real__1_0,  NT2_REAL_TYPES)
{

  using nt2::gamma;
  using nt2::tag::gamma_;
  typedef typename nt2::meta::call<gamma_(T)>::type r_t;
  typedef T wished_r_t;

  NT2_TEST_TYPE_IS(r_t, wished_r_t);

  // specific values tests
#ifndef BOOST_SIMD_NO_INVALIDS
  NT2_TEST_ULP_EQUAL(gamma(nt2::Inf<T>()), nt2::Inf<r_t>(), 0);
  NT2_TEST_ULP_EQUAL(gamma(nt2::Minf<T>()), nt2::Nan<r_t>(), 0);
  NT2_TEST_ULP_EQUAL(gamma(nt2::Nan<T>()), nt2::Nan<r_t>(), 0);
#endif
  NT2_TEST_ULP_EQUAL(gamma(nt2::Mone<T>()), nt2::Nan<r_t>(), 0);
  NT2_TEST_ULP_EQUAL(gamma(nt2::Mtwo<T>()), nt2::Nan<r_t>(), 0);
  NT2_TEST_ULP_EQUAL(gamma(nt2::Mzero<T>()), nt2::Minf<r_t>(), 0);
  NT2_TEST_ULP_EQUAL(gamma(nt2::One<T>()), nt2::One<r_t>(), 0);
  NT2_TEST_ULP_EQUAL(gamma(nt2::Zero<T>()), nt2::Inf<r_t>(), 0);
} // end of test for floating_
