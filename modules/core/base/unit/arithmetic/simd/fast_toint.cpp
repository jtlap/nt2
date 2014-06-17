//==============================================================================
//         Copyright 2014        LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2014        LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2014        NumScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#define NT2_UNIT_MODULE "nt2 arithmetic toolbox - fast_toint/simd Mode"

//////////////////////////////////////////////////////////////////////////////
// unit test behavior of arithmetic components in simd mode
//////////////////////////////////////////////////////////////////////////////
///
#include <nt2/arithmetic/include/functions/fast_toint.hpp>
#include <boost/simd/sdk/simd/native.hpp>
#include <nt2/sdk/functor/meta/call.hpp>
#include <nt2/sdk/meta/as_integer.hpp>
#include <nt2/sdk/unit/tests.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <boost/simd/sdk/simd/io.hpp>
#include <nt2/include/constants/inf.hpp>
#include <nt2/include/constants/minf.hpp>
#include <nt2/include/constants/nan.hpp>
#include <nt2/include/constants/zero.hpp>
#include <nt2/include/constants/one.hpp>
#include <nt2/include/constants/mone.hpp>
#include <boost/simd/include/functions/splat.hpp>

NT2_TEST_CASE_TPL ( fast_toint_real__1_0,  NT2_SIMD_REAL_TYPES)
{
  using nt2::fast_toint;
  using nt2::tag::fast_toint_;
  using boost::simd::native;
  typedef NT2_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef native<T,ext_t>           vT;
  typedef typename nt2::meta::call<fast_toint_(vT)>::type r_t;

  // specific values tests
  NT2_TEST_EQUAL(fast_toint(nt2::Mone<vT>()), nt2::Mone<r_t>());
  NT2_TEST_EQUAL(fast_toint(nt2::One<vT>()), nt2::One<r_t>());
  NT2_TEST_EQUAL(fast_toint(nt2::Zero<vT>()), nt2::Zero<r_t>());

  NT2_TEST_EQUAL(fast_toint(boost::simd::splat<vT>(T(4194304))), boost::simd::splat<r_t>(4194304));
  NT2_TEST_EQUAL(fast_toint(boost::simd::splat<vT>(T(16777216))), boost::simd::splat<r_t>(16777216));

  NT2_TEST_EQUAL(fast_toint(boost::simd::splat<vT>(T(-4194304))), boost::simd::splat<r_t>(-4194304));
  NT2_TEST_EQUAL(fast_toint(boost::simd::splat<vT>(T(-8388608))), boost::simd::splat<r_t>(-8388608));
  NT2_TEST_EQUAL(fast_toint(boost::simd::splat<vT>(T(-16777216))), boost::simd::splat<r_t>(-16777216));
}
