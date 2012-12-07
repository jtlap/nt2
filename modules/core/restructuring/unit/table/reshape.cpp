/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#define NT2_UNIT_MODULE "nt2::reshape function"

#include <nt2/table.hpp>
#include <nt2/include/functions/reshape.hpp>
#include <nt2/include/functions/size.hpp>
#include <nt2/include/functions/ones.hpp>
#include <nt2/include/functions/ndims.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/exceptions.hpp>

NT2_TEST_CASE_TPL( of_size, NT2_TYPES )
{
  nt2::table<T> y, ref;

  nt2::table<T> x( nt2::of_size(4,4) );
  for(int i=1;i<=16;i++)  x(i) = T(i);

  ref.resize( nt2::of_size(2,8) );
  for(int i=1;i<=16;i++)  ref(i) = x(i);

  y = nt2::reshape(x, nt2::of_size(2,8) );

  NT2_TEST_EQUAL(ref, y);

  ref.resize( nt2::of_size(8,2) );
  for(int i=1;i<=16;i++)  ref(i) = x(i);

  y = nt2::reshape(x, nt2::of_size(8,2) );

  NT2_TEST_EQUAL(ref, y);
}

NT2_TEST_CASE_TPL( size, NT2_TYPES )
{
  nt2::table<T> y, ref;

  nt2::table<T> x( nt2::of_size(4,4) );
  for(int i=1;i<=16;i++)  x(i) = T(i);

  ref.resize( nt2::of_size(8,2) );
  for(int i=1;i<=16;i++)  ref(i) = x(i);

  y = nt2::reshape(x, nt2::size(ref) );

  NT2_TEST_EQUAL(ref, y);

  ref.resize( nt2::of_size(2,8) );
  for(int i=1;i<=16;i++)  ref(i) = x(i);

  y = nt2::reshape(x, nt2::size(ref) );

  NT2_TEST_EQUAL(ref, y);

  ref.resize( nt2::of_size(2,4,2) );
  for(int i=1;i<=16;i++)  ref(i) = x(i);

  y = nt2::reshape(x, nt2::size(ref) );
  NT2_TEST_EQUAL(ref, y);

  ref.resize( nt2::of_size(2,2,2,2) );
  for(int i=1;i<=16;i++)  ref(i) = x(i);

  y = nt2::reshape(x, nt2::size(ref));
  NT2_TEST_EQUAL(ref, y);
}

NT2_TEST_CASE_TPL( scalar, NT2_TYPES )
{
  nt2::table<T> y, ref;

  nt2::table<T> x( nt2::of_size(4,4) );
  for(int i=1;i<=16;i++)  x(i) = T(i);

  ref.resize( nt2::of_size(8,2) );
  for(int i=1;i<=16;i++)  ref(i) = x(i);

  y = nt2::reshape(x, 8, 2 );

  NT2_TEST_EQUAL(ref, y);

  ref.resize( nt2::of_size(2,8) );
  for(int i=1;i<=16;i++)  ref(i) = x(i);

  y = nt2::reshape(x, 2, 8 );

  NT2_TEST_EQUAL(ref, y);

  ref.resize( nt2::of_size(2,4,2) );
  for(int i=1;i<=16;i++)  ref(i) = x(i);

  y = nt2::reshape(x, 2, 4, 2 );
  NT2_TEST_EQUAL(ref, y);

  ref.resize( nt2::of_size(2,2,2,2) );
  for(int i=1;i<=16;i++)  ref(i) = x(i);

  y = nt2::reshape(x, 2, 2, 2, 2 );
  NT2_TEST_EQUAL(ref, y);
}

NT2_TEST_CASE_TPL( incorrect_reshape, (float) )
{
  nt2::table<T, nt2::_2D> y( nt2::of_size(4,4) );

  NT2_TEST_ASSERT(nt2::reshape(y, nt2::of_size(3,8) ));
  NT2_TEST_ASSERT(nt2::reshape(y, nt2::of_size(2,8,2) ));
  NT2_TEST_ASSERT(nt2::reshape(y, nt2::of_size(1,1,1,32) ));

  NT2_TEST_ASSERT(nt2::reshape(y, nt2::size( nt2::ones(3,8) )       ));
  NT2_TEST_ASSERT(nt2::reshape(y, nt2::size( nt2::ones(2,8,2) )     ));
  NT2_TEST_ASSERT(nt2::reshape(y, nt2::size( nt2::ones(1,1,1,32) )  ));

  NT2_TEST_ASSERT(nt2::reshape(y, 3,8)      );
  NT2_TEST_ASSERT(nt2::reshape(y, 2,8,2)    );
  NT2_TEST_ASSERT(nt2::reshape(y, 1,1,1,32) );
}
