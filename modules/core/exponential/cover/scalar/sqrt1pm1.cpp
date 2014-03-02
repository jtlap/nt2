//==============================================================================
//         Copyright 2003 - 2014   LASMEA UMR 6602 CNRS/UBP
//         Copyright 2009 - 2014   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
// cover for functor sqrt1pm1 in scalar mode
#include <nt2/exponential/include/functions/sqrt1pm1.hpp>
#include <boost/simd/sdk/simd/io.hpp>
#include <cmath>
#include <iostream>
#include <nt2/include/functions/minusone.hpp>
#include <nt2/include/functions/oneplus.hpp>
#include <nt2/include/functions/rec.hpp>
#include <nt2/include/functions/sqrt.hpp>
#include <nt2/sdk/unit/args.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/cover.hpp>
#include <vector>

NT2_TEST_CASE_TPL(sqrt1pm1_0,  NT2_SIMD_REAL_TYPES)
{
  using nt2::unit::args;
  const std::size_t NR = args("samples", NT2_NB_RANDOM_TEST);
  const double ulpd = args("ulpd", 2);

  const T min0 = args("min0", T(-0.5));
  const T max0 = args("max0", T(0.5));
  std::cout << "Argument samples #0 chosen in range: [" << min0 << ",  " << max0 << "]" << std::endl;
  NT2_CREATE_BUF(a0,T, NR, min0, max0);

  std::vector<T> ref(NR);
  for(std::size_t i=0; i!=NR; ++i)
  {
    ref[i] = a0[i]*nt2::rec(nt2::oneplus(nt2::sqrt(nt2::oneplus(a0[i]))));
  }

  NT2_COVER_ULP_EQUAL(nt2::tag::sqrt1pm1_, ((T, a0)), ref, ulpd);
}

NT2_TEST_CASE_TPL(sqrt1pm1_1,  NT2_SIMD_REAL_TYPES)
{
  using nt2::unit::args;
  const std::size_t NR = args("samples", NT2_NB_RANDOM_TEST);
  const double ulpd = args("ulpd", 2);

  const T min1 = args("min1", T(0.5));
  const T max1 = args("max1", T(100));
  std::cout << "Argument samples #0 chosen in range: [" << min1 << ",  " << max1 << "]" << std::endl;
  NT2_CREATE_BUF(a0,T, NR, min1, max1);

  std::vector<T> ref(NR);
  for(std::size_t i=0; i!=NR; ++i)
  {
    ref[i] = nt2::minusone(nt2::sqrt(nt2::oneplus(a0[i])));
  }

  NT2_COVER_ULP_EQUAL(nt2::tag::sqrt1pm1_, ((T, a0)), ref, ulpd);

}
