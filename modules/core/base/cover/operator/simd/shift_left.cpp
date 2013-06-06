//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#define NT2_UNIT_MODULE "nt2 operator toolbox - shift_left/simd Mode"

#include <boost/simd/sdk/simd/native.hpp>
#include <boost/simd/sdk/simd/io.hpp>
#include <nt2/operator/include/functions/shift_left.hpp>
#include <nt2/include/constants/valmin.hpp>
#include <nt2/include/constants/valmax.hpp>
#include <nt2/sdk/meta/as_integer.hpp>
#include <vector>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/ulp.hpp>
#include <nt2/sdk/unit/tests/cover.hpp>

NT2_TEST_CASE_TPL(shift_left, NT2_SIMD_TYPES)
{
  using nt2::shift_left;
  using nt2::tag::shift_left_;
  using boost::simd::native;
  typedef NT2_SIMD_DEFAULT_EXTENSION             ext_t;
  typedef native<T,ext_t>                           nT;
  typedef typename nt2::meta::as_integer<T>::type   iT;
  typedef typename nt2::meta::as_integer<nT>::type niT;

  typedef typename nt2::meta::call<shift_left_(T, iT)>::type r_t;

  // random verifications
  nt2::uint32_t NR  = NT2_NB_RANDOM_TEST;
  std::vector<T>  in1(NR);
  std::vector<iT> in2(NR);
  nt2::roll(in1, nt2::Valmin<T>()/2, nt2::Valmax<T>()/2);
  nt2::roll(in2, 0, sizeof(T)*8-1);

  static const std::size_t N = nT::static_size;
  std::vector<r_t> ref1(NR), ref2(NR);
  for(nt2::uint32_t i=0; i < NR ; ++i)
  {
    ref1[i] = shift_left(in1[i], in2[i]);
    ref2[i] = shift_left(in1[i], in2[i/N*N]);
  }
  NT2_COVER_ULP_EQUAL(shift_left_, ((nT, in1))((niT, in2)), ref1, 0.5);
  NT2_COVER_ULP_EQUAL(shift_left_, ((nT, in1))(( iT, in2)), ref2, 0.5);
}
