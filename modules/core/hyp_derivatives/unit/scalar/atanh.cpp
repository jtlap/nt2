//==============================================================================
//         Copyright 2015 J.T. Lapreste
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/hyp_derivatives/include/functions/atanh.hpp>
#include <nt2/include/functions/atanh.hpp>
#include <nt2/include/functor.hpp>
#include <nt2/sdk/functor/meta/call.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/ulp.hpp>
#include <boost/simd/sdk/config.hpp>

#include <nt2/include/constants/half.hpp>


NT2_TEST_CASE_TPL ( atanh,  NT2_REAL_TYPES)
{
  using nt2::atanh;

  NT2_TEST_ULP_EQUAL(atanh<1>(nt2::Half<T>()),
                     T( 1.333333333333333), 1.5);
  NT2_TEST_ULP_EQUAL(atanh<2>(nt2::Half<T>()),
                     T( 1.777777777777778), 1.5);
  NT2_TEST_ULP_EQUAL(atanh<3>(nt2::Half<T>()),
                     T( 8.296296296296296), 6);
  NT2_TEST_ULP_EQUAL(atanh<4>(nt2::Half<T>()),
                     T(47.407407407407405), 6);
  NT2_TEST_ULP_EQUAL(atanh<5>(nt2::Half<T>()),
                     T( 3.855802469135803e+02), 6);
  NT2_TEST_ULP_EQUAL(atanh<6>(nt2::Half<T>()),
                     T( 3.834732510288066e+03), 6);

}
