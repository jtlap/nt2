//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/ieee/include/functions/frac.hpp>
#include <vector>
#include <nt2/sdk/unit/tests.hpp>
#include <nt2/sdk/unit/tests/cover.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/include/constants/valmax.hpp>
#include <nt2/include/constants/valmin.hpp>
#include <nt2/include/constants/zero.hpp>
#include <nt2/include/functions/trunc.hpp>

NT2_TEST_CASE_TPL ( frac,  NT2_REAL_TYPES)
{

  using nt2::frac;
  using nt2::tag::frac_;
  typedef typename nt2::meta::as_integer<T>::type iT;
  nt2::uint32_t NR = NT2_NB_RANDOM_TEST;
  std::vector<T> in1(NR);
  T Mi = nt2::Valmin<T>()/2;
  T Ma = nt2::Valmax<T>()/2;
  nt2::roll(in1, T(Mi), T(Ma));
  std::vector<iT> ref(NR);
  for(nt2::uint32_t i=0; i < NR ; ++i)
  {
    ref[i] = in1[i]-nt2::trunc(in1[i]);
  }
  NT2_COVER_ULP_EQUAL(frac_, ((T, in1)), ref, 0);
}

NT2_TEST_CASE_TPL ( fraci,  NT2_INTEGRAL_TYPES)
{

  using nt2::frac;
  using nt2::tag::frac_;
  typedef typename nt2::meta::as_integer<T>::type iT;
  nt2::uint32_t NR = NT2_NB_RANDOM_TEST;
  std::vector<T> in1(NR);
  T Mi = nt2::Valmin<T>()/2;
  T Ma = nt2::Valmax<T>()/2;
  nt2::roll(in1, T(Mi), T(Ma));
  std::vector<iT> ref(NR);
  for(nt2::uint32_t i=0; i < NR ; ++i)
  {
    ref[i] = nt2::Zero<T>();
  }
  NT2_COVER_ULP_EQUAL(frac_, ((T, in1)), ref, 0);
}
