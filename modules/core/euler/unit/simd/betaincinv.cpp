//==============================================================================
//         Copyright 2015 J.T. Lapreste
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/euler/include/functions/betaincinv.hpp>

#include <nt2/sdk/functor/meta/call.hpp>
#include <boost/simd/sdk/simd/native.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>
#include <nt2/sdk/unit/tests/ulp.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <boost/simd/sdk/config.hpp>

#include <nt2/include/functions/splat.hpp>
#include <nt2/include/constants/one.hpp>
#include <nt2/include/constants/nan.hpp>
#include <nt2/include/constants/half.hpp>
#include <nt2/include/constants/five.hpp>

NT2_TEST_CASE_TPL ( betaincinv_real, NT2_REAL_TYPES)
{
  using nt2::betaincinv;
  using nt2::tag::betaincinv_;
  using boost::simd::native;
  typedef BOOST_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef native<T,ext_t>                  vT;
  typedef typename nt2::meta::call<betaincinv_(vT,vT,vT)>::type r_t;
  typedef vT wished_r_t;

  // return type conformity test
  NT2_TEST_TYPE_IS(r_t, wished_r_t);

  // specific values tests
#ifndef BOOST_SIMD_NO_INVALIDS
  NT2_TEST_ULP_EQUAL(betaincinv( nt2::Nan<vT>() , nt2::Nan<vT>(), nt2::Nan<vT>()  ), nt2::Nan<vT>(), 0);
#endif
  NT2_TEST_ULP_EQUAL(betaincinv( nt2::Half<vT>()         , nt2::One<vT>() , nt2::One<vT>() ),nt2::Half<vT>(), 0);
  NT2_TEST_ULP_EQUAL(betaincinv( nt2::splat<vT>(8.55072394595920e-01 ) , nt2::Half<vT>(), nt2::Five<vT>()),nt2::splat<vT>(0.2)        , 10);
  NT2_TEST_ULP_EQUAL(betaincinv( nt2::Half<vT>()           , nt2::splat<vT>(4000)       , nt2::splat<vT>(4000))       ,nt2::splat<vT>(0.5)        , 10000);

}



NT2_TEST_CASE_TPL ( betaincinv_2, NT2_REAL_TYPES)
{
  using nt2::betaincinv;
  using nt2::tag::betaincinv_;
  using boost::simd::native;
  typedef BOOST_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef native<T,ext_t>                  vT;

  // specific values tests
  T x[] = {
           0.87500000000000,
           0.68750000000000,
           0.50000000000000,
           0.34375000000000,
           0.22656250000000,
           0.14453125000000,
           0.08984375000000,
           0.05468750000000,
           0.03271484375000,
           0.01928710937500};
  for(int i =  0;  i < 10; ++i)
    NT2_TEST_ULP_EQUAL(betaincinv(nt2::splat<vT>(x[i]), nt2::splat<vT>(i+1), nt2::splat<vT>(3)), nt2::splat<vT>(.5), 20);

}
