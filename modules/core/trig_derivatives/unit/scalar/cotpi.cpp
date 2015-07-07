//==============================================================================
//         Copyright 2015 J.T. Lapreste
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/trigonometric/include/functions/cotpi.hpp>
#include <nt2/trig_derivatives/include/functions/cotpi.hpp>
#include <nt2/include/functions/cotpi.hpp>
#include <nt2/include/functions/cot.hpp>
#include <nt2/include/functions/pow.hpp>
#include <nt2/include/functions/unary_minus.hpp>
#include <nt2/include/functor.hpp>
#include <nt2/sdk/functor/meta/call.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/ulp.hpp>
#include <boost/simd/sdk/config.hpp>

#include <nt2/include/constants/third.hpp>
#include <nt2/include/constants/invpi.hpp>
#include <nt2/include/constants/pio_3.hpp>
#include <iostream>

NT2_TEST_CASE_TPL ( cotpi,  NT2_REAL_TYPES)
{
  using nt2::cotpi;
  using nt2::cot;
  NT2_TEST_ULP_EQUAL(cotpi<1>(nt2::Third<T>()),
                     (cot<1>(nt2::Pio_3<T>())*nt2::pow<1>(nt2::Invpi<T>())), 1.5);
  NT2_TEST_ULP_EQUAL(cotpi<2>(nt2::Third<T>()),
                     (cot<2>(nt2::Pio_3<T>())*nt2::pow<2>(nt2::Invpi<T>())), 1.5);
  NT2_TEST_ULP_EQUAL(cotpi<3>(nt2::Third<T>()),
                     (cot<3>(nt2::Pio_3<T>())*nt2::pow<3>(nt2::Invpi<T>())), 2.5);
}


