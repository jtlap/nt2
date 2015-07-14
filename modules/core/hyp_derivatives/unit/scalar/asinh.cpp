//==============================================================================
//         Copyright 2015 J.T. Lapreste
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/hyperbolic/include/functions/asinh.hpp>
#include <nt2/hyp_derivatives/include/functions/asinh.hpp>
#include <nt2/include/functions/asinh.hpp>
#include <nt2/include/functor.hpp>
#include <nt2/sdk/functor/meta/call.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/ulp.hpp>
#include <boost/simd/sdk/config.hpp>

#include <nt2/include/constants/two.hpp>


NT2_TEST_CASE_TPL ( asinh,  NT2_REAL_TYPES)
{
  using nt2::asinh;

  NT2_TEST_ULP_EQUAL(asinh<1>(nt2::Two<T>()),
                     T(0.447213595499958), 1.5);
  NT2_TEST_ULP_EQUAL(asinh<2>(nt2::Two<T>()),
                     T(-0.178885438199983), 5);
  NT2_TEST_ULP_EQUAL(asinh<3>(nt2::Two<T>()),
                     T(0.125219806739988), 5);
  NT2_TEST_ULP_EQUAL(asinh<4>(nt2::Two<T>()),
                     T(-0.107331262919990), 5);
  NT2_TEST_ULP_EQUAL(asinh<5>(nt2::Two<T>()),
                     T(0.075131884043993), 5);
  NT2_TEST_ULP_EQUAL(asinh<6>(nt2::Two<T>()),
                     T(0.072985258785593), 5);

}
