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

#include <nt2/ad/ieee.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>
#include <nt2/sdk/unit/tests/ulp.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <boost/simd/sdk/config.hpp>
#include <nt2/table.hpp>


template < class T1, class T2>
auto test(const T1 & x, const T2 & y) -> decltype(ldexp(x,y))
{
  return ldexp(x,y);
}

using nt2::ad::valder;

NT2_TEST_CASE_TPL ( ldexp,  NT2_REAL_TYPES)
{
  int y = 3;
  {
    valder<T> vx(2, 1); //take x derivative
    valder<T> r1 = test(vx, y);
    NT2_TEST_EQUAL(r1.der(), 8);
    NT2_TEST_EQUAL(r1.der(),  test(vx, y).der());
  }
  y = 3;
  {
    valder<T> vx(-2, 1); //take x derivative
    valder<T> r1 = test(vx, y);
    NT2_TEST_EQUAL(r1.der(), 8);
    NT2_TEST_EQUAL(r1.der(),  test(vx, y).der());
  }
}



