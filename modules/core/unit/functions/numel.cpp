/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#define NT2_UNIT_MODULE "nt2::numel function"

#include <nt2/table.hpp>
#include <nt2/include/functions/numel.hpp>
#include <nt2/include/functions/of_size.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/basic.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>

////////////////////////////////////////////////////////////////////////////////
// numel of arithmetic types
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE( fundamental_numel )
{
  using nt2::numel;
  
  NT2_TEST_EQUAL( numel('4'), 1U  );
  NT2_TEST_EQUAL( numel(4)  , 1U  );
  NT2_TEST_EQUAL( numel(4.) , 1U  );
  NT2_TEST_EQUAL( numel(4.f), 1U  ); 
}

////////////////////////////////////////////////////////////////////////////////
// numel of table
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE( table_numel )
{
  using nt2::numel;
  using nt2::of_size;
  using nt2::table;
  
  table<float> t0;
  table<float> t1( of_size(2) );
  table<float> t2( of_size(2,2) );
  table<float> t3( of_size(2,2,2) );
  table<float> t4( of_size(2,2,2,2) );

  NT2_TEST_EQUAL( numel(t0), 0U   );
  NT2_TEST_EQUAL( numel(t1), 2U   );
  NT2_TEST_EQUAL( numel(t2), 4U   );
  NT2_TEST_EQUAL( numel(t3), 8U   );
  NT2_TEST_EQUAL( numel(t4), 16U  );
}

////////////////////////////////////////////////////////////////////////////////
// numel of table expression
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE( expression_numel )
{
  using nt2::numel;
  using nt2::of_size;
  using nt2::table;
  
  table<float> t0;
  table<float> t1( of_size(2) );
  table<float> t2( of_size(2,2) );
  table<float> t3( of_size(2,2,2) );
  table<float> t4( of_size(2,2,2,2) );

  NT2_TEST_EQUAL( numel(-t0), 0U   );
  NT2_TEST_EQUAL( numel(t1*t1), 2U   );
  NT2_TEST_EQUAL( numel(t2-t2*t2), 4U   );
  NT2_TEST_EQUAL( numel(t3/t3+t3), 8U   );
  NT2_TEST_EQUAL( numel(t4 * -t4), 16U  );
}
