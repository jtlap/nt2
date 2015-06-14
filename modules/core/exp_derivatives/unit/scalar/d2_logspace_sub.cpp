//==============================================================================
//         Copyright 2015 J.T. Lapreste
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/exp_derivatives/include/functions/d2_logspace_sub.hpp>
#include <nt2/include/functions/logspace_sub.hpp>
#include <nt2/include/functions/df.hpp>
#include <nt2/include/functions/rec.hpp>
#include <nt2/include/functions/sqrteps.hpp>
#include <nt2/include/functor.hpp>
#include <nt2/sdk/functor/meta/call.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/ulp.hpp>
#include <boost/simd/sdk/config.hpp>


NT2_TEST_CASE_TPL ( logspace_sub,  NT2_REAL_TYPES)
{
  using nt2::d2_logspace_sub;
  T x =  T(2);
  auto test =  [x](const T & y){return nt2::logspace_sub(x, y);};

  NT2_TEST_ULP_EQUAL(d2_logspace_sub(x, T(0.5)),
                     nt2::df(test,T(0.5)
                            , nt2::centered_
                            )
                    , 10*nt2::rec(nt2::Sqrteps<T>()));

}
