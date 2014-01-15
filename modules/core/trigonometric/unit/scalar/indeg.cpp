//==============================================================================
//         Copyright 2003 - 2013   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/trigonometric/include/functions/indeg.hpp>

#include <nt2/sdk/functor/meta/call.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>
#include <nt2/sdk/unit/tests/ulp.hpp>
#include <nt2/sdk/unit/tests/basic.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <boost/simd/sdk/config.hpp>

#include <nt2/include/constants/pi.hpp>
#include <nt2/include/constants/zero.hpp>
#include <nt2/include/constants/inf.hpp>
#include <nt2/include/constants/minf.hpp>
#include <nt2/include/constants/nan.hpp>
#include <nt2/include/constants/_45.hpp>
#include <nt2/include/constants/_90.hpp>
#include <nt2/include/constants/_180.hpp>
#include <nt2/include/constants/pio_2.hpp>
#include <nt2/include/constants/pio_4.hpp>

NT2_TEST_CASE_TPL ( indeg_real,  NT2_REAL_TYPES)
{
  using nt2::indeg;
  using nt2::tag::indeg_;

  typedef typename nt2::meta::call<indeg_(T)>::type r_t;
  typedef T wished_r_t;

  // return type conformity test
  NT2_TEST_TYPE_IS(r_t, wished_r_t);

  // specific values tests
#ifndef BOOST_SIMD_NO_INVALIDS
  NT2_TEST_ULP_EQUAL(indeg(nt2::Inf<T>()), nt2::Inf<r_t>(), 0.5);
  NT2_TEST_ULP_EQUAL(indeg(nt2::Minf<T>()), nt2::Minf<r_t>(), 0.5);
  NT2_TEST_ULP_EQUAL(indeg(nt2::Nan<T>()), nt2::Nan<r_t>(), 0.5);
#endif
  NT2_TEST_ULP_EQUAL(indeg(-nt2::Pi<T>()), -nt2::_180<r_t>(), 0.5);
  NT2_TEST_ULP_EQUAL(indeg(-nt2::Pio_2<T>()), -nt2::_90<r_t>(), 0.5);
  NT2_TEST_ULP_EQUAL(indeg(-nt2::Pio_4<T>()), -nt2::_45<r_t>(), 0.5);
  NT2_TEST_ULP_EQUAL(indeg(nt2::Pi<T>()), nt2::_180<r_t>(), 0.5);
  NT2_TEST_ULP_EQUAL(indeg(nt2::Pio_2<T>()), nt2::_90<r_t>(), 0.5);
  NT2_TEST_ULP_EQUAL(indeg(nt2::Pio_4<T>()), nt2::_45<r_t>(), 0.5);
  NT2_TEST_ULP_EQUAL(indeg(nt2::Zero<T>()), nt2::Zero<r_t>(), 0.5);
}
