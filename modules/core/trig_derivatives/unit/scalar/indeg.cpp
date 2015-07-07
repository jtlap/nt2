//==============================================================================
//         Copyright 2015 J.T. Lapreste
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/trigonometric/include/functions/indeg.hpp>
#include <nt2/trig_derivatives/include/functions/indeg.hpp>
#include <nt2/include/functions/indeg.hpp>
#include <nt2/include/constants/radindeg.hpp>
#include <nt2/include/functor.hpp>
#include <nt2/sdk/functor/meta/call.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/ulp.hpp>
#include <boost/simd/sdk/config.hpp>

#include <nt2/include/constants/half.hpp>


NT2_TEST_CASE_TPL ( indeg,  NT2_REAL_TYPES)
{
  using nt2::indeg;

  NT2_TEST_ULP_EQUAL(indeg<1>(nt2::Half<T>()),
                     nt2::Radindeg<T>(), 1.5);
  NT2_TEST_ULP_EQUAL(indeg<2>(nt2::Half<T>()),
                     T(0), 1.5);
  NT2_TEST_ULP_EQUAL(indeg<3>(nt2::Half<T>()),
                     T(0), 1.5);

}
