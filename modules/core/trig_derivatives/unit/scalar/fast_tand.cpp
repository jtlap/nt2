//==============================================================================
//         Copyright 2015 J.T. Lapreste
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/trigonometric/include/functions/fast_tand.hpp>
#include <nt2/trig_derivatives/include/functions/fast_tand.hpp>
#include <nt2/include/functions/fast_tand.hpp>
#include <nt2/include/functions/fast_tan.hpp>
#include <nt2/include/functions/pow.hpp>
#include <nt2/include/functions/unary_minus.hpp>
#include <nt2/include/functor.hpp>
#include <nt2/sdk/functor/meta/call.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/ulp.hpp>
#include <boost/simd/sdk/config.hpp>

#include <nt2/include/constants/_30.hpp>
#include <nt2/include/constants/deginrad.hpp>
#include <nt2/include/constants/pio_6.hpp>

NT2_TEST_CASE_TPL ( fast_tand,  NT2_REAL_TYPES)
{
  using nt2::fast_tand;
  using nt2::fast_tan;
  NT2_TEST_ULP_EQUAL(fast_tand<1>(nt2::_30<T>()),
                     (fast_tan<1>(nt2::Pio_6<T>())*nt2::pow<1>(nt2::Deginrad<T>())), 1.5);
  NT2_TEST_ULP_EQUAL(fast_tand<2>(nt2::_30<T>()),
                     (fast_tan<2>(nt2::Pio_6<T>())*nt2::pow<2>(nt2::Deginrad<T>())), 1.5);
  NT2_TEST_ULP_EQUAL(fast_tand<3>(nt2::_30<T>()),
                     (fast_tan<3>(nt2::Pio_6<T>())*nt2::pow<3>(nt2::Deginrad<T>())), 2.5);
}



