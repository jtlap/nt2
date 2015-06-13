//==============================================================================
//         Copyright 2015 J.T. Lapreste
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/trig_derivatives/include/functions/d_cotd.hpp>
#include <nt2/include/functions/cotd.hpp>
#include <nt2/include/functions/cot.hpp>
#include <nt2/include/functions/df.hpp>
#include <nt2/include/functions/rec.hpp>
#include <nt2/include/functions/sqrteps.hpp>
#include <nt2/include/functor.hpp>
#include <nt2/sdk/functor/meta/call.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/ulp.hpp>
#include <boost/simd/sdk/config.hpp>

#include <nt2/include/constants/pi.hpp>


NT2_TEST_CASE_TPL ( cotd,  NT2_REAL_TYPES)
{
  using nt2::d_cotd;
  NT2_TEST_ULP_EQUAL(nt2::cotd(T(45)),nt2::cot(nt2::Pi<T>()/T(4)), 0.5);
  NT2_TEST_ULP_EQUAL(d_cotd(T(45)),
                     nt2::df(nt2::functor<nt2::tag::cotd_>(),T(45), nt2::centered_) , nt2::rec(nt2::Sqrteps<T>()));

}
