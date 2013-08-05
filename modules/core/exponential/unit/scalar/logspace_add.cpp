//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/exponential/include/functions/logspace_add.hpp>
#include <nt2/sdk/functor/meta/call.hpp>
#include <nt2/sdk/unit/tests/ulp.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/meta/as_floating.hpp>

#include <nt2/constant/constant.hpp>

NT2_TEST_CASE_TPL ( logspace_add_real__2_1,  NT2_REAL_TYPES)
{

  using nt2::logspace_add;
  using nt2::tag::logspace_add_;
  typedef typename nt2::meta::call<logspace_add_(T,T)>::type r_t;
  typedef typename boost::dispatch::meta::as_floating<T>::type wished_r_t;

  NT2_TEST_TYPE_IS(r_t, wished_r_t);

  // specific values tests
#ifndef BOOST_SIMD_NO_INVALIDS
  NT2_TEST_ULP_EQUAL(logspace_add(nt2::Inf<T>(),nt2::Inf<T>()), nt2::Inf<r_t>(), 0);
  NT2_TEST_ULP_EQUAL(logspace_add(nt2::Inf<T>(),nt2::Zero<T>()), nt2::Inf<r_t>(), 0);
  NT2_TEST_ULP_EQUAL(logspace_add(nt2::Minf<T>(),nt2::Zero<T>()), nt2::Zero<r_t>(), 0);
  NT2_TEST_ULP_EQUAL(logspace_add(nt2::Inf<T>(),nt2::Nan <T>()), nt2::Nan<r_t>(), 0);
  NT2_TEST_ULP_EQUAL(logspace_add(nt2::Minf<T>(),nt2::Minf<T>()), nt2::Minf<r_t>(), 0);
  NT2_TEST_ULP_EQUAL(logspace_add(nt2::Nan<T>(),nt2::Nan<T>()), nt2::Nan<r_t>(), 0);
#endif
  NT2_TEST_ULP_EQUAL(logspace_add(nt2::Mone<T>(),nt2::Mone<T>()), nt2::Mone<r_t>()+nt2::Log_2<r_t>(), 0);
  NT2_TEST_ULP_EQUAL(logspace_add(nt2::One<T>(),nt2::One<T>()), nt2::One<r_t>()+nt2::Log_2<r_t>(), 0);
  NT2_TEST_ULP_EQUAL(logspace_add(nt2::Two <T>(), nt2::Two <T>()), nt2::Two <r_t>()+nt2::Log_2<r_t>(), 0);
  NT2_TEST_ULP_EQUAL(logspace_add(nt2::Zero<T>(),nt2::Zero<T>()), nt2::Log_2<r_t>(), 0);
} // end of test for floating_
