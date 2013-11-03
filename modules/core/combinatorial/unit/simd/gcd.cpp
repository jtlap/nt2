//==============================================================================
//         Copyright 2003 - 2013   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/combinatorial/include/functions/gcd.hpp>

#include <nt2/sdk/functor/meta/call.hpp>
#include <boost/simd/sdk/simd/native.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/ulp.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <boost/simd/sdk/config.hpp>
#include <boost/simd/sdk/simd/io.hpp>

#include <nt2/include/constants/mone.hpp>
#include <nt2/include/constants/one.hpp>
#include <nt2/include/constants/zero.hpp>
#include <nt2/include/constants/inf.hpp>
#include <nt2/include/constants/minf.hpp>
#include <nt2/include/constants/nan.hpp>
#include <nt2/include/functions/splat.hpp>

NT2_TEST_CASE_TPL ( gcd_real,  NT2_SIMD_REAL_TYPES)
{
  using nt2::gcd;
  using nt2::tag::gcd_;
  using boost::simd::native;
  typedef BOOST_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef native<T,ext_t>                  vT;
  typedef typename nt2::meta::call<gcd_(vT,vT)>::type r_t;
  typedef vT wished_r_t;

  // return type conformity test
  NT2_TEST_TYPE_IS(r_t, wished_r_t);


  // specific values tests
#ifndef BOOST_SIMD_NO_INVALIDS
  NT2_TEST_EQUAL(gcd(nt2::Inf<vT>(), nt2::Inf<vT>()), nt2::Nan<vT>());
  NT2_TEST_EQUAL(gcd(nt2::Minf<vT>(), nt2::Minf<vT>()), nt2::Nan<vT>());
  NT2_TEST_EQUAL(gcd(nt2::Nan<vT>(), nt2::Nan<vT>()), nt2::Nan<vT>());
#endif
 NT2_TEST_EQUAL(gcd(nt2::splat<vT>(120),nt2::splat<vT>(80)), nt2::splat<vT>(40));
  NT2_TEST_EQUAL(gcd(nt2::splat<vT>(3),nt2::splat<vT>(15)), nt2::splat<vT>(3));
  NT2_TEST_EQUAL(gcd(nt2::splat<vT>(3),nt2::splat<vT>(5)), nt2::splat<vT>(1));
  NT2_TEST_EQUAL(gcd(nt2::splat<vT>(6),nt2::splat<vT>(15)), nt2::splat<vT>(3));
  NT2_TEST_EQUAL(gcd(nt2::Mone<vT>(), nt2::Mone<vT>()), nt2::Mone<vT>());
  NT2_TEST_EQUAL(gcd(nt2::One<vT>(), nt2::One<vT>()), nt2::One<vT>());
  NT2_TEST_EQUAL(gcd(nt2::Zero<vT>(), nt2::Zero<vT>()), nt2::Zero<vT>());
}

NT2_TEST_CASE_TPL ( gcd_int,  NT2_SIMD_INTEGRAL_TYPES)
{
  using nt2::gcd;
  using nt2::tag::gcd_;
  using boost::simd::native;
  typedef BOOST_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef native<T,ext_t>                  vT;
  typedef typename nt2::meta::call<gcd_(vT,vT)>::type r_t;
  typedef vT wished_r_t;

  // return type conformity test
  NT2_TEST_TYPE_IS(r_t, wished_r_t);


  // specific values tests
  NT2_TEST_EQUAL(gcd(nt2::splat<vT>(120),nt2::splat<vT>(80)), nt2::splat<vT>(40));
  NT2_TEST_EQUAL(gcd(nt2::splat<vT>(3),nt2::splat<vT>(15)), nt2::splat<vT>(3));
  NT2_TEST_EQUAL(gcd(nt2::splat<vT>(3),nt2::splat<vT>(5)), nt2::splat<vT>(1));
  NT2_TEST_EQUAL(gcd(nt2::splat<vT>(6),nt2::splat<vT>(15)), nt2::splat<vT>(3));
  NT2_TEST_EQUAL(gcd(nt2::Mone<vT>(), nt2::Mone<vT>()), nt2::Mone<vT>());
  NT2_TEST_EQUAL(gcd(nt2::One<vT>(), nt2::One<vT>()), nt2::One<vT>());
  NT2_TEST_EQUAL(gcd(nt2::Zero<vT>(), nt2::Zero<vT>()), nt2::Zero<vT>());
}

