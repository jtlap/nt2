//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <boost/simd/arithmetic/include/functions/adds.hpp>
#include <boost/simd/sdk/simd/native.hpp>
#include <boost/dispatch/functor/meta/call.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <boost/simd/include/constants/mtwo.hpp>
#include <boost/simd/include/constants/two.hpp>
#include <boost/simd/include/constants/one.hpp>
#include <boost/simd/include/constants/mone.hpp>
#include <boost/simd/include/constants/inf.hpp>
#include <boost/simd/include/constants/minf.hpp>
#include <boost/simd/include/constants/nan.hpp>
#include <boost/simd/sdk/config.hpp>
#include <boost/simd/sdk/simd/io.hpp>


NT2_TEST_CASE_TPL ( adds_signed_int,  BOOST_SIMD_SIMD_INTEGRAL_SIGNED_TYPES)
{
  using boost::simd::adds;
  using boost::simd::tag::adds_;
  using boost::simd::native;
  typedef BOOST_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef native<T,ext_t>                  vT;
  typedef typename boost::dispatch::meta::call<adds_(vT,vT)>::type r_t;

  // specific values tests
  NT2_TEST_EQUAL(adds(boost::simd::Mone<vT>(), boost::simd::Mone<vT>()), boost::simd::Mtwo<r_t>());
  NT2_TEST_EQUAL(adds(boost::simd::One<vT>(), boost::simd::One<vT>()), boost::simd::Two<r_t>());
  NT2_TEST_EQUAL(adds(boost::simd::Valmax<vT>(),boost::simd::One<vT>()), boost::simd::Valmax<r_t>());
  NT2_TEST_EQUAL(adds(boost::simd::Valmin<vT>(),boost::simd::Mone<vT>()), boost::simd::Valmin<r_t>());
  NT2_TEST_EQUAL(adds(boost::simd::Zero<vT>(), boost::simd::Zero<vT>()), boost::simd::Zero<r_t>());
} // end of test for signed_int_

NT2_TEST_CASE_TPL ( adds_unsigned_int__2_0,  BOOST_SIMD_SIMD_UNSIGNED_TYPES)
{
  using boost::simd::adds;
  using boost::simd::tag::adds_;
  using boost::simd::native;
  typedef BOOST_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef native<T,ext_t>                  vT;
  typedef typename boost::dispatch::meta::call<adds_(vT,vT)>::type r_t;

  // specific values tests
  NT2_TEST_EQUAL(adds(boost::simd::One<vT>(), boost::simd::One<vT>()), boost::simd::Two<r_t>());
  NT2_TEST_EQUAL(adds(boost::simd::Valmax<vT>(),boost::simd::One<vT>()), boost::simd::Valmax<r_t>());
  NT2_TEST_EQUAL(adds(boost::simd::Zero<vT>(), boost::simd::Zero<vT>()), boost::simd::Zero<r_t>());
} // end of test for unsigned_int_
