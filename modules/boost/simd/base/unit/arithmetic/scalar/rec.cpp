//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <boost/simd/arithmetic/include/functions/rec.hpp>
#include <boost/dispatch/functor/meta/call.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/ulp.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>

#include <boost/simd/include/constants/inf.hpp>
#include <boost/simd/include/constants/one.hpp>
#include <boost/simd/include/constants/zero.hpp>
#include <boost/simd/include/constants/mone.hpp>
#include <boost/simd/include/constants/mzero.hpp>
#include <boost/simd/include/constants/minf.hpp>
#include <boost/simd/include/constants/nan.hpp>

NT2_TEST_CASE_TPL( rec_,  NT2_REAL_TYPES)
{
  using boost::simd::rec;
  using boost::simd::tag::rec_;

  // return type conformity test
  NT2_TEST_TYPE_IS( typename boost::dispatch::meta::call<rec_(T)>::type , T );

  // specific values tests
  NT2_TEST_ULP_EQUAL(rec(boost::simd::Inf<T>()), boost::simd::Zero<T>(), 0);
  NT2_TEST_ULP_EQUAL(rec(boost::simd::Minf<T>()), boost::simd::Zero<T>(), 0);
  NT2_TEST_ULP_EQUAL(rec(boost::simd::Mone<T>()), boost::simd::Mone<T>(), 0);
  NT2_TEST_ULP_EQUAL(rec(boost::simd::Mzero<T>()), boost::simd::Minf<T>(), 0);
  NT2_TEST_ULP_EQUAL(rec(boost::simd::Nan<T>()), boost::simd::Nan<T>(), 0);
  NT2_TEST_ULP_EQUAL(rec(boost::simd::One<T>()), boost::simd::One<T>(), 0);
  NT2_TEST_ULP_EQUAL(rec(boost::simd::Zero<T>()), boost::simd::Inf<T>(), 0);
} // end of test for floating_
