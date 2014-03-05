//==============================================================================
//         Copyright 2003 - 2013   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/elliptic/include/functions/ellpe.hpp>

#include <nt2/sdk/functor/meta/call.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>
#include <nt2/sdk/unit/tests/ulp.hpp>
#include <nt2/sdk/unit/tests/basic.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <boost/simd/sdk/config.hpp>

#include <nt2/include/constants/one.hpp>
#include <nt2/include/constants/pi.hpp>
#include <nt2/include/constants/pio_2.hpp>
#include <nt2/include/constants/zero.hpp>
#include <nt2/include/constants/nan.hpp>
#include <nt2/include/constants/half.hpp>
#include <nt2/include/constants/quarter.hpp>

NT2_TEST_CASE_TPL ( ellpe_real__1_0,  NT2_REAL_TYPES)
{
  using nt2::ellpe;
  using nt2::tag::ellpe_;
  typedef typename nt2::meta::call<ellpe_(T)>::type r_t;
  typedef T wished_r_t;

  // return type conformity test
  NT2_TEST_TYPE_IS(r_t, wished_r_t);

  // specific values tests
#ifndef BOOST_SIMD_NO_INVALIDS
  NT2_TEST_ULP_EQUAL(ellpe(nt2::Nan<T>()), nt2::Nan<r_t>(), 0.5);
#endif
  NT2_TEST_ULP_EQUAL(ellpe(nt2::Pio_2<T>()), nt2::Nan<r_t>(), 0.5);
  NT2_TEST_ULP_EQUAL(ellpe(nt2::One<T>()), nt2::Pio_2<r_t>(), 0.5);
  NT2_TEST_ULP_EQUAL(ellpe(nt2::Zero<T>()), nt2::One<r_t>(), 0.5);
  NT2_TEST_ULP_EQUAL(ellpe(nt2::Half<T>()),  T(1.350643881047675), 1);
  NT2_TEST_ULP_EQUAL(ellpe(nt2::Quarter<T>()),  T(1.21105602756846), 1);
}
