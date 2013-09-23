//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <boost/simd/arithmetic/include/functions/simd/fast_rsqrt.hpp>
#include <boost/simd/include/functions/splat.hpp>
#include <boost/dispatch/functor/meta/call.hpp>
#include <boost/simd/sdk/simd/io.hpp>
#include <boost/simd/sdk/simd/native.hpp>
#include <boost/simd/include/constants/one.hpp>
#include <boost/simd/include/constants/mone.hpp>
#include <boost/simd/include/constants/nan.hpp>
#include <boost/simd/include/constants/four.hpp>
#include <boost/simd/include/constants/half.hpp>
#include <boost/simd/include/constants/sqrt_2.hpp>

#include <nt2/sdk/unit/tests/ulp.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>
#include <nt2/sdk/unit/module.hpp>

NT2_TEST_CASE_TPL( fast_rsqrt, BOOST_SIMD_SIMD_REAL_TYPES )
{
  using boost::simd::fast_rsqrt;
  using boost::simd::tag::fast_rsqrt_;
  using boost::simd::native;
  using boost::simd::splat;

  typedef BOOST_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef native<T,ext_t>                  vT;

  // return type conformity test
  NT2_TEST_TYPE_IS( typename boost::dispatch::meta::call<fast_rsqrt_(vT)>::type
                  , vT
                  );

  // specific values tests
  NT2_TEST_ULP_EQUAL(fast_rsqrt(boost::simd::Mone<vT>()), boost::simd::Nan<vT>(), 75);
  NT2_TEST_ULP_EQUAL(fast_rsqrt(boost::simd::Nan<vT>()), boost::simd::Nan<vT>(), 75);
  NT2_TEST_ULP_EQUAL(fast_rsqrt(boost::simd::One<vT>()), boost::simd::One<vT>(), 75);
  NT2_TEST_ULP_EQUAL(fast_rsqrt(boost::simd::Four<vT>()), boost::simd::Half<vT>(), 75);
  NT2_TEST_ULP_EQUAL(fast_rsqrt(splat<vT>(0.5)), boost::simd::Sqrt_2<vT>(), 75);
  NT2_TEST_ULP_EQUAL(fast_rsqrt(splat<vT>(0.01)), splat<vT>(10), 75);
  NT2_TEST_ULP_EQUAL(fast_rsqrt(splat<vT>(0.0001)), splat<vT>(100), 75);
}
