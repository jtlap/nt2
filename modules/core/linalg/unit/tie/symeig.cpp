//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#define NT2_UNIT_MODULE "nt2 linalg toolbox - tied symeig function"

#include <nt2/table.hpp>
#include <nt2/include/functions/zeros.hpp>
#include <nt2/include/functions/ones.hpp>
#include <nt2/include/functions/eye.hpp>
#include <nt2/include/functions/symeig.hpp>
#include <nt2/include/functions/tie.hpp>
#include <nt2/include/functions/isulpequal.hpp>
#include <nt2/include/functions/transpose.hpp>
#include <nt2/include/functions/globalmax.hpp>
#include <nt2/include/functions/triu.hpp>
#include <nt2/include/functions/ones.hpp>
#include <nt2/include/functions/mtimes.hpp>
#include <nt2/include/functions/transpose.hpp>
#include <nt2/sdk/unit/tests.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/exceptions.hpp>
#include <nt2/sdk/unit/tests/basic.hpp>
#include <nt2/include/functions/colon.hpp>

NT2_TEST_CASE_TPL ( symeig, NT2_REAL_TYPES)
{
  typedef nt2::table<T> table_t;
  table_t w, v, d, b = nt2::ones(4, 4, nt2::meta::as_<T>())
                + T(10)*nt2::eye(4, 4, nt2::meta::as_<T>());
  w = nt2::symeig(b);
  nt2::tie(d, v) = nt2::symeig(b);
  NT2_TEST_ULP_EQUAL(b, nt2::mtimes(v, nt2::mtimes(d, nt2::trans(v))), 10.0);

}
NT2_TEST_CASE_TPL ( symeig_m_test, NT2_REAL_TYPES)
{
  typedef nt2::table<T> table_t;
  table_t v, d, z;

  T bb[9] = {-149,    -50,   -154,
             537,    180,    546,
             -27,     -9,    -25 };
  //Note that only the upper part is used!
  table_t b(nt2::of_size(3, 3));
  int k = 0;
  for(int i=1; i <= 3; ++i)
    {
      for(int j=1; j <= 3; ++j)
        {
          b(i, j) = bb[k++];
        }
    }
  nt2::tie(d, v) = nt2::symeig(b);
  z =  mtimes(mtimes(v, d), nt2::trans(v));
  NT2_TEST_ULP_EQUAL(nt2::triu(z), nt2::triu(b), T(16.0));
}


NT2_TEST_CASE_TPL ( symeig_sub, NT2_REAL_TYPES)
{
  using nt2::meta::as_;
  using nt2::mtimes;
  using nt2::_;
  typedef nt2::table<T> table_t;
  table_t v, d, z;

  T bb[9] = {-149,    -50,   -154,
             537,    180,    546,
             -27,     -9,    -25 };
  //Note that only the upper part is used!
  table_t b(nt2::of_size(3, 3));
  int k = 0;
  for(int i=1; i <= 3; ++i)
    {
      for(int j=1; j <= 3; ++j)
        {
          b(i, j) = bb[k++];
        }
    }
  v = d = nt2::ones(6, 3, as_<T>());

  nt2::tie(d(_(1, 2, 6), _), v(_(1, 2, 6), _)) = nt2::symeig(b);
  z =  mtimes(mtimes(v(_(1,2,6), _), d(_(1,2,6), _)), nt2::trans(v(_(1,2,6), _)));
  NT2_TEST_ULP_EQUAL(nt2::triu(z), nt2::triu(b), T(16.0));
}
