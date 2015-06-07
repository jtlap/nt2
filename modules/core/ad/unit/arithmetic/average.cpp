//==============================================================================
//         Copyright 2015 J.T. Lapreste
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/include/functions/ad.hpp>
#include <nt2/include/functions/ad_io.hpp>
#include <nt2/include/constants/half.hpp>

#include <nt2/ad/arithmetic.hpp>

#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <boost/simd/sdk/config.hpp>

template < class T1, class T2>
auto test(const T1 & x, const T2 & y) -> decltype(average(x, y))
{
  return average(x, y);
}

using nt2::ad::valder;

NT2_TEST_CASE_TPL ( average,  NT2_REAL_TYPES)
{
  T x = 1, y = 2;
  {
    valder<T> vx(1, 1), vy(2, 0); //take x derivative
    valder<T> r1 = test(vx, vy);
    NT2_TEST_EQUAL(r1.der(), nt2::Half<T>());
    NT2_TEST_EQUAL(r1.der(), test(vx, y).der());
  }
   {
    valder<T> vx(1, 0), vy(2, 1); //take y derivative
    valder<T> r1 = test(vx, vy);
    NT2_TEST_EQUAL(r1.der(), nt2::Half<T>());
    NT2_TEST_EQUAL(r1.der(), test(x, vy).der());
  }

}



