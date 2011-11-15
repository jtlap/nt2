/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#define NT2_UNIT_MODULE "nt2::ndims function"

#include <nt2/core/container/table/table.hpp>
#include <nt2/core/container/colon/colon.hpp>
#include <nt2/include/functions/ndims.hpp>
#include <nt2/include/functions/of_size.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/basic.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>

////////////////////////////////////////////////////////////////////////////////
// ndims of arithmetic types
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE( fundamental_ndims )
{
  using nt2::ndims;
  using nt2::_;
  
  NT2_TEST_EQUAL( ndims('4'), 2U  );
  NT2_TEST_EQUAL( ndims(4)  , 2U  );
  NT2_TEST_EQUAL( ndims(4.) , 2U  );
  NT2_TEST_EQUAL( ndims(4.f), 2U  );
  NT2_TEST_EQUAL( ndims(_)  , 2U  );
}

////////////////////////////////////////////////////////////////////////////////
// ndims of table
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE( table_ndims )
{
  using nt2::ndims;
  using nt2::of_size;
  using nt2::container::table;
  
  table<float> t0;
  table<float> t10 ( of_size(1)   );
  table<float> t11 ( of_size(2)   );
  table<float> t20( of_size(1,1)  );
  table<float> t21( of_size(2,1)  );
  table<float> t22( of_size(1,2)  );
  table<float> t30( of_size(1,1,1) );
  table<float> t31( of_size(3,1,1) );
  table<float> t32( of_size(1,3,1) );
  table<float> t33( of_size(1,1,3) );
  table<float> t40( of_size(1,1,1,1) );
  table<float> t41( of_size(4,1,1,1) );
  table<float> t42( of_size(1,4,1,1) );
  table<float> t43( of_size(1,1,4,1) );
  table<float> t44( of_size(1,1,1,4) );

  NT2_TEST_EQUAL( ndims(t0) , 2U );
  NT2_TEST_EQUAL( ndims(t10), 4U );
  NT2_TEST_EQUAL( ndims(t11), 2U );
  NT2_TEST_EQUAL( ndims(t20), 4U );
  NT2_TEST_EQUAL( ndims(t21), 2U );
  NT2_TEST_EQUAL( ndims(t22), 2U );
  NT2_TEST_EQUAL( ndims(t30), 4U );
  NT2_TEST_EQUAL( ndims(t31), 2U );
  NT2_TEST_EQUAL( ndims(t32), 2U );
  NT2_TEST_EQUAL( ndims(t33), 3U );
  NT2_TEST_EQUAL( ndims(t40), 4U );
  NT2_TEST_EQUAL( ndims(t41), 2U );
  NT2_TEST_EQUAL( ndims(t42), 2U );
  NT2_TEST_EQUAL( ndims(t43), 3U );
  NT2_TEST_EQUAL( ndims(t44), 4U );
}
