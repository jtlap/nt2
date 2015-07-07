//==============================================================================
//         Copyright 2015 J.T. Lapreste
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/trigonometric/include/functions/asin.hpp>
#include <nt2/trig_derivatives/include/functions/asin.hpp>
#include <nt2/include/functions/asin.hpp>
#include <nt2/include/functor.hpp>
#include <nt2/sdk/functor/meta/call.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/ulp.hpp>
#include <boost/simd/sdk/config.hpp>

#include <nt2/include/constants/half.hpp>


NT2_TEST_CASE_TPL ( asin,  NT2_REAL_TYPES)
{
  using nt2::asin;

  NT2_TEST_ULP_EQUAL(asin<1>(nt2::Half<T>()),
                     T(1.154700538379251529018297561), 1.5);
  NT2_TEST_ULP_EQUAL(asin<2>(nt2::Half<T>()),
                     T(0.769800358919501019345531707336), 1.5);
  NT2_TEST_ULP_EQUAL(asin<3>(nt2::Half<T>()),
                     T(3.07920143567800407738212682934), 1.5);

}
