//==============================================================================
//         Copyright 2003 - 2014   LASMEA UMR 6602 CNRS/UBP
//         Copyright 2009 - 2014   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
// cover for functor yni in simd mode
#include <nt2/bessel/include/functions/yni.hpp>

#include <boost/simd/sdk/simd/io.hpp>
#include <boost/simd/sdk/simd/native.hpp>
#include <cmath>
#include <iostream>
#include <nt2/sdk/meta/as_integer.hpp>
#include <nt2/sdk/unit/args.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/cover.hpp>
#include <vector>
extern "C" {long double cephes_ynl(int,long double);}

NT2_TEST_CASE_TPL(yni_0,  NT2_SIMD_REAL_TYPES)
{
  using boost::simd::native;
  typedef BOOST_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef native<T,ext_t>                  vT;

  using nt2::unit::args;
  const std::size_t NR = args("samples", NT2_NB_RANDOM_TEST);
  const double ulpd = args("ulpd",  4096.0);

  typedef typename nt2::meta::as_integer<T>::type iT;
  const iT min0 = args("min0", 1);
  const iT max0 = args("max0", 10);
  std::cout << "Argument samples randomly chosen in [" << min0 << ",  " << max0 << "]" << std::endl;
  NT2_CREATE_BUF(a0,iT, NR,min0, max0);
  const T min1 = args("min1", T(0));
  const T max1 = args("max1", T(10));
  std::cout << "Argument samples randomly chosen in [" << min1 << ",  " << max1 << "]" << std::endl;
  NT2_CREATE_BUF(a1,T, NR,min1, max1);

  std::vector<T> ref(NR);
  for(std::size_t i=0; i!=NR; ++i)
    ref[i] = nt2::yni(a0[i], a1[i]);

  NT2_COVER_ULP_EQUAL(nt2::tag::yni_, ((iT, a0))((vT, a1)), ref, ulpd);

}
