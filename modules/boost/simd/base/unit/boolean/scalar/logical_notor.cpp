//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <boost/simd/boolean/include/functions/logical_notor.hpp>
#include <boost/simd/sdk/simd/io.hpp>
#include <boost/dispatch/meta/as_integer.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>
#include <nt2/sdk/meta/as_logical.hpp>
#include <nt2/sdk/meta/as_integer.hpp>

#include <boost/simd/include/constants/one.hpp>
#include <boost/simd/include/constants/inf.hpp>
#include <boost/simd/include/constants/zero.hpp>
#include <boost/simd/include/constants/minf.hpp>
#include <boost/simd/include/constants/mone.hpp>
#include <boost/simd/include/constants/nan.hpp>
#include <boost/simd/include/constants/true.hpp>
#include <boost/simd/include/constants/false.hpp>

NT2_TEST_CASE_TPL ( logical_notor_real__2_0,  BOOST_SIMD_REAL_TYPES)
{

  using boost::simd::logical_notor;
  using boost::simd::tag::logical_notor_;
  using boost::simd::logical;
  using boost::simd::True;
  using boost::simd::False;
  typedef typename boost::dispatch::meta::call<logical_notor_(T, T)>::type r_t;
  typedef typename nt2::meta::as_logical<T>::type lT;
  typedef lT wished_r_t;

  // return type conformity test
  NT2_TEST_TYPE_IS( r_t, wished_r_t );

  // specific values tests
  NT2_TEST_EQUAL(logical_notor(T(0), T(1)), True<lT>());
  NT2_TEST_EQUAL(logical_notor(T(1), T(0)), False<lT>());
  NT2_TEST_EQUAL(logical_notor(boost::simd::Inf<T>(),  T(0)), False<lT>());
  NT2_TEST_EQUAL(logical_notor(boost::simd::Minf<T>(), T(0)), False<lT>());
  NT2_TEST_EQUAL(logical_notor(boost::simd::Nan<T>(),  T(0)), False<lT>());
  NT2_TEST_EQUAL(logical_notor(boost::simd::Zero<T>(), T(1)), True<lT>());
  NT2_TEST_EQUAL(logical_notor(False<lT>(), T(1)), True<lT>());
  NT2_TEST_EQUAL(logical_notor(True<lT>(), T(1)), True<lT>());


} // end of test for floating_

NT2_TEST_CASE_TPL ( logical_notor_signed_int__2_0,  BOOST_SIMD_INTEGRAL_SIGNED_TYPES)
{

  using boost::simd::logical_notor;
  using boost::simd::tag::logical_notor_;
  using boost::simd::logical;
  using boost::simd::False;
  using boost::simd::True;
  typedef typename boost::dispatch::meta::call<logical_notor_(T, T)>::type r_t;
  typedef typename nt2::meta::as_logical<T>::type lT;
  typedef lT wished_r_t;

  // return type conformity test
  NT2_TEST_TYPE_IS( r_t, wished_r_t );

  // specific values tests
  NT2_TEST_EQUAL(logical_notor(T(0), T(1)), True<lT>());
  NT2_TEST_EQUAL(logical_notor(T(1), T(0)), False<lT>());
  NT2_TEST_EQUAL(logical_notor(False<lT>(), T(1)), True<lT>());
  NT2_TEST_EQUAL(logical_notor(True<lT>(), T(1)), True<lT>());
} // end of test for signed_int_

NT2_TEST_CASE_TPL ( logical_notor_mix,  BOOST_SIMD_REAL_TYPES)
{

  using boost::simd::logical_notor;
  using boost::simd::tag::logical_notor_;
  using boost::simd::logical;
  using boost::simd::True;
  using boost::simd::False;
  typedef typename boost::dispatch::meta::call<logical_notor_(T, T)>::type r_t;
  typedef typename nt2::meta::as_integer<T>::type iT;
  typedef typename nt2::meta::as_logical<T>::type lT;
  typedef lT wished_r_t;

  // return type conformity test
  NT2_TEST_TYPE_IS( r_t, wished_r_t );

  // specific values tests
  NT2_TEST_EQUAL(logical_notor(T(0), iT(1)), True<lT>());
  NT2_TEST_EQUAL(logical_notor(T(1), iT(0)), False<lT>());
  NT2_TEST_EQUAL(logical_notor(boost::simd::Inf<T>(),  iT(0)), False<lT>());
  NT2_TEST_EQUAL(logical_notor(boost::simd::Minf<T>(), iT(0)), False<lT>());
  NT2_TEST_EQUAL(logical_notor(boost::simd::Nan<T>(),  iT(0)), False<lT>());
  NT2_TEST_EQUAL(logical_notor(boost::simd::Zero<T>(), iT(1)), True<lT>());
  NT2_TEST_EQUAL(logical_notor(False<lT>(), iT(1)), True<lT>());
  NT2_TEST_EQUAL(logical_notor(True<lT>(), iT(1)), True<lT>());


} // end of test for floating_
