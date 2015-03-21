//==============================================================================
//         Copyright 2015   J.T. Lapreste
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================

#include <nt2/table.hpp>
#include <nt2/include/functions/hess.hpp>
#include <nt2/include/functions/tie.hpp>
#include <nt2/include/functions/eye.hpp>
#include <nt2/include/functions/ishess.hpp>
#include <nt2/include/functions/istriu.hpp>
#include <nt2/include/functions/mtimes.hpp>
#include <nt2/include/functions/transpose.hpp>
#include <nt2/include/functions/reshape.hpp>
#include <nt2/include/functions/triu.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/ulp.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/basic.hpp>
#include <nt2/sdk/unit/tests/exceptions.hpp>

NT2_TEST_CASE_TPL ( hess1,  NT2_REAL_TYPES)
{
  using nt2::_;
  using nt2::meta::as_;

  nt2::table<T> h, p, hess;
  nt2::table<T> a = nt2::reshape(nt2::_(T(1), T(16)), 4, 4);
  h = nt2::hess(a);
  nt2::tie(h, p) = nt2::hess(a);
  NT2_TEST(ishess(h));
  NT2_TEST_ULP_EQUAL( a,  nt2::mtimes(p, nt2::mtimes(h, trans(p))), T(200));
}

NT2_TEST_CASE_TPL ( hess2, NT2_REAL_TYPES)
{
  using nt2::_;
  using nt2::meta::as_;
  nt2::table<T> a, b, h, r, q, z;
  a = b =  nt2::eye(4, nt2::meta::as_<T>());
  b(_, 1) = T(1);
  tie(h, r, q, z) = nt2::hess(a, b);
  NT2_TEST(ishess(h));
  NT2_TEST(istriu(r));

  NT2_TEST_ULP_EQUAL( a,  nt2::mtimes(q, nt2::mtimes(h, trans(z))), T(200));
  NT2_TEST_ULP_EQUAL( b,  nt2::mtimes(q, nt2::mtimes(r, trans(z))), T(200));
}

