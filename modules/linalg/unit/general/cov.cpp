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
#include <nt2/include/functions/sum.hpp>
#include <nt2/include/functions/center.hpp>
#include <nt2/include/functions/sqr_abs.hpp>
#include <nt2/include/functions/size.hpp>
#include <nt2/include/functions/rif.hpp>
#include <nt2/include/functions/reshape.hpp>
#include <nt2/include/functions/var.hpp>
#include <nt2/include/functions/zeros.hpp>
#include <nt2/include/functions/isequal.hpp>
#include <nt2/include/functions/sqr.hpp>
#include <nt2/include/functions/trans.hpp>
#include <nt2/include/functions/mtimes.hpp>

#include <nt2/sdk/unit/module.hpp> 
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/basic.hpp>

NT2_TEST_CASE_TPL( cov_scalar, (float)(double))//NT2_TYPES )
{
  T x = nt2::cov(T(42));
  NT2_TEST_EQUAL( x, T(0) );

  x = nt2::cov(T(42),1);
  NT2_TEST_EQUAL( x, T(0) );

  nt2::table<T> y = nt2::cov(T(42),T(1));
  NT2_TEST( isequal(y, nt2::zeros(2, 2, nt2::meta::as_<T>())));


}

NT2_TEST_CASE_TPL( cov, (float)(double))//NT2_TYPES )
{
  nt2::table<T> y;
  nt2::table<T> c, v; 
  
//   for(int i=1;i<=5;i++)
//     y(i) = i;
//  display("y", y);
//   c = nt2::cov(y, y);
//   display("c", c);

  //  v = nt2::var(y);
  //  NT2_TEST(nt2::isequal(c, v)); 
 
  y = nt2::reshape(nt2::sqr(nt2::_(T(1), T(15))), 3, 5);
//   display("y", y); 
//   nt2::table<T> yc =  nt2::center(yc, 1);
//   display("nt2::center(yc, 1)", yc); 
//   nt2::table<T> tyc =  nt2::trans(yc);
//   display("trans(yc) ", tyc); 
//   nt2::table<T> z = nt2::mtimes(tyc, yc); 
//   display("nt2::mtimes(tyc, yc)", z); 
  
// //   y = nt2::reshape(nt2::_(T(1), T(16)), 4, 4); 
    display("y", y);
    c = nt2::cov(y, 0);
    display("cov", c);
    c = nt2::cov(y, 1);
    display("cov", c);

}

