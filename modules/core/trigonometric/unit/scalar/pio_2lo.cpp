//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/include/constants/pio_2lo.hpp>
#include <nt2/sdk/unit/tests/basic.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/module.hpp>

#include <nt2/include/constants/pio_2.hpp>
#include <nt2/include/constants/eps.hpp>
#include <nt2/include/functions/abs.hpp>
#include <cmath>
#include <cfloat>

NT2_TEST_CASE ( Pio_2lo)
{

  using nt2::Pio_2lo;
  NT2_TEST_LESSER(nt2::abs(double(Pio_2lo<float>())+double(nt2::Pio_2<float>()) -nt2::Pio_2<double>()), 10*nt2::Eps<double>());
  long double pio_2 = 1.57079632679489661923132169164l;
  NT2_TEST_LESSER(double(std::abs((long double)(Pio_2lo<double>())+(long double)(nt2::Pio_2<double>()) -pio_2)), 1.0e-30);

}

