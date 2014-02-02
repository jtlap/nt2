//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/arithmetic/include/functions/scalar/rec.hpp>
#include <nt2/sdk/functor/meta/call.hpp>
#include <boost/dispatch/meta/as_floating.hpp>
#include <boost/type_traits/common_type.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/ulp.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>

#include <nt2/include/constants/inf.hpp>
#include <nt2/include/constants/one.hpp>
#include <nt2/include/constants/zero.hpp>
#include <nt2/include/constants/mzero.hpp>
#include <nt2/include/constants/mone.hpp>
#include <nt2/include/constants/minf.hpp>
#include <nt2/include/constants/nan.hpp>

NT2_TEST_CASE_TPL( rec_,  NT2_REAL_TYPES)
{
  using nt2::rec;
  using nt2::tag::rec_;

  // return type conformity test
  NT2_TEST_TYPE_IS( typename nt2::meta::call<rec_(T)>::type , T );

  // specific values tests
  NT2_TEST_ULP_EQUAL(rec(nt2::Inf<T>()), nt2::Zero<T>(), 0);
  NT2_TEST_ULP_EQUAL(rec(nt2::Minf<T>()), nt2::Zero<T>(), 0);
  NT2_TEST_ULP_EQUAL(rec(nt2::Mone<T>()), nt2::Mone<T>(), 0);
  NT2_TEST_ULP_EQUAL(rec(nt2::Mzero<T>()), nt2::Minf<T>(), 0);
  NT2_TEST_ULP_EQUAL(rec(nt2::Nan<T>()), nt2::Nan<T>(), 0);
  NT2_TEST_ULP_EQUAL(rec(nt2::One<T>()), nt2::One<T>(), 0);
  NT2_TEST_ULP_EQUAL(rec(nt2::Zero<T>()), nt2::Inf<T>(), 0);
} // end of test for floating_
