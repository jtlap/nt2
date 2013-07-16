//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/ieee/include/functions/copysign.hpp>
#include <vector>
#include <nt2/include/functions/bitofsign.hpp>
#include <nt2/sdk/unit/tests.hpp>
#include <nt2/sdk/unit/tests/cover.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/include/constants/valmax.hpp>
#include <nt2/include/constants/valmin.hpp>
#include <nt2/include/constants/zero.hpp>
#include <nt2/include/functions/is_negative.hpp>
#include <nt2/sdk/meta/as_logical.hpp>
#include <iostream>

NT2_TEST_CASE_TPL ( copysign,  NT2_REAL_TYPES)
{

  using nt2::copysign;
  using nt2::tag::copysign_;
  nt2::uint32_t NR = NT2_NB_RANDOM_TEST*100;
  typedef typename nt2::meta::as_logical<T>::type lT;
  std::vector<T> in1(NR);
  std::vector<T> in2(NR), in3(NR);
  int64_t Mi = nt2::Valmin<T>();
  int64_t Ma = nt2::Valmax<T>();
  nt2::roll(in1, T(Mi), T(Ma));
  nt2::roll(in2, T(Mi), T(Ma));
  std::vector<T>  ref(NR);
  for(nt2::uint32_t i=0; i < NR ; ++i)
  {
    in3[i] = nt2::copysign(in2[i], in1[i]);
    ref[i] = nt2::bitofsign(in1[i]);
  }
  NT2_COVER_ULP_EQUAL(nt2::tag::bitofsign_, ((T, in3)), ref, 0);
}

NT2_TEST_CASE_TPL ( copysignint,  NT2_INTEGRAL_TYPES)
{

  using nt2::copysign;
  using nt2::tag::copysign_;
  nt2::uint32_t NR = NT2_NB_RANDOM_TEST;
  typedef typename nt2::meta::as_logical<T>::type lT;
  std::vector<T> in1(NR);
  std::vector<T> in2(NR), in3(NR);
  int64_t Mi = nt2::Valmin<T>();
  int64_t Ma = nt2::Valmax<T>();
  nt2::roll(in1, T(Mi), T(Ma));
  nt2::roll(in2, T(Mi), T(Ma));
  std::vector<T>  ref(NR);
  for(nt2::uint32_t i=0; i < NR ; ++i)
  {
    in3[i] = nt2::copysign(in2[i], in1[i]);
    ref[i] = (in2[i] == 0) ? 0 : nt2::bitofsign(in1[i]);
  }
  NT2_COVER_ULP_EQUAL(nt2::tag::bitofsign_, ((T, in3)), ref, 0);
}
