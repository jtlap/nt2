//==============================================================================
//         Copyright 2015 J.T. Lapreste
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/hyperbolic/include/functions/sinhc.hpp>
#include <nt2/hyp_derivatives/include/functions/sinhc.hpp>
#include <nt2/include/functions/sinhc.hpp>
#include <nt2/include/functor.hpp>
#include <nt2/sdk/functor/meta/call.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/ulp.hpp>
#include <boost/simd/sdk/config.hpp>

#include <nt2/include/constants/two.hpp>
#include <nt2/include/constants/zero.hpp>
#include <nt2/include/constants/third.hpp>
#include <nt2/include/constants/oneo_5.hpp>
#include <nt2/include/constants/oneo_7.hpp>


NT2_TEST_CASE_TPL ( sinhc,  NT2_REAL_TYPES)
{
  using nt2::sinhc;

  NT2_TEST_ULP_EQUAL(sinhc<1>(nt2::Two<T>()),
                     T( 0.974382743580061), 4.5);
  NT2_TEST_ULP_EQUAL(sinhc<2>(nt2::Two<T>()),
                     T(0.839047460343448), 5.5);
  NT2_TEST_ULP_EQUAL(sinhc<3>(nt2::Two<T>()),
                     T( 0.622526655026643), 16);
  NT2_TEST_ULP_EQUAL(sinhc<4>(nt2::Two<T>()),
                     T( 0.568376893870223), 16);
  NT2_TEST_ULP_EQUAL(sinhc<5>(nt2::Two<T>()),
                     T(0.460155610866258), 32);

  NT2_TEST_ULP_EQUAL(sinhc<1>(nt2::Zero<T>()),
                     nt2::Zero<T>(), 1.5);
  NT2_TEST_ULP_EQUAL(sinhc<2>(nt2::Zero<T>()),
                     nt2::Third<T>(), 1.5);
  NT2_TEST_ULP_EQUAL(sinhc<3>(nt2::Zero<T>()),
                     nt2::Zero<T>(), 1.5);
  NT2_TEST_ULP_EQUAL(sinhc<4>(nt2::Zero<T>()),
                     nt2::Oneo_5<T>(), 1.5);
  NT2_TEST_ULP_EQUAL(sinhc<5>(nt2::Zero<T>()),
                     nt2::Zero<T>(), 1.5);

}
