//==============================================================================
//         Copyright 2015 J.T. Lapreste
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/include/functions/qrshift.hpp>
#include <nt2/include/functions/qr.hpp>
#include <nt2/include/functions/cons.hpp>
#include <nt2/include/functions/conj.hpp>
#include <nt2/include/functions/mtimes.hpp>
#include <nt2/include/functions/transpose.hpp>
#include <nt2/include/functions/horzcat.hpp>
#include <nt2/include/functions/tril.hpp>
#include <nt2/include/constants/i.hpp>

#include <nt2/table.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/ulp.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/exceptions.hpp>
#include <nt2/core/container/colon/colon.hpp>


NT2_TEST_CASE_TPL(qrshift1, NT2_REAL_TYPES )
{
  using nt2::_;
  using nt2::meta::as_;

  typedef nt2::table<T,nt2::rectangular_>    t_t;

  t_t b = nt2::cons<T>(nt2::of_size(5, 5),2,1,1,1,2,2,2,5,7,2,1,1,2,2,5,7,2,1,2,5,7,2,1,5,7);
  t_t q, r, q1, r1;
  tie(q, r) = nt2::qr(b);
  NT2_DISPLAY(q);
  NT2_DISPLAY(r);
  nt2_la_int i = 2;
  nt2_la_int j = 4;
  NT2_DISPLAY(i);
  NT2_DISPLAY(j);
  NT2_DISPLAY(b);
  NT2_DISPLAY(mtimes(q, r));
  tie(q1, r1) = nt2::qrshift(q, r, i, j);
  NT2_DISPLAY(q1);
  NT2_DISPLAY(r1);
  t_t sb = horzcat(horzcat(horzcat(b(_, _(1, i-1)), b(_, _(i+1, j))), b(_, i)), b(_, _(j+1, nt2::end_)));
  NT2_TEST_ULP_EQUAL(sb, nt2::mtimes(q1, r1), 16);
  NT2_DISPLAY(mtimes(q1, r1));
  NT2_DISPLAY(sb);
}

NT2_TEST_CASE_TPL(qrshift2, NT2_REAL_TYPES )
{
  using nt2::_;
  using nt2::meta::as_;

  typedef nt2::table<T,nt2::rectangular_>    t_t;

  t_t b = nt2::cons<T>(nt2::of_size(5, 5),2,1,1,1,2,2,2,5,7,2,1,1,2,2,5,7,2,1,2,5,7,2,1,5,7);
  t_t q, r, q1, r1;
  tie(q, r) = nt2::qr(b);
  NT2_DISPLAY(q);
  NT2_DISPLAY(r);
  nt2_la_int i = 4;
  nt2_la_int j = 2;
  NT2_DISPLAY(i);
  NT2_DISPLAY(j);
  NT2_DISPLAY(b);
  NT2_DISPLAY(mtimes(q, r));
  tie(q1, r1) = nt2::qrshift(q, r, i, j);
  NT2_DISPLAY(q1);
  NT2_DISPLAY(r1);
  t_t sb = horzcat(horzcat(horzcat(b(_, _(1, j-1)), b(_, i)), b(_, _(j, i-1))), b(_, _(i+1, nt2::end_)));
  NT2_TEST_ULP_EQUAL(sb, nt2::mtimes(q1, r1), 16);
  NT2_DISPLAY(mtimes(q1, r1));
  NT2_DISPLAY(sb);
}
NT2_TEST_CASE_TPL(qrshift1c, NT2_REAL_TYPES )
{
  using nt2::_;
  using nt2::meta::as_;
  typedef typename std::complex<T> cT;

  typedef nt2::table<cT,nt2::rectangular_>    t_t;

  t_t b = nt2::cons<T>(nt2::of_size(5, 5),2,1,1,1,2,2,2,5,7,2,1,1,2,2,5,7,2,1,2,5,7,2,1,5,7);
  b =  b+T(2)*nt2::I<cT>()*nt2::conj(b);
  t_t q, r, q1, r1;
  tie(q, r) = nt2::qr(b);
  NT2_DISPLAY(q);
  NT2_DISPLAY(r);
  nt2_la_int i = 2;
  nt2_la_int j = 4;
  NT2_DISPLAY(i);
  NT2_DISPLAY(j);
  NT2_DISPLAY(b);
  NT2_DISPLAY(mtimes(q, r));
  tie(q1, r1) = nt2::qrshift(q, r, i, j);
  NT2_DISPLAY(q1);
  NT2_DISPLAY(r1);
  t_t sb = horzcat(horzcat(horzcat(b(_, _(1, i-1)), b(_, _(i+1, j))), b(_, i)), b(_, _(j+1, nt2::end_)));
  NT2_TEST_ULP_EQUAL(sb, nt2::mtimes(q1, r1), 16);
  NT2_DISPLAY(mtimes(q1, r1));
  NT2_DISPLAY(sb);
}

NT2_TEST_CASE_TPL(qrshift2c, NT2_REAL_TYPES )
{
  using nt2::_;
  using nt2::meta::as_;
  typedef typename std::complex<T> cT;
  typedef nt2::table<cT,nt2::rectangular_>    t_t;

  t_t b = nt2::cons<T>(nt2::of_size(5, 5),2,1,1,1,2,2,2,5,7,2,1,1,2,2,5,7,2,1,2,5,7,2,1,5,7);
  b =  b+T(2)*nt2::I<cT>()*nt2::conj(b);
  t_t q, r, q1, r1;
  tie(q, r) = nt2::qr(b);
  NT2_DISPLAY(q);
  NT2_DISPLAY(r);
  nt2_la_int i = 4;
  nt2_la_int j = 2;
  NT2_DISPLAY(i);
  NT2_DISPLAY(j);
  NT2_DISPLAY(b);
  NT2_DISPLAY(mtimes(q, r));
  tie(q1, r1) = nt2::qrshift(q, r, i, j);
  NT2_DISPLAY(q1);
  NT2_DISPLAY(r1);
  t_t sb = horzcat(horzcat(horzcat(b(_, _(1, j-1)), b(_, i)), b(_, _(j, i-1))), b(_, _(i+1, nt2::end_)));
  NT2_TEST_ULP_EQUAL(sb, nt2::mtimes(q1, r1), 16);
  NT2_DISPLAY(mtimes(q1, r1));
  NT2_DISPLAY(sb);
}
