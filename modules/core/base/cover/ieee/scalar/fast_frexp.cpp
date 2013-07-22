//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
//////////////////////////////////////////////////////////////////////////////
// cover test behavior of arithmetic components in scalar mode
//////////////////////////////////////////////////////////////////////////////

#include <nt2/ieee/include/functions/fast_frexp.hpp>
#include <boost/fusion/include/std_pair.hpp>
#include <nt2/include/constants/valmin.hpp>
#include <nt2/include/constants/valmax.hpp>
#include <nt2/include/functions/mantissa.hpp>
#include <nt2/include/functions/exponent.hpp>

#include <nt2/sdk/unit/tests/cover.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <vector>

NT2_TEST_CASE_TPL ( fast_frexp_real__1_0_1,  NT2_REAL_TYPES)
{

  using nt2::fast_frexp;
  using nt2::tag::fast_frexp_;
  typedef typename nt2::meta::call<fast_frexp_(T)>::type r_t;

  nt2::uint32_t NR = NT2_NB_RANDOM_TEST;
  std::vector<T> in1(NR);
  std::vector<r_t> ref(NR);
  nt2::roll(in1, nt2::Valmin<T>()/2, nt2::Valmax<T>()/2);
  for(nt2::uint32_t i=0; i < NR ; ++i)
  {
    ref[i].first = nt2::mantissa(in1[i])/2;
    ref[i].second = nt2::exponent(in1[i])+1;
  }
  NT2_COVER_ULP_EQUAL(fast_frexp_, ((T, in1)), ref, 0);
}

