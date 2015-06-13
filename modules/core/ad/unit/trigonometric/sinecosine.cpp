//==============================================================================
//         Copyright 2015 J.T. Lapreste
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/ad/trigonometric/functions/generic/sinecosine.hpp>
#include <nt2/include/functions/ad.hpp>
#include <nt2/include/functions/ad_io.hpp>
#include <nt2/include/functions/d_sine.hpp>
#include <nt2/include/functions/d_cosine.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <boost/simd/sdk/config.hpp>
#include <nt2/table.hpp>

using nt2::medium_;
using nt2::sinecosine;

template < class T>
void test(const T & x, T &s, T& c)
{
   sinecosine<medium_>(x, s, c);
}

using nt2::ad::valder;

NT2_TEST_CASE_TPL ( sincos,  NT2_REAL_TYPES)
{
  valder<T> vx(0.5, 1);
  valder<T> vs, vc;
  test(vx, vs, vc);
  NT2_TEST_EQUAL(vs.der(), nt2::d_sine<medium_>(vx.val()));
  NT2_TEST_EQUAL(vc.der(), nt2::d_cosine<medium_>(vx.val()));
}
