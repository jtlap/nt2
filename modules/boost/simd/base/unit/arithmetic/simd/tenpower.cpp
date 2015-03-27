//==============================================================================
//         Copyright 2015 J.T. Lapreste
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <boost/simd/arithmetic/include/functions/tenpower.hpp>
#include <boost/simd/sdk/simd/native.hpp>
#include <boost/dispatch/functor/meta/call.hpp>
#include <nt2/sdk/unit/tests/ulp.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <boost/simd/include/constants/one.hpp>
#include <boost/simd/include/constants/oneo_10.hpp>
#include <boost/simd/include/constants/zero.hpp>
#include <boost/simd/include/constants/mone.hpp>
#include <boost/simd/include/constants/two.hpp>
#include <boost/simd/include/constants/three.hpp>
#include <boost/simd/include/constants/hundred.hpp>
#include <boost/simd/include/functions/sqr.hpp>
#include <boost/simd/include/functions/splat.hpp>


NT2_TEST_CASE_TPL ( tenpower_unsigned_int, BOOST_SIMD_SIMD_UINT_CONVERT_TYPES)
{

  using boost::simd::tenpower;
  using boost::simd::tag::tenpower_;
  using boost::simd::native;
  typedef BOOST_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef native<T,ext_t>                  vT;
  typedef typename boost::dispatch::meta::call<tenpower_(vT)>::type r_t;

  // specific values tests
  NT2_TEST_ULP_EQUAL(tenpower(boost::simd::One<vT>()), boost::simd::Ten<r_t>(), 0.5);
  NT2_TEST_ULP_EQUAL(tenpower(boost::simd::Two<vT>()), boost::simd::Hundred<r_t>(), 0.5);
  NT2_TEST_ULP_EQUAL(tenpower(boost::simd::Zero<vT>()), boost::simd::One<r_t>(), 0.5);
} // end of test for unsigned_int_

NT2_TEST_CASE_TPL ( tenpower_signed_int,  BOOST_SIMD_SIMD_INT_CONVERT_TYPES)
{

  using boost::simd::tenpower;
  using boost::simd::tag::tenpower_;
  using boost::simd::native;
  typedef BOOST_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef native<T,ext_t>                  vT;
  typedef typename boost::dispatch::meta::call<tenpower_(vT)>::type r_t;
  // specific values tests
  NT2_TEST_ULP_EQUAL(tenpower(boost::simd::Mone<vT>()), boost::simd::Oneo_10<r_t>(), 0.5);
  NT2_TEST_ULP_EQUAL(tenpower(boost::simd::One<vT>()), boost::simd::Ten<r_t>(), 0.5);
  NT2_TEST_ULP_EQUAL(tenpower(boost::simd::Two<vT>()), boost::simd::Hundred<r_t>(), 0.5);
  NT2_TEST_ULP_EQUAL(tenpower(boost::simd::Three<vT>()),boost::simd::splat<r_t>(1000.0), 0.5);
  NT2_TEST_ULP_EQUAL(tenpower(boost::simd::Mtwo<vT>()), boost::simd::sqr(boost::simd::Oneo_10<r_t>()), 0.5);
  NT2_TEST_ULP_EQUAL(tenpower(boost::simd::Zero<vT>()), boost::simd::One<r_t>(), 0.5);
} // end of test for signed_int_
