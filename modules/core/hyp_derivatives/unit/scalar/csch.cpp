//==============================================================================
//         Copyright 2015 J.T. Lapreste
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/hyperbolic/include/functions/csch.hpp>
#include <nt2/hyp_derivatives/include/functions/csch.hpp>
#include <nt2/include/functions/csch.hpp>
#include <nt2/include/functor.hpp>
#include <nt2/sdk/functor/meta/call.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/ulp.hpp>
#include <boost/simd/sdk/config.hpp>

#include <nt2/include/constants/half.hpp>


NT2_TEST_CASE_TPL ( csch,  NT2_REAL_TYPES)
{
  using nt2::csch;

  NT2_TEST_ULP_EQUAL(csch<1>(nt2::Half<T>()),
                     -4.152701801234358, 2.5);
  NT2_TEST_ULP_EQUAL(csch<2>(nt2::Half<T>()),
                     16.053471726704540, 2.5);
  NT2_TEST_ULP_EQUAL(csch<3>(nt2::Half<T>()),
                      -95.911491233608999, 2.5);
  NT2_TEST_ULP_EQUAL(csch<4>(nt2::Half<T>()),
                      7.678971433314490e+02, 2.5);
  NT2_TEST_ULP_EQUAL(csch<5>(nt2::Half<T>()),
                      -7.680132153473808e+03, 3);
  NT2_TEST_ULP_EQUAL(csch<6>(nt2::Half<T>()),
                      9.216038838508698e+04, 3.5);

}

