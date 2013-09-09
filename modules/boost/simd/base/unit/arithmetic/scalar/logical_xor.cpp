//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <boost/simd/arithmetic/include/functions/logical_xor.hpp>
#include <boost/dispatch/functor/meta/call.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <boost/simd/sdk/meta/as_logical.hpp>
#include <boost/simd/include/constants/one.hpp>
#include <boost/simd/include/constants/zero.hpp>
#include <boost/simd/include/constants/mzero.hpp>
#include <boost/simd/include/constants/mone.hpp>
#include <boost/simd/include/constants/inf.hpp>
#include <boost/simd/include/constants/minf.hpp>
#include <boost/simd/include/constants/nan.hpp>
#include <boost/simd/include/constants/valmax.hpp>
#include <boost/simd/include/constants/valmin.hpp>
#include <boost/simd/include/constants/true.hpp>
#include <boost/simd/include/constants/false.hpp>
#include <boost/simd/sdk/config.hpp>


NT2_TEST_CASE_TPL ( logical_xor_real,  BOOST_SIMD_REAL_TYPES)
{

  using boost::simd::logical_xor;
  using boost::simd::tag::logical_xor_;
  typedef typename boost::dispatch::meta::call<logical_xor_(T,T)>::type r_t;
  typedef typename boost::simd::meta::as_logical<T>::type  wished_r_t;

  NT2_TEST_TYPE_IS(r_t, wished_r_t);

  // specific values tests
#ifndef BOOST_SIMD_NO_INVALIDS
 NT2_TEST_EQUAL(logical_xor(boost::simd::Inf<T>(), boost::simd::Inf<T>()), boost::simd::False<r_t>());
  NT2_TEST_EQUAL(logical_xor(boost::simd::Minf<T>(), boost::simd::Minf<T>()), boost::simd::False<r_t>());
  NT2_TEST_EQUAL(logical_xor(boost::simd::Nan<T>(), boost::simd::Nan<T>()), boost::simd::False<r_t>());
#endif
  NT2_TEST_EQUAL(logical_xor(boost::simd::One<T>(), boost::simd::One<T>()), boost::simd::False<r_t>());
  NT2_TEST_EQUAL(logical_xor(boost::simd::Zero<T>(), boost::simd::Zero<T>()), boost::simd::False<r_t>());
  NT2_TEST_EQUAL(logical_xor(boost::simd::Mone<T>(), boost::simd::Mone<T>()), boost::simd::False<r_t>());
  NT2_TEST_EQUAL(logical_xor(T(0),T(1)), boost::simd::True<r_t>());
  NT2_TEST_EQUAL(logical_xor(T(3),T(0)), boost::simd::True<r_t>());
 } // end of test for floating_

NT2_TEST_CASE_TPL ( logical_xor_unsigned_int,  BOOST_SIMD_UNSIGNED_TYPES)
{

  using boost::simd::logical_xor;
  using boost::simd::tag::logical_xor_;
  typedef typename boost::dispatch::meta::call<logical_xor_(T,T)>::type r_t;
  typedef typename  boost::simd::meta::as_logical<T>::type  wished_r_t;

  // return type conformity test
  NT2_TEST_TYPE_IS(r_t, wished_r_t);

  // specific values tests
  NT2_TEST_EQUAL(logical_xor(boost::simd::One<T>(), boost::simd::One<T>()), boost::simd::False<r_t>());
  NT2_TEST_EQUAL(logical_xor(boost::simd::Zero<T>(), boost::simd::Zero<T>()), boost::simd::False<r_t>());
} // end of test for unsigned_int_

NT2_TEST_CASE_TPL ( logical_xor_signed_int,  BOOST_SIMD_INTEGRAL_SIGNED_TYPES)
{

  using boost::simd::logical_xor;
  using boost::simd::tag::logical_xor_;
  typedef typename boost::dispatch::meta::call<logical_xor_(T,T)>::type r_t;
  typedef typename  boost::simd::meta::as_logical<T>::type  wished_r_t;

  // return type conformity test
  NT2_TEST_TYPE_IS(r_t, wished_r_t);

  // specific values tests
  NT2_TEST_EQUAL(logical_xor(boost::simd::Mone<T>(), boost::simd::Mone<T>()), boost::simd::False<r_t>());
  NT2_TEST_EQUAL(logical_xor(boost::simd::One<T>(), boost::simd::One<T>()), boost::simd::False<r_t>());
  NT2_TEST_EQUAL(logical_xor(boost::simd::Zero<T>(), boost::simd::Zero<T>()), boost::simd::False<r_t>());
} // end of test for signed_int_
