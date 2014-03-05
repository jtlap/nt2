//==============================================================================
//         Copyright 2003 - 2014   LASMEA UMR 6602 CNRS/UBP
//         Copyright 2009 - 2014   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
// cover for functor atan2 in scalar mode
#include <nt2/trigonometric/include/functions/atan2.hpp>
#include <boost/simd/sdk/simd/io.hpp>
#include <cmath>
#include <iostream>
#include <nt2/include/constants/one.hpp>
#include <nt2/include/constants/zero.hpp>
#include <nt2/sdk/unit/args.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/cover.hpp>
#include <vector>

extern "C" {extern long double cephes_atanl(long double);}

NT2_TEST_CASE_TPL(atan2_0,  NT2_SIMD_REAL_TYPES)
{
  using nt2::unit::args;
  const std::size_t NR = args("samples", NT2_NB_RANDOM_TEST);
  const double ulpd = args("ulpd", 1);

  const T min0 = args("min0", nt2::Zero<T>());
  const T max0 = args("max0", nt2::One<T>());
  std::cout << "Argument samples #0 chosen in range: [" << min0 << ",  " << max0 << "]" << std::endl;
  NT2_CREATE_BUF(a0,T, NR, min0, max0);
  const T min1 = args("min1", nt2::Zero<T>());
  const T max1 = args("max1", nt2::One<T>());
  std::cout << "Argument samples #1 chosen in range: [" << min1 << ",  " << max1 << "]" << std::endl;
  NT2_CREATE_BUF(a1,T, NR, min1, max1);

  std::vector<T> ref(NR);
  for(std::size_t i=0; i!=NR; ++i)
    ref[i] = ::atan2(a0[i],a1[i]);

  NT2_COVER_ULP_EQUAL(nt2::tag::atan2_, ((T, a0))((T, a1)), ref, ulpd);

}
