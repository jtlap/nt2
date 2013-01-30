//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#define NT2_UNIT_MODULE "nt2 statistics toolbox - unifrnd/scalar Mode"

//////////////////////////////////////////////////////////////////////////////
// unit test behavior of statistics  components in scalar mode
//////////////////////////////////////////////////////////////////////////////
/// created  by jt the 22/02/2011
///
#include <nt2/include/functions/unifrnd.hpp>
#include <nt2/include/functions/is_less_equal.hpp>
#include <nt2/include/functions/is_greater_equal.hpp>
#include <nt2/include/functions/globalall.hpp>
#include <nt2/include/functions/ones.hpp>
#include <nt2/sdk/unit/tests.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/memory/buffer.hpp>
#include <nt2/toolbox/constant/constant.hpp>
#include <nt2/options.hpp>
#include <nt2/table.hpp>

NT2_TEST_CASE_TPL ( unifrnd_real__2_0,  NT2_REAL_TYPES)
{

  using nt2::unifrnd;
  using nt2::tag::unifrnd_;
  // specific values tests
  nt2::table<T> b = unifrnd(T(0.0), T(1.0));
  NT2_DISPLAY(b);

  nt2::table<T> c =  unifrnd(T(0.0), T(1.0), 3);
  NT2_DISPLAY(c);
  nt2::table<T> d =  unifrnd(T(0.0), T(1.0), 3, 5);
  NT2_DISPLAY(d);
  nt2::table<T> e =  unifrnd(T(0.0), T(1.0), nt2::of_size(3, 2));
  NT2_DISPLAY(e);
  nt2::table<T> f =  unifrnd(T(0.0), T(1.0), size(e));
  NT2_DISPLAY(f);
  NT2_TEST_COMPLETE("unifrnd_real__2_0");
 } // end of test for floating_
NT2_TEST_CASE_TPL ( unifrnd_real__2_1,  NT2_REAL_TYPES)
{

  using nt2::unifrnd;
  using nt2::tag::unifrnd_;
  // specific values tests
  nt2::table<T> a =  nt2::ones(3, 4, nt2::meta::as_<T>());
  nt2::table<T> b = unifrnd(T(-1.0), T(2.0));
  NT2_TEST(nt2::globalall(ge(b, T(-1))));
  NT2_TEST(nt2::globalall(le(b, T(2))));
  NT2_DISPLAY(b);
  nt2::table<T> c =  unifrnd(T(-1.0), T(2.0), 3);
  NT2_TEST(nt2::globalall(ge(c, T(-1))));
  NT2_TEST(nt2::globalall(le(c, T(2))));
  NT2_DISPLAY(c);
  nt2::table<T> d =  unifrnd(T(-1.0), T(2.0), 3, 5);
  NT2_TEST(nt2::globalall(ge(d, T(-1))));
  NT2_TEST(nt2::globalall(le(d, T(2))));
  NT2_DISPLAY(d);
  nt2::table<T> e =  unifrnd(T(-1.0), T(2.0), nt2::of_size(3, 2));
  NT2_TEST(nt2::globalall(ge(e, T(-1))));
  NT2_TEST(nt2::globalall(le(e, T(2))));
  NT2_DISPLAY(e);
  nt2::table<T> f =  unifrnd(T(-1.0), T(2.0), size(e));
  NT2_TEST(nt2::globalall(ge(f, T(-1))));
  NT2_TEST(nt2::globalall(le(f, T(2))));
  NT2_DISPLAY(f);

 } // end of test for floating_


