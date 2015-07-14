//==============================================================================
//         Copyright 2015 J.T. Lapreste
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/hyperbolic/include/functions/acosh.hpp>
#include <nt2/hyp_derivatives/include/functions/acosh.hpp>
#include <nt2/include/functions/acosh.hpp>
#include <nt2/include/functor.hpp>
#include <nt2/sdk/functor/meta/call.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/ulp.hpp>
#include <boost/simd/sdk/config.hpp>

#include <nt2/include/constants/half.hpp>


NT2_TEST_CASE_TPL ( acosh,  NT2_REAL_TYPES)
{
  using nt2::acosh;

  NT2_TEST_ULP_EQUAL(acosh<1>(nt2::Two<T>()),
                     T( 0.577350269189626), 1.5);
  NT2_TEST_ULP_EQUAL(acosh<2>(nt2::Two<T>()),
                     T(-0.384900179459751), 5);
  NT2_TEST_ULP_EQUAL(acosh<3>(nt2::Two<T>()),
                     T(0.577350269189626), 1.5);
  NT2_TEST_ULP_EQUAL(acosh<4>(nt2::Two<T>()),
                     T(-1.411300658019085), 1.5);
  NT2_TEST_ULP_EQUAL(acosh<5>(nt2::Two<T>()),
                     T(4.854018929853520), 1.5);

  NT2_TEST_ULP_EQUAL(acosh<6>(nt2::Two<T>()),
                     T( -21.597176736352669), 1.5);

  NT2_TEST_ULP_EQUAL(acosh<7>(nt2::Two<T>()),
                     T(1.179291383178069e+02), 1.5);

}
