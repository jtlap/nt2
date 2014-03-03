//==============================================================================
//         Copyright 2003 - 2014   LASMEA UMR 6602 CNRS/UBP
//         Copyright 2009 - 2014   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
// cover for functor ellie in scalar mode
#include <nt2/elliptic/include/functions/ellie.hpp>
#include <boost/simd/sdk/simd/io.hpp>
#include <cmath>
#include <iostream>
#include <nt2/include/constants/pi.hpp>
#include <nt2/sdk/meta/as_integer.hpp>
#include <nt2/sdk/unit/args.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/cover.hpp>
#include <vector>

extern "C" {long double cephes_elliel(long double,long double);}

NT2_TEST_CASE_TPL(ellie_0,  NT2_SIMD_REAL_TYPES)
{
  using nt2::unit::args;
  const std::size_t NR = args("samples", NT2_NB_RANDOM_TEST);
  const double ulpd = args("ulpd", 3);

  typedef typename nt2::meta::as_integer<T>::type iT;
  const T min0 = args("min0", T(0));
  const T max0 = args("max0", T(1));
  std::cout << "Argument samples #0 chosen in range: [" << min0 << ",  " << max0 << "]" << std::endl;
  NT2_CREATE_BUF(a0,T, NR, min0, max0);
  const T min1 = args("min1", T(0));
  const T max1 = args("max1", nt2::Pi<T>()/T(2));
  std::cout << "Argument samples #1 chosen in range: [" << min1 << ",  " << max1 << "]" << std::endl;
  NT2_CREATE_BUF(a1,T, NR, min1, max1);

  std::vector<T> ref(NR);
  for(std::size_t i=0; i!=NR; ++i)
    ref[i] = ::cephes_elliel(a0[i],a1[i]);

  NT2_COVER_ULP_EQUAL(nt2::tag::ellie_, ((T, a0))((T, a1)), ref, ulpd);

}
