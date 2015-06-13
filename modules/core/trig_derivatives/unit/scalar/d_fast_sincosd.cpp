//==============================================================================
//         Copyright 2015 J.T. Lapreste
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/trig_derivatives/include/functions/d_fast_sincosd.hpp>
#include <nt2/include/functions/fast_sincosd.hpp>
#include <nt2/include/functions/d_sind.hpp>
#include <nt2/include/functions/d_cosd.hpp>
#include <nt2/include/functions/df.hpp>
#include <nt2/include/functions/rec.hpp>
#include <nt2/include/functions/sqrteps.hpp>
#include <nt2/include/functor.hpp>
#include <nt2/sdk/functor/meta/call.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/ulp.hpp>
#include <boost/simd/sdk/config.hpp>


NT2_TEST_CASE_TPL ( sincos,  NT2_REAL_TYPES)
{
  using nt2::d_fast_sincosd;
  T x = T(30);
  T dc, ds;
  d_fast_sincosd(x, ds, dc);
  NT2_TEST_ULP_EQUAL(dc, nt2::d_cosd(x), 0.5);
  NT2_TEST_ULP_EQUAL(ds, nt2::d_sind(x), 0.5);
}

