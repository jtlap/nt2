//==============================================================================
//         Copyright 2015 J.T. Lapreste
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/trigonometric/include/functions/atan2.hpp>
#include <nt2/trig_derivatives/include/functions/atan2.hpp>
#include <nt2/include/functions/atan2.hpp>
#include <nt2/include/functions/log.hpp>
#include <nt2/include/functor.hpp>
#include <nt2/sdk/functor/meta/call.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/ulp.hpp>
#include <boost/simd/sdk/config.hpp>

#include <nt2/include/constants/half.hpp>
#include <nt2/include/constants/mhalf.hpp>


NT2_TEST_CASE_TPL ( atan2,  NT2_REAL_TYPES)
{
  using nt2::atan2;

  NT2_TEST_ULP_EQUAL((nt2::atan2<0, 1>(nt2::One<T>(), nt2::Half<T>()))
                    , T(0.8)
                    ,0.5);
  NT2_TEST_ULP_EQUAL((nt2::atan2<1, 0>(nt2::One<T>(), nt2::Half<T>()))
                    , T(-0.4)
                    ,0.5);
  NT2_TEST_ULP_EQUAL((nt2::atan2<1, 1>(nt2::One<T>(), nt2::Half<T>()))
                    , T(-0.48)
                    ,0.5);
  NT2_TEST_ULP_EQUAL((nt2::atan2<0, 2>(nt2::One<T>(), nt2::Half<T>()))
                    , T(-0.64)
                    ,0.5);
  NT2_TEST_ULP_EQUAL((nt2::atan2<2, 0>(nt2::One<T>(), nt2::Half<T>()))
                    , T(0.64)
                    ,0.5);


}
