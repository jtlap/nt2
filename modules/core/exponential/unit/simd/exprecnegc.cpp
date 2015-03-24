//==============================================================================
//         Copyright 2015 J.T. Lapreste
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/exponential/include/functions/exprecnegc.hpp>

#include <nt2/sdk/functor/meta/call.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>
#include <nt2/sdk/unit/tests/ulp.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <boost/simd/sdk/config.hpp>
#include <nt2/sdk/meta/as_floating.hpp>
#include <nt2/include/functions/rec.hpp>
#include <nt2/include/constants/mone.hpp>
#include <nt2/include/constants/one.hpp>
#include <nt2/include/constants/zero.hpp>
#include <nt2/include/constants/mzero.hpp>
#include <nt2/include/constants/inf.hpp>
#include <nt2/include/constants/minf.hpp>
#include <nt2/include/constants/nan.hpp>
#include <nt2/include/constants/exp_1.hpp>

NT2_TEST_CASE_TPL ( exprecnegc,  NT2_SIMD_REAL_TYPES)
{
  using nt2::exprecnegc;
  using nt2::tag::exprecnegc_;
  using boost::simd::native;
  typedef BOOST_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef native<T,ext_t>                  vT;

  typedef typename nt2::meta::call<exprecnegc_(vT)>::type r_t;
  typedef vT wished_r_t;

  // return type conformity test
  NT2_TEST_TYPE_IS(r_t, wished_r_t);

  // specific values tests
#ifndef BOOST_SIMD_NO_INVALIDS
  NT2_TEST_ULP_EQUAL(exprecnegc(nt2::Inf<vT>()), nt2::Zero<r_t>(), 0.75);
  NT2_TEST_ULP_EQUAL(exprecnegc(nt2::Minf<vT>()), nt2::Zero<r_t>(), 0.75);
  NT2_TEST_ULP_EQUAL(exprecnegc(nt2::Nan<vT>()), nt2::Nan<r_t>(), 0.75);
#endif
  NT2_TEST_ULP_EQUAL(exprecnegc(nt2::Mone<vT>()),
                     nt2::oneminus(nt2::Exp_1<r_t>()),0.75);
  NT2_TEST_ULP_EQUAL(exprecnegc(nt2::One<vT>()),
                     nt2::oneminus(nt2::rec(nt2::Exp_1<r_t>())), 0.75);
  NT2_TEST_ULP_EQUAL(exprecnegc(nt2::Zero<vT>()), nt2::One<r_t>(), 0.75);
  NT2_TEST_ULP_EQUAL(exprecnegc(nt2::Mzero<vT>()), nt2::Minf<r_t>(), 0.75);
}
