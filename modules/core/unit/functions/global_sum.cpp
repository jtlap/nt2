/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#define NT2_UNIT_MODULE "nt2::global_sum function"

#include <nt2/table.hpp>
#include <nt2/include/functions/global_sum.hpp>
#include <nt2/include/functions/of_size.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/basic.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>

////////////////////////////////////////////////////////////////////////////////
// global_sum of arithmetic types
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE( fundamental_global_sum )
{
  using nt2::global_sum;
  
  NT2_TEST_EQUAL( global_sum(4)  , 4  );
  NT2_TEST_EQUAL( global_sum(4.) , 4.  );
  NT2_TEST_EQUAL( global_sum(4.f), 4.f  );
}

////////////////////////////////////////////////////////////////////////////////
// global_sum of table
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE( table_global_sum )
{
  using nt2::global_sum;
  using nt2::of_size;
  using nt2::table;
  using boost::mpl::_;
  
  //table<float> t0;
  table<float> t1( of_size(2) );
  // table<float> t2( of_size(4,2) );
  // table<float> t3( of_size(4,6,2) );
  // table<float> t4( of_size(4,6,8,2) );



  NT2_TEST_EXPR_TYPE( global_sum(t1)
                      , (_)
                      ,(float)
                      );

  // NT2_TEST_EQUAL( global_sum(t0), 1U  );
  // NT2_TEST_EQUAL( global_sum(t1), 2U  );
  // NT2_TEST_EQUAL( global_sum(t2), 4U  );
  // NT2_TEST_EQUAL( global_sum(t3), 6U  );
  // NT2_TEST_EQUAL( global_sum(t4), 8U  );
  
}
