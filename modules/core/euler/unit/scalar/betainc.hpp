//==============================================================================
//         Copyright 2003 - 2013   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/euler/include/functions/betainc.hpp>

#include <nt2/sdk/functor/meta/call.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>
#include <nt2/sdk/unit/tests/ulp.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <boost/simd/sdk/config.hpp>

#include <nt2/include/constants/one.hpp>
#include <nt2/include/constants/nan.hpp>

NT2_TEST_CASE_TPL ( betainc_real,  NT2_REAL_TYPES)
{
  using nt2::betainc;
  using nt2::tag::betainc_;
  typedef typename nt2::meta::call<betainc_(T,T)>::type r_t;
  typedef T wished_r_t;

  // return type conformity test
  NT2_TEST_TYPE_IS(r_t, wished_r_t);

  // specific values tests
#ifndef BOOST_SIMD_NO_INVALIDS
  NT2_TEST_ULP_EQUAL(betainc(nt2::Nan<T>(), nt2::Nan<T>(), nt2::Nan<T>()), nt2::Nan<r_t>(), 0);
#endif
  NT2_TEST_ULP_EQUAL(betainc(nt2::One<T>(), nt2::One<T>(), Half<T>()), nt2::One<r_t>(), 0);
  NT2_TEST_ULP_EQUAL(betainc(nt2::Half<T>(), nt2::Five<T>(), T(0.2)), (2.87138480061941e-03), 0);
}
