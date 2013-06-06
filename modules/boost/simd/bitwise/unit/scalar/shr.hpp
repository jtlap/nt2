//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#define NT2_UNIT_MODULE "nt2 boost.simd.bitwise toolbox - shr/scalar Mode"

//////////////////////////////////////////////////////////////////////////////
// unit test behavior of boost.simd.bitwise components in scalar mode
//////////////////////////////////////////////////////////////////////////////
/// created  by jt the 18/02/2011
///
#include <boost/simd/bitwise/include/functions/shr.hpp>
#include <boost/simd/sdk/simd/io.hpp>
#include <boost/dispatch/meta/as_integer.hpp>
#include <nt2/sdk/unit/tests.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>


NT2_TEST_CASE_TPL ( shr_unsigned_int__2_0,  BOOST_SIMD_UNSIGNED_TYPES)
{

  using boost::simd::shr;
  using boost::simd::tag::shr_;
  typedef typename boost::dispatch::meta::as_integer<T>::type iT;
  typedef typename boost::dispatch::meta::call<shr_(T,iT)>::type r_t;
  typedef T wished_r_t;


  // return type conformity test
  NT2_TEST_TYPE_IS( r_t, wished_r_t );

  // specific values tests
  NT2_TEST_EQUAL(shr(T(2),1), boost::simd::One<T>());
  NT2_TEST_EQUAL(shr(boost::simd::Mone<T>(),(sizeof(T)*8-1)), boost::simd::One<r_t>());
  NT2_TEST_EQUAL(shr(boost::simd::Mone<T>(),(sizeof(T)*8-2)), boost::simd::Three<r_t>());
  NT2_TEST_EQUAL(shr(boost::simd::One<T>(),1), boost::simd::Zero<r_t>());
  NT2_TEST_EQUAL(shr(boost::simd::Zero<T>(),1), boost::simd::Zero<r_t>());
} // end of test for unsigned_int_

NT2_TEST_CASE_TPL ( shr_unsigned_int__2_0,  BOOST_SIMD_INTEGRAL_SIGNED_TYPES)
{

  using boost::simd::shr;
  using boost::simd::tag::shr_;
  typedef typename boost::dispatch::meta::as_integer<T>::type iT;
  typedef typename boost::dispatch::meta::call<shr_(T,iT)>::type r_t;
  typedef T wished_r_t;


  // return type conformity test
  NT2_TEST_TYPE_IS( r_t, wished_r_t );

  // specific values tests
  NT2_TEST_EQUAL(shr(T(2),1), boost::simd::One<T>());
  NT2_TEST_EQUAL(shr(boost::simd::Mone<T>(),(sizeof(T)*8-1)), boost::simd::One<r_t>());
  NT2_TEST_EQUAL(shr(boost::simd::Mone<T>(),(sizeof(T)*8-2)), boost::simd::Three<r_t>());
  NT2_TEST_EQUAL(shr(boost::simd::One<T>(),1), boost::simd::Zero<r_t>());
  NT2_TEST_EQUAL(shr(boost::simd::Zero<T>(),1), boost::simd::Zero<r_t>());
} // end of test for unsigned_int_
