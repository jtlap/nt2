//==============================================================================
//         Copyright 2015 J.T. Lapreste
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/hyperbolic/include/functions/sech.hpp>
#include <nt2/hyp_derivatives/include/functions/sech.hpp>
#include <nt2/include/functions/sech.hpp>
#include <nt2/include/functor.hpp>
#include <nt2/sdk/functor/meta/call.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/ulp.hpp>
#include <boost/simd/sdk/config.hpp>

#include <nt2/include/constants/half.hpp>


NT2_TEST_CASE_TPL ( sech,  NT2_REAL_TYPES)
{
  using nt2::sech;

  NT2_TEST_ULP_EQUAL(sech<1>(nt2::Half<T>()),
                     -0.409814221664745, 2.5);
  NT2_TEST_ULP_EQUAL(sech<2>(nt2::Half<T>()),
                     -0.508054517729203, 2.5);
  NT2_TEST_ULP_EQUAL(sech<3>(nt2::Half<T>()),
                      1.523970571727864, 2.5);
  NT2_TEST_ULP_EQUAL(sech<4>(nt2::Half<T>()),
                      0.102025161467718, 12.5);
  NT2_TEST_ULP_EQUAL(sech<5>(nt2::Half<T>()),
                      -11.488379623890685, 2.5);
  NT2_TEST_ULP_EQUAL(sech<6>(nt2::Half<T>()),
                      24.108719591476081, 2.5);
}

