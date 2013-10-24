//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <boost/simd/arithmetic/include/functions/fast_trunc.hpp>
#include <boost/simd/sdk/simd/native.hpp>
#include <boost/dispatch/functor/meta/call.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <boost/simd/include/functions/simd/minus.hpp>
#include <boost/simd/include/functions/simd/splat.hpp>
#include <boost/simd/include/constants/mhalf.hpp>
#include <boost/simd/include/constants/one.hpp>
#include <boost/simd/include/constants/two.hpp>
#include <boost/simd/include/constants/mone.hpp>
#include <boost/simd/include/constants/inf.hpp>
#include <boost/simd/include/constants/minf.hpp>
#include <boost/simd/include/constants/nan.hpp>
#include <boost/simd/include/constants/valmax.hpp>
#include <boost/simd/include/constants/valmin.hpp>
#include <boost/simd/include/constants/maxflint.hpp>
#include <boost/simd/include/constants/half.hpp>

#include <boost/simd/sdk/config.hpp>
#include <boost/simd/sdk/simd/io.hpp>

NT2_TEST_CASE_TPL ( fast_trunc_real,  BOOST_SIMD_SIMD_REAL_TYPES)
{
  using boost::simd::fast_trunc;
  using boost::simd::tag::fast_trunc_;
  using boost::simd::native;
  typedef BOOST_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef native<T,ext_t>                  vT;
  typedef typename boost::dispatch::meta::call<fast_trunc_(vT)>::type r_t;

  // specific values tests
  NT2_TEST_EQUAL(fast_trunc(boost::simd::splat<vT>(1.4)), boost::simd::One<r_t>());
  NT2_TEST_EQUAL(fast_trunc(boost::simd::splat<vT>(1.5)), boost::simd::One<r_t>());
  NT2_TEST_EQUAL(fast_trunc(boost::simd::splat<vT>(1.6)), boost::simd::One<r_t>());
  NT2_TEST_EQUAL(fast_trunc(boost::simd::splat<vT>(2.5)), boost::simd::Two<r_t>());
  NT2_TEST_EQUAL(fast_trunc(boost::simd::Half<vT>()), boost::simd::Zero<r_t>());
  NT2_TEST_EQUAL(fast_trunc(boost::simd::Mhalf<vT>()), boost::simd::Zero<r_t>());
  NT2_TEST_EQUAL(fast_trunc(boost::simd::Mone<vT>()), boost::simd::Mone<r_t>());
  NT2_TEST_EQUAL(fast_trunc(boost::simd::One<vT>()), boost::simd::One<r_t>());
  NT2_TEST_EQUAL(fast_trunc(boost::simd::Zero<vT>()), boost::simd::Zero<r_t>());
  NT2_TEST_EQUAL(fast_trunc(boost::simd::Maxflint<vT>()-boost::simd::Half<vT>()),boost::simd::Maxflint<vT>());
  NT2_TEST_EQUAL(fast_trunc(boost::simd::Maxflint<vT>()-boost::simd::splat<vT>(1.5)),boost::simd::Maxflint<vT>()-boost::simd::Two<vT>());
  NT2_TEST_EQUAL(fast_trunc(boost::simd::Maxflint<vT>()),boost::simd::Maxflint<vT>());
} // end of test for floating_

NT2_TEST_CASE_TPL ( fast_trunc_unsigned_int,  BOOST_SIMD_SIMD_UNSIGNED_TYPES)
{
  using boost::simd::fast_trunc;
  using boost::simd::tag::fast_trunc_;
  using boost::simd::native;
  typedef BOOST_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef native<T,ext_t>                  vT;
  typedef typename boost::dispatch::meta::call<fast_trunc_(vT)>::type r_t;

  // specific values tests
  NT2_TEST_EQUAL(fast_trunc(boost::simd::One<vT>()), boost::simd::One<r_t>());
  NT2_TEST_EQUAL(fast_trunc(boost::simd::Valmax<vT>()), boost::simd::Valmax<r_t>());
  NT2_TEST_EQUAL(fast_trunc(boost::simd::Valmin<vT>()), boost::simd::Valmin<r_t>());
  NT2_TEST_EQUAL(fast_trunc(boost::simd::Zero<vT>()), boost::simd::Zero<r_t>());
} // end of test for unsigned_int_

NT2_TEST_CASE_TPL ( fast_trunc_signed_int,  BOOST_SIMD_SIMD_INTEGRAL_SIGNED_TYPES)
{
  using boost::simd::fast_trunc;
  using boost::simd::tag::fast_trunc_;
  using boost::simd::native;
  typedef BOOST_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef native<T,ext_t>                  vT;
  typedef typename boost::dispatch::meta::call<fast_trunc_(vT)>::type r_t;

  // specific values tests
  NT2_TEST_EQUAL(fast_trunc(boost::simd::Mone<vT>()), boost::simd::Mone<r_t>());
  NT2_TEST_EQUAL(fast_trunc(boost::simd::One<vT>()), boost::simd::One<r_t>());
  NT2_TEST_EQUAL(fast_trunc(boost::simd::Valmax<vT>()), boost::simd::Valmax<r_t>());
  NT2_TEST_EQUAL(fast_trunc(boost::simd::Valmin<vT>()), boost::simd::Valmin<r_t>());
  NT2_TEST_EQUAL(fast_trunc(boost::simd::Zero<vT>()), boost::simd::Zero<r_t>());
} // end of test for signed_int_
