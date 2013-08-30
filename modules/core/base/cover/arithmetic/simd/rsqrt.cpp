//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/arithmetic/include/functions/rsqrt.hpp>
#include <nt2/include/functions/scalar/sqrt.hpp>
#include <nt2/include/constants/valmax.hpp>
#include <nt2/include/constants/zero.hpp>
#include <boost/simd/sdk/simd/native.hpp>
#include <boost/simd/sdk/simd/io.hpp>

#include <nt2/sdk/unit/tests/cover.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <vector>

NT2_TEST_CASE_TPL ( rsqrt_all_types,  NT2_SIMD_REAL_TYPES)
{
  using nt2::rsqrt;
  using nt2::tag::rsqrt_;
  using boost::simd::native;
  typedef NT2_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef native<T,ext_t>                nT;

  typedef typename nt2::meta::call<rsqrt_(T)>::type r_t;

  // random verifications
  nt2::uint32_t NR  = NT2_NB_RANDOM_TEST;
  std::vector<T> in1(NR);
  nt2::roll(in1, nt2::Zero<T>(), nt2::Valmax<T>());

  std::vector<r_t>  ref(NR);
  for(nt2::uint32_t i=0; i < NR ; ++i)
    ref[i] = 1./sqrt(in1[i]);

  NT2_COVER_ULP_EQUAL(rsqrt_, ((nT, in1)), ref, 1);
}
