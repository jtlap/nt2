//==============================================================================
//         Copyright 2015 J.T. Lapreste
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/trig_derivatives/include/functions/atand.hpp>
#include <nt2/include/functions/atand.hpp>
#include <nt2/include/functions/indeg.hpp>
#include <nt2/include/functor.hpp>
#include <nt2/sdk/functor/meta/call.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/ulp.hpp>
#include <boost/simd/sdk/config.hpp>

#include <nt2/include/constants/half.hpp>


NT2_TEST_CASE_TPL ( atand,  NT2_REAL_TYPES)
{
  using nt2::atand;

  NT2_TEST_ULP_EQUAL(atand<1>(nt2::Half<T>()),
                     nt2::indeg(T(0.8)), 1.5);
  NT2_TEST_ULP_EQUAL(atand<2>(nt2::Half<T>()),
                     nt2::indeg(T(-0.64)), 1.5);
  NT2_TEST_ULP_EQUAL(atand<3>(nt2::Half<T>()),
                     nt2::indeg(T(-0.256)), 12);

}

