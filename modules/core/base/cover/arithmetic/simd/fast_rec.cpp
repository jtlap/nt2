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

#include <nt2/arithmetic/include/functions/rec.hpp>
#include <nt2/arithmetic/include/functions/fast_rec.hpp>
#include <vector>
#include <nt2/include/constants/valmin.hpp>
#include <nt2/include/constants/valmax.hpp>

#include <nt2/sdk/unit/tests/cover.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <boost/simd/sdk/simd/native.hpp>
#include <boost/simd/sdk/simd/io.hpp>

NT2_TEST_CASE_TPL ( fast_rec_all_types,  NT2_SIMD_REAL_TYPES)
{
  using nt2::fast_rec;
  using nt2::tag::fast_rec_;
  using boost::simd::native;
  typedef NT2_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef native<T,ext_t>                nT;

  typedef typename nt2::meta::call<fast_rec_(T)>::type r_t;

  // random verifications
  nt2::uint32_t NR  = 16384;
  std::vector<T> in1(NR);
  nt2::roll(in1, T(1.234567), T(1.987654));

  std::vector<r_t>  ref(NR);
  for(nt2::uint32_t i=0; i < NR ; ++i)
    ref[i] = T(1. / double(in1[i]));

  NT2_COVER_ULP_EQUAL(fast_rec_, ((nT, in1)), ref, 16);
}

