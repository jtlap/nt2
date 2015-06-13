//==============================================================================
//         Copyright 2015 J.T. Lapreste
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/ad/trigonometric/functions/generic/cosine.hpp>
#include <nt2/include/functions/ad.hpp>
#include <nt2/include/functions/ad_io.hpp>
#include <nt2/include/functions/d_cosine.hpp>

#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <boost/simd/sdk/config.hpp>
#include <nt2/table.hpp>

using nt2::medium_;
using nt2::cosine;

template < class T>
auto test(const T & x) -> decltype(cosine<medium_>(x))
{
  return cosine<medium_>(x);
}

using nt2::ad::valder;

NT2_TEST_CASE_TPL ( cosine,  NT2_REAL_TYPES)
{
  valder<T> vx(0.5, 1), vy(-0.25, 1);
  valder<T> r1 = test(vx);
  NT2_TEST_EQUAL(r1.der(), nt2::d_cosine<nt2::medium_>(vx.val()));
  valder<T> r2 = test(vy);
  NT2_TEST_EQUAL(r2.der(), nt2::d_cosine<nt2::medium_>(vy.val()));
}



