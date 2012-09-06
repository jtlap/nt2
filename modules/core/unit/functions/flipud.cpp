/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#define NT2_UNIT_MODULE "nt2::flipud function"

#include <nt2/table.hpp>
#include <nt2/include/functions/flipud.hpp>
#include <nt2/include/functions/ones.hpp>
#include <nt2/include/functions/isequal.hpp>


#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/basic.hpp>

NT2_TEST_CASE_TPL( flipud_scalar, NT2_TYPES )
{
  T x = nt2::flipud(T(42));
  NT2_TEST_EQUAL( x, T(42) );
}

NT2_TEST_CASE_TPL( flipud, NT2_TYPES )
{
  nt2::table<T> x,x2,y( nt2::of_size(5,3) );

  for(int j=1;j<=3;j++)
    for(int i=1;i<=5;i++)
      y(i,j) = T(i + 10*j);
  display("y", y);

  x = nt2::flipud(y);
  x2 = nt2::flipud(y)(nt2::_);
  display("x", x);

 std::cout << "y" << std::endl;
  for(int i=1;i<=5;i++)
    {
      for(int j=1;j<=3;j++)
        std::cout << T(y(i,j)) << "\t";
      std::cout << std::endl;
    }
  std::cout << std::endl;

  for(int j=1;j<=3;j++)
  {
    for(int i=1;i<=5;i++)
    {
      NT2_TEST_EQUAL( T(x(i,j)),T(y(6-i,j)) );
      NT2_TEST_EQUAL( T(x2(i+(j-1)*5)),T(y(6-i,j)) );
    }
  }
}
NT2_TEST_CASE_TPL( flipud_2, NT2_TYPES )
{
  nt2::table<T> z = nt2::flipud(nt2::flipud(nt2::ones(3, 3, nt2::meta::as_<T>())));
  NT2_TEST( isequal(z, nt2::ones(3, 3, nt2::meta::as_<T>())));
}

NT2_TEST_CASE_TPL( flipud_3, NT2_TYPES )
{
  nt2::table<T> x,y( nt2::of_size(5,3) );

  for(int j=1;j<=3;j++)
    for(int i=1;i<=5;i++)
      y(i,j) = T(i + 10*j);
  display("y", y);

  x = nt2::flipud(y);
  display("x", x);

  NT2_TEST(nt2::isequal(x, nt2::flipud(y)));
  NT2_TEST(nt2::isequal(nt2::flipud(x), y));          
           
}
