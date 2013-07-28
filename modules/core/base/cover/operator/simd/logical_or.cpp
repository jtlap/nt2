//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/operator/include/functions/logical_or.hpp>
#include <vector>
#include <nt2/include/constants/valmin.hpp>
#include <nt2/include/constants/valmax.hpp>
#include <nt2/sdk/meta/as_logical.hpp>

#include <nt2/sdk/unit/tests/cover.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <boost/simd/sdk/simd/native.hpp>
#include <boost/simd/sdk/simd/io.hpp>

NT2_TEST_CASE_TPL ( logical_or_all_types,  NT2_SIMD_TYPES)
{
  using nt2::logical_or;
  using nt2::tag::logical_or_;
  using boost::simd::native;
  typedef NT2_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef native<T,ext_t>                nT;
  typedef typename nt2::meta::as_logical<T>::type lT;
  typedef typename nt2::meta::call<logical_or_(T, T)>::type r_t;

  // random verifications
  nt2::uint32_t NR  = NT2_NB_RANDOM_TEST;
  std::vector<T> in1(NR), in2(NR), in3(NR);
  nt2::roll(in1, nt2::Valmin<T>()/2, nt2::Valmax<T>()/2);
  nt2::roll(in2, nt2::Valmin<T>()/2, nt2::Valmax<T>()/2);
  nt2::roll(in3, nt2::Valmin<T>()/2, nt2::Valmax<T>()/2);
  std::vector<lT> in4(NR), in5(NR);
  std::vector<r_t> ref(NR);
  for(nt2::uint32_t i=0; i < NR ; ++i)
  {
    in4[i] = in1[i] >  in2[i];
    in5[i] = in1[i] >  in3[i];
    ref[i] = logical_or(in5[i], in4[i]);
  }

  NT2_COVER_ULP_EQUAL(logical_or_, ((nT, in5))((nT, in4)), ref, 0);

}
