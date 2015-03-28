//==============================================================================
//         Copyright 2015 J.T. Lapreste
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/exponential/include/functions/significants.hpp>

#include <nt2/sdk/functor/meta/call.hpp>
#include <boost/simd/sdk/simd/native.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>
#include <nt2/sdk/unit/tests/ulp.hpp>
#include <nt2/include/functions/splat.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <boost/simd/sdk/config.hpp>
#include <boost/simd/sdk/simd/io.hpp>

#include <nt2/include/constants/mone.hpp>
#include <nt2/include/constants/one.hpp>
#include <nt2/include/constants/zero.hpp>
#include <nt2/include/constants/inf.hpp>
#include <nt2/include/constants/minf.hpp>
#include <nt2/include/constants/nan.hpp>

NT2_TEST_CASE_TPL ( significants,  NT2_SIMD_REAL_TYPES)
{
  using nt2::significants;
  using nt2::tag::significants_;
  using boost::simd::native;
  typedef BOOST_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef native<T,ext_t>                  vT;
  typedef typename nt2::meta::as_integer<vT>::type ivT;

  typedef typename nt2::meta::call<significants_(vT, ivT)>::type r_t;
  typedef vT wished_r_t;

  // return type conformity test
  NT2_TEST_TYPE_IS(r_t, wished_r_t);


  // specific values tests
#ifndef BOOST_SIMD_NO_INVALIDS
  NT2_TEST_ULP_EQUAL(significants(nt2::Inf<vT>(), 1), nt2::Inf<r_t>(), 0.5);
  NT2_TEST_ULP_EQUAL(significants(nt2::Minf<vT>(), 1), nt2::Minf<r_t>(), 0.5);
  NT2_TEST_ULP_EQUAL(significants(nt2::Nan<vT>(), 1), nt2::Nan<r_t>(), 0.5);
#endif
  NT2_TEST_ULP_EQUAL(significants(nt2::splat<vT>(25.34), nt2::splat<ivT>(1)), nt2::splat<vT>(30), 0.5);
  NT2_TEST_ULP_EQUAL(significants(nt2::splat<vT>(25.34), nt2::splat<ivT>(2)), nt2::splat<vT>(25), 0.5);
  NT2_TEST_ULP_EQUAL(significants(nt2::splat<vT>(25.34), nt2::splat<ivT>(3)), nt2::splat<vT>(25.3), 0.5);
  NT2_TEST_ULP_EQUAL(significants(nt2::splat<vT>(25.34), nt2::splat<ivT>(4)), nt2::splat<vT>(25.34), 0.5);
  NT2_TEST_ULP_EQUAL(significants(nt2::splat<vT>(-25.34), nt2::splat<ivT>(1)), nt2::splat<vT>(-30), 0.5);
  NT2_TEST_ULP_EQUAL(significants(nt2::splat<vT>(-25.34), nt2::splat<ivT>(2)), nt2::splat<vT>(-25), 0.5);
  NT2_TEST_ULP_EQUAL(significants(nt2::splat<vT>(-25.34), nt2::splat<ivT>(3)), nt2::splat<vT>(-25.3), 0.5);
  NT2_TEST_ULP_EQUAL(significants(nt2::splat<vT>(-25.34), nt2::splat<ivT>(4)), nt2::splat<vT>(-25.34), 0.5);
}
