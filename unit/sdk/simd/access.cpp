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
#include <unit/sdk/simd/types.hpp>
#include <nt2/sdk/memory/store.hpp>
#include <nt2/sdk/memory/is_aligned.hpp>
#include <nt2/sdk/memory/aligned_type.hpp>

#include <boost/mpl/int.hpp>
#include <nt2/sdk/unit/tests.hpp>
#include <nt2/sdk/unit/module.hpp>

////////////////////////////////////////////////////////////////////////////////
// Test load behavior
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE_TPL(load, NT2_SIMD_TYPES )
{
  using nt2::load;
  using nt2::simd::native;
  using nt2::meta::cardinal_of;

  typedef NT2_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef native<T,ext_t>             n_t;

  NT2_ALIGNED_TYPE(T) data[3*cardinal_of<n_t>::value];
  for(std::size_t i=0;i<3*cardinal_of<n_t>::value;++i)
    data[i] = 1+i;

  for(std::size_t i=0;i<3;++i)
  {
    n_t v = load<n_t>(&data[0],i);
    for(std::size_t j=0;j<cardinal_of<n_t>::value;++j)
    {
      NT2_TEST_EQUAL( v[j], 1+i*cardinal_of<n_t>::value+j );
    }
  }
}

/*
////////////////////////////////////////////////////////////////////////////////
// Test shifed load behavior
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE_TPL(shifted_load, NT2_SIMD_TYPES )
{
  using nt2::load;
  using nt2::simd::native;
  using nt2::meta::cardinal_of;

  typedef NT2_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef native<T,ext_t>             n_t;

  NT2_ALIGNED_TYPE(T) data[3*cardinal_of<n_t>::value];
  for(std::size_t i=0;i<3*cardinal_of<n_t>::value;++i)
    data[i] = 1+i;

  n_t v = load<n_t,-2>(&data[0],1);
  for(std::size_t j=0;j<cardinal_of<n_t>::value;++j)
    NT2_TEST_EQUAL( v[j], 1+cardinal_of<n_t>::value+j-2 );

  v = load<n_t,-1>(&data[0],1);
  for(std::size_t j=0;j<cardinal_of<n_t>::value;++j)
    NT2_TEST_EQUAL( v[j], 1+cardinal_of<n_t>::value+j-1 );

  v = load<n_t,0>(&data[0],1);
  for(std::size_t j=0;j<cardinal_of<n_t>::value;++j)
    NT2_TEST_EQUAL( v[j], 1+cardinal_of<n_t>::value+j );

  v = load<n_t,1>(&data[0],1);
  for(std::size_t j=0;j<cardinal_of<n_t>::value;++j)
    NT2_TEST_EQUAL( v[j], 1+cardinal_of<n_t>::value+j+1 );

  v = load<n_t,2>(&data[0],1);
  for(std::size_t j=0;j<cardinal_of<n_t>::value;++j)
    NT2_TEST_EQUAL( v[j], 1+cardinal_of<n_t>::value+j+2 );
}
*/
////////////////////////////////////////////////////////////////////////////////
// Test store behavior
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE_TPL(store, NT2_SIMD_TYPES )
{
  using nt2::store;
  using nt2::load;
  using nt2::simd::native;
  using nt2::meta::cardinal_of;

  typedef NT2_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef native<T,ext_t>             n_t;

  NT2_ALIGNED_TYPE(T) data[2*cardinal_of<n_t>::value];
  for(std::size_t i=0;i<cardinal_of<n_t>::value;++i)
    data[i] = 1+i;

  n_t v = load<n_t>(&data[0],0);
  store(v,&data[0],1);

  for(std::size_t j=0;j<cardinal_of<n_t>::value;++j)
  {
    NT2_TEST_EQUAL( data[j], data[j+cardinal_of<n_t>::value] );
  }
}
