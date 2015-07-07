//==============================================================================
//         Copyright 2015 J.T. Lapreste
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/trigonometric/include/functions/sincpi.hpp>
#include <nt2/trig_derivatives/include/functions/sincpi.hpp>
#include <nt2/include/functions/sincpi.hpp>
#include <nt2/include/functions/sinc.hpp>
#include <nt2/include/functor.hpp>
#include <nt2/sdk/functor/meta/call.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/ulp.hpp>
#include <boost/simd/sdk/config.hpp>

#include <nt2/include/constants/pio_3.hpp>
#include <nt2/include/constants/invpi.hpp>



NT2_TEST_CASE_TPL ( sincpi,  NT2_REAL_TYPES)
{
  using nt2::sincpi;
  using nt2::sinc;

  NT2_TEST_ULP_EQUAL(sincpi<1>(nt2::Pio_3<T>()),
                     sinc<1>(nt2::Pio_3<T>())*nt2::pow<1>(nt2::Invpi<T>()), 4.5);
  NT2_TEST_ULP_EQUAL(sincpi<2>(nt2::Pio_3<T>()),
                     sinc<2>(nt2::Pio_3<T>())*nt2::pow<2>(nt2::Invpi<T>()), 4.5);
  NT2_TEST_ULP_EQUAL(sincpi<3>(nt2::Pio_3<T>()),
                     sinc<3>(nt2::Pio_3<T>())*nt2::pow<3>(nt2::Invpi<T>()), 16);

}



