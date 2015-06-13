//==============================================================================
//         Copyright 2015 J.T. Lapreste
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/ad/trigonometric/functions/generic/fast_sincospi.hpp>
#include <nt2/include/functions/ad.hpp>
#include <nt2/include/functions/ad_io.hpp>
#include <nt2/include/functions/d_fast_sinpi.hpp>
#include <nt2/include/functions/d_fast_cospi.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <boost/simd/sdk/config.hpp>
#include <nt2/table.hpp>


template < class T>
void test(const T & x, T &s, T& c)
{
   fast_sincospi(x, s, c);
}

using nt2::ad::valder;

NT2_TEST_CASE_TPL ( fast_sincospi,  NT2_REAL_TYPES)
{
  valder<T> vx(0.5, 1);
  valder<T> vs, vc;
  test(vx, vs, vc);
  NT2_TEST_EQUAL(vs.der(), nt2::d_fast_sinpi(vx.val()));
  NT2_TEST_EQUAL(vc.der(), nt2::d_fast_cospi(vx.val()));
}



