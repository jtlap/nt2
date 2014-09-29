//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <boost/simd/operator/include/functions/bitwise_xor.hpp>

#include <boost/dispatch/functor/meta/call.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <boost/simd/sdk/config.hpp>
#include <boost/simd/sdk/simd/io.hpp>

#include <boost/simd/include/constants/one.hpp>
#include <boost/simd/include/constants/mone.hpp>
#include <boost/simd/include/constants/zero.hpp>
#include <boost/simd/include/constants/three.hpp>
#include <boost/simd/include/constants/inf.hpp>
#include <boost/simd/include/constants/minf.hpp>
#include <boost/simd/include/constants/nan.hpp>
#include <boost/simd/include/constants/valmax.hpp>

NT2_TEST_CASE_TPL ( bitwise_xor_real,  BOOST_SIMD_REAL_TYPES)
{
  using boost::simd::bitwise_xor;
  using boost::simd::tag::bitwise_xor_;
  typedef typename boost::dispatch::meta::call<bitwise_xor_(T,T)>::type r_t;

  // return type conformity test
  NT2_TEST_TYPE_IS(r_t, T);

  // specific values tests
#ifndef BOOST_SIMD_NO_INVALIDS
  NT2_TEST_EQUAL(bitwise_xor(boost::simd::Inf<T>(), boost::simd::Inf<T>()), boost::simd::Zero<r_t>());
  NT2_TEST_EQUAL(bitwise_xor(boost::simd::Minf<T>(), boost::simd::Minf<T>()), boost::simd::Zero<r_t>());
  NT2_TEST_EQUAL(bitwise_xor(boost::simd::Nan<T>(), boost::simd::Nan<T>()), boost::simd::Zero<r_t>());
#endif
  NT2_TEST_EQUAL(bitwise_xor(boost::simd::One<T>(),boost::simd::Zero<T>()), boost::simd::One<r_t>());
  NT2_TEST_EQUAL(bitwise_xor(boost::simd::Zero<T>(), boost::simd::Zero<T>()), boost::simd::Zero<r_t>());
} // end of test for floating_

NT2_TEST_CASE_TPL ( bitwise_xor_integer,  BOOST_SIMD_INTEGRAL_TYPES)
{

  using boost::simd::bitwise_xor;
  using boost::simd::tag::bitwise_xor_;
  typedef typename boost::dispatch::meta::call<bitwise_xor_(T,T)>::type r_t;

  // return type conformity test
  NT2_TEST_TYPE_IS(r_t, T);

  // specific values tests
  NT2_TEST_EQUAL(bitwise_xor(boost::simd::One<T>(), boost::simd::One<T>()), boost::simd::Zero<r_t>());
  NT2_TEST_EQUAL(bitwise_xor(boost::simd::One<T>(),boost::simd::Zero<T>()), boost::simd::One<r_t>());
  NT2_TEST_EQUAL(bitwise_xor(boost::simd::Zero<T>(), boost::simd::Zero<T>()), boost::simd::Zero<r_t>());
} // end of test for integer_


NT2_TEST_CASE_TPL(bitwise_xor_mix, BOOST_SIMD_REAL_TYPES)
{
  using boost::simd::bitwise_xor;
  using boost::simd::tag::bitwise_xor_;
  typedef typename  boost::dispatch::meta::as_integer<T>::type siT;
  typedef typename  boost::dispatch::meta::as_integer<T, unsigned>::type uiT;

  // return type conformity test
  NT2_TEST_TYPE_IS(typename boost::dispatch::meta::call<bitwise_xor_(T,uiT)>::type, T);
  NT2_TEST_TYPE_IS(typename boost::dispatch::meta::call<bitwise_xor_(T,siT)>::type, T);
  NT2_TEST_TYPE_IS(typename boost::dispatch::meta::call<bitwise_xor_(uiT, T)>::type, uiT);
  NT2_TEST_TYPE_IS(typename boost::dispatch::meta::call<bitwise_xor_(siT, T)>::type, siT);

  // specific values tests
  NT2_TEST_EQUAL(bitwise_xor(boost::simd::Nan<T>(),boost::simd::Valmax<uiT>()), boost::simd::Zero<T>());
  NT2_TEST_EQUAL(bitwise_xor(boost::simd::Nan<T>(), boost::simd::Mone<siT>()), boost::simd::Zero<T>());
  NT2_TEST_EQUAL(bitwise_xor(boost::simd::Mone<siT>(),boost::simd::Zero<T>()), boost::simd::Mone<siT>());
  NT2_TEST_EQUAL(bitwise_xor(boost::simd::Valmax<uiT>(), boost::simd::Zero<T>()), boost::simd::Valmax<uiT>());
}
