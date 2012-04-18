/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#define NT2_UNIT_MODULE "nt2::asump function"

#include <nt2/table.hpp>
#include <nt2/include/functions/asump.hpp>
#include <nt2/include/functions/sum.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>

NT2_TEST_CASE_TPL( asump_scalar, (float)(double))//NT2_TYPES )
{
  T x = nt2::asump(T(42), T(2));
  NT2_TEST_EQUAL( x, sqr(T(42)) );

  x = nt2::asump(T(42),T(2), 1);
  NT2_TEST_EQUAL( x, T(0) );

  x = nt2::asump(T(42),T(2), 2);
  NT2_TEST_EQUAL( x, sqr(T(42)) );

}

NT2_TEST_CASE_TPL( asump, (float)(double))//NT2_TYPES )
{
  nt2::table<T> y( nt2::of_size(5,3) );
  nt2::table<T> sy( nt2::of_size(1,3) );
  nt2::table<T> sy2( nt2::of_size(1,3) );

  //  sy = nt2::sum(y, 0);
  disp("sy", sy);
 
  for(int j=1;j<=3;j++)
    for(int i=1;i<=5;i++)
      y(i,j) = i + 10*j;
  disp("y", y); 
  sy = nt2::sum(y);
  std::cout << size(sy) << std::endl; 
  disp("sy", sy);
  sy2 = nt2::asump(y, T(1));
  std::cout << size(sy2) << std::endl; 
  disp("sy2", sy2);
  
  disp("y", y); 
  sy = nt2::sum(y, 1);
  std::cout << size(sy) << std::endl; 
  disp("sy", sy);
  sy2 = nt2::asump(y, T(1), 1);
  std::cout << size(sy2) << std::endl; 
  disp("sy2", sy2);

  disp("y", y); 
  sy = nt2::sum(y, 2);
  std::cout << size(sy) << std::endl; 
  disp("sy", sy);
  sy2 = nt2::asump(y,T(1), 2);
  std::cout << size(sy2) << std::endl; 
  disp("sy2", sy2);
 
  disp("y", y); 
  sy = nt2::sum(y, 3);
  std::cout << size(sy) << std::endl; 
  disp("sy", sy);
  sy2 = nt2::asump(y, T(1), 3);
  std::cout << size(sy2) << std::endl; 
   disp("sy2", sy2);

}

