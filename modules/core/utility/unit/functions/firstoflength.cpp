/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#define NT2_UNIT_MODULE "nt2::firstoflength function"

#include <nt2/table.hpp>
#include <nt2/include/functions/firstoflength.hpp>
#include <nt2/include/functions/of_size.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/basic.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>

////////////////////////////////////////////////////////////////////////////////
// firstoflength of arithmetic types
////////////////////////////////////////////////////////////////////////////////
// NT2_TEST_CASE( fundamental_firstoflength )
// {
//   using nt2::firstoflength;

//   NT2_TEST_EQUAL( firstoflength('4'), 1U  );
//   NT2_TEST_EQUAL( firstoflength(4)  , 1U  );
//   NT2_TEST_EQUAL( firstoflength(4.) , 1U  );
//   NT2_TEST_EQUAL( firstoflength(4.f), 1U  );
// }

////////////////////////////////////////////////////////////////////////////////
// firstoflength of of_size
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE(of_size_firstoflength )
{
  using nt2::firstoflength;
  using nt2::_4D;

  _4D t0;
  _4D t1(2,2,2,2);
  _4D t2(1,2,2,2);
  _4D t3(1,1,2,2);
  _4D t4(1,1,1,2);

  NT2_TEST_EQUAL( firstoflength(t0, 2), 0U );
  NT2_TEST_EQUAL( firstoflength(t1, 2), 1U );
  NT2_TEST_EQUAL( firstoflength(t2, 2), 2U );
  NT2_TEST_EQUAL( firstoflength(t3, 2), 3U );
  NT2_TEST_EQUAL( firstoflength(t4, 2), 4U );
}

////////////////////////////////////////////////////////////////////////////////
// firstoflength of table
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE( table_firstoflength )
{
  using nt2::firstoflength;
  using nt2::of_size;
  using nt2::table;

  table<float> t0;
  table<float> t1( of_size(3) );
  table<float> t2( of_size(1,3) );
  table<float> t3( of_size(1,1,3) );
  table<float> t4( of_size(1,1,1,3) );
  table<float> t5( of_size(1,1,1,1) );

  NT2_TEST_EQUAL( firstoflength(t0, 3), 0U   );
  NT2_TEST_EQUAL( firstoflength(t1, 3), 1U   );
  NT2_TEST_EQUAL( firstoflength(t2, 3), 2U   );
  NT2_TEST_EQUAL( firstoflength(t3, 3), 3U   );
  NT2_TEST_EQUAL( firstoflength(t4, 3), 4U  );
  NT2_TEST_EQUAL( firstoflength(t5, 3), 0U  );
}

////////////////////////////////////////////////////////////////////////////////
// firstoflength of table expression
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE( expression_firstoflength )
{
  using nt2::firstoflength;
  using nt2::of_size;
  using nt2::table;

  table<float> t0;
  table<float> t1( of_size(3) );
  table<float> t2( of_size(1,3) );
  table<float> t3( of_size(1,1,3) );
  table<float> t4( of_size(1,1,1,3) );
  table<float> t5( of_size(1,1,1,1) );

  NT2_TEST_EQUAL( firstoflength((-t0     ), 3), 0U );
  NT2_TEST_EQUAL( firstoflength((t1*t1   ), 3), 1U );
  NT2_TEST_EQUAL( firstoflength((t2-t2*t2), 3), 2U );
  NT2_TEST_EQUAL( firstoflength((t3/t3+t3), 3), 3U );
  NT2_TEST_EQUAL( firstoflength((t4 * -t4), 3), 4U );
  NT2_TEST_EQUAL( firstoflength((t5*t5-t5), 3), 0U );
}
