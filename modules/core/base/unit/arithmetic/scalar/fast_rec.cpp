//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/arithmetic/include/functions/fast_rec.hpp>

#include <boost/dispatch/functor/meta/call.hpp>
#include <boost/simd/constant/constant.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/ulp.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>

NT2_TEST_CASE_TPL ( fast_rec,  BOOST_SIMD_SIMD_REAL_TYPES)
{
  using nt2::fast_rec;
  using nt2::tag::fast_rec_;

  NT2_TEST_TYPE_IS( typename boost::dispatch::meta::call<fast_rec_(T)>::type
                  , T
                  );

  // specific values tests

  // 1/+-inf = 0
  NT2_TEST_ULP_EQUAL(fast_rec(boost::simd::Inf<T>()) , boost::simd::Zero<T>(), 0.5);
  NT2_TEST_ULP_EQUAL(fast_rec(boost::simd::Minf<T>()), boost::simd::Zero<T>(), 0.5);

  // 1/+-0 = +-inf
  NT2_TEST_ULP_EQUAL(fast_rec(boost::simd::Mzero<T>()), boost::simd::Minf<T>(), 0.5);
  NT2_TEST_ULP_EQUAL(fast_rec(boost::simd::Zero<T>()), boost::simd::Inf<T>(), 0.5);

  // 1/Nan = Nan
  NT2_TEST_ULP_EQUAL(fast_rec(boost::simd::Nan<T>()), boost::simd::Nan<T>(), 0.5);

  // 1/+-1 = +-1
  NT2_TEST_ULP_EQUAL(fast_rec(boost::simd::Mone<T>()), boost::simd::Mone<T>(), 0.5);
  NT2_TEST_ULP_EQUAL(fast_rec(boost::simd::One<T>()), boost::simd::One<T>(), 0.5);

  // 1/(1/x) = x
  NT2_TEST_ULP_EQUAL(fast_rec(fast_rec(boost::simd::Ten<T>())), boost::simd::Ten<T>(), 0.5);
}
