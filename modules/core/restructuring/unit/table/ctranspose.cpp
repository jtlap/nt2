/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#define NT2_UNIT_MODULE "nt2::ctrans function"

#include <nt2/table.hpp>
#include <nt2/include/functions/ctranspose.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>

NT2_TEST_CASE_TPL( ctranspose, NT2_TYPES )
{
  nt2::table<T> z, x( nt2::of_size(5,4) ),y( nt2::of_size(4,5) );

  for(int j=1;j<=5;j++)
    for(int i=1;i<=4;i++)
      x(j, i) = y(i,j) = i + 10*j;

  z = nt2::ctrans(y);

  for(std::size_t i=1;i<=nt2::numel(x);i++)
    NT2_TEST_EQUAL( x(i),z(i) );
}

