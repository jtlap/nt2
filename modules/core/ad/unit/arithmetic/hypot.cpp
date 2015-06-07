//==============================================================================
//         Copyright 2015 J.T. Lapreste
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/include/functions/ad.hpp>
#include <nt2/include/functions/ad_io.hpp>

#include <nt2/ad/arithmetic.hpp>

#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/ulp.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <boost/simd/sdk/config.hpp>
#include <nt2/table.hpp>


template < class T1, class T2>
auto test(const T1 & x, const T2 & y) -> decltype(hypot(x, y))
{
  return hypot(x, y);
}

using nt2::ad::valder;

NT2_TEST_CASE_TPL ( hypot,  NT2_REAL_TYPES)
{
  T x = 3, y = 4;
  {
    valder<T> vx(3, 1), vy(4, 0); //take x derivative
    valder<T> r1 = test(vx, vy);
    NT2_TEST_ULP_EQUAL(r1.der(), T(3)/T(5), 0.5);
    NT2_TEST_EQUAL(r1.der(), test(vx, y).der());
  }
  {
    valder<T> vx(3, 0), vy(4, 1); //take y derivative
    valder<T> r1 = test(vx, vy);
    NT2_TEST_ULP_EQUAL(r1.der(), T(4)/T(5), 0.5);
    NT2_TEST_EQUAL(r1.der(), test(x, vy).der());
  }
}


