//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2014   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/table.hpp>
#include <nt2/include/functions/freqspace.hpp>
#include <nt2/include/functions/meshgrid.hpp>
#include <nt2/include/functions/of_size.hpp>
#include <nt2/include/functions/colon.hpp>
#include <nt2/include/functions/tie.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/ulp.hpp>

NT2_TEST_CASE( freqspace_untyped_expr )
{
  using nt2::freqspace;
  using nt2::meshgrid;

  nt2::table<int> a(nt2::of_size(1, 2));
  a(1) = 10; a(2) = 5;

  {
    nt2::table<double> f;
    nt2::tie(f) = freqspace(a);
    NT2_TEST_ULP_EQUAL(f, nt2::_(-0.8, 0.4, 0.8), 2);
  }

  {
    nt2::table<double> f;
    f = freqspace(a);
    NT2_TEST_ULP_EQUAL(f, nt2::_(-0.8, 0.4, 0.8), 2);
  }

  {
    // Even & Odd size
    nt2::table<double> f,g;
    nt2::tie(f,g) = freqspace(a);

    NT2_TEST_ULP_EQUAL(f, nt2::_(-0.8, 0.4, 0.8), 2);
    NT2_TEST_ULP_EQUAL(g, nt2::_(-1. , 0.2, 0.8), 2);
  }

  {
    // meshgrid_ option
    nt2::table<double> f,g;
    nt2::tie(f,g) = freqspace(a, nt2::meshgrid_);

    nt2::table<double> bf,bg,mf,mg;
    nt2::tie(bf,bg) = freqspace(a);
    nt2::tie(mf,mg) = meshgrid(bf,bg);

    NT2_TEST_ULP_EQUAL(f,mf,2);
    NT2_TEST_ULP_EQUAL(g,mg,2);
  }
}

NT2_TEST_CASE_TPL( freqspace_expr, (double)(float) )
{
  using nt2::freqspace;
  nt2::table<int> a(nt2::of_size(1, 2));
  a(1) = 10; a(2) = 5;

  {
    nt2::table<T> f;
    nt2::tie(f) = freqspace(a, nt2::meta::as_<T>());
    NT2_TEST_ULP_EQUAL(f, nt2::_(T(-0.8), T(0.4), T(0.8)), 2);
  }

  {
    nt2::table<T> f;
    f = freqspace(a, nt2::meta::as_<T>());
    NT2_TEST_ULP_EQUAL(f, nt2::_(T(-0.8), T(0.4), T(0.8)), 2);
  }

  {
    // Even & Odd size
    nt2::table<T> f,g;
    nt2::tie(f,g) = freqspace(a, nt2::meta::as_<T>());

    NT2_TEST_ULP_EQUAL(f, nt2::_(T(-0.8), T(0.4), T(0.8)), 2);
    NT2_TEST_ULP_EQUAL(g, nt2::_(T(-1), T(0.2), T(0.8)), 2);
  }

  {
    // meshgrid_ option
    nt2::table<T> f,g;
    nt2::tie(f,g) = freqspace(a, nt2::meshgrid_, nt2::meta::as_<T>());

    nt2::table<T> bf,bg,mf,mg;
    nt2::tie(bf,bg) = freqspace(a, nt2::meta::as_<T>());
    nt2::tie(mf,mg) = meshgrid(bf,bg);

    NT2_TEST_ULP_EQUAL(f,mf,2);
    NT2_TEST_ULP_EQUAL(g,mg,2);
  }
}

NT2_TEST_CASE( freqspace_untyped_scalar )
{
  using nt2::freqspace;

  {
    nt2::table<double> f;
    nt2::tie(f) = freqspace(10);
    NT2_TEST_ULP_EQUAL(f, nt2::_(0., 0.2, 1.), 2);
  }

  {
    nt2::table<double> f;
    f = freqspace(10);
    NT2_TEST_ULP_EQUAL(f, nt2::_(0., 0.2, 1.), 2);
  }

  {
    // Even size
    nt2::table<double> f,g;
    nt2::tie(f,g) = freqspace(10);
    NT2_TEST_ULP_EQUAL(f, nt2::_(-1., 0.2, 0.8), 2);
    NT2_TEST_ULP_EQUAL(g, nt2::_(-1., 0.2, 0.8), 2);
  }

  {
    // Odd size
    nt2::table<double> f,g;
    nt2::tie(f,g) = freqspace(5);
    NT2_TEST_ULP_EQUAL(f, nt2::_(-0.8, 0.4, 0.8), 2);
    NT2_TEST_ULP_EQUAL(g, nt2::_(-0.8, 0.4, 0.8), 2);
  }

  {
    // whole_ option
    nt2::table<double> f;
    nt2::tie(f) = freqspace(10, nt2::whole_);
    NT2_TEST_ULP_EQUAL(f, nt2::_(0., 0.2, 1.8), 2);
  }

  {
    // whole_ option
    nt2::table<double> f;
    f = freqspace(10, nt2::whole_);
    NT2_TEST_ULP_EQUAL(f, nt2::_(0., 0.2, 1.8), 2);
  }
}

NT2_TEST_CASE_TPL( freqspace_scalar, (double)(float) )
{
  using nt2::freqspace;

  {
    nt2::table<T> f;
    nt2::tie(f) = freqspace(10, nt2::meta::as_<T>());
    NT2_TEST_ULP_EQUAL(f, nt2::_(T(0), T(0.2), T(1)), 2);
  }

  {
    nt2::table<T> f;
    f = freqspace(10, nt2::meta::as_<T>());
    NT2_TEST_ULP_EQUAL(f, nt2::_(T(0), T(0.2), T(1)), 2);
  }

  {
    // Even size
    nt2::table<T> f,g;
    nt2::tie(f,g) = freqspace(10, nt2::meta::as_<T>());

    NT2_TEST_ULP_EQUAL(f, nt2::_(T(-1), T(0.2), T(0.8)), 2);
    NT2_TEST_ULP_EQUAL(g, nt2::_(T(-1), T(0.2), T(0.8)), 2);
  }

  {
    // Odd size
    nt2::table<T> f,g;
    nt2::tie(f,g) = freqspace(5, nt2::meta::as_<T>());
    NT2_TEST_ULP_EQUAL(f, nt2::_(T(-0.8), T(0.4), T(0.8)), 2);
    NT2_TEST_ULP_EQUAL(g, nt2::_(T(-0.8), T(0.4), T(0.8)), 2);
  }

  {
    // whole_ option
    nt2::table<T> f;
    nt2::tie(f) = freqspace(10, nt2::whole_, nt2::meta::as_<T>());
    NT2_TEST_ULP_EQUAL(f, nt2::_(T(0), T(0.2), T(1.8)), 2);
  }

  {
    // whole_ option
    nt2::table<T> f;
    f = freqspace(10, nt2::whole_, nt2::meta::as_<T>());
    NT2_TEST_ULP_EQUAL(f, nt2::_(T(0), T(0.2), T(1.8)), 2);
  }
}
