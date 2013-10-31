//==============================================================================
//         Copyright 2003 - 2013   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <boost/simd/bitwise/include/functions/genmaskc.hpp>

#include <boost/dispatch/functor/meta/call.hpp>
#include <boost/simd/sdk/simd/native.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <boost/simd/sdk/config.hpp>
#include <boost/simd/sdk/simd/io.hpp>
#include <boost/simd/sdk/meta/as_logical.hpp>

#include <boost/simd/include/constants/false.hpp>
#include <boost/simd/include/constants/mone.hpp>
#include <boost/simd/include/constants/one.hpp>
#include <boost/simd/include/constants/true.hpp>
#include <boost/simd/include/constants/false.hpp>
#include <boost/simd/include/constants/zero.hpp>
#include <boost/simd/include/constants/inf.hpp>
#include <boost/simd/include/constants/minf.hpp>
#include <boost/simd/include/constants/nan.hpp>
#include <boost/simd/include/constants/valmax.hpp>
#include <boost/simd/include/constants/valmin.hpp>
#include <boost/simd/include/functions/plus.hpp>

NT2_TEST_CASE_TPL(genmaskc_real, BOOST_SIMD_SIMD_REAL_TYPES)
{
  using boost::simd::genmaskc;
  using boost::simd::tag::genmaskc_;
  using boost::simd::native;
  typedef BOOST_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef native<T,ext_t>                  vT;
  typedef typename boost::simd::meta::as_logical<vT>::type vlT;
  typedef typename boost::dispatch::meta::call<genmaskc_(vT)>::type r_t;

  // specific values tests
#ifndef BOOST_SIMD_NO_INVALIDS
  NT2_TEST_EQUAL(genmaskc(boost::simd::Inf<vT>()), boost::simd::Zero<r_t>());
  NT2_TEST_EQUAL(genmaskc(boost::simd::Minf<vT>()), boost::simd::Zero<r_t>());
  NT2_TEST_EQUAL(genmaskc(boost::simd::Nan<vT>()), boost::simd::Zero<r_t>());
  NT2_TEST_EQUAL(genmaskc(boost::simd::True<vlT>()), boost::simd::Zero<r_t>());
#endif
  NT2_TEST_EQUAL(genmaskc(boost::simd::Zero<vT>()), boost::simd::Allbits<r_t>());
  NT2_TEST_EQUAL(genmaskc(boost::simd::False<vlT>()), boost::simd::Allbits<r_t>());
}

NT2_TEST_CASE_TPL(genmaskc_ui, BOOST_SIMD_SIMD_UNSIGNED_TYPES)
{
  using boost::simd::genmaskc;
  using boost::simd::tag::genmaskc_;
  using boost::simd::native;
  typedef BOOST_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef native<T,ext_t>                  vT;
  typedef typename boost::simd::meta::as_logical<vT>::type vlT;
  typedef typename boost::dispatch::meta::call<genmaskc_(vT)>::type r_t;

  // specific values tests
  NT2_TEST_EQUAL(genmaskc(boost::simd::Zero<vT>()), boost::simd::Allbits<r_t>());
  NT2_TEST_EQUAL(genmaskc(boost::simd::False<vlT>()), boost::simd::Allbits<r_t>());
}

NT2_TEST_CASE_TPL(genmaskc_si, BOOST_SIMD_SIMD_INTEGRAL_SIGNED_TYPES)
{
  using boost::simd::genmaskc;
  using boost::simd::tag::genmaskc_;
  using boost::simd::native;
  typedef BOOST_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef native<T,ext_t>                  vT;
  typedef typename boost::simd::meta::as_logical<vT>::type vlT;
  typedef typename boost::dispatch::meta::call<genmaskc_(vT)>::type r_t;

  // specific values tests
  NT2_TEST_EQUAL(genmaskc(boost::simd::Zero<vT>()), boost::simd::Allbits<r_t>());
  NT2_TEST_EQUAL(genmaskc(boost::simd::Valmax<vT>()), boost::simd::Zero<r_t>());
  NT2_TEST_EQUAL(genmaskc(boost::simd::Valmin<vT>()+boost::simd::One<vT>()), boost::simd::Zero<r_t>());
  NT2_TEST_EQUAL(genmaskc(boost::simd::False<vlT>()), boost::simd::Allbits<r_t>());
  NT2_TEST_EQUAL(genmaskc(boost::simd::True<vlT>()), boost::simd::Zero<r_t>());
}
