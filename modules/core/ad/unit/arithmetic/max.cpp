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

#include <nt2/ad/arithmetic.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>
#include <nt2/sdk/unit/tests/ulp.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <boost/simd/sdk/config.hpp>
#include <nt2/table.hpp>


template < class T1, class T2>
auto test(const T1 & x, const T2 & y) -> decltype(max(x,y))
{
  return max(x,y);
}

using nt2::ad::valder;

NT2_TEST_CASE_TPL ( max,  NT2_REAL_TYPES)
{
  T x = 2,  y = 3;
  {
    valder<T> vx(2, 1), vy(3, 0); //take x derivative
    valder<T> r1 = test(vx, vy);
    NT2_TEST_EQUAL(r1.der(), 0);
    NT2_TEST_EQUAL(r1.der(),  test(vx, y).der());
  }
   {
    valder<T> vx(2, 0), vy(3, 1); //take x derivative
    valder<T> r1 = test(vx, vy);
    NT2_TEST_EQUAL(r1.der(), 1);
    NT2_TEST_EQUAL(r1.der(),  test(x, vy).der());
  }
}



