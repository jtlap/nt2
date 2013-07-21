//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/bitwise/include/functions/rshr.hpp>
#include <vector>
#include <nt2/include/constants/valmin.hpp>
#include <nt2/include/constants/valmax.hpp>
#include <nt2/include/functions/shr.hpp>
#include <nt2/include/functions/shift_left.hpp>
#include <nt2/sdk/unit/tests/cover.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/meta/as_integer.hpp>


NT2_TEST_CASE_TPL ( rshr,  NT2_INTEGRAL_TYPES)
{

  using nt2::rshr;
  using nt2::tag::rshr_;
  typedef typename nt2::meta::as_integer<T, signed>::type iT;
  typedef typename nt2::meta::call<rshr_(T, iT)>::type r_t;

  nt2::uint32_t NR = NT2_NB_RANDOM_TEST;
  std::vector<T> in1(NR);
  std::vector<iT> in2(NR);
  nt2::roll(in1,  nt2::Valmin<T>(), nt2::Valmax<T>());
  int S = sizeof(T)*8-1;
  nt2::roll(in2,  -S, S);
  std::vector<r_t>  ref(NR);
  for(nt2::uint32_t i=0; i < NR ; ++i)
  {
    ref[i] =  (in2[i] >= 0) ? nt2::shr(in1[i], in2[i]) : nt2::shl(in1[i], -in2[i]);
  }

  NT2_COVER_ULP_EQUAL(nt2::tag::rshr_, ((T, in1))((iT, in2)), ref, 0);
}
