/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#define NT2_UNIT_MODULE "nt2::from_diag function"

#include <nt2/table.hpp>
#include <nt2/include/functions/length.hpp>
#include <nt2/include/functions/from_diag.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>

NT2_TEST_CASE_TPL( from_diag, NT2_TYPES )
{
  nt2::table<T> x,y( nt2::of_size(1,31) );

  for(size_t i=1;i<=nt2::length(y);i++) y(i) = i;

  x = nt2::from_diag(y);

  NT2_TEST_EQUAL( nt2::ndims(x) , 2u             );
  NT2_TEST_EQUAL( nt2::size(x,1), nt2::length(y));
  NT2_TEST_EQUAL( nt2::size(x,2), nt2::length(y));

  for(size_t i=1;i<=nt2::length(y);i++) NT2_TEST_EQUAL( x(i,i), y(i) );
}

NT2_TEST_CASE_TPL( from_diag_scalar, NT2_TYPES )
{
  T x,y = 42;
  x = nt2::from_diag(y);
  NT2_TEST_EQUAL(x, y);
}

NT2_TEST_CASE_TPL( from_diag_expr, NT2_TYPES )
{
  nt2::table<T> x,y( nt2::of_size(1,31) );

  for(size_t i=1;i<=nt2::length(y);i++) y(i) = i;

  x = nt2::from_diag(y+y-T(1));

  NT2_TEST_EQUAL( nt2::ndims(x) , 2u            );
  NT2_TEST_EQUAL( nt2::size(x,1), nt2::length(y));
  NT2_TEST_EQUAL( nt2::size(x,2), nt2::length(y));

  for(size_t i=1;i<=nt2::length(y);i++) NT2_TEST_EQUAL( x(i,i), (y+y-T(1))(i) );
}

NT2_TEST_CASE_TPL( from_diag_offset, NT2_TYPES )
{
  nt2::table<T> y( nt2::of_size(1,5) ), x;

  for(size_t i=1;i<=nt2::length(y);i++) y(i) = i;
  NT2_DISPLAY(y);

  x = nt2::from_diag(y, -2);
  NT2_DISPLAY(x);

  NT2_TEST_EQUAL( nt2::ndims(x) , 2u             );
  NT2_TEST_EQUAL( nt2::size(x,1), nt2::length(y)+2);
  NT2_TEST_EQUAL( nt2::size(x,2), nt2::length(y)+2);

  for(size_t i=3;i<=nt2::length(x);i++) NT2_TEST_EQUAL( x(i,i-2), y(i-2) );
}
