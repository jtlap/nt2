/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#define NT2_UNIT_MODULE "nt2::along function"

#include <nt2/table.hpp>
#include <nt2/include/functions/along.hpp>
#include <nt2/include/functions/size.hpp>
#include <nt2/include/functions/cat.hpp>
#include <nt2/include/functions/isequal.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/basic.hpp>

NT2_TEST_CASE_TPL( along_scalar, NT2_TYPES )
{
  using nt2::_;
  nt2::table<T> y( nt2::of_size(3, 4, 2) );
  nt2::table<T> sy;

  size_t k = 0;
  for(size_t l=1;l<=size(y, 3);l++)
    for(size_t j=1;j<=size(y, 2);j++)
      for(size_t i=1;i<=size(y, 1);i++)
        y(i,j, l) = k++;

  NT2_DISPLAY(y);
  
  for(size_t k=1;k<= nt2::size(y, 1);++k)
    {
      std::cout << "column " << k << std::endl; 
      NT2_TEST(isequal(y(k, _, _), nt2::along(y, k, 1))); 
    }
  for(size_t k=1;k<= nt2::size(y, 2);++k)
    {
      std::cout << "row " << k << std::endl; 
      NT2_TEST(isequal(y(_, k, _), nt2::along(y, k, 2))); 
    }
  for(size_t k=1;k<= nt2::size(y, 3);++k)
    {
      std::cout << "depth " << k << std::endl; 
      NT2_TEST(isequal(y(_, _, k), nt2::along(y, k, 3))); 
    }

}
NT2_TEST_CASE_TPL( along_vect, NT2_REAL_TYPES )
{
  using nt2::_;
  typedef typename nt2::meta::as_integer<T>::type iT; 
  nt2::table<T> y( nt2::of_size(3, 4, 2) );
  nt2::table<T> sy;

  size_t k = 0;
  for(size_t l=1;l<=size(y, 3);l++)
    for(size_t j=1;j<=size(y, 2);j++)
      for(size_t i=1;i<=size(y, 1);i++)
        y(i,j, l) = k++; 

  nt2::table<iT> kk = _(iT(1), iT(2)); 
  NT2_TEST(isequal(y(kk, _, _), nt2::along(y, kk, 1))); 
  NT2_TEST(isequal(y(_, kk, _), nt2::along(y, kk, 2))); 
  NT2_TEST(isequal(y(_, _, kk), nt2::along(y, kk, 3))); 


}
