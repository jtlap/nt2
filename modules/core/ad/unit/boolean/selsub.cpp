//==============================================================================
//         Copyright 2015 J.T. Lapreste
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/include/functions/ad.hpp>
#include <nt2/include/functions/ad_io.hpp>
#include <nt2/include/functions/eye.hpp>
#include <nt2/include/functions/cons.hpp>
#include <nt2/include/functions/cat.hpp>

#include <nt2/ad/boolean.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>
#include <nt2/sdk/unit/tests/ulp.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <boost/simd/sdk/config.hpp>
#include <nt2/table.hpp>


template <class L, class T1, class T2>
auto test(const L & l, const T1 & x, const T2 & y) -> decltype(selsub(l, x, y))
{
  return selsub(l, x, y);
}

using nt2::ad::valder;

NT2_TEST_CASE_TPL ( selsub,  NT2_REAL_TYPES)
{
  T x = 2, y = 3;
  {
    bool l = false;
    valder<T> vx(2, 1), vy(3, 2);
    valder<T> r1 = test(l, vx, vy);
    valder<T> r2 = test(l, vx,  y);
    valder<T> r3 = test(l, x, vy);
    NT2_TEST_EQUAL(r1.der(), vx.der());
    NT2_TEST_EQUAL(r2.der(), vx.der());
    NT2_TEST_EQUAL(r3.der(), 0);
  }
  {
    bool l = true;
    valder<T> vy(3, 2), vx(2, 1);
    valder<T> r1 = test(l, vx, vy);
    valder<T> r2 = test(l, vx,  y);
    valder<T> r3 = test(l,  x, vy);
    NT2_TEST_EQUAL(r1.der(), vx.der()-vy.der());
    NT2_TEST_EQUAL(r2.der(), vx.der());
    NT2_TEST_EQUAL(r3.der(), -vy.der());
  }
  {
    valder<T> l(T(0));
    valder<T> vx(2, 1), vy(3, 2);
    valder<T> r1 = test(l, vx, vy);
    valder<T> r2 = test(l, vx,  y);
    valder<T> r3 = test(l, x, vy);
    NT2_TEST_EQUAL(r1.der(), vx.der());
    NT2_TEST_EQUAL(r2.der(), vx.der());
    NT2_TEST_EQUAL(r3.der(), 0);
  }
  {
    valder<T> l(T(1));
    valder<T> vy(3, 2), vx(2, 1);
    valder<T> r1 = test(l, vx, vy);
    valder<T> r2 = test(l, vx,  y);
    valder<T> r3 = test(l,  x, vy);
    NT2_TEST_EQUAL(r1.der(), vx.der()-vy.der());
    NT2_TEST_EQUAL(r2.der(), vx.der());
    NT2_TEST_EQUAL(r3.der(), -vy.der());
  }
}



