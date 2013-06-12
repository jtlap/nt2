//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#define NT2_UNIT_MODULE "nt2::cov function"

#include <nt2/table.hpp>
#include <nt2/include/functions/cov.hpp>
#include <nt2/include/functions/reshape.hpp>
#include <nt2/include/functions/zeros.hpp>
#include <nt2/include/functions/repnum.hpp>
#include <nt2/include/functions/cast.hpp>
#include <nt2/include/constants/i.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/ulp.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>

#include <nt2/sdk/complex/meta/as_complex.hpp>

NT2_TEST_CASE_TPL( cov_scalar, NT2_REAL_TYPES )
{
 typedef typename nt2::meta::as_complex<T>::type  cT;
  cT x = nt2::cov(cT(42));
  NT2_TEST_EQUAL( x, cT(0) );

  x = nt2::cov(cT(42),1);
  NT2_TEST_EQUAL( x, cT(0) );

  nt2::table<cT> y = nt2::cov(cT(42),cT(1));
  NT2_TEST_EQUAL( y, nt2::zeros(2, 2, nt2::meta::as_<cT>()) );
}

NT2_TEST_CASE_TPL( cov, NT2_REAL_TYPES )
{
  typedef typename nt2::meta::as_complex<T>::type  cT;
  nt2::table<cT> y(nt2::of_size(3, 5));
  nt2::table<T> ry;
  nt2::table<cT> c, v;
  ry = nt2::cast<T>(nt2::reshape(nt2::_(T(1), T(15)), 3, 5));
  y =  ry;
  c = nt2::cov(y, 0);
  NT2_TEST_ULP_EQUAL(c, nt2::repnum(cT(1), 5, 5), 1.5);
  c = nt2::cov(y, 1);
  NT2_TEST_ULP_EQUAL(c, nt2::repnum(cT(2)/cT(3), 5, 5), 2);
 }

NT2_TEST_CASE_TPL( cov_2, NT2_REAL_TYPES )
{
 typedef typename nt2::meta::as_complex<T>::type  cT;
  nt2::table<cT> y;
  nt2::table<cT> c, v;
  nt2::table<T> ry;
  ry = nt2::reshape(nt2::_(T(1), T(15)), 3, 5);
  y = ry;
  c = nt2::cov(y, y);
  NT2_TEST_ULP_EQUAL(c, nt2::repnum(cT(20), 2, 2), 1.5);
  c = nt2::cov(y, y, 1);
  NT2_TEST_ULP_EQUAL(c, nt2::repnum(cT(56)/cT(3), 2, 2), 1.5);


}
NT2_TEST_CASE_TPL( cov_3, NT2_REAL_TYPES )
{
 typedef typename nt2::meta::as_complex<T>::type  cT;
  nt2::table<cT> y;
  nt2::table<cT> c, v;
  nt2::table<T> ry;
  y = nt2::_(T(1), T(15));
  c = nt2::cov(y);
  NT2_TEST_ULP_EQUAL(c, nt2::repnum(cT(20), 1), 1.5);
  c = nt2::cov(y, 1);
  NT2_TEST_ULP_EQUAL(c, nt2::repnum(cT(56)/cT(3), 1), 1.5);
  c = nt2::cov(y(nt2::_));
  NT2_TEST_ULP_EQUAL(c, nt2::repnum(cT(20), 1), 1.5);
  c = nt2::cov(y(nt2::_), 1);
  NT2_TEST_ULP_EQUAL(c, nt2::repnum(cT(56)/cT(3), 1), 1.5);


}
NT2_TEST_CASE_TPL( cov_4, NT2_REAL_TYPES )
{
  typedef typename nt2::meta::as_complex<T>::type  cT;
  nt2::table<cT> y(nt2::of_size(3, 5));
  nt2::table<T> ry;
  nt2::table<cT> c, v;
  ry = nt2::cast<T>(nt2::reshape(nt2::_(T(1), T(15)), 3, 5));
  y =  ry*nt2::I<cT>()+ry;
  c = nt2::cov(y, 0);
  NT2_TEST_ULP_EQUAL(c, nt2::repnum(cT(2), 5, 5), 1.5);
  c = nt2::cov(y, 1);
  NT2_TEST_ULP_EQUAL(c, nt2::repnum(cT(4)/cT(3), 5, 5), 2);
 }
