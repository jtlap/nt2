//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#define NT2_UNIT_MODULE "nt2 boost.simd.arithmetic toolbox - touint/scalar Mode"

//////////////////////////////////////////////////////////////////////////////
// unit test behavior of boost.simd.arithmetic components in scalar mode
//////////////////////////////////////////////////////////////////////////////
/// created by jt the 04/12/2010
///
#include <boost/simd/toolbox/arithmetic/include/functions/touint.hpp>
#include <boost/simd/sdk/simd/native.hpp>
#include <boost/dispatch/functor/meta/call.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/include/constants/inf.hpp>
#include <nt2/include/constants/zero.hpp>
#include <nt2/include/constants/one.hpp>
#include <nt2/include/constants/minf.hpp>
#include <nt2/include/constants/nan.hpp>


NT2_TEST_CASE_TPL ( touint_real__1_0,  BOOST_SIMD_REAL_TYPES)
{

  using boost::simd::touint;
  using boost::simd::tag::touint_;
  typedef typename boost::dispatch::meta::strip<typename boost::dispatch::meta::call<touint_(T)>::type>::type r_t;
  typedef typename boost::dispatch::meta::as_integer<T, unsigned>::type wished_r_t;

  NT2_TEST_TYPE_IS( r_t, wished_r_t );
  // specific values tests
  NT2_TEST_EQUAL(touint(boost::simd::Inf<T>()) , boost::simd::Inf<r_t>());
  NT2_TEST_EQUAL(touint(boost::simd::Minf<T>()), boost::simd::Zero<r_t>());
//  NT2_TEST_EQUAL(touint(boost::simd::Mone<T>()), boost::simd::Zero<r_t>());
  NT2_TEST_EQUAL(touint(boost::simd::Nan<T>()) , boost::simd::Zero<r_t>());
  NT2_TEST_EQUAL(touint(boost::simd::One<T>()) , boost::simd::One<r_t>());
  NT2_TEST_EQUAL(touint(boost::simd::Zero<T>()), boost::simd::Zero<r_t>());
 } // end of test for floating_

NT2_TEST_CASE_TPL ( touint_unsigned_int__1_0,  BOOST_SIMD_UNSIGNED_TYPES)
{

  using boost::simd::touint;
  using boost::simd::tag::touint_;
  typedef typename boost::dispatch::meta::strip<typename boost::dispatch::meta::call<touint_(T)>::type>::type r_t;
  typedef typename boost::dispatch::meta::as_integer<T, unsigned>::type wished_r_t;
  NT2_TEST_TYPE_IS( r_t, wished_r_t );
  // specific values tests
  NT2_TEST_EQUAL(touint(boost::simd::One<T>()), boost::simd::One<r_t>());
  NT2_TEST_EQUAL(touint(boost::simd::Zero<T>()), boost::simd::Zero<r_t>());
} // end of test for unsigned_int_

NT2_TEST_CASE_TPL ( touint_signed_int__1_0,  BOOST_SIMD_INTEGRAL_SIGNED_TYPES)
{

  using boost::simd::touint;
  using boost::simd::tag::touint_;
  typedef typename boost::dispatch::meta::strip<typename boost::dispatch::meta::call<touint_(T)>::type>::type r_t;
  typedef typename boost::dispatch::meta::as_integer<T, unsigned>::type wished_r_t;
  NT2_TEST_TYPE_IS( r_t, wished_r_t );
//  NT2_TEST_EQUAL(touint(boost::simd::Mone<T>()), boost::simd::Valmax<r_t>());
  NT2_TEST_EQUAL(touint(boost::simd::One<T>()), boost::simd::One<r_t>());
  NT2_TEST_EQUAL(touint(boost::simd::Zero<T>()), boost::simd::Zero<r_t>());
} // end of test for signed_int_
