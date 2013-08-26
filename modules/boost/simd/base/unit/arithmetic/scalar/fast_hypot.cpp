//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================

#include <boost/simd/arithmetic/include/functions/fast_hypot.hpp>
#include <boost/simd/sdk/simd/io.hpp>
#include <boost/dispatch/meta/as_integer.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/ulp.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>
#include <nt2/sdk/meta/as_floating.hpp>
#include <boost/simd/include/constants/two.hpp>
#include <boost/simd/include/constants/zero.hpp>
#include <boost/simd/include/constants/mtwo.hpp>
#include <boost/simd/include/constants/one.hpp>
#include <boost/simd/include/constants/mone.hpp>
#include <boost/simd/include/constants/inf.hpp>
#include <boost/simd/include/constants/minf.hpp>
#include <boost/simd/include/constants/nan.hpp>
#include <boost/simd/include/constants/valmax.hpp>
#include <boost/simd/include/constants/valmin.hpp>
#include <boost/simd/include/constants/sqrt_2.hpp>
#include <boost/simd/sdk/config.hpp>


NT2_TEST_CASE_TPL ( fast_hypot_real,  BOOST_SIMD_REAL_TYPES)
{

  using boost::simd::fast_hypot;
  using boost::simd::tag::fast_hypot_;
  typedef typename boost::dispatch::meta::call<fast_hypot_(T,T)>::type r_t;
  typedef T wished_r_t;


  // return type conformity test
  NT2_TEST_TYPE_IS(r_t, wished_r_t);

  // specific values tests
#ifndef BOOST_SIMD_NO_INVALIDS
  NT2_TEST_ULP_EQUAL(fast_hypot(boost::simd::Inf<T>(), boost::simd::Inf<T>()), boost::simd::Inf<r_t>(), 0);
  NT2_TEST_ULP_EQUAL(fast_hypot(boost::simd::Minf<T>(), boost::simd::Minf<T>()), boost::simd::Inf<r_t>(), 0);
  NT2_TEST_ULP_EQUAL(fast_hypot(boost::simd::Nan<T>(), boost::simd::Nan<T>()), boost::simd::Nan<r_t>(), 0);
#endif
  NT2_TEST_ULP_EQUAL(fast_hypot(boost::simd::Mone<T>(), boost::simd::Mone<T>()), boost::simd::Sqrt_2<r_t>(), 0.5);
  NT2_TEST_ULP_EQUAL(fast_hypot(boost::simd::One<T>(), boost::simd::One<T>()), boost::simd::Sqrt_2<r_t>(), 0.5);
  NT2_TEST_ULP_EQUAL(fast_hypot(boost::simd::Zero<T>(), boost::simd::Zero<T>()), boost::simd::Zero<T>(), 0);
} // end of test for floating_

NT2_TEST_CASE_TPL ( fast_hypot_unsigned_int,  BOOST_SIMD_UNSIGNED_TYPES)
{

  using boost::simd::fast_hypot;
  using boost::simd::tag::fast_hypot_;
  typedef typename boost::dispatch::meta::call<fast_hypot_(T,T)>::type r_t;
  typedef typename boost::dispatch::meta::as_floating<T,T>::type wished_r_t;


  // return type conformity test
  NT2_TEST_TYPE_IS(r_t, wished_r_t);

  // specific values tests
  NT2_TEST_ULP_EQUAL(fast_hypot(boost::simd::One<T>(), boost::simd::One<T>()), boost::simd::Sqrt_2<r_t>(), 0.5);
  NT2_TEST_ULP_EQUAL(fast_hypot(boost::simd::Zero<T>(), boost::simd::Zero<T>()), boost::simd::Zero<r_t>(), 0);
} // end of test for unsigned_int_

NT2_TEST_CASE_TPL ( fast_hypot_signed_int,  BOOST_SIMD_INTEGRAL_SIGNED_TYPES)
{

  using boost::simd::fast_hypot;
  using boost::simd::tag::fast_hypot_;
  typedef typename boost::dispatch::meta::call<fast_hypot_(T,T)>::type r_t;
  typedef typename boost::dispatch::meta::as_floating<T,T>::type wished_r_t;


  // return type conformity test
  NT2_TEST_TYPE_IS(r_t, wished_r_t);

  // specific values tests
  NT2_TEST_ULP_EQUAL(fast_hypot(boost::simd::Mone<T>(), boost::simd::Mone<T>()), boost::simd::Sqrt_2<r_t>(), 0.5);
  NT2_TEST_ULP_EQUAL(fast_hypot(boost::simd::One<T>(), boost::simd::One<T>()), boost::simd::Sqrt_2<r_t>(), 0.5);
  NT2_TEST_ULP_EQUAL(fast_hypot(boost::simd::Zero<T>(), boost::simd::Zero<T>()), boost::simd::Zero<r_t>(), 0);
} // end of test for signed_int_
