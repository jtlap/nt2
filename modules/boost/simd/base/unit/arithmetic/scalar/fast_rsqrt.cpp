//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <boost/simd/arithmetic/include/functions/scalar/fast_rsqrt.hpp>
#include <boost/dispatch/functor/meta/call.hpp>
#include <boost/simd/include/constants/one.hpp>
#include <boost/simd/include/constants/mone.hpp>
#include <boost/simd/include/constants/nan.hpp>
#include <boost/simd/include/constants/four.hpp>
#include <boost/simd/include/constants/half.hpp>
#include <boost/simd/include/constants/sqrt_2.hpp>

#include <nt2/sdk/unit/tests/ulp.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>
#include <nt2/sdk/unit/module.hpp>

NT2_TEST_CASE_TPL( fast_rsqrt, BOOST_SIMD_REAL_TYPES )
{
  using boost::simd::fast_rsqrt;
  using boost::simd::tag::fast_rsqrt_;

  // return type conformity test
  NT2_TEST_TYPE_IS( typename boost::dispatch::meta::call<fast_rsqrt_(T)>::type
                  , T
                  );

  // specific values tests
  NT2_TEST_ULP_EQUAL(fast_rsqrt(boost::simd::Nan<T>()), boost::simd::Nan<T>(), 0.5);
  NT2_TEST_ULP_EQUAL(fast_rsqrt(boost::simd::One<T>()), boost::simd::One<T>(), 30);
  NT2_TEST_ULP_EQUAL(fast_rsqrt(boost::simd::Four<T>()), boost::simd::Half<T>(), 30);
  NT2_TEST_ULP_EQUAL(fast_rsqrt(T(0.5)), boost::simd::Sqrt_2<T>(), 70);
  NT2_TEST_ULP_EQUAL(fast_rsqrt(T(0.01)), T(10), 30);
  NT2_TEST_ULP_EQUAL(fast_rsqrt(T(0.0001)), T(100), 30);
}
