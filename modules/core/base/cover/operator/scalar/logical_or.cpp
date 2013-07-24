//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/operator/include/functions/logical_or.hpp>
#include <vector>
#include <nt2/sdk/meta/as_logical.hpp>

#include <nt2/sdk/unit/tests/cover.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/include/constants/valmax.hpp>
#include <nt2/include/constants/valmin.hpp>
#include <nt2/include/functions/is_odd.hpp>

NT2_TEST_CASE_TPL ( logical_or,  NT2_TYPES)
{

  using nt2::logical_or;
  using nt2::tag::logical_or_;
  typedef typename nt2::meta::as_logical<T>::type lT;

  nt2::uint32_t NR = NT2_NB_RANDOM_TEST;
  std::vector<T> in0(NR), in1(NR), in2(NR);
  std::vector<lT> in3(NR), in4(NR);
  int64_t Mi = nt2::Valmin<T>();
  int64_t Ma = nt2::Valmax<T>();
  nt2::roll(in2,T(Mi),T(Ma));
  nt2::roll(in1,T(Mi),T(Ma));
  nt2::roll(in0,T(Mi),T(Ma));
  std::vector<lT>  ref(NR);
  for(nt2::uint32_t i=0; i < NR ; ++i)
  {
    in3[i] = in0[i] > in1[i];
    in4[i] = in0[i] > in2[i];
    ref[i] = in3[i] || in4[i];
  }

  NT2_COVER_ULP_EQUAL(logical_or_, ((lT, in3))((lT, in4)), ref, 0);
}

