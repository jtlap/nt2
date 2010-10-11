/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 0x01.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#define NT2_UNIT_MODULE "nt2::memory::load and store"

#include <nt2/sdk/memory/load.hpp>
#include <nt2/sdk/memory/store.hpp>

#include <boost/mpl/int.hpp>
#include <nt2/sdk/unit/tests.hpp>
#include <nt2/sdk/unit/module.hpp>

////////////////////////////////////////////////////////////////////////////////
// Test load behavior
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE(load)
{
  using nt2::load;

  float data[5] = {0,1,2,3,4};

  NT2_TEST_EQUAL( (load<float,-4>(&data[0],4)), 0.f );
  NT2_TEST_EQUAL( (load<float,-4>(&data[0],5)), 1.f );
  NT2_TEST_EQUAL( (load<float,-4>(&data[0],6)), 2.f );
  NT2_TEST_EQUAL( (load<float,-4>(&data[0],7)), 3.f );
  NT2_TEST_EQUAL( (load<float,-4>(&data[0],8)), 4.f );

  NT2_TEST_EQUAL( (load<float,-3>(&data[0],3)), 0.f );
  NT2_TEST_EQUAL( (load<float,-3>(&data[0],4)), 1.f );
  NT2_TEST_EQUAL( (load<float,-3>(&data[0],5)), 2.f );
  NT2_TEST_EQUAL( (load<float,-3>(&data[0],6)), 3.f );
  NT2_TEST_EQUAL( (load<float,-3>(&data[0],7)), 4.f );

  NT2_TEST_EQUAL( (load<float,-2>(&data[0],2)), 0.f );
  NT2_TEST_EQUAL( (load<float,-2>(&data[0],3)), 1.f );
  NT2_TEST_EQUAL( (load<float,-2>(&data[0],4)), 2.f );
  NT2_TEST_EQUAL( (load<float,-2>(&data[0],5)), 3.f );
  NT2_TEST_EQUAL( (load<float,-2>(&data[0],6)), 4.f );

  NT2_TEST_EQUAL( (load<float,-1>(&data[0],1)), 0.f );
  NT2_TEST_EQUAL( (load<float,-1>(&data[0],2)), 1.f );
  NT2_TEST_EQUAL( (load<float,-1>(&data[0],3)), 2.f );
  NT2_TEST_EQUAL( (load<float,-1>(&data[0],4)), 3.f );
  NT2_TEST_EQUAL( (load<float,-1>(&data[0],5)), 4.f );

  NT2_TEST_EQUAL( load<float>(&data[0],0), 0.f );
  NT2_TEST_EQUAL( load<float>(&data[0],1), 1.f );
  NT2_TEST_EQUAL( load<float>(&data[0],2), 2.f );
  NT2_TEST_EQUAL( load<float>(&data[0],3), 3.f );
  NT2_TEST_EQUAL( load<float>(&data[0],4), 4.f );

  NT2_TEST_EQUAL( (load<float,0>(&data[0],0)), 0.f );
  NT2_TEST_EQUAL( (load<float,0>(&data[0],1)), 1.f );
  NT2_TEST_EQUAL( (load<float,0>(&data[0],2)), 2.f );
  NT2_TEST_EQUAL( (load<float,0>(&data[0],3)), 3.f );
  NT2_TEST_EQUAL( (load<float,0>(&data[0],4)), 4.f );

  NT2_TEST_EQUAL( (load<float,1>(&data[0],-1)), 0.f );
  NT2_TEST_EQUAL( (load<float,1>(&data[0],0)), 1.f );
  NT2_TEST_EQUAL( (load<float,1>(&data[0],1)), 2.f );
  NT2_TEST_EQUAL( (load<float,1>(&data[0],2)), 3.f );
  NT2_TEST_EQUAL( (load<float,1>(&data[0],3)), 4.f );

  NT2_TEST_EQUAL( (load<float,2>(&data[0],-2)), 0.f );
  NT2_TEST_EQUAL( (load<float,2>(&data[0],-1)), 1.f );
  NT2_TEST_EQUAL( (load<float,2>(&data[0],0)) , 2.f );
  NT2_TEST_EQUAL( (load<float,2>(&data[0],1)) , 3.f );
  NT2_TEST_EQUAL( (load<float,2>(&data[0],2)) , 4.f );

  NT2_TEST_EQUAL( (load<float,3>(&data[0],-3)), 0.f );
  NT2_TEST_EQUAL( (load<float,3>(&data[0],-2)), 1.f );
  NT2_TEST_EQUAL( (load<float,3>(&data[0],-1)), 2.f );
  NT2_TEST_EQUAL( (load<float,3>(&data[0],0)) , 3.f );
  NT2_TEST_EQUAL( (load<float,3>(&data[0],1)) , 4.f );

  NT2_TEST_EQUAL( (load<float,4>(&data[0],-4)), 0.f );
  NT2_TEST_EQUAL( (load<float,4>(&data[0],-3)), 1.f );
  NT2_TEST_EQUAL( (load<float,4>(&data[0],-2)), 2.f );
  NT2_TEST_EQUAL( (load<float,4>(&data[0],-1)), 3.f );
  NT2_TEST_EQUAL( (load<float,4>(&data[0],0)) , 4.f );
}

////////////////////////////////////////////////////////////////////////////////
// Test store behavior
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE(store)
{
  using nt2::store;

  float data[5];
  for(nt2::int32_t i=0;i<5;++i) store(static_cast<float>(i),&data[0],i);  
  NT2_TEST_EQUAL( data[0], 0.f );
  NT2_TEST_EQUAL( data[1], 1.f );
  NT2_TEST_EQUAL( data[2], 2.f );
  NT2_TEST_EQUAL( data[3], 3.f );
  NT2_TEST_EQUAL( data[4], 4.f );
}
