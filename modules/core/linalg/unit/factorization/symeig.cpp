//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/table.hpp>
#include <nt2/include/functions/zeros.hpp>
#include <nt2/include/functions/ones.hpp>
#include <nt2/include/functions/symeig.hpp>
#include <nt2/include/functions/cons.hpp>
#include <nt2/include/functions/eye.hpp>
#include <nt2/include/functions/transpose.hpp>
#include <nt2/include/functions/ctranspose.hpp>
#include <nt2/include/functions/globalmax.hpp>
#include <nt2/include/functions/triu.hpp>
#include <nt2/include/functions/tril.hpp>
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
  w =   symeig(T(2), nt2::matrix_, nt2::lower_);
  NT2_TEST_ULP_EQUAL(w, T(2), 0);
//  t_t v;
//  nt2::tie(w, v) = symeig(T(2), nt2::matrix_);//this does not work
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
  t_t w = symeig(b);
  t_t sw =  nt2::cons<T>(nt2::of_size(4, 1), T(10), T(10), T(10), T(14));
  NT2_TEST_ULP_EQUAL(w, sw, 1);
  nt2::display("w     ", w);
  nt2::display("b     ", b);
  w = symeig(b, nt2::matrix_);
  NT2_TEST_ULP_EQUAL(w, from_diag(sw), 1);
  w = symeig(b, nt2::vector_);
  nt2::display("w     ", w);
  NT2_TEST_ULP_EQUAL(w, sw, 1);

  w = symeig(b, nt2::lower_);
  NT2_TEST_ULP_EQUAL(w, sw, 1);

  w = symeig(b, nt2::matrix_, nt2::lower_);
  NT2_TEST_ULP_EQUAL(w, from_diag(sw), 1);
  w = symeig(b, nt2::vector_, nt2::lower_);
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

  nt2::tie(w, v) = symeig(nt2::tril(b), nt2::lower_);
  z =  mtimes(mtimes(v, w), nt2::trans(v));
  NT2_TEST_ULP_EQUAL(nt2::tril(b), nt2::tril(z), 8);

  nt2::tie(w, v) = symeig(b, nt2::matrix_, nt2::lower_);
  z =  mtimes(mtimes(v, w), nt2::trans(v));
  NT2_TEST_ULP_EQUAL(nt2::triu(b), nt2::triu(z), 8);

  nt2::tie(w, v) = symeig(b, nt2::vector_, nt2::lower_);
  z =  mtimes(mtimes(v, nt2::from_diag(w)), nt2::trans(v));
  NT2_TEST_ULP_EQUAL(nt2::triu(b), nt2::triu(z), 8);

}

NT2_TEST_CASE_TPL(symeigc, NT2_REAL_TYPES)
{
  using nt2::symeig;
  using nt2::_;
  typedef std::complex<T> cT;
  typedef nt2::table<T> t_t;
  typedef nt2::table<cT> ct_t;
  ct_t b =       nt2::ones (4, 4, nt2::meta::as_<T>())
        + T(10)*nt2::eye  (4, 4, nt2::meta::as_<T>());
  t_t sw =  nt2::cons<T>(nt2::of_size(4, 1), T(10), T(10), T(10), T(14));
  nt2::display("b     ", b);

  {
    t_t w = symeig(b);
   NT2_TEST_ULP_EQUAL(w, sw, 2);
    nt2::display("w     ", w);
  }

  {
    t_t w = symeig(b, nt2::matrix_);
    NT2_TEST_ULP_EQUAL(w, from_diag(sw), 2);
  }

  {
    t_t w = symeig(b, nt2::vector_);
    nt2::display("w     ", w);
    NT2_TEST_ULP_EQUAL(w, sw, 2);
  }

  {

    t_t w = symeig(b, nt2::lower_);
    NT2_TEST_ULP_EQUAL(w, sw, 2);
  }

  {

    t_t w = symeig(b, nt2::matrix_, nt2::lower_);
    NT2_TEST_ULP_EQUAL(w, from_diag(sw), 1);
    w = symeig(b, nt2::vector_, nt2::lower_);
    NT2_TEST_ULP_EQUAL(w, sw, 1);
  }

  {
    ct_t v;
    t_t w;
    nt2::tie(w, v) = symeig(b);
    nt2::display("w     ", w);
    nt2::display("v     ", v);
    NT2_TEST_ULP_EQUAL(w, from_diag(sw), 2);
    ct_t z =  mtimes(mtimes(v, w), nt2::ctrans(v));
    NT2_TEST_ULP_EQUAL(nt2::triu(b), nt2::triu(z), 8);
  }

  {
    ct_t v;
    t_t w;
    nt2::tie(w, v) = symeig(b, nt2::matrix_);
    nt2::display("w     ", w);
    nt2::display("v     ", v);
    ct_t z =  mtimes(mtimes(v, w), nt2::ctrans(v));
    NT2_TEST_ULP_EQUAL(nt2::triu(b), nt2::triu(z), 8);
  }

  {
    ct_t v;
    t_t w;

    nt2::tie(w, v) = symeig(b, nt2::vector_);
    nt2::display("w     ", w);
    nt2::display("v     ", v);

    t_t ww = nt2::from_diag(w);
    ct_t z =  mtimes(mtimes(v, ww), nt2::ctrans(v));
    NT2_TEST_ULP_EQUAL(nt2::triu(b), nt2::triu(z), 8);
  }

  {
    ct_t v;
    t_t w;

    nt2::tie(w, v) = symeig(nt2::tril(b), nt2::lower_);
    ct_t z =  mtimes(mtimes(v, w), nt2::trans(v));
    NT2_TEST_ULP_EQUAL(nt2::tril(b), nt2::tril(z), 8);
  }

  {
    ct_t v;
    t_t w;

    nt2::tie(w, v) = symeig(b, nt2::matrix_, nt2::lower_);
    ct_t z =  mtimes(mtimes(v, w), nt2::ctrans(v));
    NT2_TEST_ULP_EQUAL(nt2::triu(b), nt2::triu(z), 8);
  }

  {
    ct_t v;
    t_t w;
    nt2::tie(w, v) = symeig(b, nt2::vector_, nt2::lower_);
    nt2::display("w     ", w);
    nt2::display("v     ", v);
    t_t ww = nt2::from_diag(w);
    nt2::display("ww     ", ww);
    ct_t z =  mtimes(mtimes(v, ww), nt2::ctrans(v));
    nt2::display("z     ", z);
    NT2_TEST_ULP_EQUAL(nt2::tril(b), nt2::tril(z), 8);
  }
  {
    ct_t v;
    t_t w;
    nt2::tie(w, v) = symeig(b, nt2::lower_, nt2::vector_);
    nt2::display("w     ", w);
    nt2::display("v     ", v);
    t_t ww = nt2::from_diag(w);
    nt2::display("ww     ", ww);
    ct_t z =  mtimes(mtimes(v, ww), nt2::ctrans(v));
    nt2::display("z     ", z);
    NT2_TEST_ULP_EQUAL(nt2::tril(b), nt2::tril(z), 8);
  }

}
