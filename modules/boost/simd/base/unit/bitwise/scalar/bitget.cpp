//==============================================================================
//          Copyright 2015 J.T. Lapreste
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <boost/simd/bitwise/include/functions/bitget.hpp>
#include <boost/simd/sdk/simd/io.hpp>
#include <boost/dispatch/meta/as_integer.hpp>
#include <nt2/sdk/unit/tests.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>

#include <boost/simd/include/constants/one.hpp>
#include <boost/simd/include/constants/mone.hpp>
#include <boost/simd/include/constants/zero.hpp>
#include <boost/simd/include/constants/valmax.hpp>
#include <boost/simd/include/constants/three.hpp>


NT2_TEST_CASE_TPL ( bitget_uit,  BOOST_SIMD_UNSIGNED_TYPES)
{

  using boost::simd::bitget;
  using boost::simd::tag::bitget_;
  typedef typename boost::dispatch::meta::as_integer<T, unsigned>::type iT;
  typedef typename boost::dispatch::meta::call<bitget_(T,iT)>::type r_t;
  typedef iT wished_r_t;


  // return type conformity test
  NT2_TEST_TYPE_IS( r_t, wished_r_t );

  // specific values tests
  NT2_TEST_EQUAL(bitget(T(3),1), boost::simd::One<iT>());
  NT2_TEST_EQUAL(bitget(T(3),2), boost::simd::One<iT>());
  NT2_TEST_EQUAL(bitget(T(3),3), boost::simd::Zero<iT>());
} // end of test for unsigned_int_

NT2_TEST_CASE_TPL ( bitget_si,  BOOST_SIMD_INTEGRAL_SIGNED_TYPES)
{

  using boost::simd::bitget;
  using boost::simd::tag::bitget_;
  typedef typename boost::dispatch::meta::as_integer<T, unsigned>::type iT;
  typedef typename boost::dispatch::meta::call<bitget_(T,iT)>::type r_t;
  typedef iT wished_r_t;


  // return type conformity test
  NT2_TEST_TYPE_IS( r_t, wished_r_t );

  // specific values tests
  NT2_TEST_EQUAL(bitget(T(2),1), boost::simd::Zero<iT>());
  NT2_TEST_EQUAL(bitget(T(2),2), boost::simd::One<iT>());
  NT2_TEST_EQUAL(bitget(T(-1), sizeof(T)*CHAR_BIT), boost::simd::One<iT>());
} // end of test for unsigned_int_
