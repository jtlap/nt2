//==============================================================================
//         Copyright 2003 - 2013   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/include/functions/sqr.hpp>

#include <boost/dispatch/functor/meta/call.hpp>
#include <nt2/sdk/functor/meta/call.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>
#include <complex>
#include <nt2/sdk/complex/complex.hpp>
#include <nt2/sdk/unit/tests/ulp.hpp>
#include <nt2/sdk/unit/tests/basic.hpp>
#include <nt2/sdk/meta/as_integer.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <boost/simd/sdk/config.hpp>

#include <nt2/include/constants/mone.hpp>
#include <nt2/include/constants/one.hpp>
#include <nt2/include/constants/zero.hpp>
#include <nt2/include/constants/inf.hpp>
#include <nt2/include/constants/minf.hpp>
#include <nt2/include/constants/nan.hpp>

NT2_TEST_CASE_TPL ( sqr_real,  BOOST_SIMD_REAL_TYPES)
{
  using nt2::sqr;
  using nt2::tag::sqr_;
  typedef typename std::complex<T> cT;
  typedef typename boost::dispatch::meta::call<sqr_(T)>::type r_t;

  // return type conformity test
  NT2_TEST_TYPE_IS(r_t, cT);

  // specific values tests
#ifndef BOOST_SIMD_NO_INVALIDS
  NT2_TEST_ULP_EQUAL(sqr(boost::simd::Inf<T>()), boost::simd::Inf<T>(), 0);
  NT2_TEST_ULP_EQUAL(sqr(boost::simd::Minf<T>()), boost::simd::Inf<T>(), 0);
  NT2_TEST_ULP_EQUAL(sqr(boost::simd::Nan<T>()), boost::simd::Nan<T>(), 0);
#endif
  NT2_TEST_ULP_EQUAL(sqr(boost::simd::Mone<T>()), boost::simd::One<T>(), 0);
  NT2_TEST_ULP_EQUAL(sqr(boost::simd::One<T>()), boost::simd::One<T>(), 0);
  NT2_TEST_ULP_EQUAL(sqr(boost::simd::Zero<T>()), boost::simd::Zero<T>(), 0);
          NT2_TEST_ULP_EQUAL(nt2::sqr(cT(i, j)), nt2::mul(cT(i, j),cT(i, j)) , 10);
}
