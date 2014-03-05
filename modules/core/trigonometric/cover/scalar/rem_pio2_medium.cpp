//==============================================================================
//         Copyright 2003 - 2014   LASMEA UMR 6602 CNRS/UBP
//         Copyright 2009 - 2014   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
// cover for functor rem_pio2_medium in scalar mode
#include <nt2/trigonometric/include/functions/rem_pio2_medium.hpp>
#include <boost/fusion/include/std_pair.hpp>
#include <boost/simd/sdk/simd/io.hpp>
#include <cmath>
#include <iostream>
#include <nt2/include/constants/pi.hpp>
#include <nt2/include/constants/zero.hpp>
#include <nt2/include/functions/scalar/rem_pio2.hpp>
#include <nt2/sdk/meta/as_integer.hpp>
#include <nt2/sdk/unit/args.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/cover.hpp>
#include <vector>

NT2_TEST_CASE_TPL(rem_pio2_medium_0,  NT2_SIMD_REAL_TYPES)
{
  using nt2::unit::args;
  const std::size_t NR = args("samples", NT2_NB_RANDOM_TEST);
  const double ulpd = args("ulpd",  0.5);

  const T min = args("min", nt2::Zero<T>());
  const T max = args("max", 64*nt2::Pi<T>());
  std::cout << "Argument samples #0 chosen in range: [" << min << ",  " << max << "]" << std::endl;
  NT2_CREATE_BUF(a0,T, NR, min, max);
  typedef typename nt2::meta::as_integer<T>::type iT;

  std::vector<std::pair<iT, T> > ref(NR);
  for(std::size_t i=0; i!=NR; ++i)
  {
    T x, y;
    iT n;
    n = nt2::rem_pio2(a0[i], x, y);
    ref[i] = std::make_pair(n, x);
  }


  NT2_COVER_ULP_EQUAL(nt2::tag::rem_pio2_medium_, ((T, a0)), ref, ulpd);
}
