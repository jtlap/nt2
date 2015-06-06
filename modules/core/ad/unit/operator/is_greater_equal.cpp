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

#include <nt2/ad/operator.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>
#include <nt2/sdk/unit/tests/basic.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <boost/simd/sdk/config.hpp>
#include <nt2/table.hpp>


using nt2::ad::valder;

NT2_TEST_CASE_TPL ( is_greater_equal,  NT2_REAL_TYPES)
{
  T x = 2, y = 3;
  valder<T> vx(2, 1), vy(3, 0);
  NT2_TEST(!is_greater_equal(vx, vy));
  NT2_TEST(!is_greater_equal(x, vy));
  NT2_TEST(is_greater_equal(vx, x));
  NT2_TEST(is_greater_equal(vx, vx));
  NT2_TEST(is_greater_equal(vy, vx));
  NT2_TEST(is_greater_equal(vy, x));
}



