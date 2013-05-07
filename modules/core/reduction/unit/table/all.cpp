//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#define NT2_UNIT_MODULE "nt2::all function"

#include <nt2/table.hpp>
// #include <nt2/include/functions/toint.hpp>
#include <nt2/include/functions/of_size.hpp>
#include <nt2/include/functions/all.hpp>
#include <nt2/include/functions/is_true.hpp>
#include <nt2/include/functions/is_nez.hpp>
#include <nt2/include/constants/true.hpp>
#include <nt2/include/functions/logical_and.hpp>
#include <nt2/include/functions/sb2b.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/basic.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>
#include <nt2/sdk/unit/tests/exceptions.hpp>

NT2_TEST_CASE_TPL( all_scalar, NT2_TYPES )
{
  nt2::logical<T> x = nt2::all(nt2::True< nt2::logical<T> >());
  NT2_TEST_EQUAL( x, (nt2::True< nt2::logical<T> >()) );

  x = nt2::all(nt2::True< nt2::logical<T> >(),1);
  NT2_TEST_EQUAL( x, nt2::True< nt2::logical<T> >() );

  x = nt2::all(nt2::True< nt2::logical<T> >(),2);
  NT2_TEST_EQUAL( x, (nt2::True< nt2::logical<T> >()) );

}

NT2_TEST_CASE_TPL( all_expr, NT2_TYPES )
{
  using nt2::_;
  nt2::table<T> y( nt2::of_size(5,3) );
  nt2::table<nt2::logical<T> > sy( nt2::of_size(1,3) );
  for(int j=1;j<=3;j++)
    for(int i=1;i<=5;i++)
      y(i,j) = i + 10*j;
  y(2, 2) = 0;

  display("y", y);

  sy = nt2::all(y);
  display("sy", sy);
  for(int j=1;j<=3;j++)
    {
      nt2::logical<T> z = nt2::True< nt2::logical<T> >();
      for(int i=1;i<=5;i++) z= nt2::logical_and(z, y(i, j));
      NT2_TEST_EQUAL(z, sy(j));
    }
  sy = nt2::all(y, 1);
  display("sy", sy);
  for(int j=1;j<=3;j++)
    {
      nt2::logical<T> z = nt2::True< nt2::logical<T> >();
      for(int i=1;i<=5;i++) z= nt2::logical_and(z, y(i, j));
      NT2_TEST_EQUAL(z, sy(j));
    }

  sy = nt2::all(y, 2);
  display("sy", sy);
  for(int j=1;j<=5;j++)
    {
      nt2::logical<T> z = nt2::True< nt2::logical<T> >();
      for(int i=1;i<=3;i++) z= nt2::logical_and(z, y(j, i));
      NT2_TEST_EQUAL(z, sy(j));
    }

  sy = nt2::all(y, 3);
  display("sy", sy);
  for(int j=1;j<=3;j++)
    {
      nt2::logical<T> z;
      for(int i=1;i<=5;i++)
        {
          z= nt2::is_nez(y(i, j));
          NT2_TEST_EQUAL(z, sy(i, j));
        }
    }
//   sy = nt2::all(y(_));
//   display("sy", sy);
//   NT2_TEST_EQUAL(nt2::False< nt2::logical<T> >(), sy(1));

}

