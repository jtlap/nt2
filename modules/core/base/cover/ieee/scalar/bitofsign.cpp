//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/ieee/include/functions/bitofsign.hpp>
#include <vector>
#include <nt2/include/functions/is_negative.hpp>

#include <nt2/sdk/unit/tests/cover.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/include/constants/valmax.hpp>
#include <nt2/include/constants/valmin.hpp>
#include <nt2/include/constants/zero.hpp>
#include <nt2/include/functions/is_negative.hpp>
#include <nt2/sdk/meta/as_logical.hpp>

NT2_TEST_CASE_TPL ( bitofsign,  NT2_TYPES)
{

  using nt2::bitofsign;
  using nt2::tag::bitofsign_;
  nt2::uint32_t NR = NT2_NB_RANDOM_TEST;
  typedef typename nt2::meta::as_logical<T>::type lT;
  std::vector<T> in1(NR);
  std::vector<T> in2(NR);
  T Mi = nt2::Valmin<T>()/2;
  T Ma = nt2::Valmax<T>()/2;
  nt2::roll(in1, T(Mi), T(Ma));
  std::vector<lT>  ref(NR);
  for(nt2::uint32_t i=0; i < NR ; ++i)
  {
    in2[i] = nt2::bitofsign(in1[i]);
    ref[i] = nt2::is_negative(in1[i]);
  }
  NT2_COVER_ULP_EQUAL(nt2::tag::is_negative_, ((T, in2)), ref, 0);
}


