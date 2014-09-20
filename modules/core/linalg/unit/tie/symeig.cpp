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
#include <nt2/include/functions/diag_of.hpp>
#include <nt2/include/functions/from_diag.hpp>
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


NT2_TEST_CASE_TPL ( symeig_no_1i, NT2_REAL_TYPES)
{
  typedef nt2::table<T> table_t;
  table_t w, v, d, b = nt2::ones(4, 4, nt2::meta::as_<T>())
    + T(10)*nt2::eye(4, 4, nt2::meta::as_<T>());

  std::cout << "11 nt2::tie(d, v) = nt2::symeig(b);" << std::endl;
  nt2::tie(d, v) = nt2::symeig(b);
  NT2_TEST_ULP_EQUAL(b, nt2::mtimes(v, nt2::mtimes(d, nt2::trans(v))), 10.0);

  std::cout << "12 w = nt2::symeig(b);" << std::endl;
  w = nt2::symeig(b);
  NT2_TEST_ULP_EQUAL(w, nt2::diag_of(d), 10.0);
}

NT2_TEST_CASE_TPL ( symeig_no_2i, NT2_REAL_TYPES)
{
  typedef nt2::table<T> table_t;
  table_t w, v, d, b = nt2::ones(4, 4, nt2::meta::as_<T>())
                + T(10)*nt2::eye(4, 4, nt2::meta::as_<T>());

  std::cout << "21 nt2::tie(d, v) = nt2::symeig(b, nt2::upper_);" << std::endl;
  nt2::tie(d, v) = nt2::symeig(b, nt2::upper_);
  NT2_TEST_ULP_EQUAL(b, nt2::mtimes(v, nt2::mtimes(d, nt2::trans(v))), 10.0);

  std::cout << "22w = nt2::symeig(b nt2::upper_);" << std::endl;
  w = nt2::symeig(b, nt2::upper_);
  NT2_TEST_ULP_EQUAL(w, nt2::diag_of(d), 10.0);

  std::cout << "23 nt2::tie(d, v) = nt2::symeig(b, nt2::lower_);" << std::endl;
  nt2::tie(d, v) = nt2::symeig(b, nt2::lower_);
  NT2_TEST_ULP_EQUAL(b, nt2::mtimes(v, nt2::mtimes(d, nt2::trans(v))), 10.0);

  std::cout << "24 w = nt2::symeig(b nt2::lower_);" << std::endl;
  w = nt2::symeig(b, nt2::lower_);
  NT2_TEST_ULP_EQUAL(w, nt2::diag_of(d), 10.0);

  std::cout << "25 nt2::tie(d, v) = nt2::symeig(b, nt2::matrix_);" << std::endl;
  nt2::tie(d, v) = nt2::symeig(b, nt2::matrix_);
  NT2_TEST_ULP_EQUAL(b, nt2::mtimes(v, nt2::mtimes(d, nt2::trans(v))), 10.0);

  std::cout << "26 w = nt2::symeig(b, nt2::matrix_);" << std::endl;
  w = nt2::symeig(b, nt2::matrix_);
  NT2_TEST_ULP_EQUAL(w, d, 10.0);

  std::cout << "27 nt2::tie(d, v) = nt2::symeig(b, nt2::vector_);" << std::endl;
  nt2::tie(d, v) = nt2::symeig(b, nt2::vector_);
  NT2_TEST_ULP_EQUAL(b, nt2::mtimes(v, nt2::mtimes(nt2::from_diag(d), nt2::trans(v))), 10.0);

  std::cout << "28 w = nt2::symeig(b, nt2::vector_);" << std::endl;
  w = nt2::symeig(b, nt2::vector_);
  NT2_TEST_ULP_EQUAL(w, d, 10.0);

  std::cout << "29 nt2::tie(d, v) = nt2::symeig(b, nt2::raw_);" << std::endl;
  nt2::tie(d, v) = nt2::symeig(b, nt2::raw_);
  NT2_TEST_ULP_EQUAL(b, nt2::mtimes(v, nt2::mtimes(nt2::from_diag(d), nt2::trans(v))), 10.0);

  std::cout << "210 w = nt2::symeig(b, nt2::raw_);" << std::endl;
  w = nt2::symeig(b, nt2::raw_);
  NT2_TEST_ULP_EQUAL(w, d, 10.0); }

NT2_TEST_CASE_TPL ( symeig_no_3i, NT2_REAL_TYPES)
{
  typedef nt2::table<T> table_t;
  table_t w, v, d, b = nt2::ones(4, 4, nt2::meta::as_<T>())
                + T(10)*nt2::eye(4, 4, nt2::meta::as_<T>());

  std::cout << "31 nt2::tie(d, v) = nt2::symeig(b, nt2::matrix_, nt2::upper_);" << std::endl;
  nt2::tie(d, v) = nt2::symeig(b, nt2::upper_);
  NT2_TEST_ULP_EQUAL(b, nt2::mtimes(v, nt2::mtimes(d, nt2::trans(v))), 10.0);

  std::cout << "32 w = nt2::symeig(b, nt2::matrix_, nt2::upper_);" << std::endl;
  w = nt2::symeig(b, nt2::matrix_, nt2::upper_);
  NT2_TEST_ULP_EQUAL(w, d, 10.0);


  std::cout << "33 nt2::tie(d, v) = nt2::symeig(b, nt2::vector_, nt2::upper_);" << std::endl;
  nt2::tie(d, v) = nt2::symeig(b, nt2::vector_, nt2::upper_);
  NT2_TEST_ULP_EQUAL(b, nt2::mtimes(v, nt2::mtimes(nt2::from_diag(d), nt2::trans(v))), 10.0);

  std::cout << "34 w = nt2::symeig(b, nt2::vector_, nt2::upper_);" << std::endl;
  w = nt2::symeig(b, nt2::vector_, nt2::upper_);
  NT2_TEST_ULP_EQUAL(w, d, 10.0);

  std::cout << "35 nt2::tie(d, v) = nt2::symeig(b, nt2::matrix_, nt2::lower_);" << std::endl;
  nt2::tie(d, v) = nt2::symeig(b, nt2::matrix_, nt2::lower_);
  NT2_TEST_ULP_EQUAL(b, nt2::mtimes(v, nt2::mtimes(d, nt2::trans(v))), 10.0);

  std::cout << "36 w = nt2::symeig(b, nt2::matrix_, nt2::lower_);" << std::endl;
  w = nt2::symeig(b, nt2::matrix_, nt2::lower_);
  NT2_TEST_ULP_EQUAL(w, d, 10.0);

  std::cout << "37 nt2::tie(d, v) = nt2::symeig(b, nt2::vector_, nt2::lower_);" << std::endl;
  nt2::tie(d, v) = nt2::symeig(b, nt2::vector_, nt2::lower_);
  NT2_TEST_ULP_EQUAL(b, nt2::mtimes(v, nt2::mtimes(nt2::from_diag(d), nt2::trans(v))), 10.0);

  std::cout << "38 w = nt2::symeig(b, nt2::vector_, nt2::lower_);" << std::endl;
  w = nt2::symeig(b, nt2::vector_, nt2::lower_);
  NT2_TEST_ULP_EQUAL(w, d, 10.0);

  std::cout << "39 nt2::tie(d, v) = nt2::symeig(b, nt2::raw_, nt2::lower_);" << std::endl;
  nt2::tie(d, v) = nt2::symeig(b, nt2::raw_, nt2::lower_);
  NT2_TEST_ULP_EQUAL(b, nt2::mtimes(v, nt2::mtimes(nt2::from_diag(d), nt2::trans(v))), 10.0);

  std::cout << "310 w = nt2::symeig(b, nt2::raw_, nt2::lower_);" << std::endl;
  w = nt2::symeig(b, nt2::raw_, nt2::lower_);
  NT2_TEST_ULP_EQUAL(w, d, 10.0);

  std::cout << "311 nt2::tie(d, v) = nt2::symeig(b, nt2::raw_, nt2::upper_);" << std::endl;
  nt2::tie(d, v) = nt2::symeig(b, nt2::raw_, nt2::upper_);
  NT2_TEST_ULP_EQUAL(b, nt2::mtimes(v, nt2::mtimes(nt2::from_diag(d), nt2::trans(v))), 10.0);

  std::cout << "312 w = nt2::symeig(b, nt2::raw_, nt2::upper_);" << std::endl;
  w = nt2::symeig(b, nt2::raw_, nt2::upper_);
  NT2_TEST_ULP_EQUAL(w, d, 10.0);
}

NT2_TEST_CASE_TPL ( symeig_no_1i_sub, NT2_REAL_TYPES)
{
  using nt2::meta::as_;
  using nt2::_;
  typedef nt2::table<T> table_t;
  table_t w, v, d, b = nt2::ones(4, 4, nt2::meta::as_<T>())
    + T(10)*nt2::eye(4, 4, nt2::meta::as_<T>());
  w = nt2::ones(1, 8, as_<T>());
  d = nt2::ones(8, 4, as_<T>());
  v = nt2::ones(8, 4, as_<T>());
  std::cout << "sub11 nt2::tie(d(_(1, 2, 8), _), v(_(1, 2, 8), _)) = nt2::symeig(b);" << std::endl;
  nt2::tie(d(_(1, 2, 8), _), v(_(1, 2, 8), _)) = nt2::symeig(b);
  NT2_TEST_ULP_EQUAL(b, nt2::mtimes(v(_(1, 2, 8), _), nt2::mtimes(d(_(1, 2, 8), _), nt2::trans(v(_(1, 2, 8), _)))), 10.0);

  std::cout << "sub12 w(_(1, 2, 8)) = nt2::symeig(b);" << std::endl;
  w(_(1, 2, 8)) = nt2::symeig(b);
  NT2_TEST_ULP_EQUAL(w(_(1, 2, 8)), nt2::diag_of(d(_(1, 2, 8), _)), 10.0);
}

NT2_TEST_CASE_TPL ( symeig_no_2i_sub, NT2_REAL_TYPES)
{
  using nt2::meta::as_;
  using nt2::_;
  typedef nt2::table<T> table_t;
  table_t w, v, d, dd,  ww,
    b = nt2::ones(4, 4, nt2::meta::as_<T>())
    + T(10)*nt2::eye(4, 4, nt2::meta::as_<T>());
  w = nt2::ones(1, 8, as_<T>());
  ww = nt2::ones(8, 4, as_<T>());
  d = nt2::ones(8, 4, as_<T>());
  dd = nt2::ones(1, 8, as_<T>());
  v = nt2::ones(8, 4, as_<T>());

  std::cout << "sub21 nt2::tie(d, v) = nt2::symeig(b, nt2::upper_);" << std::endl;
  nt2::tie(d(_(1, 2, 8), _), v(_(1, 2, 8), _)) = nt2::symeig(b, nt2::upper_);
  NT2_TEST_ULP_EQUAL(b, nt2::mtimes(v(_(1, 2, 8), _), nt2::mtimes(d(_(1, 2, 8), _), nt2::trans(v(_(1, 2, 8), _)))), 10.0);

  std::cout << "sub22 w(_(1, 2, 8)) = nt2::symeig(b, nt2::upper_);" << std::endl;
  w(_(1, 2, 8)) = nt2::symeig(b, nt2::upper_);
  NT2_TEST_ULP_EQUAL(w(_(1, 2, 8)), nt2::diag_of(d(_(1, 2, 8), _)), 10.0);

  std::cout << "sub23 nt2::tie(d(_(1, 2, 8), _), v(_(1, 2, 8), _)) = nt2::symeig(b, nt2::lower_);" << std::endl;
  nt2::tie(d(_(1, 2, 8), _), v(_(1, 2, 8), _)) = nt2::symeig(b, nt2::lower_);
  NT2_TEST_ULP_EQUAL(b, nt2::mtimes(v(_(1, 2, 8), _), nt2::mtimes(d(_(1, 2, 8), _), nt2::trans(v(_(1, 2, 8), _)))), 10.0);

  std::cout << "sub24 w(_(1, 2, 8)) = nt2::symeig(b nt2::lower_);" << std::endl;
  w(_(1, 2, 8)) = nt2::symeig(b, nt2::lower_);
  NT2_TEST_ULP_EQUAL(w(_(1, 2, 8)), nt2::diag_of(d(_(1, 2, 8), _)), 10.0);

  std::cout << "sub25 nt2::tie(d(_(1, 2, 8), _), v(_(1, 2, 8), _)) = nt2::symeig(b, nt2::matrix_);" << std::endl;
  nt2::tie(d(_(1, 2, 8), _), v(_(1, 2, 8), _)) = nt2::symeig(b, nt2::matrix_);
  NT2_TEST_ULP_EQUAL(b, nt2::mtimes(v(_(1, 2, 8), _), nt2::mtimes(d(_(1, 2, 8), _), nt2::trans(v(_(1, 2, 8), _)))), 10.0);

  std::cout << "sub26 ww(_(1, 2, 8), _) = nt2::symeig(b, nt2::matrix_);" << std::endl;
  ww(_(1, 2, 8), _) = nt2::symeig(b, nt2::matrix_);
  NT2_TEST_ULP_EQUAL(ww, d, 10.0);

  std::cout << "sub27 nt2::tie(dd(_(1, 2, 8)), v(_(1, 2, 8), _)) = nt2::symeig(b, nt2::vector_);" << std::endl;
  nt2::tie(dd(_(1, 2, 8)), v(_(1, 2, 8), _)) = nt2::symeig(b, nt2::vector_);
  NT2_TEST_ULP_EQUAL(b, nt2::mtimes(v(_(1, 2, 8), _), nt2::mtimes(nt2::from_diag(dd(_(1, 2, 8))), nt2::trans(v(_(1, 2, 8), _)))), 10.0);

  std::cout << "sub28 w(_(1, 2, 8)) = nt2::symeig(b, nt2::vector_);" << std::endl;
  w(_(1, 2, 8)) = nt2::symeig(b, nt2::vector_);
  NT2_DISPLAY(w);
  NT2_DISPLAY(dd);
  NT2_TEST_ULP_EQUAL(w(_(1, 2, 8)), dd(_(1, 2, 8)), 10.0);

  std::cout << "sub29 nt2::tie(dd_(1, 2, 8)), v_(1, 2, 8), _)) = nt2::symeig(b, nt2::raw_);" << std::endl;
  nt2::tie(dd(_(1, 2, 8)), v(_(1, 2, 8), _)) = nt2::symeig(b, nt2::raw_);
  NT2_TEST_ULP_EQUAL(b, nt2::mtimes(v(_(1, 2, 8), _), nt2::mtimes(nt2::from_diag(dd(_(1, 2, 8))), nt2::trans(v(_(1, 2, 8), _)))), 10.0);

  std::cout << "sub210 w(_(1, 2, 8)) = nt2::symeig(b, nt2::raw_);" << std::endl;
  w(_(1, 2, 8)) = nt2::symeig(b, nt2::raw_);
  NT2_TEST_ULP_EQUAL(w(_(1, 2, 8)), dd(_(1, 2, 8)), 10.0);
 }

NT2_TEST_CASE_TPL ( symeig_no_3i_sub, NT2_REAL_TYPES)
{
  using nt2::meta::as_;
  using nt2::_;
  typedef nt2::table<T> table_t;
  table_t w, v, d, dd, ww,
    b = nt2::ones(4, 4, nt2::meta::as_<T>())
    + T(10)*nt2::eye(4, 4, nt2::meta::as_<T>());
  w = nt2::ones(1, 8, as_<T>());
  ww = nt2::ones(8, 4, as_<T>());
  d = nt2::ones(8, 4, as_<T>());
  dd = nt2::ones(1, 8, as_<T>());
  v = nt2::ones(8, 4, as_<T>());

  std::cout << "31 nt2::tie(d(_(1, 2, 8), _), v(_(1, 2, 8), _)) = nt2::symeig(b, nt2::matrix_, nt2::upper_);" << std::endl;
  nt2::tie(d(_(1, 2, 8), _), v(_(1, 2, 8), _)) = nt2::symeig(b, nt2::upper_);
  NT2_TEST_ULP_EQUAL(b, nt2::mtimes(v(_(1, 2, 8), _), nt2::mtimes(d(_(1, 2, 8), _), nt2::trans(v(_(1, 2, 8), _)))), 10.0);

  std::cout << "32 ww(_(1, 2, 8), _) = nt2::symeig(b, nt2::matrix_, nt2::upper_);" << std::endl;
  ww(_(1, 2, 8), _) = nt2::symeig(b, nt2::matrix_, nt2::upper_);
  NT2_TEST_ULP_EQUAL(ww(_(1, 2, 8), _), d(_(1, 2, 8), _), 10.0);


  std::cout << "33 nt2::tie(dd(_(1, 2, 8)), v(_(1, 2, 8), _)) = nt2::symeig(b, nt2::vector_, nt2::upper_);" << std::endl;
  nt2::tie(dd(_(1, 2, 8)), v(_(1, 2, 8), _)) = nt2::symeig(b, nt2::vector_, nt2::upper_);
  NT2_TEST_ULP_EQUAL(b, nt2::mtimes(v(_(1, 2, 8), _), nt2::mtimes(nt2::from_diag(dd(_(1, 2, 8))), nt2::trans(v(_(1, 2, 8), _)))), 10.0);

  std::cout << "34 w(_(1, 2, 8)) = nt2::symeig(b, nt2::vector_, nt2::upper_);" << std::endl;
  w(_(1, 2, 8)) = nt2::symeig(b, nt2::vector_, nt2::upper_);
  NT2_TEST_ULP_EQUAL(w(_(1, 2, 8)), dd(_(1, 2, 8)), 10.0);

  std::cout << "35 nt2::tie(d(_(1, 2, 8), _), v(_(1, 2, 8), _)) = nt2::symeig(b, nt2::matrix_, nt2::lower_);" << std::endl;
  nt2::tie(d(_(1, 2, 8), _), v(_(1, 2, 8), _)) = nt2::symeig(b, nt2::matrix_, nt2::lower_);
  NT2_TEST_ULP_EQUAL(b, nt2::mtimes(v(_(1, 2, 8), _), nt2::mtimes(d(_(1, 2, 8), _), nt2::trans(v(_(1, 2, 8), _)))), 10.0);

  std::cout << "36 ww(_(1, 2, 8), _) = nt2::symeig(b, nt2::matrix_, nt2::lower_);" << std::endl;
  ww(_(1, 2, 8), _) = nt2::symeig(b, nt2::matrix_, nt2::lower_);
  NT2_TEST_ULP_EQUAL(ww(_(1, 2, 8), _), d(_(1, 2, 8), _), 10.0);


  std::cout << "37 nt2::tie(dd(_(1, 2, 8)), v(_(1, 2, 8), _)) = nt2::symeig(b, nt2::vector_, nt2::lower_);" << std::endl;
  nt2::tie(dd(_(1, 2, 8)), v(_(1, 2, 8), _)) = nt2::symeig(b, nt2::vector_, nt2::lower_);
  NT2_TEST_ULP_EQUAL(b, nt2::mtimes(v(_(1, 2, 8), _), nt2::mtimes(nt2::from_diag(dd(_(1, 2, 8))), nt2::trans(v(_(1, 2, 8), _)))), 10.0);

  std::cout << "38 w(_(1, 2, 8)) = nt2::symeig(b, nt2::vector_, nt2::lower_);" << std::endl;
  w(_(1, 2, 8)) = nt2::symeig(b, nt2::vector_, nt2::lower_);
  NT2_TEST_ULP_EQUAL(w(_(1, 2, 8)), dd(_(1, 2, 8)), 10.0);

  std::cout << "39 nt2::tie(d, v) = nt2::symeig(b, nt2::raw_, nt2::lower_);" << std::endl;
  nt2::tie(dd(_(1, 2, 8)), v(_(1, 2, 8), _)) = nt2::symeig(b, nt2::raw_, nt2::lower_);
  NT2_TEST_ULP_EQUAL(b, nt2::mtimes(v(_(1, 2, 8), _), nt2::mtimes(nt2::from_diag(dd(_(1, 2, 8))), nt2::trans(v(_(1, 2, 8), _)))), 10.0);

  std::cout << "310 w(_(1, 2, 8)) = nt2::symeig(b, nt2::raw_, nt2::lower_);" << std::endl;
  w(_(1, 2, 8)) = nt2::symeig(b, nt2::raw_, nt2::lower_);
  NT2_TEST_ULP_EQUAL(w(_(1, 2, 8)), dd(_(1, 2, 8)), 10.0);

  std::cout << "311 nt2::tie(dd(_(1, 2, 8)), v(_(1, 2, 8), _)) = nt2::symeig(b, nt2::raw_, nt2::upper_);" << std::endl;
  nt2::tie(dd(_(1, 2, 8)), v(_(1, 2, 8), _)) = nt2::symeig(b, nt2::raw_, nt2::upper_);
  NT2_TEST_ULP_EQUAL(b, nt2::mtimes(v(_(1, 2, 8), _), nt2::mtimes(nt2::from_diag(dd(_(1, 2, 8))), nt2::trans(v(_(1, 2, 8), _)))), 10.0);

  std::cout << "312 w(_(1, 2, 8)) = nt2::symeig(b, nt2::raw_, nt2::upper_);" << std::endl;
  w(_(1, 2, 8)) = nt2::symeig(b, nt2::raw_, nt2::upper_);
  NT2_TEST_ULP_EQUAL(w(_(1, 2, 8)), dd(_(1, 2, 8)), 10.0);
}


