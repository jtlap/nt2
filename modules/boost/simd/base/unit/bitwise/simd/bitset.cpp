//==============================================================================
//         Copyright 2015 J.T. Lapreste
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <boost/simd/bitwise/include/functions/bitset.hpp>
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


NT2_TEST_CASE_TPL ( bitset_uit,  BOOST_SIMD_SIMD_UNSIGNED_TYPES)
{

  using boost::simd::bitset;
  using boost::simd::tag::bitset_;
  using boost::simd::native;
  typedef BOOST_SIMD_DEFAULT_EXTENSION                          ext_t;
  typedef native<T,ext_t>                                          vT;
  typedef typename boost::dispatch::meta::as_integer<vT, unsigned>::type viT;
  typedef typename boost::dispatch::meta::call<bitset_(T,viT)>::type r_t;
  typedef vT wished_r_t;


  // return type conformity test
  NT2_TEST_TYPE_IS( r_t, wished_r_t );

  // specific values tests
  NT2_TEST_EQUAL(bitset(boost::simd::splat<vT>(T(2)),1), boost::simd::splat<vT>(T(3)));
  NT2_TEST_EQUAL(bitset(boost::simd::splat<vT>(T(3)),2), boost::simd::splat<vT>(T(3)));
  NT2_TEST_EQUAL(bitset(boost::simd::splat<vT>(T(3)),3), boost::simd::splat<vT>(T(7)));
} // end of test for unsigned_int_

NT2_TEST_CASE_TPL ( bitset_si,  BOOST_SIMD_SIMD_INTEGRAL_SIGNED_TYPES)
{

  using boost::simd::bitset;
  using boost::simd::tag::bitset_;
  using boost::simd::native;
  typedef BOOST_SIMD_DEFAULT_EXTENSION                          ext_t;
  typedef native<T,ext_t>                                          vT;
  typedef typename boost::dispatch::meta::as_integer<vT, unsigned>::type viT;
  typedef typename boost::dispatch::meta::call<bitset_(T,viT)>::type r_t;
  typedef vT wished_r_t;


  // return type conformity test
  NT2_TEST_TYPE_IS( r_t, wished_r_t );

  // specific values tests
  NT2_TEST_EQUAL(bitset(boost::simd::splat<vT>(T(2)) ,1),boost::simd::splat<vT>(T(3)));
  NT2_TEST_EQUAL(bitset(boost::simd::splat<vT>(T(2)) ,2), boost::simd::splat<vT>(T(2)));
  NT2_TEST_EQUAL(bitset(boost::simd::splat<vT>(T(-1)), 1), boost::simd::splat<vT>(T(-1)));
} // end of test for unsigned_int_
