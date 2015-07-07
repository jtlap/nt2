//==============================================================================
//         Copyright 2015 J.T. Lapreste
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/trigonometric/include/functions/sec.hpp>
#include <nt2/trig_derivatives/include/functions/sec.hpp>
#include <nt2/include/functions/sec.hpp>
#include <nt2/include/functor.hpp>
#include <nt2/sdk/functor/meta/call.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/ulp.hpp>
#include <boost/simd/sdk/config.hpp>

#include <nt2/include/constants/pio_3.hpp>


NT2_TEST_CASE_TPL ( sec,  NT2_REAL_TYPES)
{
  using nt2::sec;

  NT2_TEST_ULP_EQUAL(sec<1>(nt2::Pio_3<T>()),
                     3.464101615137754, 2.5);
  NT2_TEST_ULP_EQUAL(sec<2>(nt2::Pio_3<T>()),
                     14, 2.5);
  NT2_TEST_ULP_EQUAL(sec<3>(nt2::Pio_3<T>()),
                     79.674337148168362, 2.5);

}


