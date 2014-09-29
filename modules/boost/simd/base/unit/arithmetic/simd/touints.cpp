//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <boost/simd/arithmetic/include/functions/touints.hpp>
#include <boost/simd/sdk/simd/native.hpp>
#include <boost/dispatch/functor/meta/call.hpp>
#include <nt2/sdk/unit/tests.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <boost/simd/include/functions/multiplies.hpp>
#include <boost/simd/include/functions/splat.hpp>
#include <boost/simd/include/functions/ldexp.hpp>
#include <nt2/include/constants/inf.hpp>
#include <nt2/include/constants/zero.hpp>
#include <nt2/include/constants/one.hpp>
#include <nt2/include/constants/mone.hpp>
#include <nt2/include/constants/minf.hpp>
#include <nt2/include/constants/nan.hpp>
#include <boost/simd/sdk/simd/io.hpp>

NT2_TEST_CASE_TPL ( touints_real,  BOOST_SIMD_SIMD_REAL_TYPES)
{
  using boost::simd::touints;
  using boost::simd::tag::touints_;
  using boost::simd::native;
  typedef BOOST_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef native<T,ext_t>                  vT;
  typedef typename boost::dispatch::meta::call<touints_(vT)>::type       r_t;
  typedef typename boost::dispatch::meta::call<touints_(T)>::type       sr_t;

  // specific values tests
  NT2_TEST_EQUAL(touints(boost::simd::splat<vT>(T(1.5)*boost::simd::Valmax<sr_t>())),  boost::simd::Valmax<r_t>());
  NT2_TEST_EQUAL(touints(boost::simd::splat<vT>(T(1.5)*boost::simd::Valmin<sr_t>())),  boost::simd::Valmin<r_t>());
  NT2_TEST_EQUAL(touints(boost::simd::splat<vT>(T(2)*boost::simd::Valmax<sr_t>())),  boost::simd::Valmax<r_t>());
  NT2_TEST_EQUAL(touints(boost::simd::splat<vT>(T(2)*boost::simd::Valmin<sr_t>())),  boost::simd::Valmin<r_t>());
  NT2_TEST_EQUAL(touints(boost::simd::Inf<vT>()), boost::simd::Inf<r_t>());
  NT2_TEST_EQUAL(touints(boost::simd::Minf<vT>()), boost::simd::Zero<r_t>());
  NT2_TEST_EQUAL(touints(boost::simd::Mone<vT>()), boost::simd::Zero<r_t>());
  NT2_TEST_EQUAL(touints(boost::simd::Nan<vT>()), boost::simd::Zero<r_t>());
  NT2_TEST_EQUAL(touints(boost::simd::One<vT>()), boost::simd::One<r_t>());
  NT2_TEST_EQUAL(touints(boost::simd::Zero<vT>()), boost::simd::Zero<r_t>());

  vT v = boost::simd::One<vT>();
  r_t iv = boost::simd::One<r_t>();
  int N = sizeof(T)*8-1;
  for(int i=0; i <= N ; i++)
  {
    NT2_TEST_EQUAL(touints(v), iv);
    v *= boost::simd::Two<vT>();
    iv *= boost::simd::Two<r_t>();
  }
  NT2_TEST_EQUAL(touints(boost::simd::ldexp(boost::simd::One<vT>(), N+1)), boost::simd::Valmax<r_t>());
  NT2_TEST_EQUAL(touints(boost::simd::ldexp(boost::simd::One<vT>(), N+2)), boost::simd::Valmax<r_t>());
}

NT2_TEST_CASE_TPL ( touints_integral,  BOOST_SIMD_SIMD_INTEGRAL_TYPES)
{
  using boost::simd::touints;
  using boost::simd::tag::touints_;
  using boost::simd::native;
  typedef BOOST_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef native<T,ext_t>                  vT;
  typedef typename boost::dispatch::meta::call<touints_(vT)>::type       r_t;

  // specific values tests
  NT2_TEST_EQUAL(touints(boost::simd::One<vT>()), boost::simd::One<r_t>());
  NT2_TEST_EQUAL(touints(boost::simd::Zero<vT>()), boost::simd::Zero<r_t>());
} // end of test for floating_

NT2_TEST_CASE_TPL ( touints_signed_int,  BOOST_SIMD_SIMD_INTEGRAL_SIGNED_TYPES)
{
  using boost::simd::touints;
  using boost::simd::tag::touints_;
  using boost::simd::native;
  typedef BOOST_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef native<T,ext_t>                  vT;
  typedef typename boost::dispatch::meta::call<touints_(vT)>::type       r_t;

  // specific values tests
  NT2_TEST_EQUAL(touints(boost::simd::Mone<vT>()), boost::simd::Valmin<r_t>());
  NT2_TEST_EQUAL(touints(boost::simd::One<vT>()), boost::simd::One<r_t>());
  NT2_TEST_EQUAL(touints(boost::simd::Zero<vT>()), boost::simd::Zero<r_t>());
}
