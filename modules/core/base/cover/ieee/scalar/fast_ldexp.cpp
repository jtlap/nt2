//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/ieee/include/functions/fast_ldexp.hpp>
#include <vector>
#include <nt2/include/functions/bitofsign.hpp>
#include <nt2/sdk/unit/tests.hpp>
#include <nt2/sdk/unit/tests/cover.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/include/constants/valmax.hpp>
#include <nt2/include/constants/valmin.hpp>
#include <nt2/include/constants/maxexponent.hpp>
#include <nt2/include/constants/one.hpp>
#include <nt2/include/constants/mone.hpp>
#include <nt2/include/constants/zero.hpp>
#include <nt2/sdk/meta/as_integer.hpp>

NT2_TEST_CASE_TPL ( fast_ldexp,  NT2_REAL_TYPES)
{

  using nt2::fast_ldexp;
  using nt2::tag::fast_ldexp_;
  nt2::uint32_t NR = NT2_NB_RANDOM_TEST;
  typedef typename nt2::meta::as_integer<T>::type iT;
  std::vector<T> in1(NR);
  std::vector<iT> in2(NR);
  T Mi = nt2::Mone<T>();
  T Ma = nt2::One<T>();
  iT iMi = -nt2::Maxexponent<T>()/2;
  iT iMa =  nt2::Maxexponent<T>()/2;
  nt2::roll(in1, Mi, Ma);
  nt2::roll(in2, iMi, iMa);
  std::vector<T>  ref(NR);
  for(nt2::uint32_t i=0; i < NR ; ++i)
  {
    ref[i] = in1[i]*exp2(in2[i]);
  }
  NT2_COVER_ULP_EQUAL(nt2::tag::fast_ldexp_, ((T, in1))((iT, in2)), ref, 0);
}

