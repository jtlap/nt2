//==============================================================================
//         Copyright 2015 J.T. Lapreste
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/exponential/include/functions/cbrt.hpp>
#include <nt2/exp_derivatives/include/functions/cbrt.hpp>
#include <nt2/include/functions/cbrt.hpp>
#include <nt2/include/functions/sqr.hpp>
#include <nt2/include/functions/rec.hpp>
#include <nt2/include/functions/sqrteps.hpp>
#include <nt2/include/functor.hpp>
#include <nt2/sdk/functor/meta/call.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/ulp.hpp>
#include <boost/simd/sdk/config.hpp>

#include <nt2/include/constants/half.hpp>
#include <nt2/include/constants/three.hpp>


NT2_TEST_CASE_TPL ( cbrt,  NT2_REAL_TYPES)
{
  using nt2::cbrt;

  NT2_TEST_ULP_EQUAL(nt2::cbrt( boost::mpl::long_<0>(), nt2::Half<T>())
                    , nt2::cbrt(nt2::Half<T>())
                    , 0.5);
  NT2_TEST_ULP_EQUAL(nt2::cbrt<1>(nt2::Half<T>())
                    , nt2::rec(nt2::Three<T>()*nt2::sqr(nt2::cbrt(nt2::Half<T>())))
                    ,0.5);

  auto d2 =  [](const T& x) {return -T(2)/(T(9)*pow(x, T(5)/T(3)));};

  NT2_TEST_ULP_EQUAL(nt2::cbrt<2>(nt2::Half<T>())
                    , d2(nt2::Half<T>())
                    ,0.5);


}
