//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================

#include <boost/simd/arithmetic/include/functions/divfloor.hpp>
#include <boost/simd/sdk/simd/native.hpp>
#include <boost/dispatch/functor/meta/call.hpp>
#include <boost/simd/include/functions/splat.hpp>
#include <boost/simd/include/constants/two.hpp>
#include <boost/simd/include/constants/one.hpp>
#include <boost/simd/include/constants/mone.hpp>
#include <boost/simd/include/constants/valmin.hpp>
#include <boost/simd/include/constants/valmax.hpp>
#include <boost/simd/include/constants/zero.hpp>
#include <boost/simd/include/constants/inf.hpp>
#include <boost/simd/include/constants/minf.hpp>
#include <boost/simd/include/constants/nan.hpp>
#include <boost/simd/include/constants/maxflint.hpp>
#include <boost/simd/sdk/simd/io.hpp>
#include <boost/simd/sdk/config.hpp>

#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/module.hpp>

NT2_TEST_CASE_TPL ( divfloor_real,  BOOST_SIMD_SIMD_REAL_TYPES)
{
  using boost::simd::divfloor;
  using boost::simd::tag::divfloor_;
  using boost::simd::native;
  typedef BOOST_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef native<T,ext_t>                  vT;
  typedef typename boost::dispatch::meta::call<divfloor_(vT,vT)>::type r_t;

  // specific values tests
#ifndef BOOST_SIMD_NO_INVALIDS
  NT2_TEST_EQUAL(divfloor(boost::simd::Inf<vT>(), boost::simd::Inf<vT>()), boost::simd::Nan<r_t>());
  NT2_TEST_EQUAL(divfloor(boost::simd::Minf<vT>(), boost::simd::Minf<vT>()), boost::simd::Nan<r_t>());
  NT2_TEST_EQUAL(divfloor(boost::simd::Nan<vT>(), boost::simd::Nan<vT>()), boost::simd::Nan<r_t>());
#endif
  NT2_TEST_EQUAL(divfloor(boost::simd::splat<vT>(4),boost::simd::splat<vT>(0)), boost::simd::Inf<r_t>());
  NT2_TEST_EQUAL(divfloor(boost::simd::splat<vT>(4),boost::simd::splat<vT>(3)),  boost::simd::One<r_t>());
  NT2_TEST_EQUAL(divfloor(boost::simd::Mone<vT>(), boost::simd::Mone<vT>()), boost::simd::One<r_t>());
  NT2_TEST_EQUAL(divfloor(boost::simd::One<vT>(), boost::simd::One<vT>()), boost::simd::One<r_t>());
} // end of test for floating_

NT2_TEST_CASE_TPL ( divfloor_u,  BOOST_SIMD_SIMD_UNSIGNED_TYPES)
{
  using boost::simd::divfloor;
  using boost::simd::tag::divfloor_;
  using boost::simd::native;
  typedef BOOST_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef native<T,ext_t>                  vT;
  typedef typename boost::dispatch::meta::call<divfloor_(vT,vT)>::type r_t;

  // specific values tests
  NT2_TEST_EQUAL(divfloor(boost::simd::splat<vT>(4),boost::simd::splat<vT>(0)), boost::simd::Valmax<r_t>());
  NT2_TEST_EQUAL(divfloor(boost::simd::splat<vT>(4),boost::simd::splat<vT>(3)), boost::simd::splat<r_t>(1));
  NT2_TEST_EQUAL(divfloor(boost::simd::One<vT>(), boost::simd::One<vT>()), boost::simd::One<r_t>());
  NT2_TEST_EQUAL(divfloor(boost::simd::One<vT>(),boost::simd::Zero<vT>()), boost::simd::Valmax<r_t>());
  NT2_TEST_EQUAL(divfloor(boost::simd::Zero<vT>(),boost::simd::Zero<vT>()), boost::simd::Zero<r_t>());
  NT2_TEST_EQUAL(divfloor(boost::simd::Valmax<vT>(),boost::simd::One<vT>()), boost::simd::Valmax<vT>());
  NT2_TEST_EQUAL(divfloor(boost::simd::Valmax<vT>(),boost::simd::Two<vT>()), boost::simd::Valmax<vT>()/boost::simd::Two<vT>());
} // end of test for floating_

NT2_TEST_CASE_TPL ( divfloor_s,  BOOST_SIMD_SIMD_INTEGRAL_SIGNED_TYPES)
{
  using boost::simd::divfloor;
  using boost::simd::tag::divfloor_;
  using boost::simd::native;
  typedef BOOST_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef native<T,ext_t>                  vT;
  typedef typename boost::dispatch::meta::call<divfloor_(vT,vT)>::type r_t;

  // specific values tests
  NT2_TEST_EQUAL(divfloor(boost::simd::splat<vT>(4),boost::simd::splat<vT>(0)), boost::simd::Valmax<r_t>());
  NT2_TEST_EQUAL(divfloor(boost::simd::splat<vT>(4),boost::simd::splat<vT>(3)), boost::simd::splat<vT>(1));
  NT2_TEST_EQUAL(divfloor(boost::simd::Mone<vT>(), boost::simd::Mone<vT>()), boost::simd::One<r_t>());
  NT2_TEST_EQUAL(divfloor(boost::simd::Mone<vT>(),boost::simd::Zero<vT>()), boost::simd::Valmin<r_t>());
  NT2_TEST_EQUAL(divfloor(boost::simd::One<vT>(), boost::simd::One<vT>()), boost::simd::One<r_t>());
  NT2_TEST_EQUAL(divfloor(boost::simd::One<vT>(),boost::simd::Zero<vT>()), boost::simd::Valmax<r_t>());
  NT2_TEST_EQUAL(divfloor(boost::simd::Zero<vT>(),boost::simd::Zero<vT>()), boost::simd::Zero<r_t>());
} // end of test for floating_

NT2_TEST_CASE_TPL ( divfloor_s2,   BOOST_SIMD_SIMD_INT_CONVERT_TYPES)
{
  using boost::simd::divfloor;
  using boost::simd::tag::divfloor_;
  using boost::simd::native;
  typedef BOOST_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef native<T,ext_t>                  vT;
  typedef typename boost::dispatch::meta::as_floating<T>::type f_t;

  T mf = boost::simd::Maxflint<f_t>();
  T tz = mf+T(1);
  vT z =  boost::simd::splat<vT>(tz);
  vT mz =  boost::simd::splat<vT>(-tz);
  vT mz2 =  boost::simd::splat<vT>(-tz/2-1);
  vT z2  =  boost::simd::splat<vT>(tz/2);
  NT2_TEST_EQUAL(divfloor(z,boost::simd::splat<vT>(1)), z);
  NT2_TEST_EQUAL(divfloor(z,boost::simd::splat<vT>(-1)), mz);
  NT2_TEST_EQUAL(divfloor(z,boost::simd::splat<vT>(2)), z2);
  NT2_TEST_EQUAL(divfloor(z,boost::simd::splat<vT>(-2)), mz2);
} // end of test for floating_
