//==============================================================================
//         Copyright 2015 J.T. Lapreste
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/exp_derivatives/include/functions/log.hpp>
#include <nt2/include/functions/log.hpp>
#include <nt2/include/functions/sqr.hpp>
#include <nt2/include/functions/sqrteps.hpp>
#include <nt2/include/functor.hpp>
#include <nt2/sdk/functor/meta/call.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/ulp.hpp>
#include <boost/simd/sdk/config.hpp>
#include <nt2/include/functor.hpp>
#include <nt2/table.hpp>


#include <nt2/include/constants/half.hpp>
#include <nt2/include/constants/two.hpp>
#include <nt2/include/constants/four.hpp>

NT2_TEST_CASE_TPL ( log,  NT2_REAL_TYPES)
{
  NT2_TEST_ULP_EQUAL(nt2::log(nt2::Half<T>()),
                     nt2::log<0>(nt2::Half<T>())
                    , 0.5);
  NT2_TEST_ULP_EQUAL(nt2::Two<T>(),
                     nt2::log<1>(nt2::Half<T>())
                    , 0.5);
  NT2_TEST_ULP_EQUAL(-nt2::Four<T>(),
                     nt2::log<2>(nt2::Half<T>())
                    , 0.5);


}


