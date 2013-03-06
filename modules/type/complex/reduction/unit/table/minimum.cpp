//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#define NT2_UNIT_MODULE "nt2::minimum function"

#include <nt2/table.hpp>
#include <nt2/include/functions/min.hpp>
#include <nt2/include/functions/of_size.hpp>
#include <nt2/include/functions/minimum.hpp>
#include <nt2/include/functions/isequal.hpp>
#include <nt2/sdk/unit/tests/basic.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/basic.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>
#include <nt2/sdk/unit/tests/exceptions.hpp>

NT2_TEST_CASE_TPL( minimum_scalar, NT2_REAL_TYPES )
{
  typedef std::complex<T>  cT;
  cT x = nt2::minimum(cT(42));
  NT2_TEST_EQUAL( x, (cT(42)) );

  x = nt2::minimum(cT(42),1);
  NT2_TEST_EQUAL( x, cT(42) );

  x = nt2::minimum(cT(42),2);
  NT2_TEST_EQUAL( x, (cT(42)) );
}


NT2_TEST_CASE_TPL( minimum_2, (float)(double) )
{
  typedef std::complex<T>  cT;
  using nt2::_;
  nt2::table<cT> y( nt2::of_size(5,3) );
  nt2::table<cT> sy( nt2::of_size(1,3) );
  for(int j=1;j<=3;j++)
    for(int i=1;i<=5;i++)
      y(i,j) =  -cT(i + 10*j, i + 10*j);
  display("y", y);
  sy = nt2::minimum(y);
  NT2_DISPLAY(sy);
  NT2_DISPLAY(y(1, nt2::_));
  NT2_TEST(nt2::isequal(y(1, nt2::_),  nt2::minimum(y)));
  sy = nt2::minimum(y, 1);
  NT2_DISPLAY(sy);
  NT2_DISPLAY(y(1, nt2::_));
  NT2_TEST(nt2::isequal(y(1, nt2::_),  nt2::minimum(y, 1)));
  sy = nt2::minimum(y, 2);
  NT2_DISPLAY(sy);
  NT2_DISPLAY(y(nt2::_, 1));
  NT2_TEST(nt2::isequal(y(nt2::_, 1),  nt2::minimum(y, 2)));
  sy = nt2::minimum(y, 1);
  NT2_DISPLAY(y);
  NT2_TEST(nt2::isequal(y,  nt2::minimum(y, 3)));

}

