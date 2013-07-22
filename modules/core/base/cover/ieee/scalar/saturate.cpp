//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/ieee/include/functions/saturate.hpp>
#include <vector>

#include <nt2/sdk/unit/tests/cover.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/io.hpp>
#include <nt2/include/functions/abs.hpp>
#include <nt2/include/constants/valmax.hpp>
#include <nt2/include/constants/valmin.hpp>

NT2_TEST_CASE_TPL ( saturate,  NT2_TYPES)
{

  using nt2::saturate;
  using nt2::tag::saturate_;
  nt2::uint32_t NR = NT2_NB_RANDOM_TEST;
  typedef typename nt2::meta::as_<uint16_t> aT;
  std::vector<T> in1(NR);
  std::vector<aT> in2(NR);
  T Mi = nt2::Valmin<T>()/2;
  T Ma = nt2::Valmax<T>()/2;
  nt2::roll(in1, T(Mi), T(Ma));
  std::vector<T> ref(NR);
  for(nt2::uint32_t i=0; i < NR ; ++i)
  {
    ref[i] = (in1[i] >= 0) ? ((in1[i] > nt2::Valmax<uint16_t>()) ? nt2::Valmax<uint16_t>() : in1[i]) : 0;
  }
  NT2_COVER_ULP_EQUAL(saturate_, ((T, in1))((aT, in2)), ref, 0);
}

NT2_TEST_CASE_TPL ( saturatesigned,  NT2_INTEGRAL_SIGNED_TYPES)
{

  using nt2::saturate;
  using nt2::tag::saturate_;
  nt2::uint32_t NR = NT2_NB_RANDOM_TEST;
  typedef typename nt2::meta::as_<int16_t> aT;
  std::vector<T> in1(NR);
  std::vector<aT> in2(NR);
  T Mi = nt2::Valmin<T>()/2;
  T Ma = nt2::Valmax<T>()/2;
  nt2::roll(in1, T(Mi), T(Ma));
  std::vector<T> ref(NR);
  for(nt2::uint32_t i=0; i < NR ; ++i)
  {
    ref[i] = ((in1[i] <= nt2::Valmin<int16_t>()) ?  nt2::Valmin<int16_t>() :
              ((in1[i] > nt2::Valmax<int16_t>()) ? nt2::Valmax<int16_t>() : in1[i]));
  }
  NT2_COVER_ULP_EQUAL(saturate_, ((T, in1))((aT, in2)), ref, 0);
}
NT2_TEST_CASE_TPL ( saturateunsigned,  NT2_UNSIGNED_TYPES)
{

  using nt2::saturate;
  using nt2::tag::saturate_;
  nt2::uint32_t NR = NT2_NB_RANDOM_TEST;
  typedef typename nt2::meta::as_<int16_t> aT;
  std::vector<T> in1(NR);
  std::vector<aT> in2(NR);
  T Mi = nt2::Valmin<T>()/2;
  T Ma = nt2::Valmax<T>()/2;
  nt2::roll(in1, T(Mi), T(Ma));
  std::vector<T> ref(NR);
  for(nt2::uint32_t i=0; i < NR ; ++i)
  {
    ref[i] = ((in1[i] <= 0) ?  nt2::Valmin<int16_t>() :
              ((in1[i] > uint16_t(nt2::Valmax<int16_t>())) ? nt2::Valmax<int16_t>() : in1[i]));
  }
  NT2_COVER_ULP_EQUAL(saturate_, ((T, in1))((aT, in2)), ref, 0);
}
