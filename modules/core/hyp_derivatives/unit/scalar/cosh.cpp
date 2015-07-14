//==============================================================================
//         Copyright 2015 J.T. Lapreste
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/hyperbolic/include/functions/cosh.hpp>
#include <nt2/hyp_derivatives/include/functions/cosh.hpp>
#include <nt2/include/functions/cosh.hpp>
#include <nt2/include/functor.hpp>
#include <nt2/sdk/functor/meta/call.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/ulp.hpp>
#include <boost/simd/sdk/config.hpp>

#include <nt2/include/constants/one.hpp>


NT2_TEST_CASE_TPL ( cosh,  NT2_REAL_TYPES)
{
  using nt2::cosh;

  NT2_TEST_ULP_EQUAL(cosh<1>(nt2::One<T>()),
                     T(1.175201193643801), 1.5);
  NT2_TEST_ULP_EQUAL(cosh<2>(nt2::One<T>()),
                     T(1.543080634815244), 1.5);
  NT2_TEST_ULP_EQUAL(cosh<3>(nt2::One<T>()),
                     T(1.175201193643801), 1.5);
  NT2_TEST_ULP_EQUAL(cosh<4>(nt2::One<T>()),
                     T(1.543080634815244), 1.5);
  NT2_TEST_ULP_EQUAL(cosh<5>(nt2::One<T>()),
                     T(1.175201193643801), 1.5);

}

