//==============================================================================
//         Copyright 2015 J.T. Lapreste
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/trigonometric/include/functions/sinc.hpp>
#include <nt2/trig_derivatives/include/functions/sinc.hpp>
#include <nt2/include/functions/sinc.hpp>
#include <nt2/include/functor.hpp>
#include <nt2/sdk/functor/meta/call.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/ulp.hpp>
#include <boost/simd/sdk/config.hpp>

#include <nt2/include/constants/pio_3.hpp>
#include <nt2/include/constants/zero.hpp>
#include <nt2/include/constants/third.hpp>
#include <nt2/include/constants/oneo_5.hpp>
#include <nt2/include/constants/oneo_7.hpp>


NT2_TEST_CASE_TPL ( sinc,  NT2_REAL_TYPES)
{
  using nt2::sinc;

  NT2_TEST_ULP_EQUAL(sinc<1>(nt2::Pio_3<T>()),
                     T(-0.312255641506269), 4.5);
  NT2_TEST_ULP_EQUAL(sinc<2>(nt2::Pio_3<T>()),
                     T(-0.230628996884045), 4.5);
  NT2_TEST_ULP_EQUAL(sinc<3>(nt2::Pio_3<T>()),
                     T(0.183238578463894), 16);

  NT2_TEST_ULP_EQUAL(sinc<1>(nt2::Zero<T>()),
                     nt2::Zero<T>(), 1.5);
  NT2_TEST_ULP_EQUAL(sinc<2>(nt2::Zero<T>()),
                     -nt2::Third<T>(), 1.5);
  NT2_TEST_ULP_EQUAL(sinc<3>(nt2::Zero<T>()),
                     nt2::Zero<T>(), 1.5);
  NT2_TEST_ULP_EQUAL(sinc<4>(nt2::Zero<T>()),
                     nt2::Oneo_5<T>(), 1.5);
  NT2_TEST_ULP_EQUAL(sinc<5>(nt2::Zero<T>()),
                     nt2::Zero<T>(), 1.5);
  NT2_TEST_ULP_EQUAL(sinc<6>(nt2::Zero<T>()),
                     -nt2::Oneo_7<T>(), 1.5);

}



