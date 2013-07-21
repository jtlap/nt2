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

#include <nt2/bitwise/include/functions/bitwise_select.hpp>
#include <boost/simd/sdk/simd/io.hpp>
#include <vector>
#include <nt2/include/constants/valmin.hpp>
#include <nt2/include/constants/valmax.hpp>


#include <nt2/sdk/unit/tests/cover.hpp>
#include <nt2/sdk/unit/tests/ulp.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>



NT2_TEST_CASE_TPL ( bitwise_select_real__1_0_2,  NT2_INTEGRAL_TYPES)
{

  using nt2::bitwise_select;
  using nt2::tag::bitwise_select_;

  nt2::uint32_t NR = NT2_NB_RANDOM_TEST;
  std::vector<T> in0(NR), in1(NR), in2(NR);
  std::vector<T> ref(NR);
  nt2::roll(in0, nt2::Valmin<T>()/2, nt2::Valmax<T>()/2);
  nt2::roll(in1, nt2::Valmin<T>()/2, nt2::Valmax<T>()/2);
  nt2::roll(in2, nt2::Valmin<T>()/2, nt2::Valmax<T>()/2);
  for(nt2::uint32_t i=0; i < NR ; ++i)
  {
    ref[i] = (in1[i]&in0[i])|(in2[i]&(~in0[i]));
  }

  NT2_COVER_ULP_EQUAL(bitwise_select_, ((T, in0))((T, in1))((T, in2)), ref, 0);
}

