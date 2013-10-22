//==============================================================================
//         Copyright 2003 - 2013   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <boost/simd/ieee/include/functions/bitfloating.hpp>

#include <boost/dispatch/functor/meta/call.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <boost/simd/sdk/config.hpp>
#include <boost/dispatch/meta/as_floating.hpp>
#include <boost/simd/include/constants/mone.hpp>
#include <boost/simd/include/constants/one.hpp>
#include <boost/simd/include/constants/zero.hpp>
#include <boost/simd/include/constants/bitincrement.hpp>


NT2_TEST_CASE_TPL ( bitfloating_int_convert,  BOOST_SIMD_INT_CONVERT_TYPES)
{
  using boost::simd::bitfloating;
  using boost::simd::tag::bitfloating_;
  typedef typename boost::dispatch::meta::call<bitfloating_(T)>::type r_t;
  typedef typename boost::dispatch::meta::as_floating<T>::type  wished_r_t;

  // return type conformity test
  NT2_TEST_TYPE_IS(r_t, wished_r_t);

  // specific values tests
#if !defined(BOOST_SIMD_NO_DENORMALS)
  NT2_TEST_EQUAL(bitfloating(boost::simd::One<T>()), boost::simd::Bitincrement<r_t>());
  NT2_TEST_EQUAL(bitfloating(boost::simd::Mone<T>()), -boost::simd::Bitincrement<r_t>());
#endif
  NT2_TEST_EQUAL(bitfloating(boost::simd::Zero<T>()), boost::simd::Zero<r_t>());
}

NT2_TEST_CASE_TPL ( bitfloating_uint_convert,  BOOST_SIMD_UINT_CONVERT_TYPES)
{
  using boost::simd::bitfloating;
  using boost::simd::tag::bitfloating_;
  typedef typename boost::dispatch::meta::call<bitfloating_(T)>::type r_t;
  typedef typename boost::dispatch::meta::as_floating<T>::type  wished_r_t;

  // return type conformity test
  NT2_TEST_TYPE_IS(r_t, wished_r_t);

  // specific values tests
  NT2_TEST_EQUAL(bitfloating(boost::simd::One<T>()), boost::simd::Bitincrement<r_t>());
  NT2_TEST_EQUAL(bitfloating(boost::simd::Zero<T>()), boost::simd::Zero<r_t>());
}
