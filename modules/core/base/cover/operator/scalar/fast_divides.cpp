//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/operator/include/functions/fast_divides.hpp>
#include <nt2/include/constants/valmin.hpp>
#include <nt2/include/constants/valmax.hpp>
#include <vector>

#include <nt2/sdk/unit/tests/cover.hpp>
#include <nt2/sdk/unit/module.hpp>

NT2_TEST_CASE_TPL( fast_divides,  NT2_REAL_TYPES)
{
  using nt2::fast_divides;
  using nt2::tag::fast_divides_;

  nt2::uint32_t NR = NT2_NB_RANDOM_TEST;
  std::vector<T> in1(NR), in2(NR);
  std::vector<T> ref(NR);

  nt2::roll(in1, T(-1e19), T(1e19));
  nt2::roll(in2, T(-1e19), T(1e19));
  for(nt2::uint32_t i=0; i < NR ; ++i)
  {
    in2[i] = (in2[i]) ? in2[i] : 1;
    ref[i] = in1[i]/in2[i];
  }

  NT2_COVER_ULP_EQUAL(fast_divides_, ((T, in1))((T, in2)), ref, 1);
}
