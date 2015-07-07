//==============================================================================
//         Copyright 2015 J.T. Lapreste
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/trigonometric/include/functions/csc.hpp>
#include <nt2/trig_derivatives/include/functions/csc.hpp>
#include <nt2/include/functions/csc.hpp>
#include <nt2/include/functor.hpp>
#include <nt2/sdk/functor/meta/call.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/ulp.hpp>
#include <boost/simd/sdk/config.hpp>

#include <nt2/include/constants/pio_3.hpp>


NT2_TEST_CASE_TPL ( csc,  NT2_REAL_TYPES)
{
  using nt2::csc;

  NT2_TEST_ULP_EQUAL(csc<1>(nt2::Pio_3<T>()),
                     -0.666666666666667, 2.5);
  NT2_TEST_ULP_EQUAL(csc<2>(nt2::Pio_3<T>()),
                     1.924500897298753, 2.5);
  NT2_TEST_ULP_EQUAL(csc<3>(nt2::Pio_3<T>()),
                     -4.666666666666667, 2.5);
  NT2_TEST_ULP_EQUAL(csc<4>(nt2::Pio_3<T>()),
                     19.629909152447276, 2.5);

}


