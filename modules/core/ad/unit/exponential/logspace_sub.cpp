//==============================================================================
//         Copyright 2015 J.T. Lapreste
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/ad/exponential/functions/generic/logspace_sub.hpp>
#include <nt2/include/functions/ad.hpp>
#include <nt2/include/functions/ad_io.hpp>
#include <nt2/include/functions/d1_logspace_sub.hpp>
#include <nt2/include/functions/d2_logspace_sub.hpp>

#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <boost/simd/sdk/config.hpp>
#include <nt2/table.hpp>


template < class T>
auto test(const T & x, const T & y) -> decltype(logspace_sub(x, y))
{
  return logspace_sub(x, y);
}

using nt2::ad::valder;

NT2_TEST_CASE_TPL ( logspace_sub,  NT2_REAL_TYPES)
{
  valder<T> vx(2, 1), vy(-0.25, 0);
  valder<T> r1 = test(vx, vy);
  NT2_TEST_EQUAL(r1.der(), nt2::d1_logspace_sub(vx.val(), vy.val()));
  vx = valder<T>(2, 0);
  vy = valder<T>(-0.25, 1);
  valder<T> r2 = test(vx, vy);
  NT2_TEST_EQUAL(r2.der(), nt2::d2_logspace_sub(vx.val(), vy.val()));
}



