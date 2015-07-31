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
#include <nt2/include/functions/eye.hpp>
#include <nt2/include/functions/planerot.hpp>
#include <nt2/include/functions/sincos.hpp>
#include <nt2/include/functions/cons.hpp>
#include <nt2/include/functions/colvect.hpp>
#include <nt2/include/functions/rowvect.hpp>
#include <nt2/include/functions/linspace.hpp>
#include <nt2/include/functions/rif.hpp>
#include <nt2/include/functions/tie.hpp>
#include <nt2/include/functions/isulpequal.hpp>
#include <nt2/include/functions/mtimes.hpp>
#include <nt2/include/constants/sqrt_2.hpp>
#include <nt2/include/constants/i.hpp>
#include <nt2/sdk/unit/tests.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/exceptions.hpp>
#include <nt2/sdk/unit/tests/basic.hpp>
//#include <nt2/include/functions/lartg.hpp>

NT2_TEST_CASE_TPL ( planerot, NT2_REAL_TYPES)
{
  typedef nt2::table<T> table_t;
  table_t x = nt2::ones(2, 1, nt2::meta::as_<T>());
  table_t g, y;
  nt2::tie(g, y) = nt2::planerot(x);
  NT2_TEST_ULP_EQUAL(mtimes(g,nt2::colvect(x)), y, 0.5);
  table_t r = nt2::zeros(2, 1, nt2::meta::as_<T>());
  r(1) = nt2::Sqrt_2<T>();
  NT2_TEST_ULP_EQUAL(r, y, 0.5);
  nt2::tie(g, y) = nt2::planerot(nt2::rowvect(x));
  NT2_TEST_ULP_EQUAL(mtimes(nt2::rowvect(x), g), y, 0.5);
  NT2_DISPLAY(rowvect(x));
  NT2_DISPLAY(mtimes(nt2::rowvect(x), g));
  NT2_DISPLAY(g);


}

NT2_TEST_CASE_TPL ( planerot2, NT2_REAL_TYPES)
{
  typedef nt2::table<T> table_t;
  table_t x = nt2::rif(2, 1, nt2::meta::as_<T>());
  table_t g, y;
  nt2::tie(g, y) = nt2::planerot(x);
  NT2_TEST_ULP_EQUAL(nt2::mtimes(g, x), y, 1);
}


NT2_TEST_CASE_TPL ( planerot3, NT2_REAL_TYPES)
{
  typedef nt2::table<T> table_t;
  table_t x = nt2::rif(2, 1, nt2::meta::as_<T>());
  T c, s;
  nt2::tie(s, c) = nt2::planerot(x, nt2::tag::sincos_());
  table_t g = nt2::cons(nt2::of_size(2, 2), c, -s, s, c);
  NT2_TEST(nt2::isulpequal(nt2::mtimes(g, x)(2), nt2::Zero<T>()));

}

NT2_TEST_CASE_TPL ( planerotc4, NT2_REAL_TYPES)
{
  typedef typename std::complex<T> cT;
  typedef nt2::table<cT> table_t;
  table_t x = nt2::linspace(cT(1, 2), cT(3, 2), 2);
  table_t g;
  table_t y;
  nt2::tie(g, y) = nt2::planerot(colvect(x));
  NT2_TEST_ULP_EQUAL(nt2::mtimes(g, colvect(x)), y, 2);
}

NT2_TEST_CASE_TPL ( planerotc4b, NT2_REAL_TYPES)
{
  typedef typename std::complex<T> cT;
  typedef nt2::table<cT> table_t;
  table_t x = nt2::linspace(cT(1, 2), cT(3, 2), 2);
  T c;
  cT s, r;
  nt2::tie(s, c, r) = nt2::planerot(x, nt2::tag::sincos_());
  table_t g = nt2::cons(nt2::of_size(2, 2), cT(c), -conj(s), s, cT(c));
  table_t y = nt2::cons(nt2::of_size(2, 1), r, nt2::Zero<cT>());
  NT2_TEST_ULP_EQUAL(nt2::mtimes(g, colvect(x)), y, 2);
}

NT2_TEST_CASE_TPL ( planerotlimits, NT2_REAL_TYPES)
{
  typedef typename std::complex<T> cT;
  typedef nt2::table<cT> table_t;
  table_t x = nt2::linspace(cT(1, 2), cT(0, 0), 2);
  T c;
  cT s, r;
  nt2::tie(s, c, r) = nt2::planerot(x, nt2::tag::sincos_());
  table_t g = nt2::cons(nt2::of_size(2, 2), cT(c), -conj(s), s, cT(c));
  table_t y = nt2::cons(nt2::of_size(2, 1), r, nt2::Zero<cT>());
  NT2_TEST_ULP_EQUAL(nt2::mtimes(g, colvect(x)), y, 2);
  NT2_DISPLAY(x);
  NT2_DISPLAY(c);
  NT2_DISPLAY(s);
  NT2_DISPLAY(r);
  x = nt2::linspace(cT(0, 0), cT(1, 2), 2);
  nt2::tie(s, c, r) = nt2::planerot(x, nt2::tag::sincos_());
  g = nt2::cons(nt2::of_size(2, 2), cT(c), -conj(s), s, cT(c));
  y = nt2::cons(nt2::of_size(2, 1), r, nt2::Zero<cT>());
  NT2_TEST_ULP_EQUAL(nt2::mtimes(g, colvect(x)), y, 2);
  NT2_DISPLAY(x);
  NT2_DISPLAY(c);
  NT2_DISPLAY(s);
  NT2_DISPLAY(r);
}


NT2_TEST_CASE_TPL ( planerotc1, NT2_REAL_TYPES)
{
  typedef typename std::complex<T> cT;
  typedef nt2::table<cT> table_t;
  table_t x = nt2::linspace(cT(1, 2), cT(3, 1), 2);
  table_t g, y;
  nt2::tie(g, y) = nt2::planerot(nt2::colvect(x));
  NT2_TEST_ULP_EQUAL(mtimes(g,nt2::colvect(x)), y, 2);
  NT2_DISPLAY(colvect(x));
  NT2_DISPLAY(mtimes(g, colvect(x)));
  NT2_DISPLAY(g);


  nt2::tie(g, y) = nt2::planerot(nt2::rowvect(x));
  NT2_TEST_ULP_EQUAL(mtimes(nt2::rowvect(x), g), y, 2);
  NT2_DISPLAY(rowvect(x));
  NT2_DISPLAY(mtimes(rowvect(x), g));
  NT2_DISPLAY(g);
}
