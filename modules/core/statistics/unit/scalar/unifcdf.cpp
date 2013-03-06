//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#define NT2_UNIT_MODULE "nt2 statistics toolbox - unifcdf/scalar Mode"

//////////////////////////////////////////////////////////////////////////////
// unit test behavior of statistics  components in scalar mode
//////////////////////////////////////////////////////////////////////////////
/// created  by jt the 22/02/2011
///
#include <nt2/include/functions/unifcdf.hpp>
#include <nt2/include/functions/ones.hpp>
#include <nt2/include/functions/repnum.hpp>
#include <nt2/include/functions/zeros.hpp>
#include <nt2/include/functions/reshape.hpp>
#include <nt2/include/functions/bsxfun.hpp>
#include <nt2/include/functions/is_less_equal.hpp>
#include <nt2/include/constants/invpi.hpp>
#include <nt2/sdk/unit/tests.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/memory/buffer.hpp>
#include <nt2/toolbox/constant/constant.hpp>
#include <nt2/table.hpp>

NT2_TEST_CASE_TPL ( unifcdf_real__2_0,  NT2_REAL_TYPES)
{

  using nt2::unifcdf;
  using nt2::tag::unifcdf_;
  // specific values tests
  NT2_TEST_ULP_EQUAL(unifcdf(nt2::Nan<T>())  , nt2::Nan<T>()  , 0);
  NT2_TEST_ULP_EQUAL(unifcdf(nt2::One<T>())  , nt2::One<T>()  , 0);
  NT2_TEST_ULP_EQUAL(unifcdf(nt2::Half<T>()) , nt2::Half<T>() , 0);
  NT2_TEST_ULP_EQUAL(unifcdf(nt2::Zero<T>()) , nt2::Zero<T>() , 0);
  NT2_TEST_ULP_EQUAL(unifcdf(nt2::Inf<T>())  , nt2::One<T>()  , 0);
  NT2_TEST_ULP_EQUAL(unifcdf(nt2::Minf<T>()) , nt2::Zero<T>() , 0);
} // end of test for floating_

NT2_TEST_CASE_TPL ( unifcdf_2,  NT2_REAL_TYPES)
{

  using nt2::unifcdf;
  using nt2::tag::unifcdf_;
  using nt2::_;
  using nt2::meta::as_;

  // specific values tests
  NT2_TEST_ULP_EQUAL(unifcdf(nt2::Nan<T>(),  nt2::Zero<T>(),nt2::One<T>())  , nt2::Nan<T>() , 0);
  NT2_TEST_ULP_EQUAL(unifcdf(nt2::One<T>(),  nt2::Zero<T>(),nt2::One<T>())  , nt2::One<T>() , 0);
  NT2_TEST_ULP_EQUAL(unifcdf(nt2::Half<T>(), nt2::Zero<T>(),nt2::One<T>())  , nt2::Half<T>(), 0);
  NT2_TEST_ULP_EQUAL(unifcdf(nt2::Zero<T>(), nt2::Zero<T>(),nt2::One<T>())  , nt2::Zero<T>(), 0);
  NT2_TEST_ULP_EQUAL(unifcdf(nt2::Inf<T>(),  nt2::Zero<T>(),nt2::One<T>())  , nt2::One<T>() , 0);
  NT2_TEST_ULP_EQUAL(unifcdf(nt2::Minf<T>(), nt2::Zero<T>(),nt2::One<T>())  , nt2::Zero<T>(), 0);

  NT2_TEST_ULP_EQUAL(unifcdf(nt2::Half<T>(), nt2::One<T>(),nt2::Zero<T>())  , nt2::Nan<T>() , 0);
} // end of test for floating_

NT2_TEST_CASE_TPL ( unifcdf_3,  NT2_REAL_TYPES)
{

  using nt2::unifcdf;
  using nt2::tag::unifcdf_;
  using nt2::_;
  using nt2::meta::as_;

  nt2::table<T> a = _(T(-5), T(1), T(5))/T(10);
  NT2_DISPLAY(a);
  nt2::table<T> z =  unifcdf(a+T(0.5), T(0), T(1));
  NT2_DISPLAY(z);
  NT2_TEST_ULP_EQUAL(z, nt2::_(T(0),T(0.1), T(1)), 5.0);
  z =  unifcdf(a+T(0.5), a, a+T(1));
  NT2_TEST_ULP_EQUAL(z, nt2::repnum(T(0.5), 1, 11), 5.0);
} // end of test for floating_




