//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#define NT2_UNIT_MODULE "nt2 polynom toolbox - polyfit/scalar Mode"

//////////////////////////////////////////////////////////////////////////////
// unit test behavior of polynom components in scalar mode
//////////////////////////////////////////////////////////////////////////////
/// created  by jt the 06/03/2011
///
#include <nt2/include/functions/polyfit.hpp>
#include <nt2/include/functions/ulpdist.hpp>
#include <nt2/include/functions/polyval.hpp>
#include <nt2/include/functions/isulpequal.hpp>
#include <boost/type_traits/is_same.hpp>
#include <nt2/sdk/functor/meta/call.hpp>
#include <nt2/sdk/unit/tests.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/memory/buffer.hpp>
#include <nt2/include/constants/real.hpp>
#include <nt2/table.hpp>
#include <nt2/include/functions/tie.hpp>
#include <nt2/include/functions/complexify.hpp>

#include <boost/array.hpp>

NT2_TEST_CASE_TPL ( polyfit_real__1_0,  NT2_REAL_TYPES)
{

  using nt2::polyfit;
  using nt2::tag::polyfit_;
  typedef std::complex<T> cT;
  nt2::table<cT> x =  nt2::complexify(nt2::_(T(1), T(3)));
  nt2::table<cT> p =  nt2::complexify(nt2::_(T(1), T(3)));
  nt2::table<cT> y =  nt2::polyval(p, x);
  NT2_DISPLAY(y);
  NT2_DISPLAY(x);
  NT2_DISPLAY(p);
  NT2_DISPLAY(nt2::polyfit(x, y));
  nt2::table<cT> p1 =nt2::polyfit(x, y);
  NT2_DISPLAY(p1);
  NT2_DISPLAY(nt2::polyval(p1, x));
  NT2_DISPLAY(y);
  NT2_TEST(nt2::isulpequal(nt2::polyval(p1, x), y, 0.5));

  NT2_DISPLAY(polyfit(x, y, 2));
  nt2::table<cT> p2 =polyfit(x, y, 2);
  NT2_DISPLAY(p2);
  NT2_DISPLAY(nt2::polyval(p2, x));
  NT2_DISPLAY(y);
  NT2_TEST(nt2::isulpequal(nt2::polyval(p2, x), y, 0.5));

  nt2::table<cT> r;
  T df, normr;
  nt2::table<cT> mu;
  nt2::tie(p, r, df, normr, mu) = nt2::polyfit(x, y);
  NT2_DISPLAY(p);
  NT2_DISPLAY(r);
  NT2_DISPLAY(df);
  NT2_DISPLAY(normr);
  NT2_DISPLAY(mu);
  NT2_DISPLAY(polyval(p, (x-mu(1))/mu(2)));
  NT2_DISPLAY(y);
  NT2_TEST(nt2::isulpequal(nt2::polyval(p, (x-mu(1))/mu(2)), y, T(5.0)));



  //////////////////////////////////////////////////////
  // TODO This does not work s being a structure defined in polyfit.hpp
  //   nt2::polyfit_infos<T> s;
  //   nt2::tie(p, s) = polyfit(x, y);
  //   NT2_DISPLAY(p);
  //   NT2_DISPLAY(s.r);
  //   NT2_DISPLAY(s.df);
  //    NT2_DISPLAY(s.normr);
  //////////////////////////////////////////////////////

} // end of test for floating_


NT2_TEST_CASE_TPL ( polyfit_real__4_0,  NT2_REAL_TYPES)
{

  using nt2::polyfit;
  using nt2::tag::polyfit_;
  typedef std::complex<T> cT;
  cT a [] = {0.0, 1.0, 2.0, 3.0,  4.0,  5.0};
  cT b [] = {0.0, 0.8, 0.9, 0.1, -0.8, -1.0};
  nt2::table<cT> x(nt2::of_size(1,6));
  nt2::table<cT> y(nt2::of_size(1,6));

 for(int i=0; i < 6; ++i)
   {
     x(i+1) = cT(a[i]);
     y(i+1) = cT(b[i]);
   }
  NT2_DISPLAY(x);
  NT2_DISPLAY(y);
  nt2::table<cT> z = polyfit(x, y, 3);
   NT2_DISPLAY(z);
} // end of test for floating_

