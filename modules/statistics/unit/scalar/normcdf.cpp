//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#define NT2_UNIT_MODULE "nt2 statistics toolbox - normcdf/scalar Mode"

//////////////////////////////////////////////////////////////////////////////
// unit test behavior of statistics components in scalar mode
//////////////////////////////////////////////////////////////////////////////
/// created  by jt the 22/02/2011
///
#include <nt2/include/functions/normcdf.hpp>
#include <nt2/include/functions/ulpdist.hpp>
#include <nt2/include/functions/eye.hpp>
#include <nt2/include/functions/ones.hpp>
#include <nt2/include/functions/abs.hpp>
#include <nt2/sdk/unit/tests.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/memory/buffer.hpp>
#include <nt2/toolbox/constant/constant.hpp>
#include <nt2/table.hpp>

NT2_TEST_CASE_TPL ( normcdf_1,  (float)(double))//NT2_REAL_TYPES)
{

  using nt2::normcdf;
  using nt2::tag::normcdf_;
  using nt2::_;


  // specific values tests
  NT2_TEST_ULP_EQUAL(normcdf(nt2::Nan<T>()), nt2::Nan<T>(), 0.5);
  NT2_TEST_ULP_EQUAL(normcdf(nt2::One<T>()), T(0.841344746068542948585232545632), 1.5);
  NT2_TEST_ULP_EQUAL(normcdf(nt2::Mone<T>()), T(0.158655253931457051414767454368), 5.5);
  NT2_TEST_ULP_EQUAL(normcdf(nt2::Zero<T>()), nt2::Half<T>(), 0.5);
  NT2_TEST_ULP_EQUAL(normcdf(nt2::Inf<T>()), nt2::One<T>(), 0.5);
  NT2_TEST_ULP_EQUAL(normcdf(nt2::Minf<T>()), nt2::Zero<T>(), 0.5);

  nt2::table<T> a = _(T(-5), T(1), T(5));
  NT2_DISPLAY(a);
  NT2_DISPLAY(normcdf(a));
} // end of test for floating_

NT2_TEST_CASE_TPL ( normcdf_2,  NT2_REAL_TYPES)
{

  using nt2::normcdf;
  using nt2::tag::normcdf_;
  using nt2::_;


  // specific values tests
  NT2_TEST_ULP_EQUAL(normcdf(nt2::Nan<T>(), nt2::One<T>()), nt2::Nan<T>(), 0.5);
  NT2_TEST_ULP_EQUAL(normcdf(nt2::Zero<T>(), nt2::One<T>() ), T(0.158655253931457051414767454368), 5.5);
  NT2_TEST_ULP_EQUAL(normcdf(nt2::Mone<T>(), nt2::One<T>()),  T(0.0227501319481792072002826371665), 25);
  NT2_TEST_ULP_EQUAL(normcdf(nt2::Inf<T>(), nt2::One<T>()), nt2::One<T>(), 0.5);
  NT2_TEST_ULP_EQUAL(normcdf(nt2::Minf<T>(), nt2::One<T>()), nt2::Zero<T>(), 0.5);

  nt2::table<T> a = _(T(-5), T(1), T(5));
  NT2_DISPLAY(a);
  NT2_DISPLAY(normcdf(a));
  NT2_DISPLAY(normcdf(a, nt2::Zero<T>()));
  NT2_DISPLAY(normcdf(a, nt2::Zero<T>(), nt2::One<T>()));
  //  a = nt2::reshape(_(T(1), T(16)), 4, 4);
  //   NT2_DISPLAY(normcdf(a, a(_, 1)));
  //   NT2_DISPLAY(normcdf(a, a(1, _)));
  NT2_DISPLAY(normcdf(a, a));
  NT2_DISPLAY(normcdf(a, a, nt2::abs(a)));
  NT2_DISPLAY(normcdf(a, a, T(2)));
  //   NT2_DISPLAY(normcdf(a, a(_, 1), T(2)));
  nt2::table<T> r, plo, pup;
  nt2::table<T> cov = nt2::eye(2, nt2::meta::as_<T>());
  nt2::tie(r, plo, pup) = nt2::normcdf(a, nt2::ones(size(a), nt2::meta::as_<T>()), T(1), cov, T(0.05));
  NT2_DISPLAY(r);
  NT2_DISPLAY(plo);
  NT2_DISPLAY(pup);
  r =  nt2::normcdf(a, nt2::ones(size(a), nt2::meta::as_<T>()), T(1), cov, T(0.05));
  NT2_DISPLAY(r);
  nt2::tie(r, plo, pup) = nt2::normcdf(a, T(0), T(1), cov, T(0.05));
  NT2_DISPLAY(r);
  NT2_DISPLAY(plo);
  NT2_DISPLAY(pup);


} // end of test for floating_

