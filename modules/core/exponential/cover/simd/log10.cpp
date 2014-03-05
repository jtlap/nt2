//==============================================================================
//         Copyright 2003 - 2014   LASMEA UMR 6602 CNRS/UBP
//         Copyright 2009 - 2014   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
// cover for functor log10 in simd mode
#include <nt2/exponential/include/functions/log10.hpp>
#include <boost/simd/sdk/simd/io.hpp>
#include <boost/simd/sdk/simd/native.hpp>
#include <cmath>
#include <iostream>
#include <nt2/sdk/unit/args.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/cover.hpp>
#include <vector>

NT2_TEST_CASE_TPL(log10_0,  NT2_SIMD_REAL_TYPES)
{
  using boost::simd::native;
  typedef BOOST_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef native<T,ext_t>                  vT;

  using nt2::unit::args;
  const std::size_t NR = args("samples", NT2_NB_RANDOM_TEST);
  const double ulpd = args("ulpd",  1);

  const T min = args("min", T(0));
  const T max = args("max", T(100));
  std::cout << "Argument samples #0 chosen in range: [" << min << ",  " << max << "]" << std::endl;
  NT2_CREATE_BUF(a0,T, NR, min, max);

  std::vector<T> ref(NR);
  for(std::size_t i=0; i!=NR; ++i)
    ref[i] = T(nt2::log10(a0[i]));

  NT2_COVER_ULP_EQUAL(nt2::tag::log10_, ((vT, a0)), ref, ulpd);

}
