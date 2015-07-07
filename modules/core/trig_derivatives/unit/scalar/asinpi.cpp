//==============================================================================
//         Copyright 2015 J.T. Lapreste
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/trig_derivatives/include/functions/asinpi.hpp>
#include <nt2/include/functions/asinpi.hpp>
#include <nt2/include/functions/indeg.hpp>
#include <nt2/include/functor.hpp>
#include <nt2/sdk/functor/meta/call.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/ulp.hpp>
#include <boost/simd/sdk/config.hpp>

#include <nt2/include/constants/half.hpp>
#include <nt2/include/constants/invpi.hpp>


NT2_TEST_CASE_TPL ( asinpi,  NT2_REAL_TYPES)
{
  using nt2::asinpi;

  NT2_TEST_ULP_EQUAL(asinpi<1>(nt2::Half<T>()),
                     T(0.367552596947861), 6);
  NT2_TEST_ULP_EQUAL(asinpi<2>(nt2::Half<T>()),
                     T(0.245035064631907577560589554806), 6);
  NT2_TEST_ULP_EQUAL(asinpi<3>(nt2::Half<T>()),
                     T(0.980140258527630310242358219223), 6);

}

