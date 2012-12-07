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

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>

NT2_TEST_CASE_TPL( of_size, NT2_TYPES )
{
  nt2::table<T> y, ref;

  nt2::table<T> x( nt2::of_size(4,4) );
  for(int i=1;i<=16;i++)  x(i) = T(i);

  ref.resize( nt2::of_size(2,2) );
  for(int i=1;i<=4;i++)  ref(i) = x(i);

  y = nt2::resize(x, nt2::of_size(2,2) );

  NT2_TEST_EQUAL(ref, y);

  ref.resize( nt2::of_size(6,6) );
  for(int i=1;i<=16;i++)  ref(i) = x(i);
  for(int i=17;i<=36;i++)  ref(i) = T(0);

  y = nt2::resize(x, nt2::of_size(6,6) );

  NT2_TEST_EQUAL(ref, y);
}

NT2_TEST_CASE_TPL( size, NT2_TYPES )
{
  nt2::table<T> y, ref;

  nt2::table<T> x( nt2::of_size(4,4) );
  for(int i=1;i<=16;i++)  x(i) = T(i);

  ref.resize( nt2::of_size(2,2) );
  for(int i=1;i<=4;i++)  ref(i) = x(i);

  y = nt2::resize(x, nt2::size(ref) );

  NT2_TEST_EQUAL(ref, y);

  ref.resize( nt2::of_size(6,6) );
  for(int i=1;i<=16;i++)  ref(i) = x(i);
  for(int i=17;i<=36;i++)  ref(i) = T(0);

  y = nt2::resize(x, nt2::size(ref) );

  NT2_TEST_EQUAL(ref, y);

  ref.resize( nt2::of_size(2,2,2) );
  for(int i=1;i<=8;i++)  ref(i) = x(i);

  y = nt2::resize(x, nt2::size(ref) );
  NT2_TEST_EQUAL(ref, y);

  ref.resize( nt2::of_size(2,2,2,2) );
  for(int i=1;i<=16;i++)  ref(i) = x(i);

  y = nt2::resize(x, nt2::size(ref));
  NT2_TEST_EQUAL(ref, y);
}

NT2_TEST_CASE_TPL( scalar, NT2_TYPES )
{
  nt2::table<T> y, ref;

  nt2::table<T> x( nt2::of_size(4,4) );
  for(int i=1;i<=16;i++)  x(i) = T(i);

  ref.resize( nt2::of_size(2,2) );
  for(int i=1;i<=4;i++)  ref(i) = x(i);

  y = nt2::resize(x, 2 );

  NT2_TEST_EQUAL(ref, y);

  ref.resize( nt2::of_size(6,6) );
  for(int i=1;i<=16;i++)  ref(i) = x(i);
  for(int i=17;i<=36;i++)  ref(i) = T(0);

  y = nt2::resize(x, 6, 6 );

  NT2_TEST_EQUAL(ref, y);

  ref.resize( nt2::of_size(2,2,2) );
  for(int i=1;i<=8;i++)  ref(i) = x(i);

  y = nt2::resize(x, 2, 2, 2 );
  NT2_TEST_EQUAL(ref, y);

  ref.resize( nt2::of_size(2,2,2,2) );
  for(int i=1;i<=16;i++)  ref(i) = x(i);

  y = nt2::resize(x, 2, 2, 2, 2 );
  NT2_TEST_EQUAL(ref, y);
}
