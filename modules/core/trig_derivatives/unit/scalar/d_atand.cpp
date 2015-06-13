//==============================================================================
//         Copyright 2015 J.T. Lapreste
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/trig_derivatives/include/functions/d_atand.hpp>
#include <nt2/include/functions/atand.hpp>
#include <nt2/include/functions/df.hpp>
#include <nt2/include/functions/rec.hpp>
#include <nt2/include/functions/sqrteps.hpp>
#include <nt2/include/functor.hpp>
#include <nt2/sdk/functor/meta/call.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/ulp.hpp>
#include <boost/simd/sdk/config.hpp>

#include <nt2/include/constants/half.hpp>


NT2_TEST_CASE_TPL ( atand,  NT2_REAL_TYPES)
{
  using nt2::d_atand;

  NT2_TEST_ULP_EQUAL(d_atand(nt2::Half<T>()),
                     nt2::df(nt2::functor<nt2::tag::atand_>(),nt2::Half<T>(), nt2::centered_) , nt2::rec(nt2::Sqrteps<T>()));

}
