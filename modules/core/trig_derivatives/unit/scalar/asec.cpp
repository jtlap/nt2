//==============================================================================
//         Copyright 2015 J.T. Lapreste
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/trigonometric/include/functions/asec.hpp>
#include <nt2/trig_derivatives/include/functions/asec.hpp>
#include <nt2/include/functions/asec.hpp>
#include <nt2/include/functor.hpp>
#include <nt2/sdk/functor/meta/call.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/ulp.hpp>
#include <boost/simd/sdk/config.hpp>

#include <nt2/include/constants/two.hpp>


NT2_TEST_CASE_TPL ( asec,  NT2_REAL_TYPES)
{
  using nt2::asec;


  NT2_TEST_ULP_EQUAL(asec<0>(nt2::Two<T>()),
                     asec(nt2::Two<T>()), 1.5);
  NT2_TEST_ULP_EQUAL(asec<1>(nt2::Two<T>()),
                     T(-0.288675134594812882254574390251), 1.5);
  NT2_TEST_ULP_EQUAL(asec<2>(nt2::Two<T>()),
                     T(0.336787657027281695963670121959), 1.5);
  NT2_TEST_ULP_EQUAL(asec<3>(nt2::Two<T>()),
                     T(-0.62546279162209457821824451221), 1.5);
  NT2_TEST_ULP_EQUAL(asec<4>(nt2::Two<T>()),
                     T(-1.643844516442684), 1.5);

}




