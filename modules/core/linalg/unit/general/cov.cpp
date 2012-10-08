/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#define NT2_UNIT_MODULE "nt2::cov function"
 
#include <nt2/table.hpp>
#include <nt2/include/functions/cov.hpp>
#include <nt2/include/functions/rif.hpp>
#include <nt2/include/functions/reshape.hpp>
#include <nt2/include/functions/var.hpp>
#include <nt2/include/functions/zeros.hpp>
#include <nt2/include/functions/isequal.hpp>
#include <nt2/include/functions/isulpequal.hpp>  
#include <nt2/include/functions/repnum.hpp>


#include <nt2/sdk/unit/module.hpp> 
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/basic.hpp>

NT2_TEST_CASE_TPL( cov_scalar, NT2_REAL_TYPES )
{
  T x = nt2::cov(T(42));
  NT2_TEST_EQUAL( x, T(0) );

  x = nt2::cov(T(42),1);
  NT2_TEST_EQUAL( x, T(0) );

  nt2::table<T> y = nt2::cov(T(42),T(1));
  NT2_TEST( isequal(y, nt2::zeros(2, 2, nt2::meta::as_<T>())));
}

NT2_TEST_CASE_TPL( cov, NT2_REAL_TYPES )
{
  nt2::table<T> y;
  nt2::table<T> c, v; 
  y = nt2::reshape(nt2::sqr(nt2::_(T(1), T(15))), 3, 5);
  display("y", y);
  c = nt2::cov(y, 0);
  display("cov", c);
  c = nt2::cov(y, 1);
  display("cov", c);
  y = nt2::reshape(nt2::_(T(1), T(15)), 3, 5);
  display("y", y);
  c = nt2::cov(y, 0);
  display("cov", c);
  NT2_TEST(nt2::isulpequal(c, nt2::repnum(T(1), 5, 5))); 
  c = nt2::cov(y, 1);
  display("cov", c);
  NT2_TEST(nt2::isulpequal(c, nt2::repnum(T(2)/T(3), 5, 5))); 

  
}

NT2_TEST_CASE_TPL( cov_2, NT2_REAL_TYPES )
{
  nt2::table<T> y;
  nt2::table<T> c, v; 
  y = nt2::reshape(nt2::_(T(1), T(15)), 3, 5);
  display("y", y);
  c = nt2::cov(y, y);
  display("cov", c);
  NT2_TEST(nt2::isulpequal(c, nt2::repnum(T(20), 2, 2))); 
  c = nt2::cov(y, y, 1);
  display("cov", c);
  NT2_TEST(nt2::isulpequal(c, nt2::repnum(T(56)/T(3), 2, 2))); 

  
}
NT2_TEST_CASE_TPL( cov_3, NT2_REAL_TYPES )
{
  nt2::table<T> y;
  nt2::table<T> c, v; 
  y = nt2::_(T(1), T(15));
  display("y", y);
  c = nt2::cov(y);
  display("cov", c);
  NT2_TEST(nt2::isulpequal(c, nt2::repnum(T(20), 1))); 
  c = nt2::cov(y, 1);
  display("cov", c);
  NT2_TEST(nt2::isulpequal(c, nt2::repnum(T(56)/T(3), 1))); 
  c = nt2::cov(y(nt2::_));
  display("cov", c);
  NT2_TEST(nt2::isulpequal(c, nt2::repnum(T(20), 1))); 
  c = nt2::cov(y(nt2::_), 1);
  display("cov", c);
  NT2_TEST(nt2::isulpequal(c, nt2::repnum(T(56)/T(3), 1))); 

  
}
