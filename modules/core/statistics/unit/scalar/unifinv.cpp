//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/include/functions/unifinv.hpp>
#include <nt2/include/functions/ones.hpp>
#include <nt2/include/functions/zeros.hpp>
#include <nt2/include/functions/cons.hpp>
#include <nt2/include/functions/if_allbits_else.hpp>
#include <nt2/include/constants/invpi.hpp>
#include <nt2/sdk/unit/tests/ulp.hpp>
#include <nt2/sdk/unit/module.hpp>

#include <nt2/constant/constant.hpp>
#include <nt2/table.hpp>

NT2_TEST_CASE_TPL ( unifinv_real__2_0,  NT2_REAL_TYPES)
{

  using nt2::unifinv;
  using nt2::tag::unifinv_;
  // specific values tests
  NT2_TEST_ULP_EQUAL(unifinv(nt2::Nan<T>())  , nt2::Nan<T>()  , 0);
  NT2_TEST_ULP_EQUAL(unifinv(nt2::One<T>())  , nt2::One<T>()  , 0);
  NT2_TEST_ULP_EQUAL(unifinv(nt2::Half<T>()) , nt2::Half<T>() , 0);
  NT2_TEST_ULP_EQUAL(unifinv(nt2::Zero<T>()) , nt2::Zero<T>() , 0);
  NT2_TEST_ULP_EQUAL(unifinv(nt2::Inf<T>())  , nt2::Nan<T>()  , 0);
  NT2_TEST_ULP_EQUAL(unifinv(nt2::Minf<T>()) , nt2::Nan<T>() , 0);
} // end of test for floating_

NT2_TEST_CASE_TPL ( unifinv_2,  NT2_REAL_TYPES)
{

  using nt2::unifinv;
  using nt2::tag::unifinv_;
  using nt2::_;
  using nt2::meta::as_;

  // specific values tests
  NT2_TEST_ULP_EQUAL(unifinv(nt2::Nan<T>(),  nt2::Zero<T>(),nt2::One<T>())  , nt2::Nan<T>() , 0);
  NT2_TEST_ULP_EQUAL(unifinv(nt2::One<T>(),  nt2::Zero<T>(),nt2::One<T>())  , nt2::One<T>() , 0);
  NT2_TEST_ULP_EQUAL(unifinv(nt2::Half<T>(), nt2::Zero<T>(),nt2::One<T>())  , nt2::Half<T>(), 0);
  NT2_TEST_ULP_EQUAL(unifinv(nt2::Zero<T>(), nt2::Zero<T>(),nt2::One<T>())  , nt2::Zero<T>(), 0);
  NT2_TEST_ULP_EQUAL(unifinv(nt2::Inf<T>(),  nt2::Zero<T>(),nt2::One<T>())  , nt2::Nan<T>() , 0);
  NT2_TEST_ULP_EQUAL(unifinv(nt2::Minf<T>(), nt2::Zero<T>(),nt2::One<T>())  , nt2::Nan<T>(), 0);

  //  NT2_TEST_ULP_EQUAL(unifinv(nt2::Half<T>(), nt2::One<T>(),nt2::Zero<T>())  , nt2::Nan<T>() , 0);
  nt2::table<T> a = _(T(-5), T(1), T(5))/T(3);
  nt2::table<T> r = nt2::cons<T>(  nt2::Nan<T>(),  nt2::Nan<T>(),  nt2::Nan<T>(),  nt2::Nan<T>(),  nt2::Nan<T>(),
                                   0.0, 0.33333333333333331483, 0.66666666666666662966, 1.0,  nt2::Nan<T>(),  nt2::Nan<T>());
  NT2_TEST_ULP_EQUAL(unifinv(a, nt2::zeros(size(a), as_<T>()), nt2::ones(size(a), as_<T>())), r, 1);
  NT2_TEST_ULP_EQUAL(unifinv(a, T(0), T(1)), r, 1);
  nt2::table<T> z = nt2::if_allbits_else(nt2::logical_or(nt2::is_ltz(a), nt2::gt(a, nt2::One<T>())), a);
  NT2_TEST_ULP_EQUAL(z, unifinv(a), 1);
} // end of test for floating_


