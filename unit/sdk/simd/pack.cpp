/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 0x01.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#define NT2_UNIT_MODULE "nt2::simd::pack"

#include <iostream>
#include <nt2/sdk/simd/pack.hpp>
#include <nt2/include/functions/cosd.hpp>

////////////////////////////////////////////////////////////////////////////////
// Test pack computations
////////////////////////////////////////////////////////////////////////////////

int main()
{
  nt2::simd::pack<float> x(4);

  std::cout << nt2::cosd(x+x*x+x)*x << "\n";
}

