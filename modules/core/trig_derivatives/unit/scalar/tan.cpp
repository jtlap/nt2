//==============================================================================
//         Copyright 2015 J.T. Lapreste
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/trigonometric/include/functions/tan.hpp>
#include <nt2/trig_derivatives/include/functions/tan.hpp>
#include <nt2/include/functions/tan.hpp>
#include <nt2/include/functor.hpp>
#include <nt2/sdk/functor/meta/call.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/ulp.hpp>
#include <boost/simd/sdk/config.hpp>

#include <nt2/include/constants/pio_6.hpp>


NT2_TEST_CASE_TPL ( tan,  NT2_REAL_TYPES)
{
  using nt2::tan;

  NT2_TEST_ULP_EQUAL(tan<1>(nt2::Pio_6<T>()),
                     1.333333333333333, 1.5);
  NT2_TEST_ULP_EQUAL(tan<2>(nt2::Pio_6<T>()),
                     1.539600717839002, 1.5);
  NT2_TEST_ULP_EQUAL(tan<3>(nt2::Pio_6<T>()),
                     5.333333333333333, 1.5);

}


