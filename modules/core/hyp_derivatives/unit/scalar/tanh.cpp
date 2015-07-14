//==============================================================================
//         Copyright 2015 J.T. Lapreste
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/hyperbolic/include/functions/tanh.hpp>
#include <nt2/hyp_derivatives/include/functions/tanh.hpp>
#include <nt2/include/functions/tanh.hpp>
#include <nt2/include/functor.hpp>
#include <nt2/sdk/functor/meta/call.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/ulp.hpp>
#include <boost/simd/sdk/config.hpp>

#include <nt2/include/constants/half.hpp>


NT2_TEST_CASE_TPL ( tanh,  NT2_REAL_TYPES)
{
  using nt2::tanh;

  NT2_TEST_ULP_EQUAL(tanh<1>(nt2::Half<T>()),
                     0.786447732965927, 2);
  NT2_TEST_ULP_EQUAL(tanh<2>(nt2::Half<T>()),
                     -0.726861981383587, 5);
  NT2_TEST_ULP_EQUAL(tanh<3>(nt2::Half<T>()),
                      -0.565209288259770, 5);
  NT2_TEST_ULP_EQUAL(tanh<4>(nt2::Half<T>()),
                      3.952219563724583, 5);
  NT2_TEST_ULP_EQUAL(tanh<5>(nt2::Half<T>()),
                       -3.266686471971393, 5);
  NT2_TEST_ULP_EQUAL(tanh<6>(nt2::Half<T>()),
                       -36.279540291791626, 5);

}

