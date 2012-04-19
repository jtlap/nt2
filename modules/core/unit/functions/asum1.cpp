/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#define NT2_UNIT_MODULE "nt2::sum1 function"

#include <nt2/table.hpp>
#include <nt2/include/functions/asum1.hpp>
#include <nt2/include/functions/sum.hpp>
#include <nt2/include/functions/size.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>

NT2_TEST_CASE_TPL( asum1_scalar, (float)(double))//NT2_TYPES )
{
  T x = nt2::asum1(T(42));
  NT2_TEST_EQUAL( x, T(42) );

  x = nt2::asum1(T(42),1);
  NT2_TEST_EQUAL( x, T(42) );

  x = nt2::asum1(T(42),0);
  NT2_TEST_EQUAL( x, T(42) );

}

NT2_TEST_CASE_TPL( asum1, (float)(double))//NT2_TYPES )
{
  nt2::table<T> y( nt2::of_size(5,3) );
  nt2::table<T> sy( nt2::of_size(1,3) );
  nt2::table<T> sy2( nt2::of_size(1,3) );


  for(int j=1;j<=3;j++)
    for(int i=1;i<=5;i++)
      y(i,j) = i + 10*j;
  disp("y", y); 
  sy = nt2::sum(y);
  std::cout << size(sy) << std::endl; 
  disp("sy", sy);
  sy2 = nt2::asum1(y);
  std::cout << size(sy2) << std::endl; 
  disp("sy2", sy2);
  
  disp("y", y); 
  sy = nt2::sum(y, 1);
  std::cout << size(sy) << std::endl; 
  disp("sy", sy);
  sy2 = nt2::asum1(y);
  std::cout << size(sy2) << std::endl; 
  disp("sy2", sy2);

  disp("y", y); 
  sy = nt2::sum(y, 2);
  std::cout << size(sy) << std::endl; 
  disp("sy", sy);
  sy2 = nt2::asum1(y, 2);
  std::cout << size(sy2) << std::endl; 
  disp("sy2", sy2);
 
  disp("y", y); 
  sy = nt2::sum(y, 3);
  std::cout << size(sy) << std::endl; 
  disp("sy", sy);
  sy2 = nt2::asum1(y, 3);
  std::cout << size(sy2) << std::endl; 
   disp("sy2", sy2);

}

