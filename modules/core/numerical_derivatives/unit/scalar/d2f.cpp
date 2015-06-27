//==============================================================================
//         Copyright 2015 J.T. Lapreste
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/numerical_derivatives/include/functions/d2f.hpp>

#include <nt2/sdk/functor/meta/call.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>
#include <nt2/sdk/unit/tests/ulp.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <boost/simd/sdk/config.hpp>

#include <nt2/include/functions/rec.hpp>
#include <nt2/include/functions/exp.hpp>
#include <nt2/include/constants/derivinc2.hpp>
#include <nt2/include/constants/pi.hpp>
#include <nt2/include/constants/invpi.hpp>
#include <nt2/include/constants/sqrteps.hpp>
#include <nt2/table.hpp>

NT2_TEST_CASE_TPL ( d2f, NT2_REAL_TYPES)
{
  using nt2::d2f;
  using nt2::tag::d2f_;
  auto f =  [](T t){return exp(t);};
  T x =  T(0);
  T r = T(1);
  T d2fdx2 =  d2f(f, x,  nt2::Derivinc2<T>());
  NT2_TEST_ULP_EQUAL(d2fdx2, r,  nt2::rec(nt2::Sqrteps<T>()));

  d2fdx2 =  d2f(f, x,  nt2::Derivinc2<T>(), nt2::pow2den_);
  NT2_TEST_ULP_EQUAL(d2fdx2, r, nt2::rec(nt2::Sqrteps<T>()));

  d2fdx2 =  d2f(f, x, nt2::pow2den_);
  NT2_TEST_ULP_EQUAL(d2fdx2, r, nt2::rec(nt2::Sqrteps<T>()));

  d2fdx2 =  d2f(f, x);
  NT2_TEST_ULP_EQUAL(d2fdx2, r, nt2::rec(nt2::Sqrteps<T>()));

  x = T(1);
  r = exp(x);
  d2fdx2 =  d2f(f, x,  nt2::Derivinc2<T>());
  NT2_TEST_ULP_EQUAL(d2fdx2, r,  nt2::rec(nt2::Sqrteps<T>()));

  d2fdx2 =  d2f(f, x,  nt2::Derivinc2<T>(), nt2::pow2den_);
  NT2_TEST_ULP_EQUAL(d2fdx2, r, nt2::rec(nt2::Sqrteps<T>()));

  d2fdx2 =  d2f(f, x, nt2::pow2den_);
  NT2_TEST_ULP_EQUAL(d2fdx2, r, nt2::rec(nt2::Sqrteps<T>()));

  d2fdx2 =  d2f(f, x);
  NT2_TEST_ULP_EQUAL(d2fdx2, r, nt2::rec(nt2::Sqrteps<T>()));
 }

