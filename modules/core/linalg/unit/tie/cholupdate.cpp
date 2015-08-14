//==============================================================================
//         Copyright 2015 J.T. Lapreste
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/include/functions/cholupdate.hpp>
#include <nt2/include/functions/chol.hpp>
#include <nt2/include/functions/cons.hpp>
#include <nt2/include/functions/mtimes.hpp>
#include <nt2/include/functions/transpose.hpp>
#include <nt2/include/functions/tril.hpp>

#include <nt2/table.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/ulp.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/exceptions.hpp>
#include <nt2/core/container/colon/colon.hpp>

NT2_TEST_CASE_TPL(cholupdate, NT2_REAL_TYPES )
{
  using nt2::_;
  using nt2::meta::as_;

  typedef nt2::table<T,nt2::rectangular_>    t_t;

  t_t a = nt2::tril(nt2::cons<T>(nt2::of_size(3,3),2,1,1,1,2,2,2,5,7));
  t_t b = nt2::mtimes(nt2::trans(a), a);
  t_t l = nt2::chol(b);
  t_t x =  _(T(1), T(3));
  t_t l1 =  nt2::cholupdate(l, x);
  NT2_TEST_ULP_EQUAL( nt2::mtimes(nt2::trans(l1), l1), b+nt2::mtimes(nt2::trans(x), x), 10);
  t_t l2 = nt2::cholupdate(l, x, nt2::tag::plus_());
  NT2_TEST_ULP_EQUAL( l1, l2, 10);
}


NT2_TEST_CASE_TPL(choldowndate, NT2_REAL_TYPES )
{
  using nt2::_;
  using nt2::meta::as_;

  typedef nt2::table<T,nt2::rectangular_>    t_t;

  t_t a = nt2::tril(nt2::cons<T>(nt2::of_size(3,3),2,1,1,1,2,2,2,5,7));
  t_t b = nt2::mtimes(nt2::trans(a), a);
  t_t l = nt2::chol(b);
  t_t x =  _(T(1), T(3));
  t_t l2 =  nt2::cholupdate(l, x, nt2::tag::minus_());
  NT2_TEST_ULP_EQUAL( nt2::mtimes(nt2::trans(l2), l2), b-nt2::mtimes(nt2::trans(x), x), 10);
}


NT2_TEST_CASE_TPL(cholupdateassert, NT2_REAL_TYPES )
{
  using nt2::_;
  using nt2::meta::as_;

  typedef nt2::table<T,nt2::rectangular_>    t_t;

  t_t a = nt2::tril(nt2::cons<T>(nt2::of_size(3,3),2,1,1,1,2,2,2,5,7));
  t_t b = nt2::mtimes(nt2::trans(a), a);
  t_t l = nt2::chol(b);
  t_t x =  _(T(1), T(3));
  l(2, 2) = T(-1);
  t_t l2;
  NT2_TEST_ASSERT( (l2=nt2::cholupdate(l, x, nt2::tag::minus_())));
  l(2, 2) = T(2);
  x *=  T(10);
  NT2_TEST_ASSERT( (l2=nt2::cholupdate(l, x, nt2::tag::minus_())));

}

NT2_TEST_CASE_TPL(CholupdateTest, NT2_REAL_TYPES )
{
  nt2::table<T> r = nt2::transpose(nt2::cons<T>(nt2::of_size(3,3), -45.7508,     -76.8637, -108.031,
                                                                     0.,           3.92567, 5.52437,
                                                                     0.,          0.,       -2.8367));
  nt2::table<T> v =  nt2::_(T(3), T(5));
  nt2::table<T> s;
  std::size_t p;
  nt2::tie(s,p) = nt2::cholupdate(r, v, nt2::tag::minus_());
  NT2_TEST_EQUAL(p, 2u);
  NT2_DISPLAY(s);
  NT2_TEST_ASSERT( (s=nt2::cholupdate(r, v, nt2::tag::minus_())));
}
