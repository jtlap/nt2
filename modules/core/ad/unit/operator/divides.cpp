//==============================================================================
//         Copyright 2015 J.T. Lapreste
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/include/functions/ad.hpp>
#include <nt2/include/functions/ad_io.hpp>
#include <nt2/include/functions/sqr.hpp>
#include <nt2/include/functions/rec.hpp>

#include <nt2/ad/operator.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>
#include <nt2/sdk/unit/tests/ulp.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <boost/simd/sdk/config.hpp>
#include <nt2/table.hpp>
#include <nt2/include/functions/if_else.hpp>


template < class T1, class T2>
auto test(const T1 & x, const T2 & y) -> decltype(x/y)
{
  return x/y;
}

using nt2::ad::valder;
using nt2::rec;
using nt2::sqr;

NT2_TEST_CASE_TPL ( divides,  NT2_REAL_TYPES)
{
  T x = 2, y = 3;
  {
    valder<T> vx(2, 1), vy(3, 0); //take x derivative
    valder<T> r1 = test(vx, vy);
    valder<T> r2 = test(vx,  y);
    valder<T> r3 = test( x, vy);
    NT2_TEST_EQUAL(r1.der(), rec(y));
    NT2_TEST_EQUAL(r2.der(), rec(y));
    NT2_TEST_EQUAL(r3.der(), 0);
  }
  {
    valder<T> vy(3, 1), vx(2, 0); //take y derivative
    valder<T> r1 = test(vx, vy);
    valder<T> r2 = test(vx,  y);
    valder<T> r3 = test( x, vy);
    NT2_TEST_EQUAL(r1.der(), -x*rec(sqr(y)));
    NT2_TEST_EQUAL(r2.der(), 0);
    NT2_TEST_EQUAL(r3.der(), -x*rec(sqr(y)));
  }

}



