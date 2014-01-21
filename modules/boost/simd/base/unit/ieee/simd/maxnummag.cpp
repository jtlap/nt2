//==============================================================================
//         Copyright 2003 - 2013   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <boost/simd/ieee/include/functions/maxnummag.hpp>

#include <boost/dispatch/functor/meta/call.hpp>
#include <boost/simd/sdk/simd/native.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <boost/simd/sdk/config.hpp>
#include <boost/simd/sdk/simd/io.hpp>

#include <boost/simd/include/constants/mone.hpp>
#include <boost/simd/include/constants/one.hpp>
#include <boost/simd/include/constants/mtwo.hpp>
#include <boost/simd/include/constants/two.hpp>
#include <boost/simd/include/constants/zero.hpp>
#include <boost/simd/include/constants/inf.hpp>
#include <boost/simd/include/constants/minf.hpp>
#include <boost/simd/include/constants/nan.hpp>

NT2_TEST_CASE_TPL ( maxnummag_real,  BOOST_SIMD_SIMD_REAL_TYPES)
{
  using boost::simd::maxnummag;
  using boost::simd::tag::maxnummag_;
  using boost::simd::native;
  typedef BOOST_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef native<T,ext_t>                  vT;
  typedef typename boost::dispatch::meta::call<maxnummag_(vT,vT)>::type r_t;

  // specific values tests
  NT2_TEST_EQUAL(maxnummag(boost::simd::Mone<vT>(), boost::simd::Mone<vT>()), boost::simd::Mone<r_t>());
  NT2_TEST_EQUAL(maxnummag(boost::simd::One<vT>(),  boost::simd::One<vT>()),  boost::simd::One<r_t>());
  NT2_TEST_EQUAL(maxnummag(boost::simd::Zero<vT>(), boost::simd::Zero<vT>()), boost::simd::Zero<r_t>());
  NT2_TEST_EQUAL(maxnummag(boost::simd::Mone<vT>(), boost::simd::One <vT>()), boost::simd::One<r_t>());
  NT2_TEST_EQUAL(maxnummag(boost::simd::One <vT>(), boost::simd::Mone<vT>()), boost::simd::One<r_t>());
  NT2_TEST_EQUAL(maxnummag(boost::simd::One <vT>(), boost::simd::Two <vT>()), boost::simd::Two<r_t>());
  NT2_TEST_EQUAL(maxnummag(boost::simd::Two <vT>(), boost::simd::One <vT>()), boost::simd::Two<r_t>());
  NT2_TEST_EQUAL(maxnummag(boost::simd::Mtwo<vT>(), boost::simd::One <vT>()), boost::simd::Mtwo<r_t>());
  NT2_TEST_EQUAL(maxnummag(boost::simd::One <vT>(), boost::simd::Mtwo<vT>()), boost::simd::Mtwo<r_t>());
  NT2_TEST_EQUAL(maxnummag(boost::simd::Two <vT>(), boost::simd::Mone<vT>()), boost::simd::Two<r_t>());
  NT2_TEST_EQUAL(maxnummag(boost::simd::Mone<vT>(), boost::simd::Two <vT>()), boost::simd::Two<r_t>());
}

NT2_TEST_CASE_TPL ( maxnummag_unsigned_int,  BOOST_SIMD_SIMD_UNSIGNED_TYPES)
{
  using boost::simd::maxnummag;
  using boost::simd::tag::maxnummag_;
  using boost::simd::native;
  typedef BOOST_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef native<T,ext_t>                  vT;
  typedef typename boost::dispatch::meta::call<maxnummag_(vT,vT)>::type r_t;

  // specific values tests
  NT2_TEST_EQUAL(maxnummag(boost::simd::One<vT>(), boost::simd::One<vT>()), boost::simd::One<r_t>());
  NT2_TEST_EQUAL(maxnummag(boost::simd::Zero<vT>(), boost::simd::Zero<vT>()), boost::simd::Zero<r_t>());
}

NT2_TEST_CASE_TPL ( maxnummag_signed_int,  BOOST_SIMD_SIMD_INTEGRAL_SIGNED_TYPES)
{
  using boost::simd::maxnummag;
  using boost::simd::tag::maxnummag_;
  using boost::simd::native;
  typedef BOOST_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef native<T,ext_t>                  vT;
  typedef typename boost::dispatch::meta::call<maxnummag_(vT,vT)>::type r_t;

  // specific values tests
  NT2_TEST_EQUAL(maxnummag(boost::simd::Mone<vT>(), boost::simd::Mone<vT>()), boost::simd::Mone<r_t>());
  NT2_TEST_EQUAL(maxnummag(boost::simd::One<vT>(), boost::simd::One<vT>()), boost::simd::One<r_t>());
  NT2_TEST_EQUAL(maxnummag(boost::simd::Zero<vT>(), boost::simd::Zero<vT>()), boost::simd::Zero<r_t>());
  NT2_TEST_EQUAL(maxnummag(boost::simd::Mone<vT>(), boost::simd::Zero<vT>()), boost::simd::Mone<r_t>());
  NT2_TEST_EQUAL(maxnummag(boost::simd::Mone<vT>(), boost::simd::One<vT>()), boost::simd::One<r_t>());
}
