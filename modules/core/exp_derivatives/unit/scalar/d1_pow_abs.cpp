//==============================================================================
//         Copyright 2015 J.T. Lapreste
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/exp_derivatives/include/functions/d1_pow_abs.hpp>
#include <nt2/include/functions/pow_abs.hpp>
#include <nt2/include/functions/df.hpp>
#include <nt2/include/functions/rec.hpp>
#include <nt2/include/functions/sqrteps.hpp>
#include <nt2/include/functor.hpp>
#include <nt2/sdk/functor/meta/call.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/ulp.hpp>
#include <boost/simd/sdk/config.hpp>

#include <nt2/include/constants/half.hpp>


NT2_TEST_CASE_TPL ( pow_abs,  NT2_REAL_TYPES)
{
  using nt2::d1_pow_abs;
  T y =  2;
  auto test =  [y](const T & x){return nt2::pow_abs(x, y);};

  NT2_TEST_ULP_EQUAL(d1_pow_abs(nt2::Half<T>(), y),
                     nt2::df(test,nt2::Half<T>()
                            , nt2::centered_
                            )
                    , nt2::rec(nt2::Sqrteps<T>()));

}
