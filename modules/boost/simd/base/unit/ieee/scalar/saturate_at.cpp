//==============================================================================
//         Copyright 2003 - 2013   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <boost/simd/ieee/include/functions/saturate_at.hpp>
#include <boost/simd/sdk/simd/logical.hpp>

#include <boost/dispatch/functor/meta/call.hpp>
#include <nt2/sdk/unit/tests/ulp.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <boost/simd/sdk/config.hpp>

#include <boost/simd/include/constants/mone.hpp>
#include <boost/simd/include/constants/one.hpp>
#include <boost/simd/include/constants/pi.hpp>
#include <boost/simd/include/constants/valmax.hpp>
#include <boost/simd/include/constants/valmin.hpp>
#include <boost/simd/include/constants/zero.hpp>
#include <boost/simd/include/constants/inf.hpp>
#include <boost/simd/include/constants/minf.hpp>
#include <boost/simd/include/constants/nan.hpp>

NT2_TEST_CASE_TPL ( saturate_at_real,  BOOST_SIMD_REAL_TYPES)
{
  using boost::simd::saturate_at;
  using boost::simd::tag::saturate_at_;
  using boost::simd::tag::Pi;
  typedef typename boost::dispatch::meta::call<saturate_at_<boost::simd::tag::Pi>(T)>::type r_t;
  typedef T wished_r_t;

  // return type conformity test
  NT2_TEST_TYPE_IS(r_t, wished_r_t);

  // specific values tests
#ifndef BOOST_SIMD_NO_INVALIDS
  NT2_TEST_ULP_EQUAL(saturate_at<Pi>(boost::simd::Inf<T>()), boost::simd::Pi<r_t>(), 0);
  NT2_TEST_ULP_EQUAL(saturate_at<Pi>(boost::simd::Minf<T>()), -boost::simd::Pi<r_t>(), 0);
  NT2_TEST_ULP_EQUAL(saturate_at<Pi>(boost::simd::Nan<T>()), boost::simd::Nan<r_t>(), 0);
#endif
  NT2_TEST_ULP_EQUAL(saturate_at<Pi>(boost::simd::Mone<T>()), boost::simd::Mone<r_t>(), 0);
  NT2_TEST_ULP_EQUAL(saturate_at<Pi>(boost::simd::One<T>()), boost::simd::One<r_t>(), 0);
  NT2_TEST_ULP_EQUAL(saturate_at<Pi>(boost::simd::Zero<T>()), boost::simd::Zero<r_t>(), 0);
}

NT2_TEST_CASE_TPL ( saturate_at_signed_int,  BOOST_SIMD_INTEGRAL_SIGNED_TYPES)
{
  using boost::simd::saturate_at;
  using boost::simd::tag::saturate_at_;
  using boost::simd::tag::Pi;
  typedef typename boost::dispatch::meta::call<saturate_at_<Pi>(T)>::type r_t;
  typedef T wished_r_t;

  // return type conformity test
  NT2_TEST_TYPE_IS(r_t, wished_r_t);

  // specific values tests
  NT2_TEST_ULP_EQUAL(saturate_at<Pi>(boost::simd::Mone<T>()), boost::simd::Mone<r_t>(), 0);
  NT2_TEST_ULP_EQUAL(saturate_at<Pi>(boost::simd::One<T>()), boost::simd::One<r_t>(), 0);
  NT2_TEST_ULP_EQUAL(saturate_at<Pi>(boost::simd::Valmax<T>()), boost::simd::Pi<r_t>(), 0);
  NT2_TEST_ULP_EQUAL(saturate_at<Pi>(boost::simd::Valmin<T>()), -boost::simd::Pi<r_t>(), 0);
  NT2_TEST_ULP_EQUAL(saturate_at<Pi>(boost::simd::Zero<T>()), boost::simd::Zero<r_t>(), 0);
}
