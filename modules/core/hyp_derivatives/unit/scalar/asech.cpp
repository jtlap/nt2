//==============================================================================
//         Copyright 2015 J.T. Lapreste
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/hyperbolic/include/functions/asech.hpp>
#include <nt2/hyp_derivatives/include/functions/asech.hpp>
#include <nt2/include/functions/asech.hpp>
#include <nt2/include/functor.hpp>
#include <nt2/sdk/functor/meta/call.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/ulp.hpp>
#include <boost/simd/sdk/config.hpp>

#include <nt2/include/constants/half.hpp>


NT2_TEST_CASE_TPL ( asech,  NT2_REAL_TYPES)
{
  using nt2::asech;


  NT2_TEST_ULP_EQUAL(asech<0>(nt2::Half<T>()),
                     asech(nt2::Half<T>()), 1.5);
  NT2_TEST_ULP_EQUAL(asech<1>(nt2::Half<T>()),
                     T(-2.309401076758503), 1.5);
  NT2_TEST_ULP_EQUAL(asech<2>(nt2::Half<T>()),
                     T(3.079201435678004), 1.5);
  NT2_TEST_ULP_EQUAL(asech<3>(nt2::Half<T>()),
                     T(-18.475208614068023), 1.5);
  NT2_TEST_ULP_EQUAL(asech<4>(nt2::Half<T>()),
                     T(82.112038284746774), 1.5);
  NT2_TEST_ULP_EQUAL(asech<5>(nt2::Half<T>()),
                     T(-8.649134699326661e+02), 1.5);
  NT2_TEST_ULP_EQUAL(asech<6>(nt2::Half<T>()),
                     T(6.787928498205733e+03), 1.5);

}

// vd1 =

//   -2.309401076758503


// vd2 =

//    3.079201435678004


// vd3 =

//  -18.475208614068023


// vd4 =

//   82.112038284746774


// vd5 =

//     -8.649134699326661e+02


// vd6 =

//      6.787928498205733e+03



