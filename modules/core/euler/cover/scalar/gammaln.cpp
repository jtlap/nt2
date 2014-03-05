//==============================================================================
//         Copyright 2003 - 2014   LASMEA UMR 6602 CNRS/UBP
//         Copyright 2009 - 2014   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
// cover for functor gammaln in scalar mode
#include <nt2/euler/include/functions/gammaln.hpp>
#include <boost/simd/sdk/simd/io.hpp>
#include <cmath>
#include <iostream>
#include <nt2/include/functions/abs.hpp>
#include <nt2/sdk/meta/as_integer.hpp>
#include <nt2/sdk/unit/args.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/cover.hpp>
#include <vector>

extern "C" {long double cephes_lgaml(long double);}
//extern "C" {long double cephes_logl  (long double);}

NT2_TEST_CASE_TPL(gammaln_0,  NT2_SIMD_REAL_TYPES)
{
  using nt2::unit::args;
  const std::size_t NR = args("samples", NT2_NB_RANDOM_TEST);
  const double ulpd = args("ulpd", 1.5);

  typedef typename nt2::meta::as_integer<T>::type iT;
  const T min = args("min", T(0));
  const T max = args("max", T(10));
  std::cout << "Argument samples #0 chosen in range: [" << min << ",  " << max << "]" << std::endl;
  NT2_CREATE_BUF(a0,T, NR, min, max);

  std::vector<T> ref(NR);
  for(std::size_t i=0; i!=NR; ++i)
    ref[i] = ::cephes_lgaml(a0[i]); //cephes_logl(std::abs(cephes_gammal(a0[i])));

  NT2_COVER_ULP_EQUAL(nt2::tag::gammaln_, ((T, a0)), ref, ulpd);

}
