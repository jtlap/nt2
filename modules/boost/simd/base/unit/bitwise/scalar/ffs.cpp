//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <boost/simd/bitwise/include/functions/ffs.hpp>
#include <boost/dispatch/functor/meta/call.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <boost/simd/include/constants/one.hpp>
#include <boost/simd/include/constants/zero.hpp>
#include <boost/simd/include/constants/inf.hpp>
#include <boost/simd/include/constants/minf.hpp>
#include <boost/simd/include/constants/nbmantissabits.hpp>
#include <boost/simd/include/constants/signmask.hpp>
#include <boost/simd/include/constants/nan.hpp>
#include <boost/simd/sdk/config.hpp>

NT2_TEST_CASE_TPL ( ffs_real,  BOOST_SIMD_REAL_TYPES)
{

  using boost::simd::ffs;
  using boost::simd::tag::ffs_;
  typedef typename boost::dispatch::meta::call<ffs_(T)>::type r_t;
  typedef typename boost::dispatch::meta::as_integer<T, unsigned>::type wished_r_t;

  // return type conformity test
  NT2_TEST_TYPE_IS(r_t, wished_r_t);

  // specific values tests
#ifndef BOOST_SIMD_NO_INVALIDS
  NT2_TEST_EQUAL(ffs(boost::simd::Inf<T>()), r_t(boost::simd::Nbmantissabits<T>()+1));
  NT2_TEST_EQUAL(ffs(boost::simd::Minf<T>()), r_t(boost::simd::Nbmantissabits<T>()+1));
  NT2_TEST_EQUAL(ffs(boost::simd::Nan<T>()), r_t(boost::simd::One<r_t>()));
#endif
  NT2_TEST_EQUAL(ffs(boost::simd::Signmask<T>()), r_t(sizeof(T)*8));
  NT2_TEST_EQUAL(ffs(boost::simd::Zero<T>()), r_t(boost::simd::Zero<r_t>()));
} // end of test for real_

NT2_TEST_CASE_TPL ( ffs_signed_int,  BOOST_SIMD_INTEGRAL_SIGNED_TYPES)
{

  using boost::simd::ffs;
  using boost::simd::tag::ffs_;
  typedef typename boost::dispatch::meta::call<ffs_(T)>::type r_t;
  typedef typename boost::dispatch::meta::as_integer<T, unsigned>::type wished_r_t;

  // return type conformity test
  NT2_TEST_TYPE_IS(r_t, wished_r_t);

  // specific values tests
  NT2_TEST_EQUAL(ffs(boost::simd::One<T>()), boost::simd::One<r_t>());
  NT2_TEST_EQUAL(ffs(boost::simd::Signmask<T>()), sizeof(T)*8);
  NT2_TEST_EQUAL(ffs(boost::simd::Zero<T>()), boost::simd::Zero<r_t>());
} // end of test for signed_int_

NT2_TEST_CASE_TPL ( ffs_unsigned_int,  BOOST_SIMD_UNSIGNED_TYPES)
{

  using boost::simd::ffs;
  using boost::simd::tag::ffs_;
  typedef typename boost::dispatch::meta::call<ffs_(T)>::type r_t;
  typedef typename boost::dispatch::meta::as_integer<T, unsigned>::type wished_r_t;

  // return type conformity test
  NT2_TEST_TYPE_IS(r_t, wished_r_t);

  // specific values tests
  NT2_TEST_EQUAL(ffs(boost::simd::One<T>()), boost::simd::One<r_t>());
  NT2_TEST_EQUAL(ffs(boost::simd::Zero<T>()), boost::simd::Zero<r_t>());
} // end of test for unsigned_int_
