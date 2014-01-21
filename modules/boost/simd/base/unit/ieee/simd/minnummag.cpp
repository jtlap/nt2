//==============================================================================
//         Copyright 2003 - 2013   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <boost/simd/ieee/include/functions/minnummag.hpp>

#include <boost/dispatch/functor/meta/call.hpp>
#include <boost/simd/sdk/simd/native.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <boost/simd/sdk/config.hpp>
#include <boost/simd/sdk/simd/io.hpp>

#include <boost/simd/include/constants/mone.hpp>
#include <boost/simd/include/constants/one.hpp>
#include <boost/simd/include/constants/two.hpp>
#include <boost/simd/include/constants/mtwo.hpp>
#include <boost/simd/include/constants/zero.hpp>
#include <boost/simd/include/constants/inf.hpp>
#include <boost/simd/include/constants/minf.hpp>
#include <boost/simd/include/constants/nan.hpp>

NT2_TEST_CASE_TPL ( minnummag_real,  BOOST_SIMD_SIMD_REAL_TYPES)
{
  using boost::simd::minnummag;
  using boost::simd::tag::minnummag_;
  using boost::simd::native;
  typedef BOOST_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef native<T,ext_t>                  vT;
  typedef typename boost::dispatch::meta::call<minnummag_(vT,vT)>::type r_t;

  // specific values tests
#ifndef BOOST_SIMD_NO_INVALIDS
  NT2_TEST_EQUAL(minnummag(boost::simd::Inf<vT>(),  boost::simd::Inf<vT>()), boost::simd::Inf<r_t>());
  NT2_TEST_EQUAL(minnummag(boost::simd::Minf<vT>(), boost::simd::Minf<vT>()), boost::simd::Minf<r_t>());
  NT2_TEST_EQUAL(minnummag(boost::simd::Nan<vT>(),  boost::simd::Nan<vT>()), boost::simd::Nan<r_t>());
  NT2_TEST_EQUAL(minnummag(boost::simd::Nan<vT>(),  boost::simd::One<vT>()), boost::simd::One<r_t>());
  NT2_TEST_EQUAL(minnummag(boost::simd::One<vT>(),  boost::simd::Nan<vT>()), boost::simd::One<r_t>());
#endif
  NT2_TEST_EQUAL(minnummag(boost::simd::Mone<vT>(), boost::simd::Mone<vT>()), boost::simd::Mone<r_t>());
  NT2_TEST_EQUAL(minnummag(boost::simd::One<vT>(),  boost::simd::One<vT>()),  boost::simd::One<r_t>());
  NT2_TEST_EQUAL(minnummag(boost::simd::Zero<vT>(), boost::simd::Zero<vT>()), boost::simd::Zero<r_t>());
  NT2_TEST_EQUAL(minnummag(boost::simd::Mone<vT>(), boost::simd::One <vT>()), boost::simd::Mone<r_t>());
  NT2_TEST_EQUAL(minnummag(boost::simd::One <vT>(), boost::simd::Mone<vT>()), boost::simd::Mone<r_t>());
  NT2_TEST_EQUAL(minnummag(boost::simd::One <vT>(), boost::simd::Two <vT>()), boost::simd::One<r_t>());
  NT2_TEST_EQUAL(minnummag(boost::simd::Two <vT>(), boost::simd::One <vT>()), boost::simd::One<r_t>());
  NT2_TEST_EQUAL(minnummag(boost::simd::Mtwo<vT>(), boost::simd::One <vT>()), boost::simd::One<r_t>());
  NT2_TEST_EQUAL(minnummag(boost::simd::One <vT>(), boost::simd::Mtwo<vT>()), boost::simd::One<r_t>());
  NT2_TEST_EQUAL(minnummag(boost::simd::Two <vT>(), boost::simd::Mone<vT>()), boost::simd::Mone<r_t>());
  NT2_TEST_EQUAL(minnummag(boost::simd::Mone<vT>(), boost::simd::Two <vT>()), boost::simd::Mone<r_t>());
}

NT2_TEST_CASE_TPL ( minnummag_unsigned_int,  BOOST_SIMD_SIMD_UNSIGNED_TYPES)
{
  using boost::simd::minnummag;
  using boost::simd::tag::minnummag_;
  using boost::simd::native;
  typedef BOOST_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef native<T,ext_t>                  vT;
  typedef typename boost::dispatch::meta::call<minnummag_(vT,vT)>::type r_t;

  // specific values tests
  NT2_TEST_EQUAL(minnummag(boost::simd::One<vT>(), boost::simd::One<vT>()), boost::simd::One<r_t>());
  NT2_TEST_EQUAL(minnummag(boost::simd::Zero<vT>(), boost::simd::Zero<vT>()), boost::simd::Zero<r_t>());
}

NT2_TEST_CASE_TPL ( minnummag_signed_int,  BOOST_SIMD_SIMD_INTEGRAL_SIGNED_TYPES)
{
  using boost::simd::minnummag;
  using boost::simd::tag::minnummag_;
  using boost::simd::native;
  typedef BOOST_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef native<T,ext_t>                  vT;
  typedef typename boost::dispatch::meta::call<minnummag_(vT,vT)>::type r_t;

  // specific values tests
  NT2_TEST_EQUAL(minnummag(boost::simd::Mone<vT>(), boost::simd::Mone<vT>()), boost::simd::Mone<r_t>());
  NT2_TEST_EQUAL(minnummag(boost::simd::One<vT>(), boost::simd::One<vT>()), boost::simd::One<r_t>());
  NT2_TEST_EQUAL(minnummag(boost::simd::Zero<vT>(), boost::simd::Zero<vT>()), boost::simd::Zero<r_t>());
  NT2_TEST_EQUAL(minnummag(boost::simd::Mone<vT>(), boost::simd::Zero<vT>()), boost::simd::Zero<r_t>());
  NT2_TEST_EQUAL(minnummag(boost::simd::Mone<vT>(), boost::simd::One<vT>()), boost::simd::Mone<r_t>());
}
