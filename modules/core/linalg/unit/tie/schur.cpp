//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#define NT2_UNIT_MODULE "nt2 linalg toolbox - tied schur function"

#include <nt2/table.hpp>
#include <nt2/include/functions/zeros.hpp>
#include <nt2/include/functions/ones.hpp>
#include <nt2/include/functions/eye.hpp>
#include <nt2/include/functions/schur.hpp>
#include <nt2/include/functions/complexify.hpp>
#include <nt2/include/functions/mtimes.hpp>
#include <nt2/include/functions/trans.hpp>
#include <nt2/include/functions/conj.hpp>
#include <nt2/include/functions/tie.hpp>
#include <nt2/include/functions/trans.hpp>
#include <nt2/include/functions/mtimes.hpp>
#include <nt2/include/functions/globalmax.hpp>
#include <nt2/include/functions/isulpequal.hpp>

#include <nt2/sdk/unit/tests.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/exceptions.hpp>
#include <nt2/sdk/unit/tests/basic.hpp>

NT2_TEST_CASE_TPL ( schur, NT2_REAL_TYPES)
{
  typedef nt2::table<T> table_t;
  table_t z, t, b = nt2::ones(4, 4, nt2::meta::as_<T>())
                + T(10)*nt2::eye(4, 4, nt2::meta::as_<T>());
  b(1, 1) = 1;
  NT2_DISPLAY(b);
  t = nt2::schur(b);
  NT2_DISPLAY(t); // just quasi diag matrix

  nt2::tie(z, t) = nt2::schur(b); //real
  NT2_DISPLAY(z);
  NT2_DISPLAY(t);
  NT2_DISPLAY(nt2::mtimes(nt2::mtimes(z, t), nt2::trans(z)));
  NT2_TEST_ULP_EQUAL(b, nt2::mtimes(nt2::mtimes(z, t), nt2::trans(z)), 20.0);
}

NT2_TEST_CASE_TPL ( schurc, NT2_REAL_TYPES)
{
  typedef std::complex<T> cT;
  typedef nt2::table<cT> table_t;
  table_t z, t, b = nt2::ones(4, 4, nt2::meta::as_<cT>())
                + T(10)*nt2::eye(4, 4, nt2::meta::as_<cT>());
  b(1, 1) = 1;
  NT2_DISPLAY(b);
  t = nt2::schur(b);
  NT2_DISPLAY(t); // triu matrix

  nt2::tie(z, t) = nt2::schur(b); //complex
  NT2_DISPLAY(z);
  NT2_DISPLAY(t);
  NT2_DISPLAY(nt2::mtimes(nt2::mtimes(z, t), nt2::trans(z)));
  NT2_TEST_ULP_EQUAL(b, nt2::mtimes(nt2::mtimes(z, t), nt2::trans(nt2::conj(z))), 20.0);
}



NT2_TEST_CASE_TPL ( schur_m_test, NT2_REAL_TYPES)
{
  typedef nt2::table<T> table_t;
  table_t z, t, zz;

  T bb[9] = {-149,    -50,   -154,
             537,    180,    546,
             -27,     -9,    -25 };
  table_t b(nt2::of_size(3, 3));
  int k = 0;
  for(int i=1; i <= 3; ++i)
    {
      for(int j=1; j <= 3; ++j)
        {
          b(i, j) = bb[k++];
        }
    }
  NT2_DISPLAY(b);
  nt2::tie(z, t) = nt2::schur(b); //real
  NT2_DISPLAY(z);
  NT2_DISPLAY(t);
  zz =  mtimes(nt2::mtimes(z, t), nt2::trans(z));
  NT2_TEST(isulpequal(zz, b, T(16.0)));
}


