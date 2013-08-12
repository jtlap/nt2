//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <boost/simd/ieee/include/functions/negate.hpp>
#include <boost/simd/sdk/simd/native.hpp>
#include <boost/simd/include/functions/sign.hpp>

#include <boost/dispatch/functor/meta/call.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <boost/simd/constant/constant.hpp>


NT2_TEST_CASE_TPL ( negate_real__2_0,  BOOST_SIMD_REAL_TYPES)
{

  using boost::simd::negate;
  using boost::simd::tag::negate_;
  typedef typename boost::dispatch::meta::call<negate_(T,T)>::type r_t;
  typedef T wished_r_t;


  // return type conformity test
  NT2_TEST_TYPE_IS(r_t, wished_r_t);

  // specific values tests
  NT2_TEST_EQUAL(negate(boost::simd::Inf<T>(), boost::simd::Inf<T>()), boost::simd::Inf<r_t>());
  NT2_TEST_EQUAL(negate(boost::simd::Minf<T>(), boost::simd::Minf<T>()), boost::simd::Inf<r_t>());
  NT2_TEST_EQUAL(negate(boost::simd::Mone<T>(), boost::simd::Mone<T>()), boost::simd::One<r_t>());
  NT2_TEST_EQUAL(negate(boost::simd::Nan<T>(), boost::simd::Nan<T>()), boost::simd::Nan<r_t>());
  NT2_TEST_EQUAL(negate(boost::simd::One<T>(), boost::simd::One<T>()), boost::simd::One<r_t>());
  NT2_TEST_EQUAL(negate(boost::simd::Zero<T>(), boost::simd::Zero<T>()), boost::simd::Zero<r_t>());
  NT2_TEST_EQUAL(negate(boost::simd::One<T>(), boost::simd::Zero<T>()), boost::simd::Zero<r_t>());
  NT2_TEST_EQUAL(negate(boost::simd::Two<T>(), boost::simd::Mthree<T>()), boost::simd::Mtwo<r_t>());
  NT2_TEST_EQUAL(negate(boost::simd::Two<T>(), boost::simd::Three<T>()), boost::simd::Two<r_t>());
  NT2_TEST_EQUAL(negate(boost::simd::Nan<T>(), boost::simd::Zero<T>()), boost::simd::Nan<r_t>());
  NT2_TEST_EQUAL(negate(boost::simd::Zero<T>(), boost::simd::Nan<T>()), boost::simd::Nan<r_t>());
  NT2_TEST_EQUAL(negate(boost::simd::Nan<T>(), boost::simd::Zero<T>()), boost::simd::Nan<r_t>());
  NT2_TEST_EQUAL(negate(boost::simd::One<T>(), boost::simd::Nan<T>()), boost::simd::Nan<r_t>());
  NT2_TEST_EQUAL(negate(boost::simd::Nan<T>(), boost::simd::One<T>()), boost::simd::Nan<r_t>());
} // end of test for floating_

NT2_TEST_CASE_TPL ( negate_unsigned_int__2_0,  BOOST_SIMD_UNSIGNED_TYPES)
{

  using boost::simd::negate;
  using boost::simd::tag::negate_;
  typedef typename boost::dispatch::meta::call<negate_(T,T)>::type r_t;
  typedef T wished_r_t;

  NT2_TEST_TYPE_IS(r_t, wished_r_t);

  // specific values tests
  NT2_TEST_EQUAL(negate(boost::simd::One<T>(), boost::simd::One<T>()), boost::simd::One<r_t>());
  NT2_TEST_EQUAL(negate(boost::simd::Zero<T>(), boost::simd::Zero<T>()), boost::simd::Zero<r_t>());
  NT2_TEST_EQUAL(negate(boost::simd::One<T>(), boost::simd::Zero<T>()), boost::simd::Zero<r_t>());

} // end of test for unsigned_int_

NT2_TEST_CASE_TPL ( negate_signed_int__2_0,  BOOST_SIMD_INTEGRAL_SIGNED_TYPES)
{

  using boost::simd::negate;
  using boost::simd::tag::negate_;
  typedef typename boost::dispatch::meta::call<negate_(T,T)>::type r_t;
  typedef T wished_r_t;

  NT2_TEST_TYPE_IS(r_t, wished_r_t);

  // specific values tests
  NT2_TEST_EQUAL(negate(boost::simd::Mone<T>(), boost::simd::Mone<T>()), boost::simd::One<r_t>());
  NT2_TEST_EQUAL(negate(boost::simd::One<T>(), boost::simd::One<T>()), boost::simd::One<r_t>());
  NT2_TEST_EQUAL(negate(boost::simd::Zero<T>(), boost::simd::Zero<T>()), boost::simd::Zero<r_t>());
  NT2_TEST_EQUAL(negate(boost::simd::One<T>(), boost::simd::Zero<T>()), boost::simd::Zero<r_t>());
} // end of test for signed_int_
