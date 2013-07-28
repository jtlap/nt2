//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/predicates/include/functions/is_inf.hpp>
#include <vector>
#include <nt2/include/constants/valmin.hpp>
#include <nt2/include/constants/valmax.hpp>
#include <nt2/include/constants/inf.hpp>
#include <nt2/include/functions/abs.hpp>
#include <nt2/sdk/unit/tests/cover.hpp>
#include <nt2/sdk/unit/module.hpp>

NT2_TEST_CASE_TPL ( is_inf,  NT2_REAL_TYPES)
{

  using nt2::is_inf;
  using nt2::tag::is_inf_;
  typedef typename nt2::meta::call<is_inf_(T)>::type r_t;

  nt2::uint32_t NR = NT2_NB_RANDOM_TEST;
  std::vector<T> in1(NR), in2(NR);
  nt2::roll(in1, nt2::Valmin<T>()/2, nt2::Valmax<T>()/2);
  std::vector<r_t>  ref(NR);
  for(nt2::uint32_t i=0; i < NR ; ++i)
  {
    ref[i] = nt2::abs(in1[i]) == nt2::Inf<T>();
  }

  NT2_COVER_ULP_EQUAL(is_inf_, ((T, in1)), ref, 0);
}
NT2_TEST_CASE_TPL ( is_inf2,  NT2_INTEGRAL_TYPES)
{

  using nt2::is_inf;
  using nt2::tag::is_inf_;
  typedef typename nt2::meta::call<is_inf_(T)>::type r_t;

  nt2::uint32_t NR = NT2_NB_RANDOM_TEST;
  std::vector<T> in1(NR), in2(NR);
  nt2::roll(in1, nt2::Valmin<T>()/2, nt2::Valmax<T>()/2);
  std::vector<r_t>  ref(NR);
  for(nt2::uint32_t i=0; i < NR ; ++i)
  {
    ref[i] = false;
  }

  NT2_COVER_ULP_EQUAL(is_inf_, ((T, in1)), ref, 0);
}
