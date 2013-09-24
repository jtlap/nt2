//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <boost/simd/bitwise/include/functions/bitwise_ornot.hpp>
#include <boost/dispatch/functor/meta/call.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <boost/simd/include/constants/two.hpp>
#include <boost/simd/include/constants/one.hpp>
#include <boost/simd/include/constants/mone.hpp>
#include <boost/simd/include/constants/inf.hpp>
#include <boost/simd/include/constants/minf.hpp>
#include <boost/simd/include/constants/nan.hpp>
#include <boost/simd/sdk/config.hpp>

NT2_TEST_CASE_TPL ( bitwise_ornot_real,  BOOST_SIMD_REAL_TYPES)
{

  using boost::simd::bitwise_ornot;
  using boost::simd::tag::bitwise_ornot_;
  typedef typename boost::dispatch::meta::call<bitwise_ornot_(T,T)>::type r_t;
  typedef T wished_r_t;


  // return type conformity test
  NT2_TEST_TYPE_IS(r_t, wished_r_t);

  // specific values tests
#ifndef BOOST_SIMD_NO_INVALIDS
  NT2_TEST_EQUAL(bitwise_ornot(boost::simd::Inf<T>(), boost::simd::Inf<T>()), boost::simd::Nan<r_t>());
  NT2_TEST_EQUAL(bitwise_ornot(boost::simd::Minf<T>(), boost::simd::Minf<T>()), boost::simd::Nan<r_t>());
  NT2_TEST_EQUAL(bitwise_ornot(boost::simd::Nan<T>(), boost::simd::Nan<T>()), boost::simd::Nan<r_t>());
#endif
  NT2_TEST_EQUAL(bitwise_ornot(boost::simd::Zero<T>(), boost::simd::Zero<T>()), boost::simd::Nan<r_t>());
} // end of test for floating_

NT2_TEST_CASE_TPL ( bitwise_ornot_integer,  BOOST_SIMD_INTEGRAL_TYPES)
{

  using boost::simd::bitwise_ornot;
  using boost::simd::tag::bitwise_ornot_;
  typedef typename boost::dispatch::meta::call<bitwise_ornot_(T,T)>::type r_t;
  typedef T wished_r_t;


  // return type conformity test
  NT2_TEST_TYPE_IS(r_t, wished_r_t);

  // specific values tests
  NT2_TEST_EQUAL(bitwise_ornot(boost::simd::Mone<T>(),boost::simd::Zero<T>()), boost::simd::Mone<r_t>());
  NT2_TEST_EQUAL(bitwise_ornot(boost::simd::One<T>(), boost::simd::One<T>()), boost::simd::Mone<r_t>());
  NT2_TEST_EQUAL(bitwise_ornot(boost::simd::One<T>(),boost::simd::Zero<T>()), boost::simd::Mone<r_t>());
  NT2_TEST_EQUAL(bitwise_ornot(boost::simd::Zero<T>(), boost::simd::Zero<T>()), boost::simd::Mone<r_t>());
} // end of test for integer_


NT2_TEST_CASE_TPL(bitwise_ornot_mix, BOOST_SIMD_REAL_TYPES)
{
  using boost::simd::bitwise_ornot;
  using boost::simd::tag::bitwise_ornot_;
  typedef typename  boost::dispatch::meta::as_integer<T>::type siT;
  typedef typename  boost::dispatch::meta::as_integer<T, unsigned>::type uiT;

  // return type conformity test
  NT2_TEST_TYPE_IS(typename boost::dispatch::meta::call<bitwise_ornot_(T,uiT)>::type, T);
  NT2_TEST_TYPE_IS(typename boost::dispatch::meta::call<bitwise_ornot_(T,siT)>::type, T);
  NT2_TEST_TYPE_IS(typename boost::dispatch::meta::call<bitwise_ornot_(uiT, T)>::type, uiT);
  NT2_TEST_TYPE_IS(typename boost::dispatch::meta::call<bitwise_ornot_(siT, T)>::type, siT);

  // specific values tests
  NT2_TEST_EQUAL(bitwise_ornot(boost::simd::Zero<T>(),boost::simd::Zero<uiT>()), boost::simd::Nan<T>());
  NT2_TEST_EQUAL(bitwise_ornot(boost::simd::Zero<T>(), boost::simd::Zero<siT>()), boost::simd::Nan<T>());
  NT2_TEST_EQUAL(bitwise_ornot(boost::simd::Valmin<siT>(),boost::simd::Nan<T>()), boost::simd::Valmin<siT>());
  NT2_TEST_EQUAL(bitwise_ornot(boost::simd::Zero<uiT>(), boost::simd::Nan<T>()), boost::simd::Zero<uiT>());
}
