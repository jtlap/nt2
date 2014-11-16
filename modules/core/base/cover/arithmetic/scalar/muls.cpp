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
/// created by jt the 30/11/2010
///
#include <nt2/arithmetic/include/functions/muls.hpp>
#include <boost/simd/sdk/simd/io.hpp>
#include <vector>
#include <nt2/include/constants/valmin.hpp>
#include <nt2/include/constants/valmax.hpp>
#include <nt2/include/constants/sqrtvalmax.hpp>

#include <nt2/sdk/unit/tests/cover.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>


NT2_TEST_CASE_TPL ( muls_real__1_0_1,  NT2_REAL_TYPES)
{

  using nt2::muls;
  using nt2::tag::muls_;
  typedef typename nt2::meta::call<muls_(T, T)>::type r_t;

  nt2::uint32_t NR = NT2_NB_RANDOM_TEST;
  std::vector<T> in1(NR), in2(NR);
  std::vector<r_t> ref(NR);
  nt2::roll(in1, -nt2::Sqrtvalmax<T>(), nt2::Sqrtvalmax<T>());
  nt2::roll(in2, -nt2::Sqrtvalmax<T>(), nt2::Sqrtvalmax<T>());
  for(nt2::uint32_t i=0; i < NR ; ++i)
  {
    ref[i] = in1[i]*in2[i];
  }

  NT2_COVER_ULP_EQUAL(muls_, ((T, in1))((T, in2)), ref, 0);

}

NT2_TEST_CASE_TPL ( muls_real__1_0_2,  NT2_INTEGRAL_SIGNED_TYPES)
{

  using nt2::muls;
  using nt2::tag::muls_;
  typedef typename nt2::meta::call<muls_(T, T)>::type r_t;

  static const nt2::uint32_t NR = NT2_NB_RANDOM_TEST;
  std::vector<T> in1(NR), in2(NR);
  std::vector<r_t> ref(NR);
  nt2::roll(in1, (nt2::Valmin<T>()+1), -nt2::Sqrtvalmax<T>());
  nt2::roll(in2, nt2::Sqrtvalmax<T>()+1, nt2::Valmax<T>());
  for(nt2::uint32_t i=0; i < NR ; ++i)
  {
    ref[i] = nt2::Valmin<T>();
  }

  NT2_COVER_ULP_EQUAL(muls_, ((T, in1))((T, in2)), ref, 0);

}

NT2_TEST_CASE_TPL ( muls_real__1_0_3,  NT2_INTEGRAL_TYPES)
{

  using nt2::muls;
  using nt2::tag::muls_;
  typedef typename nt2::meta::call<muls_(T, T)>::type r_t;

  static const nt2::uint32_t NR = NT2_NB_RANDOM_TEST;
  std::vector<T> in1(NR), in2(NR);
  std::vector<r_t> ref(NR);
  nt2::roll(in1, nt2::Sqrtvalmax<T>(), nt2::Valmax<T>());
  nt2::roll(in2, nt2::Sqrtvalmax<T>(), nt2::Valmax<T>());
  for(nt2::uint32_t i=0; i < NR ; ++i)
  {
    ref[i] = nt2::Valmax<T>();
  }

  NT2_COVER_ULP_EQUAL(muls_, ((T, in1))((T, in2)), ref, 0);

}
