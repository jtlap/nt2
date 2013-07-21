//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/boolean/include/functions/if_one_else_zero.hpp>
#include <vector>

#include <nt2/sdk/unit/tests/cover.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/include/constants/valmax.hpp>
#include <nt2/include/constants/valmin.hpp>
#include <nt2/include/functions/min.hpp>
#include <nt2/include/functions/max.hpp>

NT2_TEST_CASE_TPL ( if_one_else_zero,  NT2_SIGNED_TYPES)
{

  using nt2::if_one_else_zero;
  using nt2::tag::if_one_else_zero_;
  typedef typename nt2::meta::call<if_one_else_zero_(T)>::type r_t;

  nt2::uint32_t NR = NT2_NB_RANDOM_TEST;
  std::vector<T> in1(NR);
  int64_t Mi = nt2::max(int64_t(nt2::Valmin<T>()), int64_t(-10000));
  int64_t Ma = nt2::min(int64_t(nt2::Valmax<T>()), int64_t(10000));
  nt2::roll(in1, T(Mi),T(Ma));
  std::vector<r_t>  ref(NR);
  for(nt2::uint32_t i=0; i < NR ; ++i)
  {
    ref[i] = r_t(in1[i]!=0);
  }

  NT2_COVER_ULP_EQUAL(if_one_else_zero_, ((T, in1)), ref, 0);
}

NT2_TEST_CASE_TPL ( if_one_else_zero_unsigned_int__1_0,  NT2_UNSIGNED_TYPES)
{


  using nt2::if_one_else_zero;
  using nt2::tag::if_one_else_zero_;
  typedef typename nt2::meta::call<if_one_else_zero_(T)>::type r_t;

  nt2::uint32_t NR = NT2_NB_RANDOM_TEST;
  std::vector<T> in1(NR);
  uint64_t M = nt2::min(uint64_t(nt2::Valmax<T>()), uint64_t(10000));
  nt2::roll(in1, T(0), T(M));
  std::vector<r_t>  ref(NR);
  for(nt2::uint32_t i=0; i < NR ; ++i)
  {
    ref[i] = r_t(in1[i]!=0);
  }

  NT2_COVER_ULP_EQUAL(if_one_else_zero_, ((T, in1)), ref, 0);
}
