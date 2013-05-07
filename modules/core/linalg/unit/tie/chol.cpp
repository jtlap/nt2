//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#define NT2_UNIT_MODULE "nt2 linalg toolbox - tied chol function"

#include <nt2/table.hpp>
#include <nt2/include/functions/zeros.hpp>
#include <nt2/include/functions/ones.hpp>
#include <nt2/include/functions/eye.hpp>
#include <nt2/include/functions/chol.hpp>
#include <nt2/include/functions/mtimes.hpp>
#include <nt2/include/functions/transpose.hpp>
#include <nt2/include/functions/tie.hpp>

#include <nt2/sdk/unit/tests.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/exceptions.hpp>

NT2_TEST_CASE_TPL ( chol_upper, NT2_REAL_TYPES)
{
  typedef nt2::table<T> table_t;
  table_t a, z, b = nt2::ones(4, 4, nt2::meta::as_<T>())
                + T(10)*nt2::eye(4, 4, nt2::meta::as_<T>());
  size_t p = 999;

  nt2::tie(z) = nt2::chol(b);
  NT2_DISPLAY(z);

  nt2::tie(a,p) = nt2::chol(b, nt2::upper_);
  NT2_DISPLAY(a);
  NT2_TEST_EQUAL(p, 0u);

  b = nt2::zeros(4, 4, nt2::meta::as_<T>());
  b(1,1) = 1;
  nt2::tie(a,p) = nt2::chol(b,nt2::upper_);
  NT2_DISPLAY(a);
  NT2_TEST_EQUAL(p, 2u);
}

NT2_TEST_CASE_TPL ( chol_lower, NT2_REAL_TYPES)
{
  typedef nt2::table<T> table_t;
  table_t a,z,b = nt2::ones(4, 4, nt2::meta::as_<T>())
                + T(10)*nt2::eye(4, 4, nt2::meta::as_<T>());

  size_t p = 999;

  nt2::tie(z) = nt2::chol(b, nt2::lower_);
  NT2_DISPLAY(z);

  nt2::tie(a,p) = nt2::chol(b, nt2::lower_);
  NT2_DISPLAY(a);
  NT2_TEST_EQUAL(p, 0u);

  b = nt2::zeros(4, 4, nt2::meta::as_<T>());
  b(1,1) = 1;

  nt2::tie(a,p) = nt2::chol(b, nt2::lower_);
  NT2_DISPLAY(a);
  NT2_TEST_EQUAL(p, 2u);
}

NT2_TEST_CASE_TPL ( chol_lower2, NT2_REAL_TYPES)
{
  typedef nt2::table<T> table_t;
  table_t a , b = nt2::ones(4, 4, nt2::meta::as_<T>())
                + T(10)*nt2::eye(4, 4, nt2::meta::as_<T>());

  a = nt2::chol(b, nt2::lower_);
  //  NT2_DISPLAY(chol(b, nt2::lower_));
  NT2_DISPLAY(a);
  NT2_TEST_ULP_EQUAL(b, nt2::mtimes(a, nt2::trans(a)), 0.5);
  table_t u = nt2::ones(4, 9, nt2::meta::as_<T>());
  NT2_DISPLAY(u);

  u(nt2::_(1,4),nt2::_(1,4)) = chol(b, nt2::lower_);
  NT2_DISPLAY(u);

  table_t x;
  x = chol(b, nt2::lower_) + b;
  NT2_DISPLAY(x);

  b = nt2::zeros(4, 4, nt2::meta::as_<T>());
  b(1,1) = 1;
  size_t p = 999;
  nt2::tie(a, p)= nt2::chol(b, nt2::lower_);
  NT2_DISPLAY(a);
  NT2_TEST_EQUAL(a, nt2::ones(1, 1, nt2::meta::as_<T>()));
  NT2_TEST_EQUAL(p, 2u);
}
