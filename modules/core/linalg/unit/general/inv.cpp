//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#define NT2_UNIT_MODULE "nt2 linalg toolbox - inv factorization"

#include <nt2/table.hpp>
#include <nt2/include/functions/inv.hpp>
#include <nt2/include/functions/eye.hpp>
#include <nt2/include/functions/ones.hpp>
#include <nt2/include/functions/zeros.hpp>
#include <nt2/include/functions/mtimes.hpp>

#include <nt2/sdk/unit/tests.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/exceptions.hpp>

NT2_TEST_CASE_TPL(inv, NT2_REAL_TYPES)
{
  using nt2::inv;

  nt2::table<T> n =   nt2::eye(10, 10, nt2::meta::as_<T>())
                    + T(7)*nt2::ones(10, 10, nt2::meta::as_<T>());

  nt2::table<T> invn = nt2::inv(n);

  NT2_TEST_ULP_EQUAL( (nt2::mtimes(invn, n))
                    , nt2::eye(10, 10, nt2::meta::as_<T>())
                    , 8
                    );

  nt2::table<T> invn2 = nt2::zeros(10,10, nt2::meta::as_<T>());
  invn2(nt2::_(3,6), nt2::_(3,6)) = nt2::inv( n( nt2::_(3,6), nt2::_(3,6)) );

  NT2_TEST_ULP_EQUAL( ( nt2::mtimes (  n( nt2::_(3,6), nt2::_(3,6))
                                    , invn2(nt2::_(3,6), nt2::_(3,6))
                                    )
                      )
                    , nt2::eye(4, 4, nt2::meta::as_<T>())
                    , 8
                    );
}

// TODO: need rcond
// NT2_TEST_CASE_TPL(inv_singular, NT2_REAL_TYPES)
// {
//   using nt2::inv;

//   nt2::table<T> nn, n =   nt2::eye(10, 10, nt2::meta::as_<T>())
//                         + T(7)*nt2::ones(10, 10, nt2::meta::as_<T>());

//   n(2, nt2::_) = T(0);

//   NT2_TEST_ASSERT( nn = nt2::inv(n) );
// }

NT2_TEST_CASE_TPL(inv_assert, NT2_REAL_TYPES)
{
  using nt2::inv;
  nt2::table<T> nn, n = nt2::eye(10, 8, nt2::meta::as_<T>());

  NT2_TEST_ASSERT( nn = nt2::inv(n) );
}
