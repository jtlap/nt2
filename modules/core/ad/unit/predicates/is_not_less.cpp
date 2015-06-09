//==============================================================================
//         Copyright 2015 J.T. Lapreste
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/include/functions/ad.hpp>
#include <nt2/include/functions/ad_io.hpp>
#include <nt2/include/constants/nan.hpp>

#include <nt2/ad/predicates.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <boost/simd/sdk/config.hpp>
#include <nt2/table.hpp>

template < class T1, class T2>
auto test(const T1 & x, const T2 & y) -> decltype(is_not_less(x, y))
{
  return is_not_less(x, y);
}

using nt2::ad::valder;

NT2_TEST_CASE_TPL ( is_not_less,  NT2_REAL_TYPES)
{
  valder<T> vx(2, 1), vy(2, 1);
  NT2_TEST_EQUAL(test(vx, vy), true);
  vx = valder<T>(2, 1);
  vy = valder<T>(3, 1);
  NT2_TEST_EQUAL(test(vx, vy), false);
}



