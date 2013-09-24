//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/bitwise/include/functions/rshr.hpp>
#include <vector>
#include <nt2/include/constants/valmin.hpp>
#include <nt2/include/constants/valmax.hpp>

#include <nt2/sdk/unit/tests/cover.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/meta/as_integer.hpp>
#include <boost/simd/sdk/simd/native.hpp>
#include <boost/simd/sdk/simd/io.hpp>

NT2_TEST_CASE_TPL ( rshr_si,  NT2_SIMD_INTEGRAL_SIGNED_TYPES)
{
  using nt2::rshr;
  using nt2::tag::rshr_;
  using boost::simd::native;
  typedef NT2_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef native<T,ext_t>                nT;
  typedef typename nt2::meta::as_integer<T>::type iT;
  typedef typename nt2::meta::call<rshr_(T,iT)>::type r_t;

  // random verifications
  nt2::uint32_t NR  = NT2_NB_RANDOM_TEST;
  std::vector<T> in1(NR);
  std::vector<iT> in2(NR);
  nt2::roll(in1, nt2::Valmin<T>()/2, nt2::Valmax<T>()/2);
  int32_t N = sizeof(T)*8-1;
  nt2::roll(in2, -N, N);
  std::vector<r_t> ref(NR);
  for(nt2::uint32_t i=0; i < NR ; ++i) ref[i] = rshr(in1[i], in2[i]);
  NT2_COVER_ULP_EQUAL(rshr_, ((nT, in1))((nT, in2)), ref, 0);
} // end of test for integer_

NT2_TEST_CASE_TPL ( rshr_ui,  NT2_SIMD_UNSIGNED_TYPES)
{
  using nt2::rshr;
  using nt2::tag::rshr_;
  using boost::simd::native;
  typedef NT2_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef native<T,ext_t>                nT;
  typedef typename nt2::meta::as_integer<T>::type iT;
  typedef typename nt2::meta::call<rshr_(T,iT)>::type r_t;

  // random verifications
  nt2::uint32_t NR  = NT2_NB_RANDOM_TEST;
  std::vector<T> in1(NR);
  std::vector<iT> in2(NR);
  nt2::roll(in1, nt2::Valmin<T>()/2, nt2::Valmax<T>()/2);
  nt2::roll(in2, 0, sizeof(T)*8-1);
  std::vector<r_t> ref(NR);
  for(nt2::uint32_t i=0; i < NR ; ++i) ref[i] = rshr(in1[i], in2[i]);
  NT2_COVER_ULP_EQUAL(rshr_, ((nT, in1))((nT, in2)), ref, 0);
} // end of test for integer_
