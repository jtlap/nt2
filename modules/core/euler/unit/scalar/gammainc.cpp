//==============================================================================
//         Copyright 2003 - 2013   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/euler/include/functions/gammainc.hpp>

#include <nt2/sdk/functor/meta/call.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>
#include <nt2/sdk/unit/tests/ulp.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <boost/simd/sdk/config.hpp>

#include <nt2/include/constants/mzero.hpp>
#include <nt2/include/constants/one.hpp>
#include <nt2/include/constants/zero.hpp>
#include <nt2/include/constants/inf.hpp>
#include <nt2/include/constants/nan.hpp>
#include <nt2/include/constants/invexp_1.hpp>

NT2_TEST_CASE_TPL ( gammainc_real,  NT2_REAL_TYPES)
{
  using nt2::gammainc;
  using nt2::tag::gammainc_;
  typedef typename nt2::meta::call<gammainc_(T, T)>::type r_t;
  typedef T wished_r_t;

  // return type conformity test
  NT2_TEST_TYPE_IS(r_t, wished_r_t);

  // specific values tests
#ifndef BOOST_SIMD_NO_INVALIDS
  NT2_TEST_ULP_EQUAL(gammainc(nt2::Inf<T>()  ,  nt2::One<T>()), nt2::One<r_t>(), 0);
  NT2_TEST_ULP_EQUAL(gammainc(nt2::Nan<T>()  ,  nt2::One<T>()), nt2::Nan<r_t>(), 0);
#endif
  NT2_TEST_TYPE_IS(r_t, wished_r_t);
  NT2_TEST_ULP_EQUAL(gammainc(nt2::Mzero<T>(),  nt2::One<T>()), nt2::Zero<r_t>(), 0);
  NT2_TEST_ULP_EQUAL(gammainc(nt2::One<T>()  ,  nt2::One<T>()), nt2::One<r_t>()-nt2::Invexp_1<r_t>(), 0);
  NT2_TEST_ULP_EQUAL(gammainc(nt2::Zero<T>() ,  nt2::One<T>()), nt2::Zero<r_t>(), 0);
  NT2_TEST_ULP_EQUAL(gammainc(nt2::Zero<T>() ,  nt2::Zero<T>()), nt2::One<r_t>(), 0);
}
