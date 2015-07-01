//==============================================================================
//         Copyright 2015 J.T. Lapreste
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/exponential/include/functions/pow.hpp>
#include <nt2/exp_derivatives/include/functions/pow.hpp>
#include <nt2/include/functions/pow.hpp>
#include <nt2/include/functions/log.hpp>
#include <nt2/include/functor.hpp>
#include <nt2/sdk/functor/meta/call.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/ulp.hpp>
#include <boost/simd/sdk/config.hpp>

#include <nt2/include/constants/half.hpp>
#include <nt2/include/constants/mhalf.hpp>


NT2_TEST_CASE_TPL ( pow,  NT2_REAL_TYPES)
{
  using nt2::pow;

  NT2_TEST_ULP_EQUAL((nt2::pow<0, 1>(nt2::Half<T>(), nt2::Half<T>()))
                    , (nt2::pow(nt2::Half<T>(), nt2::Half<T>())*nt2::log(nt2::Half<T>()))
                    ,0.5);
  NT2_TEST_ULP_EQUAL((nt2::pow<1, 0>(nt2::Half<T>(), nt2::Half<T>()))
                    , (nt2::pow(nt2::Half<T>(), nt2::Mhalf<T>())*nt2::Half<T>())
                    ,0.5);
  NT2_TEST_ULP_EQUAL((nt2::pow<1, 1>(nt2::Half<T>(), nt2::Half<T>()))
                    , T(0.92408449063882147634)
                    ,0.5);
  NT2_TEST_ULP_EQUAL((nt2::pow<0, 2>(nt2::Half<T>(), nt2::Half<T>()))
                    , T(0.339731584183075)
                    ,0.5);
  NT2_TEST_ULP_EQUAL((nt2::pow<2, 0>(nt2::Half<T>(), nt2::Half<T>()))
                    , T(-0.70710678118654757274)
                    ,0.5);


}
