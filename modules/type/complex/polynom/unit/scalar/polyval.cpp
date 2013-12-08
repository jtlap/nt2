//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/include/functions/polyval.hpp>
#include <nt2/include/functions/polyfit.hpp>
#include <nt2/include/functions/complexify.hpp>
#include <boost/type_traits/is_same.hpp>
#include <nt2/sdk/functor/meta/call.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/ulp.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/table.hpp>
#include <boost/array.hpp>


NT2_TEST_CASE_TPL ( polyva,  NT2_REAL_TYPES)
{
  typedef std::complex<T> cT;
  using nt2::polyval;
  using nt2::tag::polyval_;
  nt2::table<cT> x =  nt2::complexify(nt2::_(T(1), T(4)));
  nt2::table<cT> p =  nt2::complexify(nt2::_(T(1), T(4)));
  NT2_TEST_EQUAL(polyval(p, cT(1)), cT(10));
  NT2_TEST_EQUAL(polyval(p, cT(2)), cT(26));
  T cv[] = { 10, 26, 58, 112 };
  nt2::table<T> v(nt2::of_size(1, 4), &cv[0], &cv[4]);
  nt2::table<cT> vv =  nt2::complexify(v);
  NT2_TEST_ULP_EQUAL(vv, polyval(p,x), 0.5);
}


NT2_TEST_CASE_TPL ( polyval2,  NT2_REAL_TYPES)
{
  typedef std::complex<T> cT;
  using nt2::polyfit;
  using nt2::tag::polyfit_;
  nt2::table<cT> x =  nt2::complexify(nt2::reshape(nt2::_(T(1), T(4)), nt2::of_size(2, 2)));
  nt2::table<cT> p =  nt2::complexify(nt2::_(T(1), T(3)));
  nt2::table<cT> y =  nt2::polyval(p, x);
  y(nt2::end_) = cT(26);
  nt2::table<cT> r;
  size_t df;
  T normr;
  nt2::table<cT> mu;
  nt2::tie(p, r, df, normr, mu) = polyfit(x, y, 2);
  std::cout << 2 << std::endl;
  nt2::table<cT> delta;
  nt2::table<cT> xx =  nt2::complexify(nt2::reshape(nt2::_(T(1), T(0.5), T(4.5)), 2, 4));
  nt2::table<cT> yy(nt2::of_size(2, 2)); yy(1) = cT(6); yy(2) = cT(11);yy(3) = cT(18);yy(4) = cT(26);
  NT2_TEST_ULP_EQUAL(y, yy, 1.0);
  tie(y, delta) = polyval(p, xx, r, df, normr);
}

