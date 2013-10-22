//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <boost/simd/arithmetic/include/functions/fast_sqrt.hpp>
#include <boost/dispatch/meta/as_integer.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/ulp.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>
#include <nt2/sdk/meta/as_floating.hpp>
#include <boost/simd/include/constants/zero.hpp>
#include <boost/simd/include/constants/two.hpp>
#include <boost/simd/include/constants/mtwo.hpp>
#include <boost/simd/include/constants/one.hpp>
#include <boost/simd/include/constants/four.hpp>
#include <boost/simd/include/constants/mone.hpp>
#include <boost/simd/include/constants/inf.hpp>
#include <boost/simd/include/constants/minf.hpp>
#include <boost/simd/include/constants/nan.hpp>
#include <boost/simd/include/constants/sqrt_2.hpp>
#include <boost/simd/sdk/config.hpp>

NT2_TEST_CASE_TPL ( fast_sqrt_real,  BOOST_SIMD_REAL_TYPES)
{
  using boost::simd::fast_sqrt;
  using boost::simd::tag::fast_sqrt_;
  typedef typename boost::dispatch::meta::call<fast_sqrt_(T)>::type r_t;
  typedef typename boost::dispatch::meta::as_floating<T>::type wished_r_t;

  // return type conformity test
  NT2_TEST_TYPE_IS(r_t, wished_r_t);

  NT2_TEST_EQUAL(fast_sqrt(boost::simd::Mone<T>()), boost::simd::Nan<r_t>());
  NT2_TEST_ULP_EQUAL(fast_sqrt(boost::simd::One<T>()), boost::simd::One<r_t>(), 75);
  NT2_TEST_ULP_EQUAL(fast_sqrt(boost::simd::Two<T>()), boost::simd::Sqrt_2<r_t>(), 75);
  NT2_TEST_ULP_EQUAL(fast_sqrt(boost::simd::Zero<T>()), boost::simd::Zero<r_t>(), 75);
  NT2_TEST_ULP_EQUAL(fast_sqrt(boost::simd::Four<T>()), boost::simd::Two<r_t>(), 75);
}

NT2_TEST_CASE_TPL ( fast_sqrt_si,  BOOST_SIMD_INTEGRAL_SIGNED_TYPES)
{
  using boost::simd::fast_sqrt;
  using boost::simd::tag::fast_sqrt_;
  typedef typename boost::dispatch::meta::call<fast_sqrt_(T)>::type r_t;
  typedef T wished_r_t;

  // return type conformity test
  NT2_TEST_TYPE_IS(r_t, wished_r_t);

  // specific values tests
  NT2_TEST_EQUAL(fast_sqrt(boost::simd::Zero<T>()), boost::simd::Zero<r_t>());
  NT2_TEST_EQUAL(fast_sqrt(boost::simd::One<T>()), boost::simd::One<r_t>());
  NT2_TEST_EQUAL(fast_sqrt(boost::simd::Two<T>()), boost::simd::One<r_t>());
  NT2_TEST_EQUAL(fast_sqrt(boost::simd::Zero<T>()), boost::simd::Zero<r_t>());
  NT2_TEST_EQUAL(fast_sqrt(boost::simd::Four<T>()), boost::simd::Two<r_t>());
}

NT2_TEST_CASE_TPL ( fast_sqrt_ui,  BOOST_SIMD_UNSIGNED_TYPES)
{
  using boost::simd::fast_sqrt;
  using boost::simd::tag::fast_sqrt_;
  typedef typename boost::dispatch::meta::call<fast_sqrt_(T)>::type r_t;
  typedef T wished_r_t;

  // return type conformity test
  NT2_TEST_TYPE_IS(r_t, wished_r_t);

  // specific values tests
  NT2_TEST_EQUAL(fast_sqrt(boost::simd::Zero<T>()), boost::simd::Zero<r_t>());
  NT2_TEST_EQUAL(fast_sqrt(boost::simd::One<T>()), boost::simd::One<r_t>());
  NT2_TEST_EQUAL(fast_sqrt(boost::simd::Two<T>()), boost::simd::One<r_t>());
  NT2_TEST_EQUAL(fast_sqrt(boost::simd::Zero<T>()), boost::simd::Zero<r_t>());
  NT2_TEST_EQUAL(fast_sqrt(boost::simd::Four<T>()), boost::simd::Two<r_t>());
}
