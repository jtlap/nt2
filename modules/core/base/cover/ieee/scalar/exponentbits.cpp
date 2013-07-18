//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/ieee/include/functions/exponentbits.hpp>
#include <vector>
#include <nt2/include/functions/fast_ldexp.hpp>
#include <nt2/include/functions/exponent.hpp>
#include <nt2/include/functions/bits.hpp>
#include <nt2/sdk/unit/tests.hpp>
#include <nt2/sdk/unit/tests/cover.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/include/constants/valmax.hpp>
#include <nt2/include/constants/valmin.hpp>
#include <nt2/include/constants/zero.hpp>
#include <nt2/include/functions/min.hpp>
#include <nt2/include/functions/max.hpp>
NT2_TEST_CASE_TPL ( exponentbits,  NT2_REAL_TYPES)
{

  using nt2::exponentbits;
  using nt2::tag::exponentbits_;
  typedef typename nt2::meta::call<exponentbits_(T)>::type r_t;
  nt2::uint32_t NR = NT2_NB_RANDOM_TEST;
  std::vector<T> in1(NR);
  std::vector<r_t> ref(NR);
  T Mi = nt2::Valmin<T>()/2;
  T Ma = nt2::Valmax<T>()/2;
  nt2::roll(in1, T(Mi), T(Ma));
  for(nt2::uint32_t i=0; i < NR ; ++i)
  {
   ref[i] = r_t(nt2::bits(nt2::fast_ldexp(nt2::One<T>(),nt2::exponent(in1[i]))));
  }
  NT2_COVER_ULP_EQUAL(exponentbits_, ((T, in1)), ref, 0);
}
