/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#define NT2_UNIT_MODULE "nt2::size function"

#include <nt2/include/functions/size.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/basic.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>

////////////////////////////////////////////////////////////////////////////////
// size of arithmetic types
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE( fundamental_size )
{
  using nt2::size;

  NT2_TEST( size(4.f).empty() );
  NT2_TEST_EQUAL( size(4.f).size()  , 0  );

  NT2_TEST_EQUAL( size(4.f)(1), 1 );
  NT2_TEST_EQUAL( size(4.f)(2), 1 );

  NT2_TEST_EQUAL( size(4.f).size(1) , 1 );
  NT2_TEST_EQUAL( size(4.f).size(2) , 1 );
  NT2_TEST_EQUAL( size(4.f).lower(1), 1 );
  NT2_TEST_EQUAL( size(4.f).lower(2), 1 );
  NT2_TEST_EQUAL( size(4.f).upper(1), 1 );
  NT2_TEST_EQUAL( size(4.f).upper(2), 1 );
}

////////////////////////////////////////////////////////////////////////////////
// size of size types
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE( size_size )
{
  using nt2::size;

/*
  NT2_TEST( size(size(4.f)).empty() );
  NT2_TEST_EQUAL( size(size(4.f)).size()  , 0  );

  NT2_TEST_EQUAL( size(size(4.f))(1), 1 );
  NT2_TEST_EQUAL( size(size(4.f))(2), 1 );

  NT2_TEST_EQUAL( size(size(4.f)).size(1) , 1 );
  NT2_TEST_EQUAL( size(size(4.f)).size(2) , 1 );
  NT2_TEST_EQUAL( size(size(4.f)).lower(1), 1 );
  NT2_TEST_EQUAL( size(size(4.f)).lower(2), 1 );
  NT2_TEST_EQUAL( size(size(4.f)).upper(1), 1 );
  NT2_TEST_EQUAL( size(size(4.f)).upper(2), 1 );
*/

}
