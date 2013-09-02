//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/arithmetic/include/functions/rsqrt.hpp>
#include <nt2/sdk/functor/meta/call.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/ulp.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>

#include <nt2/include/constants/inf.hpp>
#include <nt2/include/constants/one.hpp>
#include <nt2/include/constants/nan.hpp>
#include <nt2/include/constants/minf.hpp>
#include <nt2/include/constants/zero.hpp>

NT2_TEST_CASE_TPL ( rsqrt,  NT2_REAL_TYPES)
{
  using nt2::rsqrt;
  using nt2::tag::rsqrt_;

  NT2_TEST_TYPE_IS( typename nt2::meta::call<rsqrt_(T)>::type
                  , T
                  );

  // specific values tests
  NT2_TEST_ULP_EQUAL(rsqrt(nt2::Inf<T>()), nt2::Zero<T>(), 0);
  NT2_TEST_ULP_EQUAL(rsqrt(nt2::Minf<T>()), nt2::Nan<T>(), 0);
  NT2_TEST_ULP_EQUAL(rsqrt(nt2::Mone<T>()), nt2::Nan<T>(), 0);
  NT2_TEST_ULP_EQUAL(rsqrt(nt2::Nan<T>()), nt2::Nan<T>(), 0);
  NT2_TEST_ULP_EQUAL(rsqrt(nt2::One<T>()), nt2::One<T>(), 0);
  NT2_TEST_ULP_EQUAL(rsqrt(nt2::Zero<T>()), nt2::Inf<T>(), 0);
}
