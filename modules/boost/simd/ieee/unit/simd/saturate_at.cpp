//////////////////////////////////////////////////////////////////////////////
//   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
//   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#define NT2_UNIT_MODULE "nt2 boost.simd.ieee toolbox - saturate_at/simd Mode"

//////////////////////////////////////////////////////////////////////////////
// unit test behavior of boost.simd.ieee components in simd mode
//////////////////////////////////////////////////////////////////////////////

#include <boost/simd/toolbox/ieee/include/functions/saturate_at.hpp>
#include <boost/simd/sdk/simd/native.hpp>
#include <boost/simd/sdk/simd/io.hpp>
#include <boost/type_traits/is_same.hpp>
#include <nt2/sdk/unit/tests.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <boost/dispatch/functor/meta/call.hpp>
#include <boost/simd/include/constants/zero.hpp>
#include <boost/simd/include/constants/one.hpp>
#include <boost/simd/include/constants/mone.hpp>
#include <boost/simd/include/constants/pi.hpp>
#include <boost/simd/include/constants/four.hpp>
#include <boost/simd/include/constants/mten.hpp>
#include <boost/simd/include/constants/ten.hpp>

NT2_TEST_CASE_TPL ( saturate_at_real__1_0,  BOOST_SIMD_SIMD_REAL_TYPES)
{
  using boost::simd::native;
  using boost::simd::saturate_at;
  using boost::simd::tag::saturate_at_;
  typedef BOOST_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef native<T,ext_t>                        n_t;
  typedef typename boost::dispatch::meta::call<saturate_at_<boost::simd::tag::Pi>(n_t)>::type r_t;
  typedef typename boost::simd::meta::scalar_of<r_t>::type sr_t;

  NT2_TEST_TYPE_IS( r_t, (native<T,ext_t>) );

  NT2_TEST_ULP_EQUAL(saturate_at<boost::simd::tag::Pi>(boost::simd::Nan<n_t>())[0] , boost::simd::Nan<sr_t>(), 0);
  NT2_TEST_ULP_EQUAL(saturate_at<boost::simd::tag::Pi>(boost::simd::Minf<n_t>())[0], -boost::simd::Pi<sr_t>(), 0);
  NT2_TEST_ULP_EQUAL(saturate_at<boost::simd::tag::Pi>(boost::simd::Mten<n_t>())[0], -boost::simd::Pi<sr_t>(), 0);
  NT2_TEST_ULP_EQUAL(saturate_at<boost::simd::tag::Pi>(boost::simd::Mone<n_t>())[0], boost::simd::Mone<sr_t>(), 0);
  NT2_TEST_ULP_EQUAL(saturate_at<boost::simd::tag::Pi>(boost::simd::Zero<n_t>())[0], boost::simd::Zero<sr_t>(), 0);
  NT2_TEST_ULP_EQUAL(saturate_at<boost::simd::tag::Pi>(boost::simd::One<n_t>())[0] , boost::simd::One<sr_t>(), 0);
  NT2_TEST_ULP_EQUAL(saturate_at<boost::simd::tag::Pi>(boost::simd::Ten<n_t>())[0] , boost::simd::Pi<sr_t>(), 0);
  NT2_TEST_ULP_EQUAL(saturate_at<boost::simd::tag::Pi>(boost::simd::Inf<n_t>())[0] , boost::simd::Pi<sr_t>(), 0);
}

NT2_TEST_CASE_TPL ( saturate_at_signed,  BOOST_SIMD_SIMD_INTEGRAL_SIGNED_TYPES)
{
  using boost::simd::native;
  using boost::simd::saturate_at;
  using boost::simd::tag::saturate_at_;
  typedef BOOST_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef native<T,ext_t>                        n_t;
  typedef typename boost::dispatch::meta::call<saturate_at_<boost::simd::tag::Pi>(n_t)>::type r_t;
  typedef typename boost::simd::meta::scalar_of<r_t>::type sr_t;

  NT2_TEST_TYPE_IS( r_t, (native<T,ext_t>) );

  NT2_TEST_EQUAL(saturate_at<boost::simd::tag::Four>(boost::simd::Mten<n_t>()), -boost::simd::Four<r_t>() );
  NT2_TEST_EQUAL(saturate_at<boost::simd::tag::Four>(boost::simd::Mone<n_t>()), boost::simd::Mone<r_t>() );
  NT2_TEST_EQUAL(saturate_at<boost::simd::tag::Four>(boost::simd::Zero<n_t>()), boost::simd::Zero<r_t>() );
  NT2_TEST_EQUAL(saturate_at<boost::simd::tag::Four>(boost::simd::One<n_t>()), boost::simd::One<r_t>() );
  NT2_TEST_EQUAL(saturate_at<boost::simd::tag::Four>(boost::simd::Ten<n_t>()), boost::simd::Four<r_t>() );
}

NT2_TEST_CASE_TPL ( saturate_at_unsigned,  BOOST_SIMD_SIMD_INTEGRAL_UNSIGNED_TYPES)
{
  using boost::simd::native;
  using boost::simd::saturate_at;
  using boost::simd::tag::saturate_at_;
  typedef BOOST_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef native<T,ext_t>                        n_t;
  typedef typename boost::dispatch::meta::call<saturate_at_<boost::simd::tag::Pi>(n_t)>::type r_t;
  typedef typename boost::simd::meta::scalar_of<r_t>::type sr_t;

  NT2_TEST_TYPE_IS( r_t, (native<T,ext_t>) );

  NT2_TEST_EQUAL(saturate_at<boost::simd::tag::Four>(boost::simd::Zero<n_t>()), boost::simd::Zero<r_t>() );
  NT2_TEST_EQUAL(saturate_at<boost::simd::tag::Four>(boost::simd::One<n_t>()) , boost::simd::One<r_t>() );
  NT2_TEST_EQUAL(saturate_at<boost::simd::tag::Four>(boost::simd::Ten<n_t>()) , boost::simd::Four<r_t>() );
}
