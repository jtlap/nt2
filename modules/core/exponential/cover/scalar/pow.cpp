//==============================================================================
//         Copyright 2003 - 2014   LASMEA UMR 6602 CNRS/UBP
//         Copyright 2009 - 2014   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
// cover for functor pow in scalar mode
#include <nt2/exponential/include/functions/pow.hpp>
#include <boost/simd/sdk/simd/io.hpp>
#include <cmath>
#include <iostream>
#include <nt2/sdk/meta/as_integer.hpp>
#include <nt2/sdk/unit/args.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/cover.hpp>
#include <vector>

extern "C" { long double cephes_powil(long double,int); }
extern "C" { long double cephes_powl(long double,long double); }

NT2_TEST_CASE_TPL(pow_1,  NT2_REAL_TYPES)
{
  using nt2::unit::args;
  const std::size_t NR = args("samples", NT2_NB_RANDOM_TEST);
  const double ulpd = args("ulpd", 2);

  const T min1_0 = args("min1_0", T(0));
  const T max1_0 = args("max1_0", T(100));
  std::cout << "Argument samples #0 chosen in range: [" << min1_0 << ",  " << max1_0 << "]" << std::endl;
  NT2_CREATE_BUF(a0,T, NR, min1_0, max1_0);
  const T min1_1 = args("min1_1", T(-10));
  const T max1_1 = args("max1_1", T(10));
  std::cout << "Argument samples #1 chosen in range: [" << min1_1 << ",  " << max1_1 << "]" << std::endl;
  NT2_CREATE_BUF(a1,T, NR, min1_1, max1_1);

  std::vector<T> ref(NR);
  for(std::size_t i=0; i!=NR; ++i)
    ref[i] = ::cephes_powl(a0[i],a1[i]);

  NT2_COVER_ULP_EQUAL(nt2::tag::pow_, ((T, a0))((T, a1)), ref, ulpd);
}

NT2_TEST_CASE_TPL(pow_2,  NT2_REAL_TYPES)
{
  using nt2::unit::args;
  const std::size_t NR = args("samples", NT2_NB_RANDOM_TEST);
  const double ulpd = args("ulpd", 2);

  typedef typename nt2::meta::as_integer<T>::type iT;
  const T min1_0 = args("min1_0", T(0));
  const T max1_0 = args("max1_0", T(100));
  std::cout << "Argument samples #0 chosen in range: [" << min1_0 << ",  " << max1_0 << "]" << std::endl;
  NT2_CREATE_BUF(a0,T, NR, min1_0, max1_0);
  const iT min1_1 = args("min1_1", iT(-10));
  const iT max1_1 = args("max1_1", iT(10));
  std::cout << "Argument samples #1 chosen in range: [" << min1_1 << ",  " << max1_1 << "]" << std::endl;
  NT2_CREATE_BUF(a1,iT, NR, min1_1, max1_1);

  std::vector<T> ref(NR);
  for(std::size_t i=0; i!=NR; ++i)
    ref[i] = ::cephes_powl(a0[i],(long double)a1[i]);

  NT2_COVER_ULP_EQUAL(nt2::tag::pow_, ((T, a0))((iT, a1)), ref, ulpd);
}
