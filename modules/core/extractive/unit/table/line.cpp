//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#define NT2_UNIT_MODULE "nt2::line function"

#include <nt2/table.hpp>
#include <nt2/include/functions/line.hpp>
#include <nt2/include/functions/size.hpp>
#include <nt2/include/functions/nblines.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/basic.hpp>

NT2_TEST_CASE_TPL( line_scalar, NT2_TYPES )
{
  T x = nt2::line(T(42), 1);
  NT2_TEST_EQUAL( x, T(42) );

  x = nt2::line(T(42),1);
  NT2_TEST_EQUAL( x, T(42) );

  x = nt2::line(T(42),1, 2);
  NT2_TEST_EQUAL( x, T(42) );

}

NT2_TEST_CASE_TPL( line, NT2_TYPES )
{
  using nt2::_;
  nt2::table<T> y( nt2::of_size(3, 4) );
  nt2::table<T> sy;

  size_t k = 0;
  for(size_t j=1;j<=size(y, 2);j++)
    for(size_t i=1;i<=size(y, 1);i++)
      y(i,j) = k++;

  for(size_t k=0;k<nt2::nblines(y, 1);++k)
  {
    NT2_TEST_EQUAL(nt2::line(y, k, 1)(_), y(_, k+1)(_));
  }
  for(size_t k=0;k<nt2::nblines(y, 2);++k)
  {
    NT2_TEST_EQUAL(nt2::line(y, k, 2)(_), y(k+1, _)(_));
  }
  for(size_t k=0;k<nt2::nblines(y, 3);++k)
  {
    NT2_TEST_EQUAL(nt2::line(y, k, 3)(_), y(k+1));
  }
}

