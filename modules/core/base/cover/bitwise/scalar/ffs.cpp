//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/bitwise/include/functions/ffs.hpp>
#include <vector>
#include <nt2/include/constants/valmin.hpp>
#include <nt2/include/constants/valmax.hpp>
#include <nt2/include/functions/shift_left.hpp>
#include <nt2/sdk/unit/tests/cover.hpp>
#include <nt2/sdk/unit/module.hpp>

NT2_TEST_CASE_TPL ( ffs_real__1_0,  NT2_INTEGRAL_TYPES)
{

  using nt2::ffs;
  using nt2::tag::ffs_;
  typedef typename nt2::meta::call<ffs_(T)>::type r_t;

  nt2::uint32_t NR = NT2_NB_RANDOM_TEST;
  std::vector<T> in1(NR);
  nt2::roll(in1, 1, nt2::Valmax<T>()/2);
  std::vector<r_t>  ref(NR);
  for(nt2::uint32_t i=0; i < NR ; ++i)
  {
    ref[i] =  ffs(nt2::shl(in1[i], 1))-1;
  }

  NT2_COVER_ULP_EQUAL(ffs_, ((T, in1)), ref, 0);
}

