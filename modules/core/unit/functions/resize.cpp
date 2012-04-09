/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#define NT2_UNIT_MODULE "nt2::resize function"

#include <nt2/table.hpp>
#include <nt2/include/functions/resize.hpp>
#include <nt2/include/functions/size.hpp>
#include <nt2/include/functions/ones.hpp>
#include <nt2/include/functions/ndims.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/basic.hpp>
#include <nt2/sdk/unit/tests/exceptions.hpp>

NT2_TEST_CASE_TPL( resize_ofsize, (float) )
{
  nt2::table<T> r;
  nt2::table<T, nt2::_2D> y( nt2::of_size(4,4) );

  for(int j=1;j<=4;j++)
    for(int i=1;i<=4;i++)
      y(i,j) = T(i + 10*j);
  for(int i=1;i<=4;i++)
    {
    for(int j=1;j<=4;j++)
      std::cout << y(i,j) << "\t";
    std::cout << std::endl;
    }
  std::cout << std::endl;
  std::cout << std::endl;

  r = nt2::resize(y, nt2::of_size(2,2) );

  for(int i=1;i<=2;i++)
    {
    for(int j=1;j<=2;j++)
      std::cout << r(i,j) << "\t";
    std::cout << std::endl;
    }
  std::cout << std::endl;
  std::cout << std::endl;
 
  r = nt2::resize(y, nt2::of_size(5,5) );
    for(int i=1;i<=5;i++) 
    {
    for(int j=1;j<=5;j++)
      std::cout << r(i,j) << "\t";
    std::cout << std::endl;
    }
  std::cout << std::endl;
  std::cout << std::endl;

   r = nt2::resize(y, nt2::of_size(6,5) );

  for(int i=1;i<=6;i++) 
    {
    for(int j=1;j<=5;j++)
      std::cout << r(i,j) << "\t";
    std::cout << std::endl;
    }
  std::cout << std::endl;
  std::cout << std::endl;

  NT2_TEST( nt2::extent(resize(y,2,2)) == nt2::of_size(2,2)); 
  NT2_TEST( nt2::extent(resize(y,5,5)) == nt2::of_size(5,5)); 
  NT2_TEST( nt2::extent(resize(y,6,5)) == nt2::of_size(6,5)); 
  NT2_TEST( nt2::extent(resize(y,nt2::of_size(2,2))) == nt2::of_size(2,2)); 
  NT2_TEST( nt2::extent(resize(y,nt2::of_size(5,5))) == nt2::of_size(5,5)); 
  NT2_TEST( nt2::extent(resize(y,nt2::of_size(6,5))) == nt2::of_size(6,5)); 
 
}
