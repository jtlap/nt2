/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 0x01.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#define NT2_UNIT_MODULE "nt2::memory::load and store SIMD"

#include <nt2/sdk/memory/load.hpp>
#include <nt2/sdk/simd/native.hpp>
#include <nt2/sdk/memory/store.hpp>
#include <nt2/sdk/memory/is_aligned.hpp>
#include <nt2/sdk/memory/meta/make_aligned.hpp>

#include <boost/mpl/int.hpp>
#include <nt2/sdk/unit/tests.hpp>
#include <nt2/sdk/unit/module.hpp>

////////////////////////////////////////////////////////////////////////////////
// Test load behavior
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE(load)
{
  using nt2::load;
  using nt2::simd::native;

  typedef NT2_SIMD_DEFAULT_EXTENSION ext_t;

  NT2_ALIGNED_TYPE(float) data[]  = {1,2,3,4,5,6,7,8 };

/*
  NT2_TEST_EQUAL( (load<native<float,ext_t>,-1>(&data[0],1)), 0.f );
  NT2_TEST_EQUAL( (load<native<float,ext_t>,-1>(&data[0],2)), 1.f );
  NT2_TEST_EQUAL( (load<native<float,ext_t>,-1>(&data[0],3)), 2.f );
  NT2_TEST_EQUAL( (load<native<float,ext_t>,-1>(&data[0],4)), 3.f );
  NT2_TEST_EQUAL( (load<native<float,ext_t>,-1>(&data[0],5)), 4.f );
*/
  NT2_TEST_EQUAL( (load< native<float,ext_t> >(&data[0],0)[0]), 1.f );
  NT2_TEST_EQUAL( (load< native<float,ext_t> >(&data[0],1)[0]), 5.f );
  NT2_TEST_EQUAL( (load< native<float,ext_t> >(&data[0],2)[0]), 9.f );
  NT2_TEST_EQUAL( (load< native<float,ext_t> >(&data[0],3)[0]), 5.f );

/*
  NT2_TEST_EQUAL( (load<native<float,ext_t>,0>(&data[0],0)), 0.f );
  NT2_TEST_EQUAL( (load<native<float,ext_t>,0>(&data[0],1)), 1.f );
  NT2_TEST_EQUAL( (load<native<float,ext_t>,0>(&data[0],2)), 2.f );
  NT2_TEST_EQUAL( (load<native<float,ext_t>,0>(&data[0],3)), 3.f );
  NT2_TEST_EQUAL( (load<native<float,ext_t>,0>(&data[0],4)), 4.f );
*/
}

////////////////////////////////////////////////////////////////////////////////
// Test store behavior
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE(store)
{
  using nt2::store;
  using nt2::load;
  using nt2::simd::native;

  typedef NT2_SIMD_DEFAULT_EXTENSION ext_t;

  NT2_ALIGNED_TYPE(float) data [] = { 1,2,3,4,5,6,7,8 };

  native<float,ext_t> v = load< native<float,ext_t> >(&data[0],0);
  store(v,&data[0],1);

  NT2_TEST_EQUAL( data[4], 1.f );
  NT2_TEST_EQUAL( data[5], 2.f );
  NT2_TEST_EQUAL( data[6], 3.f );
  NT2_TEST_EQUAL( data[7], 4.f );
}
