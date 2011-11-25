/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 0x01.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#define NT2_UNIT_MODULE "boost::simd::memory::load and store SIMD"

#include <boost/simd/sdk/simd/native.hpp>
#include <boost/simd/sdk/simd/io.hpp>
#include <boost/simd/include/functions/load.hpp>
#include <boost/simd/include/functions/unaligned_load.hpp>
#include <boost/simd/include/functions/unaligned_store.hpp>
#include <boost/simd/include/functions/store.hpp>
#include <boost/simd/sdk/memory/is_aligned.hpp>
#include <boost/simd/sdk/memory/aligned_type.hpp>
#include <boost/mpl/int.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/basic.hpp>
#include <nt2/sdk/unit/tests/exceptions.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <exception>

////////////////////////////////////////////////////////////////////////////////
// Test unaligned_load behavior
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE_TPL(unaligned_load, BOOST_SIMD_SIMD_TYPES )
{
  using boost::simd::load;
  using boost::simd::unaligned_load; 
  using boost::simd::native;
  using boost::simd::meta::cardinal_of;

  typedef BOOST_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef native<T,ext_t>             n_t;

  T data[3*cardinal_of<n_t>::value];
  for(std::size_t i=0;i<3*cardinal_of<n_t>::value;++i)
    data[i] = T(1+i);

  for(std::size_t i=0;i<3;++i)
  {
    n_t v = unaligned_load<n_t>(&data[0],i);
    for(std::size_t j=0;j<cardinal_of<n_t>::value;++j)
    {
      NT2_TEST_EQUAL( v[j], 1+i*cardinal_of<n_t>::value+j );
    }
  }
}

////////////////////////////////////////////////////////////////////////////////
// Test load behavior
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE_TPL(load, BOOST_SIMD_SIMD_TYPES )
{
  using boost::simd::load;
  using boost::simd::native;
  using boost::simd::meta::cardinal_of;

  typedef BOOST_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef native<T,ext_t>             n_t;

  BOOST_SIMD_ALIGNED_TYPE(T) data[3*cardinal_of<n_t>::value];
  for(std::size_t i=0;i<3*cardinal_of<n_t>::value;++i)
    data[i] = T(1+i);

  n_t v;

  for(std::size_t i=0;i<3;++i)
  {
    v = load<n_t>(&data[0],i);
    for(std::size_t j=0;j<cardinal_of<n_t>::value;++j)
    {
      NT2_TEST_EQUAL( v[j], 1+i*cardinal_of<n_t>::value+j );
    }
  }

#ifdef NT2_ASSERTS_AS_EXCEPTIONS
  NT2_TEST_NO_THROW( v = load<n_t>(&data[0],0) );
  NT2_TEST_THROW( v = load<n_t>((&data[0]+1),0), nt2::assert_exception);
#endif

}

////////////////////////////////////////////////////////////////////////////////
// Test forward periodic case -- load 1 and 2 cardinal in front
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE_TPL(shifted_load_fwd_periodic, BOOST_SIMD_SIMD_TYPES )
{
  using boost::simd::load;
  using boost::simd::native;
  using boost::simd::meta::cardinal_of;

  typedef BOOST_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef native<T,ext_t>             n_t;
  n_t v;

  BOOST_SIMD_ALIGNED_TYPE(T) data[3*cardinal_of<n_t>::value];
   for(std::size_t i=0;i<3*cardinal_of<n_t>::value;++i)
     data[i] = T(1+i);

   v = load<n_t,1*cardinal_of<n_t>::value>(&data[0],0);
   for(std::size_t j=0;j<cardinal_of<n_t>::value;++j)
     NT2_TEST_EQUAL( v[j], data[j+1*cardinal_of<n_t>::value] );

   v = load<n_t,2*cardinal_of<n_t>::value>(&data[0],0);
   for(std::size_t j=0;j<cardinal_of<n_t>::value;++j)
     NT2_TEST_EQUAL( v[j], data[j+2*cardinal_of<n_t>::value] );
 }

 ////////////////////////////////////////////////////////////////////////////////
 // Test non-periodic case -- load up to cardinal-1 front
 ////////////////////////////////////////////////////////////////////////////////
 NT2_TEST_CASE_TPL(shifted_load_non_periodic, BOOST_SIMD_SIMD_TYPES )
 {
   using boost::simd::load;
   using boost::simd::native;
   using boost::simd::meta::cardinal_of;

   typedef BOOST_SIMD_DEFAULT_EXTENSION  ext_t;
   typedef native<T,ext_t>             n_t;
   n_t v;

   BOOST_SIMD_ALIGNED_TYPE(T) data[3*cardinal_of<n_t>::value];
   for(std::size_t i=0;i<3*cardinal_of<n_t>::value;++i)
     data[i] = T(1+i);

   v = load<n_t,1>(&data[0],1);
   for(std::size_t j=0;j<cardinal_of<n_t>::value;++j)
     NT2_TEST_EQUAL( v[j], data[j+cardinal_of<n_t>::value+1] );

   v = load<n_t,-1>(&data[0],1);
   for(std::size_t j=0;j<cardinal_of<n_t>::value;++j)
     NT2_TEST_EQUAL( v[j], data[j+cardinal_of<n_t>::value-1] );
 }

 ////////////////////////////////////////////////////////////////////////////////
 // Test backward periodic case -- load 1 and 2 cardinal in front
 ////////////////////////////////////////////////////////////////////////////////
 NT2_TEST_CASE_TPL(shifted_load_bkwd_periodic, BOOST_SIMD_SIMD_TYPES )
 {
   using boost::simd::load;
   using boost::simd::native;
   using boost::simd::meta::cardinal_of;

   typedef BOOST_SIMD_DEFAULT_EXTENSION  ext_t;
   typedef native<T,ext_t>             n_t;
   n_t v;

   BOOST_SIMD_ALIGNED_TYPE(T) data[3*cardinal_of<n_t>::value];
   for(std::size_t i=0;i<3*cardinal_of<n_t>::value;++i)
     data[i] = T(1+i);

   v = load<n_t,-1*int(cardinal_of<n_t>::value)>(&data[0],2);
   for(std::size_t j=0;j<cardinal_of<n_t>::value;++j)
     NT2_TEST_EQUAL( v[j], data[j+cardinal_of<n_t>::value] );

   v = load<n_t,-2*int(cardinal_of<n_t>::value)>(&data[0],2);
   for(std::size_t j=0;j<cardinal_of<n_t>::value;++j)
     NT2_TEST_EQUAL( v[j], data[j] );
 }

////////////////////////////////////////////////////////////////////////////////
// Test store behavior
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE_TPL(store, BOOST_SIMD_SIMD_TYPES )
{
  using boost::simd::store;
  using boost::simd::load;
  using boost::simd::native;
  using boost::simd::meta::cardinal_of;

  typedef BOOST_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef native<T,ext_t>             n_t;
  BOOST_SIMD_ALIGNED_TYPE(T) data[2*cardinal_of<n_t>::value];
  for(std::size_t i=0;i<cardinal_of<n_t>::value;++i)
    data[i] = T(1+i);
  std::cout << ((nt2::int64_t)(&data[0]))%32 << std::endl; 
  n_t v = load<n_t>(&data[0],0);
  store(v,&data[0],1);

  for(std::size_t j=0;j<cardinal_of<n_t>::value;++j)
  {
    NT2_TEST_EQUAL( data[j], data[j+cardinal_of<n_t>::value] );
  }

#ifdef NT2_ASSERTS_AS_EXCEPTIONS
  NT2_TEST_NO_THROW( v = store<n_t>(v,&data[0],1) );
  NT2_TEST_THROW( v = store<n_t>(v,&data[0]+1,1), nt2::assert_exception);
#endif
}

////////////////////////////////////////////////////////////////////////////////
// Test unaligned_store behavior
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE_TPL(unaligned_store, BOOST_SIMD_SIMD_TYPES )
{
   using boost::simd::unaligned_store;
   using boost::simd::unaligned_load;
   using boost::simd::native;
   using boost::simd::meta::cardinal_of;

   typedef BOOST_SIMD_DEFAULT_EXTENSION  ext_t;
   typedef native<T,ext_t>             n_t;
   T data[2*cardinal_of<n_t>::value];
   for(std::size_t i=0;i<cardinal_of<n_t>::value;++i)
     data[i] = T(1+i);
   std::cout << ((nt2::int64_t)(&data[0]))%32 << std::endl;
   n_t v = unaligned_load<n_t>(&data[0],0);
   unaligned_store(v,&data[0],1);

   for(std::size_t j=0;j<cardinal_of<n_t>::value;++j)
   {
     NT2_TEST_EQUAL( data[j], data[j+cardinal_of<n_t>::value] );
   }
}

