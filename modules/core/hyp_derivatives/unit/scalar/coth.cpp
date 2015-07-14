//==============================================================================
//         Copyright 2015 J.T. Lapreste
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/hyperbolic/include/functions/coth.hpp>
#include <nt2/hyp_derivatives/include/functions/coth.hpp>
#include <nt2/include/functions/coth.hpp>
#include <nt2/include/functor.hpp>
#include <nt2/sdk/functor/meta/call.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/ulp.hpp>
#include <boost/simd/sdk/config.hpp>

#include <nt2/include/constants/two.hpp>


NT2_TEST_CASE_TPL ( coth,  NT2_REAL_TYPES)
{
  using nt2::coth;

  NT2_TEST_ULP_EQUAL(coth<1>(nt2::Two<T>()),
                     -0.076021829838071, 16);
  NT2_TEST_ULP_EQUAL(coth<2>(nt2::Two<T>()),
                     0.157717126375352, 16);
  NT2_TEST_ULP_EQUAL(coth<3>(nt2::Two<T>()),
                     -0.338763231023856 , 16);
  NT2_TEST_ULP_EQUAL(coth<4>(nt2::Two<T>()),
                     0.774747840027686 , 16);
  NT2_TEST_ULP_EQUAL(coth<5>(nt2::Two<T>()),
                     -1.962590035972098  , 128);
  NT2_TEST_ULP_EQUAL(coth<6>(nt2::Two<T>()),
                       5.729199821128351 , 32);

}


