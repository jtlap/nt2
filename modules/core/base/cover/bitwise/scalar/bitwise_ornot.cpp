//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#define NT2_UNIT_MODULE "nt2 bitwise toolbox - bitwise_ornot/scalar Mode"

//////////////////////////////////////////////////////////////////////////////
// cover test behavior of bitwise components in scalar mode
//////////////////////////////////////////////////////////////////////////////

#include <nt2/bitwise/include/functions/bitwise_ornot.hpp>
#include <vector>
#include <nt2/sdk/meta/as_integer.hpp>
#include <nt2/include/constants/valmin.hpp>
#include <nt2/include/constants/valmax.hpp>
#include <nt2/sdk/unit/tests.hpp>
#include <nt2/sdk/unit/tests/ulp.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/include/functions/bitwise_cast.hpp>

NT2_TEST_CASE_TPL ( bitwise_ornot,  NT2_INTEGRAL_TYPES)
{

  using nt2::bitwise_ornot;
  using nt2::tag::bitwise_ornot_;
  typedef typename nt2::meta::call<bitwise_ornot_(T, T)>::type r_t;
  typedef typename nt2::meta::as_integer<T, unsigned>::type uiT;

  nt2::uint32_t NR = NT2_NB_RANDOM_TEST;
  std::vector<T> in1(NR), in2(NR);
  nt2::roll(in1, nt2::Valmin<T>()/2, nt2::Valmax<T>()/2);
  nt2::roll(in2, nt2::Valmin<T>()/2, nt2::Valmax<T>()/2);
  std::vector<r_t>  ref(NR);
  for(nt2::uint32_t i=0; i < NR ; ++i)
  {
    ref[i] = in1[i]|~in2[i];
  }

  NT2_COVER_ULP_EQUAL(bitwise_ornot_, ((T, in1))((T, in2)), ref, 0);
}
