//==============================================================================
//         Copyright 2015 J.T. Lapreste
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/exponential/include/functions/logspace_add.hpp>
#include <nt2/exp_derivatives/include/functions/logspace_add.hpp>
#include <nt2/include/functions/logspace_add.hpp>
#include <nt2/include/functions/log.hpp>
#include <nt2/include/functor.hpp>
#include <nt2/sdk/functor/meta/call.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/ulp.hpp>
#include <boost/simd/sdk/config.hpp>

#include <nt2/include/constants/half.hpp>
#include <nt2/include/constants/one.hpp>


NT2_TEST_CASE_TPL ( logspace_add,  NT2_REAL_TYPES)
{
  using nt2::logspace_add;

  NT2_TEST_ULP_EQUAL((nt2::logspace_add<0, 1>(nt2::One<T>(), nt2::Half<T>()))
                    , T(0.377540668798145435361099434254)
                    ,0.5);
  NT2_TEST_ULP_EQUAL((nt2::logspace_add<1, 0>(nt2::One<T>(), nt2::Half<T>()))
                    , T(.622459331201854564638900565746)
                    ,0.5);
  NT2_TEST_ULP_EQUAL((nt2::logspace_add<1, 1>(nt2::One<T>(), nt2::Half<T>()))
                    , -T(0.235003712201594489069302695021)
                    ,0.5);
  NT2_TEST_ULP_EQUAL((nt2::logspace_add<2, 0>(nt2::One<T>(), nt2::Half<T>()))
                    , T(0.235003712201594489069302695021)
                    ,0.5);
  NT2_TEST_ULP_EQUAL((nt2::logspace_add<0, 2>(nt2::One<T>(), nt2::Half<T>()))
                    , T(0.235003712201594489069302695021)
                    ,0.5);
}
