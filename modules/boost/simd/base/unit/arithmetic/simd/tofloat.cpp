//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <boost/simd/arithmetic/include/functions/tofloat.hpp>
#include <boost/simd/sdk/simd/native.hpp>
#include <boost/dispatch/functor/meta/call.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <boost/simd/include/constants/zero.hpp>
#include <boost/simd/include/constants/one.hpp>
#include <boost/simd/include/constants/two.hpp>
#include <boost/simd/include/constants/mone.hpp>
#include <boost/simd/include/constants/inf.hpp>
#include <boost/simd/include/constants/minf.hpp>
#include <boost/simd/include/constants/nan.hpp>
#include <boost/simd/include/constants/valmax.hpp>
#include <boost/simd/include/constants/valmin.hpp>
#include <boost/simd/sdk/config.hpp>
#include <boost/simd/sdk/simd/io.hpp>


NT2_TEST_CASE_TPL ( tofloat_real,  BOOST_SIMD_SIMD_REAL_TYPES)
{
  using boost::simd::tofloat;
  using boost::simd::tag::tofloat_;
  using boost::simd::native;
  typedef BOOST_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef native<T,ext_t>                  vT;
  typedef typename boost::dispatch::meta::strip<typename boost::dispatch::meta::call<tofloat_(vT)>::type>::type r_t;

  // specific values tests
#ifndef BOOST_SIMD_NO_INVALIDS
  NT2_TEST_EQUAL(tofloat(boost::simd::Inf<vT>()), boost::simd::Inf<r_t>());
  NT2_TEST_EQUAL(tofloat(boost::simd::Minf<vT>()), boost::simd::Minf<r_t>());
  NT2_TEST_EQUAL(tofloat(boost::simd::Nan<vT>()), boost::simd::Nan<r_t>());
#endif
  NT2_TEST_EQUAL(tofloat(boost::simd::Mone<vT>()), boost::simd::Mone<r_t>());
  NT2_TEST_EQUAL(tofloat(boost::simd::One<vT>()), boost::simd::One<r_t>());
  NT2_TEST_EQUAL(tofloat(boost::simd::Zero<vT>()), boost::simd::Zero<r_t>());
  NT2_TEST_EQUAL(tofloat(boost::simd::Two<vT>()), boost::simd::Two<r_t>());
} // end of test for floating_

NT2_TEST_CASE_TPL ( tofloat_int_convert,  BOOST_SIMD_SIMD_INT_CONVERT_TYPES)
{
  using boost::simd::tofloat;
  using boost::simd::tag::tofloat_;
  using boost::simd::native;
  typedef BOOST_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef native<T,ext_t>                  vT;
  typedef typename boost::dispatch::meta::call<tofloat_(vT)>::type r_t;

  NT2_TEST_EQUAL(tofloat(boost::simd::Mone<vT>()), boost::simd::Mone<r_t>());
  NT2_TEST_EQUAL(tofloat(boost::simd::One<vT>()), boost::simd::One<r_t>());
  NT2_TEST_EQUAL(tofloat(boost::simd::Zero<vT>()), boost::simd::Zero<r_t>());
  NT2_TEST_EQUAL(tofloat(boost::simd::Two<vT>()), boost::simd::Two<r_t>());
  NT2_TEST_EQUAL(tofloat(boost::simd::Valmax<vT>()), boost::simd::splat<vT>(boost::simd::Valmax<T>()));
  NT2_TEST_EQUAL(tofloat(boost::simd::Valmin<vT>()), boost::simd::splat<vT>(boost::simd::Valmin<T>()));

} // end of test for int_convert_

NT2_TEST_CASE_TPL ( tofloat_uint_convert,  BOOST_SIMD_SIMD_UINT_CONVERT_TYPES)
{
  using boost::simd::tofloat;
  using boost::simd::tag::tofloat_;
  using boost::simd::native;
  typedef BOOST_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef native<T,ext_t>                  vT;
  typedef typename boost::dispatch::meta::call<tofloat_(vT)>::type r_t;

  NT2_TEST_EQUAL(tofloat(boost::simd::One<vT>()), boost::simd::One<r_t>());
  NT2_TEST_EQUAL(tofloat(boost::simd::Zero<vT>()), boost::simd::Zero<r_t>());
  NT2_TEST_EQUAL(tofloat(boost::simd::Two<vT>()), boost::simd::Two<r_t>());
  NT2_TEST_EQUAL(tofloat(boost::simd::Valmax<vT>()), boost::simd::splat<vT>(boost::simd::Valmax<T>()));

} // end of test for uint_convert_

#ifdef BOOST_SIMD_HAS_SSE2_SUPPORT
NT2_TEST_CASE( tofloat_long_long )
{
  using boost::simd::tofloat;
  using boost::simd::splat;
  typedef boost::simd::native<long long, boost::simd::tag::sse_> vT;

  long long i = boost::simd::Valmin<long long>();
  NT2_TEST_EQUAL(tofloat(splat<vT>(i)), tofloat(splat<vT>(i)));
}
#endif
