//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#define NT2_UNIT_MODULE "nt2 statistics toolbox - expinv/scalar Mode"

//////////////////////////////////////////////////////////////////////////////
// unit test behavior of statistics components in scalar mode
//////////////////////////////////////////////////////////////////////////////
/// created  by jt the 22/02/2011
///
#include <nt2/include/functions/expinv.hpp>
#include <nt2/include/functions/expcdf.hpp>
#include <nt2/include/functions/bsxfun.hpp>
#include <nt2/include/functions/ulpdist.hpp>
#include <nt2/include/functions/negif.hpp>
#include <nt2/include/functions/isulpequal.hpp>
#include <nt2/include/functions/is_ltz.hpp>
#include <nt2/include/constants/invexp_1.hpp>
#include <nt2/include/constants/zero.hpp>
#include <nt2/include/constants/one.hpp>
#include <nt2/include/functions/ones.hpp>
#include <nt2/include/constants/nan.hpp>
#include <nt2/include/constants/log_2.hpp>
#include <nt2/sdk/unit/tests.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/memory/buffer.hpp>
#include <nt2/table.hpp>

NT2_TEST_CASE_TPL ( expinv_1,  NT2_REAL_TYPES)
{

  using nt2::expinv;
  using nt2::tag::expinv_;
  using nt2::_;


  // specific values tests
  NT2_TEST_ULP_EQUAL(expinv(nt2::Nan<T>()), nt2::Nan<T>(), 0);
  NT2_TEST_ULP_EQUAL(expinv(nt2::One<T>()),  nt2::Inf<T>(), 0);
  NT2_TEST_ULP_EQUAL(expinv(nt2::Zero<T>()), nt2::Zero<T>(), 0);
  NT2_TEST_ULP_EQUAL(expinv(nt2::Half<T>()),  nt2::Log_2<T>(), 0);

  nt2::table<T> a = _(T(0), T(0.5), T(5))/T(5);
  NT2_DISPLAY(a);
  NT2_DISPLAY(expinv(a));
  NT2_DISPLAY(nt2::expcdf(expinv(a)));
  NT2_TEST(isulpequal(a, nt2::expcdf(expinv(a)), T(2)));

  nt2::table<T> b = _(T(0), T(0.5), T(10))/T(5);
  NT2_DISPLAY(b);
  NT2_DISPLAY(expinv(b));
  NT2_DISPLAY(nt2::expinv(nt2::expcdf(b)));
  NT2_TEST(isulpequal(b, nt2::expinv(nt2::expcdf(b)), T(2)));
} // end of test for floating_

NT2_TEST_CASE_TPL ( expinv_2,  (float))//NT2_REAL_TYPES)
{

  using nt2::expinv;
  using nt2::tag::expinv_;
  using nt2::_;


  // specific values tests
  NT2_TEST_ULP_EQUAL(expinv(nt2::Nan<T>(), nt2::One<T>()), nt2::Nan<T>(), 0);
  NT2_TEST_ULP_EQUAL(expinv(nt2::Zero<T>(), nt2::One<T>() ), nt2::Zero<T>(), 0);
  NT2_TEST_ULP_EQUAL(expinv(nt2::One<T>(), nt2::One<T>()),   nt2::Inf<T>(), 0);
  NT2_TEST_ULP_EQUAL(expinv(nt2::Half<T>(), nt2::One<T>()), nt2::Log_2<T>(), 0);
  {
    nt2::table<T> a = _(T(0), T(1), T(10))(_)/T(10);
    NT2_DISPLAY(a);
    NT2_DISPLAY(expinv(a));
  }
  nt2::table<T> a = _(T(0), T(1), T(10))/T(10);
  nt2::table<T> r, plo, pup;
  NT2_DISPLAY(a);
  NT2_DISPLAY(expinv(a));

  NT2_DISPLAY(expinv(a, nt2::One<T>()));
  NT2_DISPLAY(expinv(nt2::Half<T>(), a+T(10)));
  a = nt2::reshape(_(T(1), T(16)), 4, 4)/T(16);
  NT2_DISPLAY(a);
  nt2::table<T> z = expinv(a, a+T(10));
  NT2_DISPLAY(z);

  a = _(T(0), T(1), T(10))/T(10);
  nt2::table<T> b = _(T(1), T(1), T(11));
  NT2_DISPLAY(b);

  NT2_DISPLAY(expinv(a, b));
  NT2_DISPLAY(expinv(nt2::Half<T>(), b));
  nt2::tie(r, plo, pup) = nt2::expinv(a, nt2::ones(size(a), nt2::meta::as_<T>()), T(0.5), T(0.05));
  NT2_DISPLAY(r);
  NT2_DISPLAY(plo);
  NT2_DISPLAY(pup);
  r =  nt2::expinv(a, nt2::ones(size(a), nt2::meta::as_<T>()), T(0.5), T(0.05));
  NT2_DISPLAY(r);
//  nt2::tie(r, plo, pup) = nt2::expinv(a, T(1), T(0.5), T(0.05)); TO DO
  NT2_DISPLAY(r);
  NT2_DISPLAY(plo);
  NT2_DISPLAY(pup);

} // end of test for floating_

