//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/ieee/include/functions/bitfloating.hpp>
#include <nt2/include/functions/bitinteger.hpp>
#include <nt2/include/functions/min.hpp>
#include <nt2/include/functions/max.hpp>
#include <nt2/include/constants/valmax.hpp>
#include <nt2/include/constants/valmin.hpp>
#include <nt2/include/constants/zero.hpp>
#include <nt2/sdk/meta/as_floating.hpp>
#include <vector>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/cover.hpp>

NT2_TEST_CASE_TPL ( bitfloating,  NT2_INT_CONVERT_TYPES)
{

  using nt2::bitfloating;
  using nt2::tag::bitfloating_;
  typedef typename nt2::meta::as_floating<T>::type fT;
  nt2::uint32_t NR = NT2_NB_RANDOM_TEST;
  std::vector<T> in1(NR), in2(NR);
  int64_t Mi = nt2::Valmin<T>();
  int64_t Ma = nt2::Valmax<T>();
  nt2::roll(in1, T(Mi), T(Ma));
  std::vector<fT>  ref(NR);
  for(nt2::uint32_t i=0; i < NR ; ++i)
  {
    in2[i] = nt2::bitinteger(nt2::bitfloating(in1[i]));
    ref[i] = nt2::bitfloating(in2[i]);
  }
  NT2_COVER_ULP_EQUAL(bitfloating_, ((T, in2)), ref, 0);
}

NT2_TEST_CASE_TPL ( bitfloatingu,  NT2_UINT_CONVERT_TYPES)
{

  using nt2::bitfloating;
  using nt2::tag::bitfloating_;
  typedef typename nt2::meta::as_floating<T>::type fT;
  nt2::uint32_t NR = NT2_NB_RANDOM_TEST;
  std::vector<T> in1(NR);
  std::vector<T> in2(NR);
  int64_t Mi = nt2::Valmin<T>();
  int64_t Ma = nt2::Valmax<T>();
  nt2::roll(in1, T(Mi), T(Ma));
  std::vector<fT>  ref(NR);
  for(nt2::uint32_t i=0; i < NR ; ++i)
  {
    in2[i] = nt2::bitinteger(nt2::bitfloating(in1[i]));
    ref[i] = nt2::bitfloating(in2[i]);
  }
  NT2_COVER_ULP_EQUAL(bitfloating_, ((T, in2)), ref, 0);
}

