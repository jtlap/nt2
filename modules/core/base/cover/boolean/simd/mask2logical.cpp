//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
//////////////////////////////////////////////////////////////////////////////
// cover test behavior of arithmetic components in simd mode
//////////////////////////////////////////////////////////////////////////////

#include <nt2/boolean/include/functions/mask2logical.hpp>
#include <vector>
#include <nt2/include/constants/valmin.hpp>
#include <nt2/include/constants/valmax.hpp>
#include <nt2/include/functions/if_allbits_else.hpp>
#include <nt2/sdk/meta/as_logical.hpp>

#include <nt2/sdk/unit/tests/cover.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <boost/simd/sdk/simd/native.hpp>
#include <boost/simd/sdk/simd/io.hpp>

NT2_TEST_CASE_TPL ( mask2logical_all_types,  NT2_SIMD_TYPES)
{
  using nt2::mask2logical;
  using nt2::tag::mask2logical_;
  using boost::simd::native;
  typedef NT2_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef native<T,ext_t>                nT;
  typedef typename nt2::meta::as_logical<T>::type lT;
  typedef native<lT,ext_t>                nlT;

  // random verifications
  nt2::uint32_t NR  = NT2_NB_RANDOM_TEST;
  std::vector<T> in0(NR), in1(NR), in2(NR);
  nt2::roll(in0, nt2::Valmin<T>()/2, nt2::Valmax<T>()/2);
  nt2::roll(in1, nt2::Valmin<T>()/2, nt2::Valmax<T>()/2);
  std::vector<lT> ref(NR);
  for(nt2::uint32_t i=0; i < NR ; ++i)
  {
    in2[i] = nt2::if_allbits_else(in1[i] > in0[i], nt2::Zero<T>());
    ref[i] = mask2logical(in2[i]);
  }

  NT2_COVER_ULP_EQUAL(mask2logical_, ((nT, in2)), ref, 0);

}
