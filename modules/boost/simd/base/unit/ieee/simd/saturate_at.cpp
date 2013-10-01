//==============================================================================
//         Copyright 2003 - 2013   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <boost/simd/ieee/include/functions/saturate_at.hpp>

#include <boost/dispatch/functor/meta/call.hpp>
#include <boost/simd/sdk/simd/native.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/ulp.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <boost/simd/sdk/config.hpp>
#include <boost/simd/sdk/simd/io.hpp>

#include <boost/simd/include/constants/mone.hpp>
#include <boost/simd/include/constants/mten.hpp>
#include <boost/simd/include/constants/one.hpp>
#include <boost/simd/include/constants/pi.hpp>
#include <boost/simd/include/constants/ten.hpp>
#include <boost/simd/include/constants/zero.hpp>
#include <boost/simd/include/constants/inf.hpp>
#include <boost/simd/include/constants/minf.hpp>
#include <boost/simd/include/constants/nan.hpp>

NT2_TEST_CASE_TPL ( saturate_at_real,  BOOST_SIMD_SIMD_REAL_TYPES)
{
  using boost::simd::saturate_at;
  using boost::simd::tag::saturate_at_;
  using boost::simd::native;
  typedef BOOST_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef native<T,ext_t>                  vT;
  typedef typename boost::dispatch::meta::call<saturate_at_<boost::simd::tag::Pi>(vT)>::type r_t;

  // specific values tests
#ifndef BOOST_SIMD_NO_INVALIDS
  NT2_TEST_ULP_EQUAL(saturate_at<boost::simd::tag::Pi>(boost::simd::Nan<vT>()) , boost::simd::Nan<r_t>(), 0);
  NT2_TEST_ULP_EQUAL(saturate_at<boost::simd::tag::Pi>(boost::simd::Minf<vT>()), -boost::simd::Pi<r_t>(), 0);
  NT2_TEST_ULP_EQUAL(saturate_at<boost::simd::tag::Pi>(boost::simd::Inf<vT>()) , boost::simd::Pi<r_t>(), 0);
#endif
  NT2_TEST_ULP_EQUAL(saturate_at<boost::simd::tag::Pi>(boost::simd::Mten<vT>()), -boost::simd::Pi<r_t>(), 0);
  NT2_TEST_ULP_EQUAL(saturate_at<boost::simd::tag::Pi>(boost::simd::Mone<vT>()), boost::simd::Mone<r_t>(), 0);
  NT2_TEST_ULP_EQUAL(saturate_at<boost::simd::tag::Pi>(boost::simd::Zero<vT>()), boost::simd::Zero<r_t>(), 0);
  NT2_TEST_ULP_EQUAL(saturate_at<boost::simd::tag::Pi>(boost::simd::One<vT>()) , boost::simd::One<r_t>(), 0);
  NT2_TEST_ULP_EQUAL(saturate_at<boost::simd::tag::Pi>(boost::simd::Ten<vT>()) , boost::simd::Pi<r_t>(), 0);
}
