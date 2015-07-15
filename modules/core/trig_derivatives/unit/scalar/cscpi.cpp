//==============================================================================
//         Copyright 2015 J.T. Lapreste
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/trigonometric/include/functions/cscpi.hpp>
#include <nt2/trig_derivatives/include/functions/cscpi.hpp>
#include <nt2/include/functions/cscpi.hpp>
#include <nt2/include/functions/csc.hpp>
#include <nt2/include/functions/pow.hpp>
#include <nt2/include/functions/unary_minus.hpp>
#include <nt2/include/functor.hpp>
#include <nt2/sdk/functor/meta/call.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/ulp.hpp>
#include <boost/simd/sdk/config.hpp>

#include <nt2/include/constants/third.hpp>
#include <nt2/include/constants/pi.hpp>
#include <nt2/include/constants/pio_3.hpp>

NT2_TEST_CASE_TPL ( cscpi,  NT2_REAL_TYPES)
{
  using nt2::cscpi;
  using nt2::csc;
  NT2_TEST_ULP_EQUAL(cscpi<0>(nt2::Third<T>()),
                     (csc<0>(nt2::Pio_3<T>())), 1.5);
  NT2_TEST_ULP_EQUAL(cscpi<1>(nt2::Third<T>()),
                     (csc<1>(nt2::Pio_3<T>())*nt2::pow<1>(nt2::Pi<T>())), 1.5);
  NT2_TEST_ULP_EQUAL(cscpi<2>(nt2::Third<T>()),
                     (csc<2>(nt2::Pio_3<T>())*nt2::pow<2>(nt2::Pi<T>())), 2.5);
  NT2_TEST_ULP_EQUAL(cscpi<3>(nt2::Third<T>()),
                     (csc<3>(nt2::Pio_3<T>())*nt2::pow<3>(nt2::Pi<T>())), 2.5);
}


