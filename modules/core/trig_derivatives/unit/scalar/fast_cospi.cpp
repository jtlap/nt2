//==============================================================================
//         Copyright 2015 J.T. Lapreste
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/trigonometric/include/functions/fast_cospi.hpp>
#include <nt2/trig_derivatives/include/functions/fast_cospi.hpp>
#include <nt2/include/functions/fast_cospi.hpp>
#include <nt2/include/functions/sinpi.hpp>
#include <nt2/include/functions/pow.hpp>
#include <nt2/include/functions/unary_minus.hpp>
#include <nt2/include/functor.hpp>
#include <nt2/sdk/functor/meta/call.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/ulp.hpp>
#include <boost/simd/sdk/config.hpp>

#include <nt2/include/constants/oneo_6.hpp>
#include <nt2/include/constants/pi.hpp>
#include <iostream>

NT2_TEST_CASE_TPL ( fast_cospi,  NT2_REAL_TYPES)
{
  using nt2::fast_cospi;
  using nt2::sinpi;
  NT2_TEST_ULP_EQUAL(fast_cospi<1>(nt2::Oneo_6<T>()),
                     (-sinpi(nt2::Oneo_6<T>())*nt2::pow<1>(nt2::Pi<T>())), 1.5);
  NT2_TEST_ULP_EQUAL(fast_cospi<2>(nt2::Oneo_6<T>()),
                     (-fast_cospi(nt2::Oneo_6<T>())*nt2::pow<2>(nt2::Pi<T>())), 1.5);
  NT2_TEST_ULP_EQUAL(fast_cospi<3>(nt2::Oneo_6<T>()),
                     (sinpi(nt2::Oneo_6<T>())*nt2::pow<3>(nt2::Pi<T>())), 1.5);
}


