//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/boolean/include/functions/selsub.hpp>
#include <vector>
#include <nt2/sdk/meta/as_logical.hpp>

#include <nt2/sdk/unit/tests/cover.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/include/constants/valmax.hpp>
#include <nt2/include/constants/valmin.hpp>
#include <nt2/include/constants/zero.hpp>
#include <nt2/include/functions/min.hpp>
#include <nt2/include/functions/max.hpp>
#include <nt2/include/functions/is_odd.hpp>

NT2_TEST_CASE_TPL ( selsub_signed,  NT2_TYPES)
{

  using nt2::selsub;
  using nt2::tag::selsub_;
  typedef typename nt2::meta::as_logical<T>::type lT;

  nt2::uint32_t NR = NT2_NB_RANDOM_TEST;
  std::vector<T> in1(NR), in0(NR);
  std::vector<lT> in2(NR);
  int64_t Mi = nt2::Valmin<T>()/T(2);
  int64_t Ma = nt2::Valmax<T>()/T(2);
  nt2::roll(in1,T(Mi),T(Ma));
  nt2::roll(in0,T(Mi),T(Ma));
  std::vector<T>  ref(NR);
  for(nt2::uint32_t i=0; i < NR ; ++i)
  {
    in2[i] = in0[i] <  in1[i];
    ref[i] = in2[i] ? in1[i]-in0[i] : in1[i];
  }

  NT2_COVER_ULP_EQUAL(selsub_, ((lT, in2))((T, in1))((T, in0)), ref, 0);
}

