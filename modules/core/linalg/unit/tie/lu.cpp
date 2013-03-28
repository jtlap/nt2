//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#define NT2_UNIT_MODULE "nt2 linalg toolbox - tied lu function"

#include <nt2/table.hpp>
#include <nt2/include/functions/lu.hpp>
#include <nt2/include/functions/eye.hpp>
#include <nt2/include/functions/tie.hpp>
#include <nt2/include/functions/eye.hpp>
#include <nt2/include/functions/ones.hpp>
#include <nt2/include/functions/mtimes.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/ulp.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>

NT2_TEST_CASE_TPL ( square_lu, NT2_REAL_TYPES)
{
  using nt2::_;
  using nt2::meta::as_;

  nt2::table<T> lu, l, u, p;
  nt2::table<T> a = nt2::ones(4, 4, as_<T>()) + T(10)*nt2::eye(4, 4, as_<T>());

  /// Interface tests
  lu = nt2::lu(a);

  lu = nt2::lu(a) - a;
  nt2::tie(lu) = nt2::lu(a);

  lu = nt2::zeros(4, 4, nt2::meta::as_<T>());
  nt2::tie(lu(_(2,3),_(2,3))) = nt2::lu( a(_(1,2),_(1,2)) );

  // [L,U] = LU(A) <=> A = L*U
  nt2::tie(l, u) = nt2::lu(a);
  NT2_TEST_ULP_EQUAL( (nt2::mtimes(l, u)), a, 0.5 );

  // [L,U,P] = LU(A) <=> P*A = L*U
  nt2::tie(l, u, p) = nt2::lu(a);
  NT2_TEST_EQUAL    ( p                  , (nt2::eye(4, nt2::meta::as_<T>())) );
  NT2_TEST_ULP_EQUAL( (nt2::mtimes(p, a)), (nt2::mtimes(l, u)), 0.5           );
}

NT2_TEST_CASE_TPL ( non_square_lu, NT2_REAL_TYPES)
{
  using nt2::_;
  using nt2::meta::as_;

  nt2::table<T> lu, l, u, p;
  nt2::table<T> a = nt2::ones(4, 7, as_<T>()) + T(10)*nt2::eye(4, 7, as_<T>());

  /// Interface tests
  lu = nt2::lu(a);

  lu = nt2::lu(a) - a;
  nt2::tie(lu) = nt2::lu(a);

  lu = nt2::zeros(4, 7, nt2::meta::as_<T>());
  nt2::tie(lu(_(2,3),_(2,5))) = nt2::lu( a(_(1,2),_(1,4)) );

  // [L,U] = LU(A) <=> A = L*U
  nt2::tie(l, u) = nt2::lu(a);
  NT2_TEST_ULP_EQUAL( (nt2::mtimes(l, u)), a, 0.5 );

  // [L,U,P] = LU(A) <=> P*A = L*U
  nt2::tie(l, u, p) = nt2::lu(a);
  NT2_TEST_EQUAL    ( p                  , (nt2::eye(4, nt2::meta::as_<T>())) );
  NT2_TEST_ULP_EQUAL( (nt2::mtimes(p, a)), (nt2::mtimes(l, u)), 0.5           );
}
