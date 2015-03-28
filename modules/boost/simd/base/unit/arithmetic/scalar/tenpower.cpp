//==============================================================================
//         Copyright 2015 J.T. Lapreste
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <boost/simd/arithmetic/include/functions/tenpower.hpp>
#include <boost/dispatch/functor/meta/call.hpp>
#include <nt2/sdk/unit/tests/ulp.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <boost/simd/include/constants/one.hpp>
#include <boost/simd/include/constants/oneo_10.hpp>
#include <boost/simd/include/constants/zero.hpp>
#include <boost/simd/include/constants/mone.hpp>
#include <boost/simd/include/constants/hundred.hpp>
#include <boost/simd/include/functions/sqr.hpp>


NT2_TEST_CASE_TPL ( tenpower_unsigned_int, BOOST_SIMD_UNSIGNED_TYPES)
{

  using boost::simd::tenpower;
  using boost::simd::tag::tenpower_;
  typedef typename boost::dispatch::meta::call<tenpower_(T)>::type r_t;
  typedef typename boost::dispatch::meta::as_floating<T>::type  wished_r_t;

  NT2_TEST_TYPE_IS(r_t, wished_r_t);

  // specific values tests
  NT2_TEST_ULP_EQUAL(tenpower(boost::simd::One<T>()), boost::simd::Ten<r_t>(), 0.5);
  NT2_TEST_ULP_EQUAL(tenpower(boost::simd::Two<T>()), boost::simd::Hundred<r_t>(), 0.5);
  NT2_TEST_ULP_EQUAL(tenpower(boost::simd::Zero<T>()), boost::simd::One<r_t>(), 0.5);
} // end of test for unsigned_int_

NT2_TEST_CASE_TPL ( tenpower_signed_int,  BOOST_SIMD_INTEGRAL_SIGNED_TYPES)
{

  using boost::simd::tenpower;
  using boost::simd::tag::tenpower_;
  typedef typename boost::dispatch::meta::call<tenpower_(T)>::type r_t;
  typedef typename boost::dispatch::meta::as_floating<T>::type  wished_r_t;

  NT2_TEST_TYPE_IS(r_t, wished_r_t);

  // specific values tests
  NT2_TEST_ULP_EQUAL(tenpower(boost::simd::Mone<T>()), boost::simd::Oneo_10<r_t>(), 0.5);
  NT2_TEST_ULP_EQUAL(tenpower(boost::simd::One<T>()), boost::simd::Ten<r_t>(), 0.5);
  NT2_TEST_ULP_EQUAL(tenpower(boost::simd::Two<T>()), boost::simd::Hundred<r_t>(), 0.5);
  NT2_TEST_ULP_EQUAL(tenpower(boost::simd::Mtwo<T>()), boost::simd::sqr(boost::simd::Oneo_10<r_t>()), 0.5);
  NT2_TEST_ULP_EQUAL(tenpower(boost::simd::Zero<T>()), boost::simd::One<r_t>(), 0.5);
} // end of test for signed_int_
