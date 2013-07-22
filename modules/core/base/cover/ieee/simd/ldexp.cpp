//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/ieee/include/functions/ldexp.hpp>
#include <vector>
#include <nt2/include/constants/valmin.hpp>
#include <nt2/include/constants/valmax.hpp>
#include <nt2/include/constants/maxexponent.hpp>
#include <nt2/include/constants/one.hpp>
#include <nt2/include/constants/mone.hpp>
#include <nt2/include/constants/zero.hpp>
#include <nt2/sdk/unit/tests/cover.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/meta/as_integer.hpp>
#include <boost/simd/sdk/simd/native.hpp>
#include <boost/simd/sdk/simd/io.hpp>

NT2_TEST_CASE_TPL ( ldexp_all_types,  NT2_SIMD_REAL_TYPES)
{
  using nt2::ldexp;
  using nt2::tag::ldexp_;
  using boost::simd::native;
  typedef NT2_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef typename nt2::meta::as_integer<T>::type iT;
  typedef native<T,ext_t>                nT;
  typedef native<iT,ext_t>              inT;

  typedef typename nt2::meta::call<ldexp_(T, iT)>::type r_t;

  // random verifications
  nt2::uint32_t NR  = NT2_NB_RANDOM_TEST;
  std::vector<T> in1(NR);
  std::vector<iT> in2(NR);
  T Mi = nt2::Mone<T>();
  T Ma = nt2::One<T>();
  nt2::roll(in1, Mi, Ma);
  iT iMi = -nt2::Maxexponent<T>()/2;
  iT iMa =  nt2::Maxexponent<T>()/2;
  nt2::roll(in2,iMi, iMa);

  std::vector<r_t> ref(NR);
  for(nt2::uint32_t i=0; i < NR ; ++i) ref[i] = ldexp(in1[i], in2[i]);
  NT2_COVER_ULP_EQUAL(ldexp_, ((nT, in1))((inT, in2)), ref, 0);

}
