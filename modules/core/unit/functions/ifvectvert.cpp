/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#define NT2_UNIT_MODULE "nt2::ifvectvert function"

#include <nt2/table.hpp>
#include <nt2/include/functions/ifvectvert.hpp>
#include <nt2/include/functions/isequal.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/basic.hpp>
#include <nt2/sdk/unit/tests/exceptions.hpp>

NT2_TEST_CASE_TPL( ifvectvert_scalar, NT2_TYPES )
{
  NT2_TEST_EQUAL(nt2::ifvectvert(T(1)), T(1));
}


NT2_TEST_CASE_TPL( ifvectvert,NT2_TYPES )
{
  nt2::table<T> r;
  nt2::table<T, nt2::_2D> y( nt2::of_size(4,4) );

  for(int j=1;j<=4;j++)
    for(int i=1;i<=4;i++)
      y(i,j) = T(i + 10*j);

  r = nt2::ifvectvert(y);
  NT2_TEST(nt2::isequal(y, r)); 
  y =  nt2::reshape(y, 1, 16); 
  r = nt2::ifvectvert(y);
  NT2_TEST(nt2::isequal(y(nt2::_), r));
  y = y(nt2::_);
  r = nt2::ifvectvert(y);
  NT2_TEST(nt2::isequal(y, r));  
}
