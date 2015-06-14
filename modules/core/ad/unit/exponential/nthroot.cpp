//==============================================================================
//         Copyright 2015 J.T. Lapreste
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/ad/exponential/functions/generic/nthroot.hpp>
#include <nt2/include/functions/ad.hpp>
#include <nt2/include/functions/ad_io.hpp>
#include <nt2/include/functions/d_nthroot.hpp>

#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <boost/simd/sdk/config.hpp>
#include <nt2/table.hpp>


template < class T, class N>
auto test(const T & x, const N & n) -> decltype(nthroot(x, n))
{
  return nthroot(x, n);
}

using nt2::ad::valder;

NT2_TEST_CASE_TPL ( nthroot,  NT2_REAL_TYPES)
{
  valder<T> vx(0.5, 1), vy(-0.25, 1);
  size_t n = 3;
  valder<T> r1 = test(vx, n);
  NT2_TEST_EQUAL(r1.der(), nt2::d_nthroot(vx.val(), n));
  valder<T> r2 = test(vy, n);
  NT2_TEST_EQUAL(r2.der(), nt2::d_nthroot(vy.val(), n));
}



