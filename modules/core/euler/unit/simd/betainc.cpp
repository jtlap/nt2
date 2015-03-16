//==============================================================================
//         Copyright 2015 J.T. Lapreste
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/euler/include/functions/betainc.hpp>

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

NT2_TEST_CASE_TPL ( betainc_real, NT2_REAL_TYPES)
{
  using nt2::betainc;
  using nt2::tag::betainc_;
  using boost::simd::native;
  typedef BOOST_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef native<T,ext_t>                  vT;
  typedef typename nt2::meta::call<betainc_(vT,vT,vT)>::type r_t;
  typedef vT wished_r_t;

  // return type conformity test
  NT2_TEST_TYPE_IS(r_t, wished_r_t);

  // specific values tests
#ifndef BOOST_SIMD_NO_INVALIDS
  NT2_TEST_ULP_EQUAL(betainc( nt2::Nan<vT>()     , nt2::Nan<vT>(),  nt2::Nan<vT>()), nt2::Nan<r_t>(), 0);
#endif
  NT2_TEST_ULP_EQUAL(betainc( nt2::Half<vT>()    , nt2::One<vT>(),  nt2::One<vT>()), nt2::Half<r_t>(), 0);
  NT2_TEST_ULP_EQUAL(betainc( nt2::splat<vT>(0.2), nt2::Half<vT>(), nt2::Five<T>()), nt2::splat<vT>(8.55072394595920e-01), 10);
}



