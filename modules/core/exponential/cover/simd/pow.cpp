//==============================================================================
//         Copyright 2003 - 2014   LASMEA UMR 6602 CNRS/UBP
//         Copyright 2009 - 2014   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
// cover for functor pow in simd mode
#include <nt2/exponential/include/functions/pow.hpp>
#include <boost/simd/sdk/simd/io.hpp>
#include <boost/simd/sdk/simd/native.hpp>
#include <cmath>
#include <iostream>
#include <nt2/sdk/meta/as_integer.hpp>
#include <nt2/sdk/unit/args.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/cover.hpp>
#include <vector>
extern "C" { long double cephes_powl(long double,long double); }

NT2_TEST_CASE_TPL(pow_1,  NT2_SIMD_REAL_TYPES)
{
  using boost::simd::native;
  typedef BOOST_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef native<T,ext_t>                  vT;

  using nt2::unit::args;
  const std::size_t NR = args("samples", NT2_NB_RANDOM_TEST);
  const double ulpd = args("ulpd",  12.5);

  typedef typename nt2::meta::as_integer<vT>::type ivT;
  typedef typename nt2::meta::as_integer<T>::type iT;
  const T min2_0 = args("min2_0", T(0));
  const T max2_0 = args("max2_0", T(100));
  std::cout << "Argument samples #0 chosen in range: [" << min2_0 << ",  " << max2_0 << "]" << std::endl;
  NT2_CREATE_BUF(a0,T, NR, min2_0, max2_0);
  const iT min2_1 = args("min2_1", iT(-10));
  const iT max2_1 = args("max2_1", iT(10));
  std::cout << "Argument samples #1 chosen in range: [" << min2_1 << ",  " << max2_1 << "]" << std::endl;
  NT2_CREATE_BUF(a1,iT, NR, min2_1, max2_1);

  std::vector<T> ref(NR);
  for(std::size_t i=0; i!=NR; ++i)
    ref[i] = T(::cephes_powl(a0[i],a1[i]));

  NT2_COVER_ULP_EQUAL(nt2::tag::pow_, ((vT, a0))((ivT, a1)), ref, ulpd);

}

NT2_TEST_CASE_TPL(pow_2,  NT2_SIMD_REAL_TYPES)
{
  using boost::simd::native;
  typedef BOOST_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef native<T,ext_t>                  vT;

  using nt2::unit::args;
  const std::size_t NR = args("samples", NT2_NB_RANDOM_TEST);
  const double ulpd = args("ulpd", 2);

  typedef typename nt2::meta::as_integer<T>::type iT;
  typedef typename nt2::meta::as_integer<vT>::type viT;
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

  NT2_COVER_ULP_EQUAL(nt2::tag::pow_, ((vT, a0))((viT, a1)), ref, ulpd);
}


