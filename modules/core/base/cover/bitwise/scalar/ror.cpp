//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/bitwise/include/functions/ror.hpp>
#include <vector>
#include <nt2/include/constants/valmin.hpp>
#include <nt2/include/constants/valmax.hpp>
#include <nt2/include/functions/rol.hpp>
#include <nt2/sdk/unit/tests/cover.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/meta/as_integer.hpp>


NT2_TEST_CASE_TPL ( ror,  NT2_INTEGRAL_TYPES)
{

  using nt2::ror;
  using nt2::tag::ror_;
  typedef typename nt2::meta::as_integer<T>::type iT;
  typedef typename nt2::meta::call<ror_(T, iT)>::type r_t;

  nt2::uint32_t NR = NT2_NB_RANDOM_TEST;
  std::vector<T> in1(NR), in3(NR);
  std::vector<iT> in2(NR);
  nt2::roll(in1,  nt2::Valmin<T>(), nt2::Valmax<T>());
  nt2::roll(in2,  0, sizeof(T)*8-1);
  std::vector<r_t>  ref(NR);
  for(nt2::uint32_t i=0; i < NR ; ++i)
  {
    in3[i] =  nt2::rol(in1[i], in2[i]);
    ref[i] =  in1[i];
  }

  NT2_COVER_ULP_EQUAL(nt2::tag::ror_, ((T, in3))((iT, in2)), ref, 0);
}
