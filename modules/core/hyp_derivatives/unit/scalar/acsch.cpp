//==============================================================================
//         Copyright 2015 J.T. Lapreste
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/hyperbolic/include/functions/acsch.hpp>
#include <nt2/hyp_derivatives/include/functions/acsch.hpp>
#include <nt2/include/functions/acsch.hpp>
#include <nt2/include/functor.hpp>
#include <nt2/sdk/functor/meta/call.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/ulp.hpp>
#include <boost/simd/sdk/config.hpp>

#include <nt2/include/constants/two.hpp>


NT2_TEST_CASE_TPL ( acsch,  NT2_REAL_TYPES)
{
  using nt2::acsch;


  NT2_TEST_ULP_EQUAL(acsch<0>(nt2::Two<T>()),
                     acsch(nt2::Two<T>()), 1.5);
  NT2_TEST_ULP_EQUAL(acsch<1>(nt2::Two<T>()),
                     T(-0.223606797749979), 1.5);
  NT2_TEST_ULP_EQUAL(acsch<2>(nt2::Two<T>()),
                     T(0.201246117974981), 1.5);
  NT2_TEST_ULP_EQUAL(acsch<3>(nt2::Two<T>()),
                     T( -0.263856021344975), 2);
  NT2_TEST_ULP_EQUAL(acsch<4>(nt2::Two<T>()),
                     T( 0.449449663477458), 2);
  NT2_TEST_ULP_EQUAL(acsch<5>(nt2::Two<T>()),
                     T(-0.936465268976912), 5);
  NT2_TEST_ULP_EQUAL(acsch<6>(nt2::Two<T>()),
                     T( 2.304670543049483), 6);

}
