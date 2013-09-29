//==============================================================================
//         Copyright 2003 - 2013   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <boost/simd/bitwise/include/functions/firstbitunset.hpp>

#include <boost/dispatch/functor/meta/call.hpp>
#include <boost/simd/sdk/simd/native.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <boost/simd/sdk/config.hpp>
#include <boost/simd/sdk/simd/io.hpp>

#include <boost/simd/include/constants/one.hpp>
#include <boost/simd/include/constants/signmask.hpp>
#include <boost/simd/include/constants/two.hpp>
#include <boost/simd/include/constants/zero.hpp>
#include <boost/simd/include/constants/inf.hpp>
#include <boost/simd/include/constants/minf.hpp>
#include <boost/simd/include/constants/nan.hpp>

NT2_TEST_CASE_TPL(firstbitunset_real, BOOST_SIMD_SIMD_REAL_TYPES)
{
  using boost::simd::firstbitunset;
  using boost::simd::tag::firstbitunset_;
  using boost::simd::native;
  typedef BOOST_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef native<T,ext_t>                  vT;
  typedef typename boost::dispatch::meta::call<firstbitunset_(vT)>::type r_t;

  // specific values tests
#ifndef BOOST_SIMD_NO_INVALIDS
  NT2_TEST_EQUAL(firstbitunset(boost::simd::Inf<vT>()), boost::simd::One<r_t>());
  NT2_TEST_EQUAL(firstbitunset(boost::simd::Minf<vT>()), boost::simd::One<r_t>());
  NT2_TEST_EQUAL(firstbitunset(boost::simd::Nan<vT>()), boost::simd::Zero<r_t>());
#endif
  NT2_TEST_EQUAL(firstbitunset(boost::simd::Signmask<vT>()), boost::simd::One<r_t>());
  NT2_TEST_EQUAL(firstbitunset(boost::simd::Zero<vT>()), boost::simd::One<r_t>());
}



NT2_TEST_CASE_TPL(firstbitunset_ui, BOOST_SIMD_SIMD_UNSIGNED_TYPES)
{
  using boost::simd::firstbitunset;
  using boost::simd::tag::firstbitunset_;
  using boost::simd::native;
  typedef BOOST_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef native<T,ext_t>                  vT;
  typedef typename boost::dispatch::meta::call<firstbitunset_(vT)>::type r_t;

  // specific values tests
  NT2_TEST_EQUAL(firstbitunset(boost::simd::Zero<vT>()), boost::simd::One<r_t>());
}

NT2_TEST_CASE_TPL(firstbitunset_si, BOOST_SIMD_INTEGRAL_SIGNED_TYPES)
{
  using boost::simd::firstbitunset;
  using boost::simd::tag::firstbitunset_;
  using boost::simd::native;
  typedef BOOST_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef native<T,ext_t>                  vT;
  typedef typename boost::dispatch::meta::call<firstbitunset_(vT)>::type r_t;

  // specific values tests
  NT2_TEST_EQUAL(firstbitunset(boost::simd::Zero<vT>()), boost::simd::One<r_t>());
}
