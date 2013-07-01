//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#define NT2_UNIT_MODULE "nt2 exponential toolbox - iexp2/simd Mode"

//////////////////////////////////////////////////////////////////////////////
// unit test behavior of exponential components in simd mode
//////////////////////////////////////////////////////////////////////////////
/// created by jt the 08/12/2010
///
#include <nt2/exponential/include/functions/iexp2.hpp>
#include <boost/simd/sdk/simd/native.hpp>
#include <nt2/sdk/functor/meta/call.hpp>
#include <nt2/sdk/unit/tests.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <boost/simd/sdk/simd/io.hpp>
#include <nt2/constant/constant.hpp>
#include <nt2/include/functions/splat.hpp>


NT2_TEST_CASE_TPL ( iexp2_unsigned_int__1_0,  NT2_SIMD_INTEGRAL_SIGNED_TYPES)
{

  using nt2::iexp2;
  using nt2::tag::iexp2_;
  using boost::simd::native;
  typedef NT2_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef native<T,ext_t>                vT;
  typedef typename nt2::meta::call<iexp2_(vT)>::type r_t;

  // specific values tests
  NT2_TEST_EQUAL(iexp2(nt2::One<vT>()), nt2::Two<r_t>());
  NT2_TEST_EQUAL(iexp2(nt2::Zero<vT>()), nt2::One<r_t>());
  NT2_TEST_EQUAL(iexp2(nt2::Mone<vT>()), nt2::Zero<r_t>());
  NT2_TEST_EQUAL(iexp2(nt2::splat<vT>(sizeof(T)*8-2)), nt2::splat<r_t>( 1ll << (sizeof(T)*8-2)));
} // end of test for unsigned_int_

NT2_TEST_CASE_TPL ( iexp2_real__1_0,  NT2_SIMD_UNSIGNED_TYPES)
{
  using nt2::iexp2;
  using nt2::tag::iexp2_;
  using boost::simd::native;
  typedef NT2_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef native<T,ext_t>                vT;
  typedef typename nt2::meta::call<iexp2_(vT)>::type r_t;
  // specific values tests
  NT2_TEST_EQUAL(iexp2(nt2::One<vT>()), nt2::Two<r_t>());
  NT2_TEST_EQUAL(iexp2(nt2::Zero<vT>()), nt2::One<r_t>());
  NT2_TEST_EQUAL(iexp2( nt2::splat<vT>(sizeof(T)*8-1)),  nt2::splat<r_t>(1ull << (sizeof(T)*8-1)));
} // end of test for floating_
