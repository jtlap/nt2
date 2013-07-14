//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/boolean/include/functions/if_allbits_else.hpp>
#include <vector>
#include <nt2/sdk/meta/as_logical.hpp>
#include <nt2/sdk/unit/tests.hpp>
#include <nt2/sdk/unit/tests/cover.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/include/constants/valmax.hpp>
#include <nt2/include/constants/valmin.hpp>
#include <nt2/include/constants/nan.hpp>
#include <nt2/include/constants/mone.hpp>
#include <nt2/include/functions/min.hpp>
#include <nt2/include/functions/max.hpp>
#include <nt2/include/functions/is_odd.hpp>

NT2_TEST_CASE_TPL ( if_allbits_else_signed,  NT2_REAL_TYPES)
{

  using nt2::if_allbits_else;
  using nt2::tag::if_allbits_else_;
  typedef typename nt2::meta::as_logical<T>::type lT;

  nt2::uint32_t NR = NT2_NB_RANDOM_TEST;
  std::vector<T> in1(NR), in0(NR);
  std::vector<lT> in3(NR);
  int64_t Mi = nt2::max(int64_t(nt2::Valmin<T>()), int64_t(-10000));
  int64_t Ma = nt2::min(int64_t(nt2::Valmax<T>()), int64_t(10000));
  nt2::roll(in1,T(Mi),T(Ma));
  nt2::roll(in0,T(Mi),T(Ma));
  std::vector<T>  ref(NR);
  for(nt2::uint32_t i=0; i < NR ; ++i)
  {
    in3[i] = in0[i] > 0;
    ref[i] = in3[i] ? in1[i] : nt2::Nan<T>();
  }

  NT2_COVER_ULP_EQUAL(if_allbits_else_, ((lT, in3))((T, in1)), ref, 0);
}


NT2_TEST_CASE_TPL ( if_allbits_else_signedsi,  NT2_INTEGRAL_SIGNED_TYPES)
{

  using nt2::if_allbits_else;
  using nt2::tag::if_allbits_else_;
  typedef typename nt2::meta::as_logical<T>::type lT;

  nt2::uint32_t NR = NT2_NB_RANDOM_TEST;
  std::vector<T> in1(NR), in0(NR);
  std::vector<lT> in3(NR);
  int64_t Mi = nt2::max(int64_t(nt2::Valmin<T>()), int64_t(-10000));
  int64_t Ma = nt2::min(int64_t(nt2::Valmax<T>()), int64_t(10000));
  nt2::roll(in1,T(Mi),T(Ma));
  nt2::roll(in0,T(Mi),T(Ma));
  std::vector<T>  ref(NR);
  for(nt2::uint32_t i=0; i < NR ; ++i)
  {
    in3[i] = in0[i] > 0;
    ref[i] = in3[i] ? in1[i]: nt2::Mone<T>();
  }

  NT2_COVER_ULP_EQUAL(if_allbits_else_, ((lT, in3))((T, in1)), ref, 0);
}


NT2_TEST_CASE_TPL ( if_allbits_else_unsigned,  NT2_UNSIGNED_TYPES)
{


  using nt2::if_allbits_else;
  using nt2::tag::if_allbits_else_;
  typedef typename nt2::meta::as_logical<T>::type lT;

  nt2::uint32_t NR = NT2_NB_RANDOM_TEST;
  std::vector<T> in1(NR), in0(NR);
  std::vector<lT> in3(NR);
  uint64_t M = nt2::min(uint64_t(nt2::Valmax<T>()), uint64_t(10000));
  nt2::roll(in1, T(0), T(M));
  nt2::roll(in0,T(0),T(M));
  std::vector<T>  ref(NR);
  for(nt2::uint32_t i=0; i < NR ; ++i)
  {
    in3[i] = nt2::is_odd(in0[i]);
    ref[i] = in3[i] ? in1[i] :  nt2::Valmax<T>();
  }

  NT2_COVER_ULP_EQUAL(if_allbits_else_, ((lT, in3))((T, in1)), ref, 0);
}
