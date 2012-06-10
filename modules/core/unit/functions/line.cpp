/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#define NT2_UNIT_MODULE "nt2::line function"

#include <nt2/table.hpp>
#include <nt2/include/functions/line.hpp>
#include <nt2/include/functions/size.hpp>
#include <nt2/include/functions/cat.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>

// NT2_TEST_CASE_TPL( line_scalar, (float)(double))//NT2_TYPES )
// {
//   T x = nt2::line(T(42), 1);
//   NT2_TEST_EQUAL( x, T(42) );

//   x = nt2::line(T(42),1);
//   NT2_TEST_EQUAL( x, T(42) );

//   x = nt2::line(T(42),1, 2);
//   NT2_TEST_EQUAL( x, T(42) );

// }

NT2_TEST_CASE_TPL( line, (float)(double))//NT2_TYPES )
{
  using nt2::_; 
  nt2::table<T> y( nt2::of_size(10,7, 2) );
  nt2::table<T> sy; 

  int k = 0; 
  for(int l=1;l<=size(y, 3);l++)
    for(int j=1;j<=size(y, 2);j++)
      for(int i=1;i<=size(y, 1);i++)
        y(i,j,l) = k++;
  
  //  y =  nt2::cat(3, y, y); 
  NT2_DISP(y);
  std::cout << "-----------------------" << std::endl; 
  NT2_DISP(nt2::line(y, 1));
  std::cout << "-----------------------" << std::endl; 
  NT2_DISP(nt2::line(y, 2));
  std::cout << "-----------------------" << std::endl; 
  NT2_DISP(nt2::line(y, 3));
  NT2_DISP(nt2::line(y, 3, 1)); 
  std::cout << "-----------------------" << std::endl; 
  NT2_DISP(nt2::line(y, 1, 2));
  std::cout << "-----------------------" << std::endl; 
  NT2_DISP(nt2::line(y, 2, 2));
  std::cout << "-----------------------" << std::endl; 
  NT2_DISP(nt2::line(y, 3, 2));
  std::cout << "-----------------------" << std::endl; 
  NT2_DISP(nt2::line(y, 1, 3));
  std::cout << "-----------------------" << std::endl; 
  NT2_DISP(nt2::line(y, 2, 3));
  std::cout << "-----------------------" << std::endl; 
  NT2_DISP(nt2::line(y, 3, 3));

  
}

