//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/ieee/include/functions/nextafter.hpp>
#include <vector>

#include <nt2/sdk/unit/tests/cover.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/include/constants/valmax.hpp>
#include <nt2/include/constants/valmin.hpp>
#include <nt2/include/constants/zero.hpp>
#include <nt2/include/functions/trunc.hpp>
#include <nt2/sdk/meta/as_integer.hpp>

static inline double standardnextafter(const double & a0,  const double& a1)
{
  return ::nextafter(a0, a1);
}

static inline float standardnextafter(const float & a0,  const float& a1)
{
  return ::nextafterf(a0, a1);
}


NT2_TEST_CASE_TPL ( nextafter,  NT2_REAL_TYPES)
{

  using nt2::nextafter;
  using nt2::tag::nextafter_;
  typedef typename nt2::meta::as_integer<T>::type iT;
  nt2::uint32_t NR = NT2_NB_RANDOM_TEST;
  std::vector<T> in1(NR), in2(NR);
  T Mi = nt2::Valmin<T>()/2;
  T Ma = nt2::Valmax<T>()/2;
  nt2::roll(in1, T(Mi), T(Ma));
  nt2::roll(in2, T(Mi), T(Ma));
  std::vector<iT> ref(NR);
  for(nt2::uint32_t i=0; i < NR ; ++i)
  {
    ref[i] = standardnextafter(in1[i], in2[i]);
  }
  NT2_COVER_ULP_EQUAL(nextafter_, ((T, in1))((T, in2)), ref, 0);
}
