//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/trigonometric/constants/pio_4lo.hpp>
#include <nt2/sdk/unit/tests/basic.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/module.hpp>

#include <nt2/include/constants/pio_4.hpp>
#include <nt2/include/constants/eps.hpp>
#include <nt2/include/functions/abs.hpp>
#include <cmath>
#include <cfloat>


NT2_TEST_CASE ( Pio_4lo)
{

  using nt2::Pio_4lo;
  NT2_TEST_LESSER(nt2::abs(double(Pio_4lo<float>())+double(nt2::Pio_4<float>()) -nt2::Pio_4<double>()), 10*nt2::Eps<double>());
  long double pio_4 = 0.78539816339744830961566084582l;
  NT2_TEST_LESSER(std::abs((long double)(Pio_4lo<double>())+(long double)(nt2::Pio_4<double>()) -pio_4), 10*LDBL_EPSILON);
} // end of test for floating_

