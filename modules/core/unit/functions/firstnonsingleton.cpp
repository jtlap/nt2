/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#define NT2_UNIT_MODULE "nt2::firstnonsingleton function"

#include <nt2/table.hpp>
#include <nt2/include/functions/firstnonsingleton.hpp>
#include <nt2/include/functions/of_size.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/basic.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>

////////////////////////////////////////////////////////////////////////////////
// firstnonsingleton of arithmetic types
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE( fundamental_firstnonsingleton )
{
  using nt2::firstnonsingleton;

  NT2_TEST_EQUAL( firstnonsingleton('4'), 1U  );
  NT2_TEST_EQUAL( firstnonsingleton(4)  , 1U  );
  NT2_TEST_EQUAL( firstnonsingleton(4.) , 1U  );
  NT2_TEST_EQUAL( firstnonsingleton(4.f), 1U  );
}

////////////////////////////////////////////////////////////////////////////////
// firstnonsingleton of container
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE( container_firstnonsingleton )
{
  using nt2::firstnonsingleton;
  using nt2::of_size;

  typedef nt2::memory::container<float,nt2::settings()> container_t;

  container_t t0;
  container_t t1( of_size(2,2,2,2) );
  container_t t2( of_size(1,2,2,2) );
  container_t t3( of_size(1,1,2,2) );
  container_t t4( of_size(1,1,1,2) );

  NT2_TEST_EQUAL( firstnonsingleton(t0.extent()), 1U   );
  NT2_TEST_EQUAL( firstnonsingleton(t1.extent()), 1U   );
  NT2_TEST_EQUAL( firstnonsingleton(t2.extent()), 2U   );
  NT2_TEST_EQUAL( firstnonsingleton(t3.extent()), 3U   );
  NT2_TEST_EQUAL( firstnonsingleton(t4.extent()), 4U  );
}

////////////////////////////////////////////////////////////////////////////////
// firstnonsingleton of table
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE( table_firstnonsingleton )
{
  using nt2::firstnonsingleton;
  using nt2::of_size;
  using nt2::table;

  table<float> t0;
  table<float> t1( of_size(2) );
  table<float> t2( of_size(1,2) );
  table<float> t3( of_size(1,1,2) );
  table<float> t4( of_size(1,1,1,2) );

  NT2_TEST_EQUAL( firstnonsingleton(t0.extent()), 1U   );
  NT2_TEST_EQUAL( firstnonsingleton(t1.extent()), 1U   );
  NT2_TEST_EQUAL( firstnonsingleton(t2.extent()), 2U   );
  NT2_TEST_EQUAL( firstnonsingleton(t3.extent()), 3U   );
  NT2_TEST_EQUAL( firstnonsingleton(t4.extent()), 4U  );
}

////////////////////////////////////////////////////////////////////////////////
// firstnonsingleton of table expression
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE( expression_firstnonsingleton )
{
  using nt2::firstnonsingleton;
  using nt2::of_size;
  using nt2::table;

  table<float> t0;
  table<float> t1( of_size(2) );
  table<float> t2( of_size(1,2) );
  table<float> t3( of_size(1,1,2) );
  table<float> t4( of_size(1,1,1,2) );

  NT2_TEST_EQUAL( firstnonsingleton((-t0).extent())     , 1U   );
  NT2_TEST_EQUAL( firstnonsingleton((t1*t1).extent())   , 1U   );
  NT2_TEST_EQUAL( firstnonsingleton((t2-t2*t2).extent()), 2U   );
  NT2_TEST_EQUAL( firstnonsingleton((t3/t3+t3).extent()), 3U   );
  NT2_TEST_EQUAL( firstnonsingleton((t4 * -t4).extent()), 4U  );
}
