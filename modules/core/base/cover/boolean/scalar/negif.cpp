//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/boolean/include/functions/negif.hpp>
#include <vector>
#include <nt2/sdk/meta/as_logical.hpp>

#include <nt2/sdk/unit/tests/cover.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/include/constants/valmax.hpp>
#include <nt2/include/constants/valmin.hpp>
#include <nt2/include/functions/min.hpp>
#include <nt2/include/functions/max.hpp>

NT2_TEST_CASE_TPL ( negif,  NT2_SIGNED_TYPES)
{

  using nt2::negif;
  using nt2::tag::negif_;
  typedef typename nt2::meta::as_logical<T>::type lT;
  nt2::uint32_t NR = NT2_NB_RANDOM_TEST;
  std::vector<T> in1(NR);
  std::vector<lT> in2(NR);
  int64_t Mi = nt2::max(int64_t(nt2::Valmin<T>()), int64_t(-10000));
  int64_t Ma = nt2::min(int64_t(nt2::Valmax<T>()), int64_t(10000));
  nt2::roll(in1, T(Mi), T(Ma));
  std::vector<T>  ref(NR), out(NR);
  for(nt2::uint32_t i=0; i < NR ; ++i)
  {
    ref[i] = nt2::abs(in1[i]);
    in2[i] = in1[i] < 0;
  }
  NT2_COVER_ULP_EQUAL(negif_, ((lT, in2))((T, in1)), ref, 0);
}

