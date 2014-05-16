//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#define NT2_UNIT_MODULE "nt2 linalg toolbox - symeig factorization"

#include <nt2/table.hpp>
#include <nt2/include/functions/zeros.hpp>
#include <nt2/include/functions/ones.hpp>
#include <nt2/include/functions/eye.hpp>
#include <nt2/include/functions/symeig.hpp>
#include <nt2/include/functions/cons.hpp>
#include <nt2/include/functions/ldexp.hpp>
#include <nt2/include/functions/repnum.hpp>
#include <nt2/include/functions/rif.hpp>
#include <nt2/include/functions/isulpequal.hpp>
#include <nt2/include/functions/transpose.hpp>
#include <nt2/include/functions/globalmax.hpp>
#include <nt2/include/functions/triu.hpp>
#include <nt2/include/functions/mtimes.hpp>
#include <nt2/sdk/unit/tests.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/exceptions.hpp>
#include <nt2/sdk/unit/tests/basic.hpp>

NT2_TEST_CASE_TPL(symeig_sca, NT2_REAL_TYPES)
{
  using nt2::symeig;
  typedef nt2::table<T> t_t;
  t_t w =   symeig(T(2));
  NT2_TEST_ULP_EQUAL(w, T(2), 0);
  w =   symeig(T(2), nt2::matrix_);
  NT2_TEST_ULP_EQUAL(w, T(2), 0);
  w =   symeig(T(2), nt2::matrix_, 'L');
  NT2_TEST_ULP_EQUAL(w, T(2), 0);
//   t_t v;
//   nt2::tie(w, v) = symeig(T(2), nt2::matrix_);
}

NT2_TEST_CASE_TPL(symeig, NT2_REAL_TYPES)
{
  using nt2::symeig;
  using nt2::_;
  typedef typename nt2::meta::as_integer<T, signed>::type itype_t;
  typedef nt2::table<T> t_t;
  typedef nt2::table<itype_t> it_t;
  t_t b =       nt2::ones (4, 4, nt2::meta::as_<T>())
        + T(10)*nt2::eye  (4, 4, nt2::meta::as_<T>());
  //  b(_, 1) = b(_, 3);
  t_t w = symeig(b);
  t_t sw =  nt2::cons<T>(nt2::of_size(4, 1), T(10), T(10), T(10), T(14));
  NT2_TEST_ULP_EQUAL(w, sw, 1);
  nt2::display("w     ", w);
  nt2::display("b     ", b);
  w = symeig(b, nt2::matrix_);
  NT2_TEST_ULP_EQUAL(w, from_diag(sw), 1);
  w = symeig(b, nt2::vector_);
  NT2_TEST_ULP_EQUAL(w, sw, 1);
  w = symeig(b, 'L');
  NT2_TEST_ULP_EQUAL(w, sw, 1);

  w = symeig(b, nt2::matrix_, 'L');
  NT2_TEST_ULP_EQUAL(w, from_diag(sw), 1);
  w = symeig(b, nt2::vector_, 'L');
  NT2_TEST_ULP_EQUAL(w, sw, 1);


  t_t v;
  nt2::tie(w, v) = symeig(b);
  nt2::display("w     ", w);
  nt2::display("v     ", v);
  NT2_TEST_ULP_EQUAL(w, from_diag(sw), 1);
  t_t z =  mtimes(mtimes(v, w), nt2::trans(v));
  NT2_TEST_ULP_EQUAL(nt2::triu(b), nt2::triu(z), 8);

  nt2::tie(w, v) = symeig(b, nt2::matrix_);
  z =  mtimes(mtimes(v, w), nt2::trans(v));
  NT2_TEST_ULP_EQUAL(nt2::triu(b), nt2::triu(z), 8);

  nt2::tie(w, v) = symeig(b, nt2::vector_);
  z =  mtimes(mtimes(v, nt2::from_diag(w)), nt2::trans(v));
  NT2_TEST_ULP_EQUAL(nt2::triu(b), nt2::triu(z), 8);

  nt2::tie(w, v) = symeig(b, 'L');
  z =  mtimes(mtimes(v, w), nt2::trans(v));
  NT2_TEST_ULP_EQUAL(nt2::triu(b), nt2::triu(z), 8);

  nt2::tie(w, v) = symeig(b, nt2::matrix_, 'L');
  z =  mtimes(mtimes(v, w), nt2::trans(v));
  NT2_TEST_ULP_EQUAL(nt2::triu(b), nt2::triu(z), 8);

  nt2::tie(w, v) = symeig(b, nt2::vector_, 'L');
  z =  mtimes(mtimes(v, nt2::from_diag(w)), nt2::trans(v));
  NT2_TEST_ULP_EQUAL(nt2::triu(b), nt2::triu(z), 8);

}
