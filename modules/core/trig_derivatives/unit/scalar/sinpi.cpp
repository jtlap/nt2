//==============================================================================
//         Copyright 2015 J.T. Lapreste
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/trigonometric/include/functions/sinpi.hpp>
#include <nt2/trig_derivatives/include/functions/sinpi.hpp>
#include <nt2/include/functions/cospi.hpp>
#include <nt2/include/functions/sinpi.hpp>
#include <nt2/include/functions/pow.hpp>
#include <nt2/include/functions/unary_minus.hpp>
#include <nt2/include/functor.hpp>
#include <nt2/sdk/functor/meta/call.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/ulp.hpp>
#include <boost/simd/sdk/config.hpp>

#include <nt2/include/constants/third.hpp>
#include <nt2/include/constants/invpi.hpp>
#include <iostream>

NT2_TEST_CASE_TPL ( sinpi,  NT2_REAL_TYPES)
{
  using nt2::cospi;
  using nt2::sinpi;
  NT2_TEST_ULP_EQUAL(sinpi<1>(nt2::Third<T>()),
                     (cospi(nt2::Third<T>())*nt2::pow<1>(nt2::Invpi<T>())), 1.5);
  NT2_TEST_ULP_EQUAL(sinpi<2>(nt2::Third<T>()),
                     (-sinpi(nt2::Third<T>())*nt2::pow<2>(nt2::Invpi<T>())), 1.5);
  NT2_TEST_ULP_EQUAL(sinpi<3>(nt2::Third<T>()),
                     (-cospi(nt2::Third<T>())*nt2::pow<3>(nt2::Invpi<T>())), 1.5);
}


