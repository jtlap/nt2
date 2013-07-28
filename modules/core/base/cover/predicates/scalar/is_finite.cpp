//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/predicates/include/functions/is_finite.hpp>
#include <vector>
#include <nt2/include/constants/valmin.hpp>
#include <nt2/include/constants/valmax.hpp>
#include <nt2/include/constants/one.hpp>
#include <nt2/include/functions/is_invalid.hpp>
#include <nt2/sdk/unit/tests/cover.hpp>
#include <nt2/sdk/unit/module.hpp>

NT2_TEST_CASE_TPL ( is_finite,  NT2_REAL_TYPES)
{

  using nt2::is_finite;
  using nt2::tag::is_finite_;
  typedef typename nt2::meta::call<is_finite_(T)>::type r_t;

  nt2::uint32_t NR = NT2_NB_RANDOM_TEST;
  std::vector<T> in1(NR), in2(NR);
  nt2::roll(in1, nt2::Valmin<T>()/2, nt2::Valmax<T>()/2);
  std::vector<r_t>  ref(NR);
  for(nt2::uint32_t i=0; i < NR ; ++i)
  {
    ref[i] = !nt2::is_invalid(in1[i]);
  }

  NT2_COVER_ULP_EQUAL(is_finite_, ((T, in1)), ref, 0);
}

NT2_TEST_CASE_TPL ( is_finitei,  NT2_INTEGRAL_TYPES)
{

  using nt2::is_finite;
  using nt2::tag::is_finite_;
  typedef typename nt2::meta::call<is_finite_(T)>::type r_t;

  nt2::uint32_t NR = NT2_NB_RANDOM_TEST;
  std::vector<T> in1(NR), in2(NR);
  nt2::roll(in1, nt2::Valmin<T>()/2, nt2::Valmax<T>()/2);
  std::vector<r_t>  ref(NR);
  for(nt2::uint32_t i=0; i < NR ; ++i)
  {
    ref[i] = true;
  }

  NT2_COVER_ULP_EQUAL(is_finite_, ((T, in1)), ref, 0);
}
