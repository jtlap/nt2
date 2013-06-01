//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#define NT2_UNIT_MODULE "nt2 arithmetic toolbox - fast_hypot/scalar Mode"

//////////////////////////////////////////////////////////////////////////////
// cover test behavior of arithmetic components in scalar mode
//////////////////////////////////////////////////////////////////////////////

#include <nt2/arithmetic/include/functions/fast_hypot.hpp>
#include <boost/simd/sdk/simd/io.hpp>
#include <vector>
#include <nt2/table.hpp>
#include <nt2/include/constants/zero.hpp>
#include <nt2/include/constants/hundred.hpp>
#include <nt2/include/functions/hypot.hpp>
#include <nt2/sdk/meta/as_floating.hpp>
#include <nt2/sdk/unit/tests.hpp>
#include <nt2/sdk/unit/tests/ulp.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>


NT2_TEST_CASE_TPL ( fast_hypot_real__1_0_1,  NT2_REAL_TYPES)
{

  using nt2::fast_hypot;
  using nt2::tag::fast_hypot_;
  typedef typename nt2::meta::call<fast_hypot_(T, T)>::type r_t;
  typedef T wished_r_t;

  // return type conformity test
  NT2_TEST_TYPE_IS( r_t, wished_r_t );


  nt2::uint32_t NR = NT2_NB_RANDOM_TEST;
  std::vector<T> in1(NR), in2(NR);
  std::vector<r_t> ref(NR);
  nt2::roll(in1, nt2::Zero<T>()/2, nt2::Hundred<T>()/2);
  nt2::roll(in2, nt2::Zero<T>()/2, nt2::Hundred<T>()/2);
  for(nt2::uint32_t i=0; i < NR ; ++i)
  {
    ref[i] = nt2::hypot( in1[i], in2[i]);
  }

 NT2_COVER_ULP_EQUAL(fast_hypot_, ((T, in1))((T, in2)), ref, 2);

}
NT2_TEST_CASE_TPL ( fast_hypot_real__1_0_2,  NT2_INTEGRAL_TYPES)
{

  using nt2::fast_hypot;
  using nt2::tag::fast_hypot_;
  typedef typename nt2::meta::call<fast_hypot_(T, T)>::type r_t;
  typedef typename nt2::meta::as_floating<T>::type wished_r_t;

  // return type conformity test
  NT2_TEST_TYPE_IS( r_t, wished_r_t );


  nt2::uint32_t NR = NT2_NB_RANDOM_TEST;
  std::vector<T> in1(NR), in2(NR);
  std::vector<r_t> ref(NR);
  nt2::roll(in1, nt2::Zero<T>()/2, nt2::Hundred<T>()/2);
  nt2::roll(in2, nt2::Zero<T>()/2, nt2::Hundred<T>()/2);
  for(nt2::uint32_t i=0; i < NR ; ++i)
  {
    ref[i] = nt2::hypot( in1[i], in2[i]);
  }

 NT2_COVER_ULP_EQUAL(fast_hypot_, ((T, in1))((T, in2)), ref, 2);

}



