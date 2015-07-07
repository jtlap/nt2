//==============================================================================
//         Copyright 2015 J.T. Lapreste
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/trigonometric/include/functions/cosd.hpp>
#include <nt2/trig_derivatives/include/functions/cosd.hpp>
#include <nt2/include/functions/cosd.hpp>
#include <nt2/include/functions/sind.hpp>
#include <nt2/include/functions/pow.hpp>
#include <nt2/include/functions/unary_minus.hpp>
#include <nt2/include/functor.hpp>
#include <nt2/sdk/functor/meta/call.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/ulp.hpp>
#include <boost/simd/sdk/config.hpp>

#include <nt2/include/constants/_30.hpp>
#include <nt2/include/constants/deginrad.hpp>
#include <iostream>

NT2_TEST_CASE_TPL ( cosd,  NT2_REAL_TYPES)
{
  using nt2::cosd;
  using nt2::sind;
  NT2_TEST_ULP_EQUAL(cosd<1>(nt2::_30<T>()),
                     (-sind(nt2::_30<T>())*nt2::pow<1>(nt2::Deginrad<T>())), 1.5);
  NT2_TEST_ULP_EQUAL(cosd<2>(nt2::_30<T>()),
                     (-cosd(nt2::_30<T>())*nt2::pow<2>(nt2::Deginrad<T>())), 1.5);
  NT2_TEST_ULP_EQUAL(cosd<3>(nt2::_30<T>()),
                     (sind(nt2::_30<T>())*nt2::pow<3>(nt2::Deginrad<T>())), 1.5);
}


