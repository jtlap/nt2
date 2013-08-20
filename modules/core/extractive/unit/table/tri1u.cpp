//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/table.hpp>
#include <nt2/include/functions/tri1u.hpp>
#include <nt2/include/functions/is_greater_equal.hpp>
#include <nt2/include/functions/is_less_equal.hpp>
#include <nt2/include/functions/is_not_equal.hpp>
#include <nt2/include/functions/whereij.hpp>
#include <nt2/include/functions/reshape.hpp>
#include <nt2/include/functions/oneplus.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>

NT2_TEST_CASE_TPL( tri1u_scalar, NT2_TYPES )
{
  T x = nt2::tri1u(T(42));
  NT2_TEST_EQUAL( x, T(1) );
  x = nt2::tri1u(T(42),1);
  NT2_TEST_EQUAL( x, T(0) );
   x = nt2::tri1u(T(42),0);
  NT2_TEST_EQUAL( x, T(1) );
  x = nt2::tri1u(T(42),-1);
  NT2_TEST_EQUAL( x, T(42) );
}

NT2_TEST_CASE_TPL( tri1u_scalar_table, NT2_TYPES )
{
  nt2::table<T> tx,ty( nt2::of_size(1, 1) );
  ty(1) = T(42);
  tx = nt2::tri1u(ty);
  NT2_TEST_EQUAL( tx(1), T(1) );

  tx = nt2::tri1u(ty, 1);
  NT2_TEST_EQUAL( tx(1), T(0) );

  tx = nt2::tri1u(ty, 0);
  NT2_TEST_EQUAL( tx(1), T(1) );

  tx = nt2::tri1u(ty, -1);
  NT2_TEST_EQUAL( tx(1), T(42) );
}

NT2_TEST_CASE_TPL( tri1u, NT2_TYPES )
{
  nt2::table<T> xx, x, y = nt2::reshape(nt2::_(T(1), T(20)), 4, 5);
  x = nt2::tri1u(y);
  xx = nt2::whereij(nt2::functor<nt2::tag::is_not_equal_>(),
                    nt2::whereij(nt2::functor<nt2::tag::is_less_equal_>(),
                                 y, T(0)),
                    T(1));
  NT2_TEST_EQUAL(x, xx);
}

struct fct1
{
  template < class A0, class A1>
  typename nt2::meta::as_logical<A0>::type
  operator ()(const A0& i, const A1& j) const
  {
    return nt2::le(nt2::oneplus(i), j);
  }
};

struct fct2
{
  template < class A0, class A1>
  typename nt2::meta::as_logical<A0>::type
  operator ()(const A0& i, const A1& j) const
  {
    return nt2::le(i, nt2::oneplus(j));
  }
};

struct fct01
{
  template < class A0, class A1>
  typename nt2::meta::as_logical<A0>::type
  operator ()(const A0& i, const A1& j) const
  {
    return nt2::ne(j, nt2::oneplus(i));
  }
};

struct fct02
{
  template < class A0, class A1>
  typename nt2::meta::as_logical<A0>::type
  operator ()(const A0& i, const A1& j) const
  {
    return nt2::ne(nt2::oneplus(j), i);
  }
};

NT2_TEST_CASE_TPL( offset_tri1u, NT2_TYPES )
{
  nt2::table<T> xx, x, y = nt2::reshape(nt2::_(T(1), T(20)), 4, 5);
  x = nt2::tri1u(y, 1);
  xx = nt2::whereij(fct01(),
                    nt2::whereij(fct1(),
                                 y, T(0)),
                    T(1));
  NT2_TEST_EQUAL(x, xx);

  x = nt2::tri1u(y, -1);
  xx = nt2::whereij(fct02(),
                    nt2::whereij(fct2(),
                                 y, T(0)),
                    T(1));
  NT2_TEST_EQUAL(x, xx);
}
