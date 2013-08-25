//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <boost/simd/arithmetic/include/functions/divround2even.hpp>
#include <boost/simd/sdk/simd/native.hpp>
#include <boost/dispatch/functor/meta/call.hpp>
#include <boost/simd/include/functions/splat.hpp>
#include <boost/simd/include/functions/plus.hpp>
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

NT2_TEST_CASE_TPL ( divround2even_real,  BOOST_SIMD_SIMD_REAL_TYPES)
{
  using boost::simd::divround2even;
  using boost::simd::tag::divround2even_;
  using boost::simd::native;
  typedef BOOST_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef native<T,ext_t>                  vT;
  typedef typename boost::dispatch::meta::call<divround2even_(vT,vT)>::type r_t;

  // specific values tests
#ifndef BOOST_SIMD_NO_INVALIDS
  NT2_TEST_EQUAL(divround2even(boost::simd::Inf<vT>(), boost::simd::Inf<vT>()), boost::simd::Nan<r_t>());
  NT2_TEST_EQUAL(divround2even(boost::simd::Minf<vT>(), boost::simd::Minf<vT>()), boost::simd::Nan<r_t>());
  NT2_TEST_EQUAL(divround2even(boost::simd::Nan<vT>(), boost::simd::Nan<vT>()), boost::simd::Nan<r_t>());
#endif
  NT2_TEST_EQUAL(divround2even(boost::simd::splat<vT>(4),boost::simd::splat<vT>(0)), boost::simd::Inf<r_t>());
  NT2_TEST_EQUAL(divround2even(boost::simd::splat<vT>(4),boost::simd::splat<vT>(3)),  boost::simd::One<r_t>());
  NT2_TEST_EQUAL(divround2even(boost::simd::Mone<vT>(), boost::simd::Mone<vT>()), boost::simd::One<r_t>());
  NT2_TEST_EQUAL(divround2even(boost::simd::One<vT>(), boost::simd::One<vT>()), boost::simd::One<r_t>());
} // end of test for floating_

NT2_TEST_CASE_TPL ( divround2even_u,  BOOST_SIMD_SIMD_UNSIGNED_TYPES)
{
  using boost::simd::divround2even;
  using boost::simd::tag::divround2even_;
  using boost::simd::native;
  typedef BOOST_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef native<T,ext_t>                  vT;
  typedef typename boost::dispatch::meta::call<divround2even_(vT,vT)>::type r_t;

  // specific values tests
  NT2_TEST_EQUAL(divround2even(boost::simd::splat<vT>(4),boost::simd::splat<vT>(0)), boost::simd::Valmax<r_t>());
  NT2_TEST_EQUAL(divround2even(boost::simd::splat<vT>(4),boost::simd::splat<vT>(3)), boost::simd::splat<r_t>(1));
  NT2_TEST_EQUAL(divround2even(boost::simd::One<vT>(), boost::simd::One<vT>()), boost::simd::One<r_t>());
  NT2_TEST_EQUAL(divround2even(boost::simd::One<vT>(),boost::simd::Zero<vT>()), boost::simd::Valmax<r_t>());
  NT2_TEST_EQUAL(divround2even(boost::simd::Zero<vT>(),boost::simd::Zero<vT>()), boost::simd::Zero<r_t>());
  NT2_TEST_EQUAL(divround2even(boost::simd::Valmax<vT>(),boost::simd::One<vT>()), boost::simd::Valmax<vT>());
  NT2_TEST_EQUAL(divround2even(boost::simd::Valmax<vT>(),boost::simd::Two<vT>()), boost::simd::Valmax<vT>()/boost::simd::Two<vT>()+boost::simd::One<r_t>());
} // end of test for floating_

NT2_TEST_CASE_TPL ( divround2even_s,  BOOST_SIMD_SIMD_INTEGRAL_SIGNED_TYPES)
{
  using boost::simd::divround2even;
  using boost::simd::tag::divround2even_;
  using boost::simd::native;
  typedef BOOST_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef native<T,ext_t>                  vT;
  typedef typename boost::dispatch::meta::call<divround2even_(vT,vT)>::type r_t;

  // specific values tests
  NT2_TEST_EQUAL(divround2even(boost::simd::splat<vT>(4),boost::simd::splat<vT>(0)), boost::simd::Valmax<r_t>());
  NT2_TEST_EQUAL(divround2even(boost::simd::splat<vT>(4),boost::simd::splat<vT>(-3)), boost::simd::splat<vT>(-1));
  NT2_TEST_EQUAL(divround2even(boost::simd::splat<vT>(-4),boost::simd::splat<vT>(-3)), boost::simd::splat<vT>(1));
  NT2_TEST_EQUAL(divround2even(boost::simd::splat<vT>(-4),boost::simd::splat<vT>(3)), boost::simd::splat<vT>(-1));
  NT2_TEST_EQUAL(divround2even(boost::simd::splat<vT>(4),boost::simd::splat<vT>(3)), boost::simd::splat<vT>(1));
  NT2_TEST_EQUAL(divround2even(boost::simd::Mone<vT>(), boost::simd::Mone<vT>()), boost::simd::One<r_t>());
  NT2_TEST_EQUAL(divround2even(boost::simd::Mone<vT>(),boost::simd::Zero<vT>()), boost::simd::Valmin<r_t>());
  NT2_TEST_EQUAL(divround2even(boost::simd::One<vT>(), boost::simd::One<vT>()), boost::simd::One<r_t>());
  NT2_TEST_EQUAL(divround2even(boost::simd::One<vT>(),boost::simd::Zero<vT>()), boost::simd::Valmax<r_t>());
  NT2_TEST_EQUAL(divround2even(boost::simd::Zero<vT>(),boost::simd::Zero<vT>()), boost::simd::Zero<r_t>());
} // end of test for floating_

