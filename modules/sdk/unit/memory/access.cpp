/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 0x01.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#define NT2_UNIT_MODULE "nt2::memory::load and store"

#include <boost/mpl/int.hpp>
#include <nt2/sdk/memory/load.hpp>
#include <nt2/sdk/memory/store.hpp>
#include <nt2/sdk/config/types.hpp>
#include <nt2/sdk/config/type_lists.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>

////////////////////////////////////////////////////////////////////////////////
// Test load behavior
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE_TPL(load, NT2_TYPES)
{
  using nt2::load;

  T data[5] = {0,1,2,3,4};

  NT2_TEST_EQUAL( (load<T,-4>(&data[0],4)), T(0) );
  NT2_TEST_EQUAL( (load<T,-4>(&data[0],5)), T(1) );
  NT2_TEST_EQUAL( (load<T,-4>(&data[0],6)), T(2) );
  NT2_TEST_EQUAL( (load<T,-4>(&data[0],7)), T(3) );
  NT2_TEST_EQUAL( (load<T,-4>(&data[0],8)), T(4) );

  NT2_TEST_EQUAL( (load<T,-3>(&data[0],3)), T(0) );
  NT2_TEST_EQUAL( (load<T,-3>(&data[0],4)), T(1) );
  NT2_TEST_EQUAL( (load<T,-3>(&data[0],5)), T(2) );
  NT2_TEST_EQUAL( (load<T,-3>(&data[0],6)), T(3) );
  NT2_TEST_EQUAL( (load<T,-3>(&data[0],7)), T(4) );

  NT2_TEST_EQUAL( (load<T,-2>(&data[0],2)), T(0) );
  NT2_TEST_EQUAL( (load<T,-2>(&data[0],3)), T(1) );
  NT2_TEST_EQUAL( (load<T,-2>(&data[0],4)), T(2) );
  NT2_TEST_EQUAL( (load<T,-2>(&data[0],5)), T(3) );
  NT2_TEST_EQUAL( (load<T,-2>(&data[0],6)), T(4) );

  NT2_TEST_EQUAL( (load<T,-1>(&data[0],1)), T(0) );
  NT2_TEST_EQUAL( (load<T,-1>(&data[0],2)), T(1) );
  NT2_TEST_EQUAL( (load<T,-1>(&data[0],3)), T(2) );
  NT2_TEST_EQUAL( (load<T,-1>(&data[0],4)), T(3) );
  NT2_TEST_EQUAL( (load<T,-1>(&data[0],5)), T(4) );

  NT2_TEST_EQUAL( load<T>(&data[0],0), T(0) );
  NT2_TEST_EQUAL( load<T>(&data[0],1), T(1) );
  NT2_TEST_EQUAL( load<T>(&data[0],2), T(2) );
  NT2_TEST_EQUAL( load<T>(&data[0],3), T(3) );
  NT2_TEST_EQUAL( load<T>(&data[0],4), T(4) );

  NT2_TEST_EQUAL( (load<T,0>(&data[0],0)), T(0) );
  NT2_TEST_EQUAL( (load<T,0>(&data[0],1)), T(1) );
  NT2_TEST_EQUAL( (load<T,0>(&data[0],2)), T(2) );
  NT2_TEST_EQUAL( (load<T,0>(&data[0],3)), T(3) );
  NT2_TEST_EQUAL( (load<T,0>(&data[0],4)), T(4) );

  NT2_TEST_EQUAL( (load<T,1>(&data[0],-1)), T(0) );
  NT2_TEST_EQUAL( (load<T,1>(&data[0],0)) , T(1) );
  NT2_TEST_EQUAL( (load<T,1>(&data[0],1)) , T(2) );
  NT2_TEST_EQUAL( (load<T,1>(&data[0],2)) , T(3) );
  NT2_TEST_EQUAL( (load<T,1>(&data[0],3)) , T(4) );

  NT2_TEST_EQUAL( (load<T,2>(&data[0],-2)), T(0) );
  NT2_TEST_EQUAL( (load<T,2>(&data[0],-1)), T(1) );
  NT2_TEST_EQUAL( (load<T,2>(&data[0],0)) , T(2) );
  NT2_TEST_EQUAL( (load<T,2>(&data[0],1)) , T(3) );
  NT2_TEST_EQUAL( (load<T,2>(&data[0],2)) , T(4) );

  NT2_TEST_EQUAL( (load<T,3>(&data[0],-3)), T(0) );
  NT2_TEST_EQUAL( (load<T,3>(&data[0],-2)), T(1) );
  NT2_TEST_EQUAL( (load<T,3>(&data[0],-1)), T(2) );
  NT2_TEST_EQUAL( (load<T,3>(&data[0],0)) , T(3) );
  NT2_TEST_EQUAL( (load<T,3>(&data[0],1)) , T(4) );

  NT2_TEST_EQUAL( (load<T,4>(&data[0],-4)), T(0) );
  NT2_TEST_EQUAL( (load<T,4>(&data[0],-3)), T(1) );
  NT2_TEST_EQUAL( (load<T,4>(&data[0],-2)), T(2) );
  NT2_TEST_EQUAL( (load<T,4>(&data[0],-1)), T(3) );
  NT2_TEST_EQUAL( (load<T,4>(&data[0],0)) , T(4) );
}

////////////////////////////////////////////////////////////////////////////////
// Test store behavior
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE_TPL(store, NT2_TYPES)
{
  using nt2::store;

  T data[5];
  for(nt2::int32_t i=0;i<5;++i) store(static_cast<T>(i),&data[0],i);
  NT2_TEST_EQUAL( data[0], T(0) );
  NT2_TEST_EQUAL( data[1], T(1) );
  NT2_TEST_EQUAL( data[2], T(2) );
  NT2_TEST_EQUAL( data[3], T(3) );
  NT2_TEST_EQUAL( data[4], T(4) );
}
