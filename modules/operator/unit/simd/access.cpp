/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 0x01.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#define NT2_UNIT_MODULE "nt2::memory::load and store SIMD"

#include <nt2/include/functions/load.hpp>
#include <nt2/include/functions/store.hpp>
#include <nt2/sdk/meta/cardinal_of.hpp>
#include <nt2/sdk/memory/is_aligned.hpp>
#include <nt2/sdk/memory/aligned_type.hpp>
#include <nt2/include/functions/unaligned_load.hpp>
#include <nt2/include/functions/unaligned_store.hpp>

#include <boost/mpl/int.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/basic.hpp>
#include <nt2/sdk/unit/module.hpp>
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
  static const std::size_t card = cardinal_of<n_t>::value;
  
  T data[3*card];
  for(std::size_t i=0;i<3*card;++i)
    data[i] = T(1+i);

  for(std::size_t i=0;i<3*card;i+=card)
  {
    n_t v = unaligned_load<n_t>(&data[0],i);
    for(std::size_t j=0;j<card;++j)
    {
      NT2_TEST_EQUAL( v[j], 1+i+j );
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
  static const std::size_t card = cardinal_of<n_t>::value;

  BOOST_SIMD_ALIGNED_TYPE(T) data[3*card];
  for(std::size_t i=0;i<3*card;++i)
    data[i] = T(1+i);

  n_t v;

  for(std::size_t i=0;i<3*card;i+=card)
  {
    v = load<n_t>(&data[0],i);
    for(std::size_t j=0;j<cardinal_of<n_t>::value;++j)
    {
      NT2_TEST_EQUAL( v[j], 1+i+j );
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
  static const std::size_t card = cardinal_of<n_t>::value;
  n_t v;

  BOOST_SIMD_ALIGNED_TYPE(T) data[3*card];
   for(std::size_t i=0;i<3*card;++i)
     data[i] = T(1+i);

   v = load<n_t,1*card>(&data[0],0);
   for(std::size_t j=0;j<card;++j)
     NT2_TEST_EQUAL( v[j], data[j+1*card] );

   v = load<n_t,2*card>(&data[0],0);
   for(std::size_t j=0;j<card;++j)
     NT2_TEST_EQUAL( v[j], data[j+2*card] );
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
   static const std::size_t card = cardinal_of<n_t>::value;
   n_t v;

   BOOST_SIMD_ALIGNED_TYPE(T) data[3*card];
   for(std::size_t i=0;i<3*card;++i)
     data[i] = T(1+i);

   v = load<n_t,1>(&data[0],card);
   for(std::size_t j=0;j<card;++j)
     NT2_TEST_EQUAL( v[j], data[j+card+1] );

   v = load<n_t,-1>(&data[0],card);
   for(std::size_t j=0;j<card;++j)
     NT2_TEST_EQUAL( v[j], data[j+card-1] );
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
   static const std::size_t card = cardinal_of<n_t>::value;
   n_t v;

   BOOST_SIMD_ALIGNED_TYPE(T) data[3*card];
   for(std::size_t i=0;i<3*card;++i)
     data[i] = T(1+i);

   v = load<n_t,-1*int(card)>(&data[0],2*card);
   for(std::size_t j=0;j<card;++j)
     NT2_TEST_EQUAL( v[j], data[j+card] );

   v = load<n_t,-2*int(card)>(&data[0],2*card);
   for(std::size_t j=0;j<card;++j)
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
  static const std::size_t card = cardinal_of<n_t>::value;
  
  BOOST_SIMD_ALIGNED_TYPE(T) data[3*card];
  for(std::size_t i=0;i<card;++i)
    data[i] = T(1+i);
  std::cout << ((nt2::int64_t)(&data[0]))%32 << std::endl; 
  n_t v = load<n_t>(&data[0],0);
  store(v,&data[0],card);

  for(std::size_t j=0;j<card;++j)
  {
    NT2_TEST_EQUAL( data[j], data[j+card] );
  }

#ifdef NT2_ASSERTS_AS_EXCEPTIONS
  NT2_TEST_NO_THROW( v = store<n_t>(v,&data[0],card) );
  NT2_TEST_THROW( v = store<n_t>(v,&data[0]+1,card), nt2::assert_exception);
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
   static const std::size_t card = cardinal_of<n_t>::value;
   
   T data[2*card];
   for(std::size_t i=0;i<card;++i)
     data[i] = T(1+i);
   std::cout << ((nt2::int64_t)(&data[0]))%32 << std::endl;
   n_t v = unaligned_load<n_t>(&data[0],0);
   unaligned_store(v,&data[0],card);

   for(std::size_t j=0;j<card;++j)
   {
     NT2_TEST_EQUAL( data[j], data[j+card] );
   }
}

