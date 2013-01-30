//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#define NT2_UNIT_MODULE "nt2 statistics toolbox - unifpdf/scalar Mode"

//////////////////////////////////////////////////////////////////////////////
/// unit test behavior of statistics  components in scalar mode
//////////////////////////////////////////////////////////////////////////////
/// created  by jt the 22/02/2011
///
#include <nt2/include/functions/unifpdf.hpp>
#include <nt2/include/functions/ones.hpp>
#include <nt2/include/functions/zeros.hpp>
#include <nt2/include/functions/linspace.hpp>
#include <nt2/include/functions/isequal.hpp>
#include <nt2/include/functions/isulpequal.hpp>
#include <nt2/include/functions/predecessor.hpp>
#include <nt2/include/functions/successor.hpp>
#include <nt2/include/functions/ones.hpp>
#include <nt2/include/functions/zeros.hpp>
#include <nt2/include/constants/invpi.hpp>
#include <nt2/sdk/unit/tests.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/memory/buffer.hpp>
#include <nt2/toolbox/constant/constant.hpp>
#include <nt2/table.hpp>

NT2_TEST_CASE_TPL ( unifpdf_real__2_0,  NT2_REAL_TYPES)
{

  using nt2::unifpdf;
  using nt2::tag::unifpdf_;
  // specific values tests
  NT2_TEST_ULP_EQUAL(unifpdf(nt2::Nan<T>())  , nt2::Nan<T>() , 0);
  NT2_TEST_ULP_EQUAL(unifpdf(nt2::One<T>())  , nt2::One<T>() , 0);
  NT2_TEST_ULP_EQUAL(unifpdf(nt2::Half<T>()) , nt2::One<T>() , 0);
  NT2_TEST_ULP_EQUAL(unifpdf(nt2::Zero<T>()) , nt2::One<T>() , 0);
  NT2_TEST_ULP_EQUAL(unifpdf(nt2::Inf<T>())  , nt2::Zero<T>(), 0);
  NT2_TEST_ULP_EQUAL(unifpdf(nt2::Minf<T>())  , nt2::Zero<T>(), 0);
} // end of test for floating_

NT2_TEST_CASE_TPL ( unifpdf_2,  NT2_REAL_TYPES)
{

  using nt2::unifpdf;
  using nt2::tag::unifpdf_;
  using nt2::_;
  using nt2::meta::as_;

  // specific values tests
  NT2_TEST_ULP_EQUAL(unifpdf(nt2::Nan<T>(),  nt2::Zero<T>(),nt2::One<T>())  , nt2::Nan<T>() , 0);
  NT2_TEST_ULP_EQUAL(unifpdf(nt2::One<T>(),  nt2::Zero<T>(),nt2::One<T>())  , nt2::One<T>() , 0);
  NT2_TEST_ULP_EQUAL(unifpdf(nt2::Half<T>(), nt2::Zero<T>(),nt2::One<T>())  , nt2::One<T>() , 0);
  NT2_TEST_ULP_EQUAL(unifpdf(nt2::Zero<T>(), nt2::Zero<T>(),nt2::One<T>())  , nt2::One<T>() , 0);
  NT2_TEST_ULP_EQUAL(unifpdf(nt2::Inf<T>(),  nt2::Zero<T>(),nt2::One<T>())  , nt2::Zero<T>(), 0);
  NT2_TEST_ULP_EQUAL(unifpdf(nt2::Minf<T>(), nt2::Zero<T>(),nt2::One<T>())  , nt2::Zero<T>(), 0);

  NT2_TEST_ULP_EQUAL(unifpdf(nt2::Half<T>(), nt2::One<T>(),nt2::Zero<T>())  , nt2::Nan<T>() , 0);

  nt2::table<T> a = _(T(-5), T(1), T(5))/T(3);
  nt2::table<T> b = nt2::zeros(size(a), as_<T>());
  nt2::table<T> c = nt2::ones(size(a), as_<T>());
  NT2_DISPLAY(a);
  NT2_DISPLAY(unifpdf(a, b, c));
  NT2_DISPLAY(unifpdf(a, nt2::zeros(size(a), as_<T>()), nt2::ones(size(a), as_<T>())));
  {
    nt2::table<T> a = nt2::reshape(nt2::linspace(T(0), T(1), 50), 10, 5);
    NT2_DISPLAY(a);
    NT2_DISPLAY(unifpdf(a, T(0), T(1)));
  }

}

NT2_TEST_CASE_TPL ( unifpdf_3,  NT2_REAL_TYPES)
{

  using nt2::unifpdf;
  using nt2::tag::unifpdf_;
  using nt2::_;
  using nt2::meta::as_;
  nt2::table<T> x = nt2::linspace(T(0), T(1));
  nt2::table<T> z = unifpdf(x);
  NT2_TEST(nt2::isulpequal(unifpdf(x), nt2::ones(size(x), nt2::meta::as_<T>())));
  NT2_TEST(nt2::isulpequal(z, nt2::ones(size(x), nt2::meta::as_<T>())));
  x =  nt2::linspace(nt2::successor(T(1)), T(100));
  z = unifpdf(x);
  NT2_TEST(nt2::isulpequal(unifpdf(x), nt2::zeros(size(x), nt2::meta::as_<T>())));
  NT2_TEST(nt2::isulpequal(z, nt2::zeros(size(x), nt2::meta::as_<T>())));
  x =  nt2::linspace(T(-100), nt2::predecessor(T(0)));
  z = unifpdf(x);
  NT2_TEST(nt2::isulpequal(unifpdf(x), nt2::zeros(size(x), nt2::meta::as_<T>())));
  NT2_TEST(nt2::isulpequal(z, nt2::zeros(size(x), nt2::meta::as_<T>())));
} // end of test for floating_

