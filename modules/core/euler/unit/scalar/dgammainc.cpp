//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/euler/include/functions/dgammainc.hpp>
#include <nt2/sdk/functor/meta/call.hpp>
#include <nt2/sdk/unit/tests.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>
#include <nt2/sdk/unit/module.hpp>

#include <nt2/constant/constant.hpp>
#include <nt2/include/constants/invexp_1.hpp>

NT2_TEST_CASE_TPL ( dgammainc_real__1_0,  NT2_REAL_TYPES)
{

  using nt2::dgammainc;
  using nt2::tag::dgammainc_;
  typedef typename nt2::meta::call<dgammainc_(T, T)>::type r_t;
  typedef T wished_r_t;


  // return type conformity test
  NT2_TEST_TYPE_IS(r_t, wished_r_t);

  // specific values tests
#ifndef BOOST_SIMD_NO_INVALIDS
  NT2_TEST_ULP_EQUAL(dgammainc( nt2::One<T>(), nt2::Inf<T>()  ), nt2::Zero<r_t>(), 0);
  NT2_TEST_ULP_EQUAL(dgammainc( nt2::One<T>(), nt2::Nan<T>()  ), nt2::Nan<r_t>(), 0);
#endif
  NT2_TEST_ULP_EQUAL(dgammainc( nt2::One<T>(), nt2::Mzero<T>()), nt2::Nan<r_t>(), 0);
  NT2_TEST_ULP_EQUAL(dgammainc( nt2::One<T>(), nt2::One<T>()  ), nt2::Invexp_1<r_t>(), 0);
  NT2_TEST_ULP_EQUAL(dgammainc( nt2::One<T>(), nt2::Zero<T>() ), nt2::Nan<r_t>(), 0);
} // end of test for floating_
