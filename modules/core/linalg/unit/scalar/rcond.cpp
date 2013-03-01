//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#define NT2_UNIT_MODULE "nt2 linalg toolbox - rcond factorization"

#include <nt2/table.hpp>
#include <nt2/include/functions/rcond.hpp>
#include <nt2/include/functions/eye.hpp>
#include <nt2/include/constants/one.hpp>
#include <nt2/include/constants/eps.hpp>
#include <nt2/include/constants/ten.hpp>
#include <nt2/include/constants/oneo_10.hpp>
#include <nt2/include/functions/binomial.hpp>
#include <nt2/include/functions/kms.hpp>
#include <nt2/include/functions/norm.hpp>
#include <nt2/include/functions/rec.hpp>
#include <nt2/include/functions/inv.hpp>

#include <nt2/sdk/unit/tests/ulp.hpp>
#include <nt2/sdk/unit/module.hpp>

NT2_TEST_CASE_TPL(rcond, NT2_REAL_TYPES)
{
  typedef T r_t;
  using nt2::rcond;
  using nt2::tag::rcond_;
  nt2::table<T> n = nt2::eye(10, 10, nt2::meta::as_<T>());
  NT2_TEST_ULP_EQUAL(rcond(n), nt2::One<T>(), 0);
  NT2_TEST_ULP_EQUAL(rcond(n+n), nt2::One<T>(), 0);
  NT2_TEST_ULP_EQUAL(rcond(n, 1), nt2::One<T>(), 0);
  NT2_TEST_ULP_EQUAL(rcond(n+n, 1), nt2::One<T>(), 0);
  n(10, 10) = 10;
  NT2_TEST_ULP_EQUAL(rcond(n), nt2::Oneo_10<T>(), 0);
  NT2_TEST_ULP_EQUAL(rcond(n+n), nt2::Oneo_10<T>(), 0);
  NT2_TEST_ULP_EQUAL(rcond(n, 1), nt2::Oneo_10<T>(), 0);
  NT2_TEST_ULP_EQUAL(rcond(n+n, 1), nt2::Oneo_10<T>(), 0);
  NT2_DISPLAY(nt2::binomial(4, nt2::meta::as_<T>()));
  NT2_TEST_ULP_EQUAL(rcond(nt2::binomial(4, nt2::meta::as_<T>())), T(0.125), 1);

  NT2_TEST_ULP_EQUAL(rcond(nt2::kms<T>(4)), T( 1.481481481481481481e-01), 1);
}
