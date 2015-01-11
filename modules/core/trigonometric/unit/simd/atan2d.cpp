//==============================================================================
//         Copyright 2015  J.T. Lapreste
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/include/functions/atan2d.hpp>

#include <nt2/sdk/functor/meta/call.hpp>
#include <boost/simd/sdk/config.hpp>
#include <nt2/include/constants/half.hpp>
#include <nt2/include/constants/mhalf.hpp>
#include <nt2/include/constants/mone.hpp>
#include <nt2/include/constants/one.hpp>
#include <nt2/include/constants/zero.hpp>
#include <nt2/include/constants/_45.hpp>
#include <nt2/include/constants/_90.hpp>
#include <nt2/include/constants/_135.hpp>
#include <nt2/include/constants/_180.hpp>
#include <nt2/include/constants/inf.hpp>
#include <nt2/include/constants/minf.hpp>
#include <nt2/include/constants/nan.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/ulp.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>

NT2_TEST_CASE_TPL ( atan2d_real,  NT2_SIMD_REAL_TYPES)
{
  using nt2::atan2d;
  using nt2::tag::atan2d_;
  using boost::simd::native;
  typedef BOOST_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef native<T,ext_t>                  vT;

  typedef typename nt2::meta::call<atan2d_(vT,vT)>::type r_t;
  typedef vT wished_r_t;

  // return type conformity test
  NT2_TEST_TYPE_IS(r_t, wished_r_t);

  // specific values tests
#ifndef BOOST_SIMD_NO_INVALIDS
  NT2_TEST_ULP_EQUAL(atan2d(nt2::Inf<vT>(), nt2::Inf<vT>())    , nt2::_45<r_t>(), 0.5);
  NT2_TEST_ULP_EQUAL(atan2d(nt2::Inf<vT>(),nt2::One<vT>())     , nt2::_90<r_t>(), 0.5);
  NT2_TEST_ULP_EQUAL(atan2d(nt2::Minf<vT>(), nt2::Minf<vT>())  , -nt2::_135<r_t>(), 0.5);
  NT2_TEST_ULP_EQUAL(atan2d(nt2::Minf<vT>(),nt2::One<vT>())    , -nt2::_90<r_t>(), 0.5);
  NT2_TEST_ULP_EQUAL(atan2d(nt2::Nan<vT>(), nt2::Nan<vT>())    , nt2::Nan<r_t>(), 0.5);
  NT2_TEST_ULP_EQUAL(atan2d(nt2::Nan<vT>(), nt2::Zero<vT>())   , nt2::Nan<r_t>(), 0.5);
  NT2_TEST_ULP_EQUAL(atan2d(nt2::Zero<vT>(), nt2::Nan<vT>())   , nt2::Nan<r_t>(), 0.5);
  NT2_TEST_ULP_EQUAL(atan2d(nt2::One<vT>(),nt2::Inf<vT>())     , nt2::Zero<r_t>(), 0.5);
  NT2_TEST_ULP_EQUAL(atan2d(nt2::One<vT>(),nt2::Minf<vT>())    , nt2::_180<r_t>(), 0.5);
#endif
  NT2_TEST_ULP_EQUAL(atan2d(nt2::Half<vT>(), nt2::Half<vT>())  , nt2::_45<r_t>(), 0.5);
  NT2_TEST_ULP_EQUAL(atan2d(nt2::Mhalf<vT>(), nt2::Mhalf<vT>()), -nt2::_135<r_t>(), 0.5);
  NT2_TEST_ULP_EQUAL(atan2d(nt2::Mone<vT>(), nt2::Mone<vT>())  , -nt2::_135<r_t>(), 0.5);
  NT2_TEST_ULP_EQUAL(atan2d(nt2::One<vT>(), nt2::One<vT>())    , nt2::_45<r_t>(), 0.5);
  NT2_TEST_ULP_EQUAL(atan2d(nt2::Zero<vT>(), nt2::Zero<vT>())  , nt2::Zero<r_t>(), 0.5);
}
