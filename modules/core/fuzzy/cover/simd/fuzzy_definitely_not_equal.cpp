//==============================================================================
//         Copyright 2003 - 2014   LASMEA UMR 6602 CNRS/UBP
//         Copyright 2009 - 2014   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
// cover for functor fuzzy_definitely_not_equal in simd mode
#include <nt2/fuzzy/include/functions/fuzzy_definitely_not_equal.hpp>
#include <boost/simd/sdk/simd/io.hpp>
#include <boost/simd/sdk/simd/native.hpp>
#include <cmath>
#include <iostream>
#include <nt2/sdk/meta/as_integer.hpp>
#include <nt2/sdk/unit/args.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/cover.hpp>
#include <vector>

NT2_TEST_CASE_TPL(fuzzy_definitely_not_equal_0,  NT2_SIMD_REAL_TYPES)
{
  using boost::simd::native;
  typedef BOOST_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef native<T,ext_t>                  vT;

  using nt2::unit::args;
  const std::size_t NR = args("samples", NT2_NB_RANDOM_TEST);
  const double ulpd = args("ulpd", 0.5);

 typedef typename nt2::meta::call<nt2::tag::fuzzy_definitely_not_equal_(T, T, T)>::type r_t;
  const T min0 = args("min0", T(-10));
  const T max0 = args("max0", T(10));
  std::cout << "Argument samples #0 chosen in range: [" << min0 << ",  " << max0 << "]" << std::endl;
  NT2_CREATE_BUF(a0,T, NR, min0, max0);
  const T min1 = args("min1", T(-10));
  const T max1 = args("max1", T(10));
  std::cout << "Argument samples #1 chosen in range: [" << min1 << ",  " << max1 << "]" << std::endl;
  NT2_CREATE_BUF(a1,T, NR, min1, max1);
  const T min2 = args("min2", T(0));
  const T max2 = args("max2", T(10));
  std::cout << "Argument samples #2 chosen in range: [" << min2 << ",  " << max2 << "]" << std::endl;
  NT2_CREATE_BUF(a2,T, NR, min2, max2);

  std::vector<r_t> ref(NR);
  for(std::size_t i=0; i!=NR; ++i)
    ref[i] = nt2::fuzzy_definitely_not_equal(a0[i],a1[i],a2[i]);

  NT2_COVER_ULP_EQUAL(nt2::tag::fuzzy_definitely_not_equal_, ((vT, a0))((vT, a1))((vT, a2)), ref, ulpd);

}
