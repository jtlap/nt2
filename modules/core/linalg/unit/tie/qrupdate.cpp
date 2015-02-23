//==============================================================================
//         Copyright 2015 J.T. Lapreste
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/include/functions/qrupdate.hpp>
#include <nt2/include/functions/qr.hpp>
#include <nt2/include/functions/cons.hpp>
#include <nt2/include/functions/mtimes.hpp>
#include <nt2/include/functions/transpose.hpp>
#include <nt2/include/functions/tril.hpp>
#include <nt2/include/constants/i.hpp>

#include <nt2/table.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/ulp.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/exceptions.hpp>
#include <nt2/core/container/colon/colon.hpp>


NT2_TEST_CASE_TPL(qrupdate, NT2_REAL_TYPES )
{
  using nt2::_;
  using nt2::meta::as_;

  typedef nt2::table<T,nt2::rectangular_>    t_t;

  t_t b = nt2::cons<T>(nt2::of_size(3,3),2,1,1,1,2,2,2,5,7);
  t_t q, r, q1, r1;
  tie(q, r) = nt2::qr(b);
  NT2_DISPLAY(q);
  NT2_DISPLAY(r);
  t_t u =  _(T(1), T(3));
  t_t v =  _(T(-3), T(1), T(-1));
  NT2_DISPLAY(u);
  NT2_DISPLAY(v);
  NT2_DISPLAY(b);
  NT2_DISPLAY(nt2::mtimes(ctrans(u), v));
  NT2_DISPLAY(nt2::mtimes(ctrans(u), v)+b);
  tie(q1, r1) = nt2::qrupdate(q, r, u, v);
  NT2_DISPLAY(q1);
  NT2_DISPLAY(r1);
  NT2_TEST_ULP_EQUAL( b+nt2::mtimes(ctrans(u), v), nt2::mtimes(q1, r1), 16);
}

NT2_TEST_CASE_TPL(qrupdatec, NT2_REAL_TYPES )
{
  using nt2::_;
  using nt2::meta::as_;
  typedef std::complex<T> cT;
  typedef nt2::table<cT,nt2::rectangular_>    t_t;

  t_t b = nt2::cons<T>(nt2::of_size(3,3),2,1,1,1,2,2,2,5,7);
  b =  b+nt2::I<cT>()*b;
  t_t q, r, q1, r1;
  tie(q, r) = nt2::qr(b);
  NT2_DISPLAY(q);
  NT2_DISPLAY(r);
  t_t u =  _(T(1), T(3));
  t_t v =  _(T(-3), T(1), T(-1));
  NT2_DISPLAY(u);
  NT2_DISPLAY(v);
  NT2_DISPLAY(b);
  NT2_DISPLAY(nt2::mtimes(ctrans(u), v));
  NT2_DISPLAY(nt2::mtimes(ctrans(u), v)+b);
  tie(q1, r1) = nt2::qrupdate(q, r, u, v);
  NT2_DISPLAY(q1);
  NT2_DISPLAY(r1);
  NT2_TEST_ULP_EQUAL( b+nt2::mtimes(ctrans(u), v), nt2::mtimes(q1, r1), 16);
}

NT2_TEST_CASE_TPL(qrupdatensq, NT2_REAL_TYPES )
{
  using nt2::_;
  using nt2::meta::as_;
  typedef nt2::table<T,nt2::rectangular_>    t_t;

  t_t b = nt2::reshape(_(T(1), T(12)), 4, 3);
  t_t q, r, q1, r1;
  tie(q, r) = nt2::qr(b, 0);
  NT2_DISPLAY(q);
  NT2_DISPLAY(r);
  t_t v =  _(T(1), T(3));
  t_t u =  _(T(1), T(4));
  NT2_DISPLAY(u);
  NT2_DISPLAY(v);
  NT2_DISPLAY(b);
  NT2_DISPLAY(nt2::mtimes(ctrans(u), v));
  NT2_DISPLAY(nt2::mtimes(ctrans(u), v)+b);
  tie(q1, r1) = nt2::qrupdate(q, r, u, v);
  NT2_DISPLAY(q1);
  NT2_DISPLAY(r1);
  NT2_TEST_ULP_EQUAL( b+nt2::mtimes(ctrans(u), v), nt2::mtimes(q1, r1), 16);
}

NT2_TEST_CASE_TPL(qrupdatecnsq, NT2_REAL_TYPES )
{
  using nt2::_;
  using nt2::meta::as_;
  typedef std::complex<T> cT;
  typedef nt2::table<cT,nt2::rectangular_>    t_t;

  t_t b = nt2::reshape(_(T(1), T(12)), 4, 3);
  b =  b+nt2::I<cT>()*b;
  t_t q, r, q1, r1;
  tie(q, r) = nt2::qr(b, 0);
  NT2_DISPLAY(q);
  NT2_DISPLAY(r);
  t_t v =  _(T(1), T(3));
  t_t u =  _(T(1), T(4));
  NT2_DISPLAY(u);
  NT2_DISPLAY(v);
  NT2_DISPLAY(b);
  NT2_DISPLAY(nt2::mtimes(ctrans(u), v));
  NT2_DISPLAY(nt2::mtimes(ctrans(u), v)+b);
  tie(q1, r1) = nt2::qrupdate(q, r, u, v);
  NT2_DISPLAY(q1);
  NT2_DISPLAY(r1);
  NT2_TEST_ULP_EQUAL( b+nt2::mtimes(ctrans(u), v), nt2::mtimes(q1, r1), 16);
}





