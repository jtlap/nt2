//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#define NT2_UNIT_MODULE "nt2 arithmetic toolbox - toint/simd Mode"

//////////////////////////////////////////////////////////////////////////////
// unit test behavior of arithmetic components in simd mode
//////////////////////////////////////////////////////////////////////////////
/// created by jt the 04/12/2010
///
#include <nt2/arithmetic/include/functions/toint.hpp>
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

NT2_TEST_CASE_TPL ( toint_real__1_0,  NT2_SIMD_REAL_TYPES)
{
  using nt2::toint;
  using nt2::tag::toint_;
  using boost::simd::native;
  typedef NT2_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef native<T,ext_t>           vT;
  typedef typename nt2::meta::call<toint_(vT)>::type r_t;

  // specific values tests
  NT2_TEST_EQUAL(toint(nt2::Mone<vT>()), nt2::Mone<r_t>());
  NT2_TEST_EQUAL(toint(nt2::One<vT>()), nt2::One<r_t>());
  NT2_TEST_EQUAL(toint(nt2::Zero<vT>()), nt2::Zero<r_t>());


  NT2_TEST_EQUAL(toint(boost::simd::splat<vT>(T(4194304))), boost::simd::splat<r_t>(4194304));
  NT2_TEST_EQUAL(toint(boost::simd::splat<vT>(T(16777216))), boost::simd::splat<r_t>(16777216));

  NT2_TEST_EQUAL(toint(boost::simd::splat<vT>(T(-4194304))), boost::simd::splat<r_t>(-4194304));
  NT2_TEST_EQUAL(toint(boost::simd::splat<vT>(T(-8388608))), boost::simd::splat<r_t>(-8388608));
  NT2_TEST_EQUAL(toint(boost::simd::splat<vT>(T(-16777216))), boost::simd::splat<r_t>(-16777216));
} // end of test for floating_
