//==============================================================================
//         Copyright 2003 - 2014   LASMEA UMR 6602 CNRS/UBP
//         Copyright 2009 - 2014   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
// cover for functor fuzzy_definitely_less in scalar mode
#include <nt2/fuzzy/include/functions/fuzzy_definitely_less.hpp>
#include <cmath>
#include <iostream>
#include <nt2/sdk/meta/as_integer.hpp>
#include <nt2/sdk/unit/args.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/cover.hpp>
#include <vector>

NT2_TEST_CASE_TPL(fuzzy_definitely_less_2,  NT2_REAL_TYPES)
{
  using nt2::unit::args;
  const std::size_t NR = args("samples", NT2_NB_RANDOM_TEST);
  const double ulpd = args("ulpd", 0.5);

  typedef typename nt2::meta::call<nt2::tag::fuzzy_definitely_less_(T, T, T)>::type r_t;
  const T min2_0 = args("min2_0", T(0));
  const T max2_0 = args("max2_0", T(10));
  std::cout << "Argument samples #0 chosen in range: [" << min2_0 << ",  " << max2_0 << "]" << std::endl;
  NT2_CREATE_BUF(a0,T, NR, min2_0, max2_0);
  const T min2_1 = args("min2_1", T(0));
  const T max2_1 = args("max2_1", T(10));
  std::cout << "Argument samples #1 chosen in range: [" << min2_1 << ",  " << max2_1 << "]" << std::endl;
  NT2_CREATE_BUF(a1,T, NR, min2_1, max2_1);
  const T min2_2 = args("min2_2", T(0));
  const T max2_2 = args("max2_2", T(10));
  std::cout << "Argument samples #2 chosen in range: [" << min2_2 << ",  " << max2_2 << "]" << std::endl;
  NT2_CREATE_BUF(a2,T, NR, min2_2, max2_2);

  std::vector<r_t> ref(NR);
  for(std::size_t i=0; i!=NR; ++i)
    ref[i] = nt2::fuzzy_definitely_less(a0[i],a1[i],a2[i]);

  NT2_COVER_ULP_EQUAL(nt2::tag::fuzzy_definitely_less_, ((T, a0))((T, a1))((T, a2)), ref, ulpd);

}
