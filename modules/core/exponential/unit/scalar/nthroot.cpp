//==============================================================================
//         Copyright 2009 - 2013   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/exponential/include/functions/nthroot.hpp>

#include <nt2/sdk/functor/meta/call.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>
#include <nt2/sdk/unit/tests/ulp.hpp>
#include <nt2/sdk/meta/as_integer.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <boost/simd/sdk/config.hpp>
#include <nt2/sdk/meta/as_floating.hpp>

#include <nt2/include/constants/mone.hpp>
#include <nt2/include/constants/one.hpp>
#include <nt2/include/constants/zero.hpp>
#include <nt2/include/constants/inf.hpp>
#include <nt2/include/constants/minf.hpp>
#include <nt2/include/constants/nan.hpp>
#include <nt2/include/constants/half.hpp>

NT2_TEST_CASE_TPL ( nthroot,  NT2_REAL_TYPES)
{
  using nt2::nthroot;
  using nt2::tag::nthroot_;
  typedef typename nt2::meta::as_integer<T>::type          iT;
  typedef typename nt2::meta::call<nthroot_(T,iT)>::type r_t;
  typedef T wished_r_t;

  // return type conformity test
  NT2_TEST_TYPE_IS(r_t, wished_r_t);

  // specific values tests
#ifndef BOOST_SIMD_NO_INVALIDS
  NT2_TEST_ULP_EQUAL(nthroot(nt2::Inf<T>(),iT(3)), nt2::Inf<r_t>(), 0.5);
  NT2_TEST_ULP_EQUAL(nthroot(nt2::Inf<T>(),iT(4)), nt2::Inf<r_t>(), 0.5);
  NT2_TEST_ULP_EQUAL(nthroot(nt2::Minf<T>(),iT(3)), nt2::Minf<r_t>(), 0.5);
  NT2_TEST_ULP_EQUAL(nthroot(nt2::Minf<T>(),iT(4)), nt2::Nan<r_t>(), 0.5);
  NT2_TEST_ULP_EQUAL(nthroot(nt2::Nan<T>(),iT(3)), nt2::Nan<r_t>(), 0.5);
  NT2_TEST_ULP_EQUAL(nthroot(nt2::Nan<T>(),iT(4)), nt2::Nan<r_t>(), 0.5);
  NT2_TEST_ULP_EQUAL(nthroot(nt2::Mone<T>(),iT(4)), nt2::Nan<r_t>(), 0.5);
#endif
  NT2_TEST_ULP_EQUAL(nthroot(nt2::Mone<T>(),iT(0)), nt2::Nan<r_t>(), 0.5);
  NT2_TEST_ULP_EQUAL(nthroot(nt2::One <T>(),iT(0)), nt2::One<r_t>(), 0.5);
  NT2_TEST_ULP_EQUAL(nthroot(nt2::Half<T>(),iT(0)), nt2::Zero<r_t>(), 0.5);
  NT2_TEST_ULP_EQUAL(nthroot(nt2::Two <T>(),iT(0)), nt2::Inf <r_t>(), 0.5);
  NT2_TEST_ULP_EQUAL(nthroot(nt2::Zero<T>(),iT(0)), nt2::Zero<r_t>(), 0.5);
  NT2_TEST_ULP_EQUAL(nthroot(nt2::Two <T>(),iT(0)), nt2::Inf<r_t>(), 0.5);
  NT2_TEST_ULP_EQUAL(nthroot(nt2::Half<T>(),iT(0)), nt2::Zero<r_t>(), 0.5);
  NT2_TEST_ULP_EQUAL(nthroot(nt2::Mone<T>(),iT(3)), nt2::Mone<r_t>(), 0.5);
  NT2_TEST_ULP_EQUAL(nthroot(nt2::One<T>(),iT(3)), nt2::One<r_t>(), 0.5);
  NT2_TEST_ULP_EQUAL(nthroot(nt2::One<T>(),iT(4)), nt2::One<r_t>(), 0.5);
  NT2_TEST_ULP_EQUAL(nthroot(nt2::Zero<T>(),iT(3)), nt2::Zero<r_t>(), 0.5);
  NT2_TEST_ULP_EQUAL(nthroot(nt2::Zero<T>(),iT(4)), nt2::Zero<r_t>(), 0.5);
  NT2_TEST_ULP_EQUAL(nthroot(T(-8),iT(3)), r_t(-2), 0.5);
  NT2_TEST_ULP_EQUAL(nthroot(T(256),iT(4)), r_t(4), 0.5);
  NT2_TEST_ULP_EQUAL(nthroot(T(8),iT(3)), r_t(2), 0.5);
}
