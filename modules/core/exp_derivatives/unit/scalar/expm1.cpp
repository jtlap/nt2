//==============================================================================
//         Copyright 2015 J.T. Lapreste
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/exponential/include/functions/expm1.hpp>
#include <nt2/exp_derivatives/include/functions/expm1.hpp>
#include <nt2/include/functions/exp.hpp>
#include <nt2/include/functor.hpp>
#include <nt2/sdk/functor/meta/call.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/ulp.hpp>
#include <boost/simd/sdk/config.hpp>

#include <nt2/include/constants/half.hpp>


NT2_TEST_CASE_TPL ( exp,  NT2_REAL_TYPES)
{
  NT2_TEST_ULP_EQUAL(nt2::expm1<0>(nt2::Half<T>())
                    , nt2::expm1(nt2::Half<T>())
                    , 0.5);
  NT2_TEST_ULP_EQUAL(nt2::expm1<1>(nt2::Half<T>())
                    , nt2::exp(nt2::Half<T>())
                    , 0.5);
  NT2_TEST_ULP_EQUAL(nt2::expm1<2>(nt2::Half<T>())
                    , nt2::exp(nt2::Half<T>())
                    , 0.5);

}

