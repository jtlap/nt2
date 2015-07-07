//==============================================================================
//         Copyright 2015 J.T. Lapreste
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/trigonometric/include/functions/fast_cos.hpp>
#include <nt2/trig_derivatives/include/functions/fast_cos.hpp>
#include <nt2/include/functions/fast_cos.hpp>
#include <nt2/include/functor.hpp>
#include <nt2/sdk/functor/meta/call.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/ulp.hpp>
#include <boost/simd/sdk/config.hpp>

#include <nt2/include/constants/pio_6.hpp>


NT2_TEST_CASE_TPL ( fast_cos,  NT2_REAL_TYPES)
{
  using nt2::fast_cos;

  NT2_TEST_ULP_EQUAL(fast_cos<1>(nt2::Pio_6<T>()),
                     -sin(nt2::Pio_6<T>()), 1.5);
  NT2_TEST_ULP_EQUAL(fast_cos<2>(nt2::Pio_6<T>()),
                     -fast_cos(nt2::Pio_6<T>()), 1.5);
  NT2_TEST_ULP_EQUAL(fast_cos<3>(nt2::Pio_6<T>()),
                     sin(nt2::Pio_6<T>()), 1.5);

}

