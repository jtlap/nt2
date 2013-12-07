//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/include/functions/polyfit.hpp>
#include <nt2/include/functions/polyval.hpp>
#include <nt2/include/functions/isulpequal.hpp>
#include <boost/type_traits/is_same.hpp>
#include <nt2/sdk/functor/meta/call.hpp>
#include <nt2/sdk/unit/tests.hpp>
#include <nt2/sdk/unit/module.hpp>

#include <nt2/include/constants/real.hpp>
#include <nt2/table.hpp>
#include <nt2/include/functions/tie.hpp>
#include <nt2/include/functions/complexify.hpp>

#include <boost/array.hpp>

NT2_TEST_CASE_TPL ( polyfit,  NT2_REAL_TYPES)
{

  using nt2::polyfit;
  using nt2::tag::polyfit_;
  typedef std::complex<T> cT;
  nt2::table<cT> x =  nt2::complexify(nt2::_(T(1), T(3)));
  nt2::table<cT> p =  nt2::complexify(nt2::_(T(1), T(3)));
  nt2::table<cT> y =  nt2::polyval(p, x);
  nt2::table<cT> p1 =nt2::polyfit(x, y);
  NT2_TEST_ULP_EQUAL(nt2::polyval(p1, x), y, 0.5);

  NT2_DISPLAY(polyfit(x, y, 2));
  nt2::table<cT> p2 =polyfit(x, y, 2);
  NT2_TEST_ULP_EQUAL(nt2::polyval(p2, x), y, 0.5);

  nt2::table<cT> r;
  size_t df;
  T normr;
  nt2::table<cT> mu;
  nt2::tie(p, r, df, normr, mu) = nt2::polyfit(x, y);
  NT2_TEST_ULP_EQUAL(nt2::polyval(p, (x-mu(1))/mu(2)), y, T(5.0));



  //////////////////////////////////////////////////////
  // TODO This does not work s being a structure defined in polyfit.hpp
  //   nt2::polyfit_infos<T> s;
  //   nt2::tie(p, s) = polyfit(x, y);
  //   NT2_DISPLAY(p);
  //   NT2_DISPLAY(s.r);
  //   NT2_DISPLAY(s.df);
  //    NT2_DISPLAY(s.normr);
  //////////////////////////////////////////////////////

}


NT2_TEST_CASE_TPL ( polyfit1,  NT2_REAL_TYPES)
{

  using nt2::polyfit;
  using nt2::tag::polyfit_;
  typedef std::complex<T> cT;
  cT a [] = {0.0, 1.0, 2.0, 3.0,  4.0,  5.0};
  cT b [] = {0.0, 0.8, 0.9, 0.1, -0.8, -1.0};
  cT c [] = {0.087037037037037245923, -0.81349206349206493183, 1.6931216931216956922, -0.039682539682541172199 };
  nt2::table<cT> x(nt2::of_size(1,6), a+0,  a+6);
  nt2::table<cT> y(nt2::of_size(1,6), b+0,  b+6);
  nt2::table<cT> zz(nt2::of_size(1,4), c+0, c+4);

  nt2::table<cT> z = polyfit(x, y, 3);
  NT2_TEST_ULP_EQUAL(z, zz, 500);
}

