//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
/// 
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt 
//////////////////////////////////////////////////////////////////////////////
#define NT2_UNIT_MODULE "nt2 boost.simd.swar toolbox - permute/simd Mode"

//////////////////////////////////////////////////////////////////////////////
// unit test behavior of boost.simd.swar components in simd mode
//////////////////////////////////////////////////////////////////////////////
/// created  by jt the 24/02/2011
/// 
#include <boost/simd/toolbox/swar/include/functions/permute.hpp>
#include <boost/simd/toolbox/swar/include/functions/arith.hpp>
#include <boost/simd/include/functions/ulpdist.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/dispatch/functor/meta/call.hpp>
#include <nt2/sdk/unit/tests.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <boost/simd/sdk/memory/buffer.hpp>
#include <boost/simd/toolbox/constant/constant.hpp>
#include <boost/simd/sdk/memory/is_aligned.hpp>
#include <boost/simd/sdk/memory/aligned_type.hpp>
#include <boost/simd/include/functions/load.hpp>
#include <boost/simd/sdk/meta/cardinal_of.hpp> 
#include <boost/simd/include/functions/make.hpp>

#ifndef BOOST_SIMD_HAS_AVX_SUPPORT
NT2_TEST_CASE_TPL ( permute_32l__2_0, (float)(int32_t)(uint32_t))
{
  using boost::simd::permute;
  using boost::simd::tag::permute_;
  using boost::simd::load; 
  using boost::simd::native;
  using boost::simd::meta::cardinal_of;
  typedef BOOST_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef typename boost::dispatch::meta::upgrade<T>::type   u_t;
  typedef native<T,ext_t>                        n_t;
  typedef n_t                                     vT;
  typedef typename boost::dispatch::meta::as_integer<T>::type iT;
  typedef native<iT,ext_t>                       ivT;

  std::size_t n = vT::static_size-1; 
  // specific values tests
  T s =  0;
  T h = 1;
  vT a0 =  boost::simd::arith<vT>(s, h); 
  vT a1 = permute<3, 2, 1, 0>(a0);
  vT a2 = permute<-3, -2, -1, -1>(a0); 
  std::cout << a0 << " -> " << a1 << std::endl; 
  for(std::size_t i=0; i < vT::static_size;++i)
    {
      NT2_TEST_EQUAL(a1[i], T(n-i));
      NT2_TEST_EQUAL(a2[i], T(0)); 
    }
  vT a3 =  boost::simd::make<vT>(1, 1, 0, 0);
  vT a4 =  permute<1, 1, -1, -1>(a0); 
  std::cout << a0 << " -> " << a4 << " expected " << a3 << std::endl; 
  for(std::size_t i=0; i < vT::static_size;++i)
    {
      NT2_TEST_EQUAL(a3[i], a4[i]);
    } 

  a3 =  boost::simd::make<vT>(0, 0, 3, 2);
  a4 =  permute<-1, -1, 3, 2>(a0); 
  std::cout << a0 << " -> " << a4 << " expected " << a3 << std::endl; 
  for(std::size_t i=0; i < vT::static_size;++i)
    {
      NT2_TEST_EQUAL(a3[i], a4[i]); 
    }
  
  a3 =  boost::simd::make<vT>(2, 0, 1, 2);
  a4 =  permute<2, -1, 1, 2>(a0);      
  std::cout << a0 << " -> " << a4 << " expected " << a3 << std::endl; 
  for(std::size_t i=0; i < vT::static_size;++i)
    {
      NT2_TEST_EQUAL(a3[i], a4[i]); 
    }
  
  a3 =  boost::simd::make<vT>(0, 0, 0, 0);
  a4 =  permute<-1, -1, -1, 0>(a0); 
  std::cout << a0 << " -> " << a4 << " expected " << a3 << std::endl; 
  for(std::size_t i=0; i < vT::static_size;++i)  
    {
      NT2_TEST_EQUAL(a3[i], a4[i]); 
    }
  a3 =  boost::simd::make<vT>(0, 0, 0, 0);
  a4 =  permute<-1, -1, -1, -1>(a0); 
  std::cout << a0 << " -> " << a4 << " expected " << a3 << std::endl; 
  for(std::size_t i=0; i < vT::static_size;++i)  
    {
      NT2_TEST_EQUAL(a3[i], a4[i]); 
    }
  a3 =  boost::simd::make<vT>(2, 3, 0, 1);
  a4 =  permute<2, 3, 0, 1>(a0); 
  std::cout << a0 << " -> " << a4 << " expected " << a3 << std::endl; 
  for(std::size_t i=0; i < vT::static_size;++i)  
    {
      NT2_TEST_EQUAL(a3[i], a4[i]); 
    }
    
} // end of test


NT2_TEST_CASE_TPL ( permute_64__2_0, (int64_t)(uint64_t)(double))
{
  using boost::simd::permute;
  using boost::simd::tag::permute_;
  using boost::simd::load; 
  using boost::simd::native;
  using boost::simd::meta::cardinal_of;
  typedef BOOST_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef typename boost::dispatch::meta::upgrade<T>::type   u_t;
  typedef native<T,ext_t>                        n_t;
  typedef n_t                                     vT;

  std::size_t n = vT::static_size-1; 
  // specific values tests
  T s = 2;
  T h = 1;
  vT a0 =  boost::simd::arith<vT>(s, h);
   
  vT a3 =  boost::simd::make<vT>(3, 0);
  vT a4 =  permute<1, -1>(a0); 
  std::cout << a0 << " -> " << a4 << " expected " << a3 << std::endl; 
  for(std::size_t i=0; i < vT::static_size;++i)
    {
      NT2_TEST_EQUAL(a3[i], a4[i]);
    } 

  a3 =  boost::simd::make<vT>(3, 3);
  a4 =  permute<1, 1>(a0); 
  std::cout << a0 << " -> " << a4 << " expected " << a3 << std::endl; 
  for(std::size_t i=0; i < vT::static_size;++i)
    {
      NT2_TEST_EQUAL(a3[i], a4[i]);
    }
  
  a3 =  boost::simd::make<vT>(0, 2);
  a4 =  permute<-1, 0>(a0); 
  std::cout << a0 << " -> " << a4 << " expected " << a3 << std::endl; 
  for(std::size_t i=0; i < vT::static_size;++i)
    {
      NT2_TEST_EQUAL(a3[i], a4[i]);
    }
  
  a3 =  boost::simd::make<vT>(0, 0);
  a4 =  permute<-1, -1>(a0); 
  std::cout << a0 << " -> " << a4 << " expected " << a3 << std::endl; 
  for(std::size_t i=0; i < vT::static_size;++i)
    {
      NT2_TEST_EQUAL(a3[i], a4[i]);
    } 
   
} // end of test



// NT2_TEST_CASE_TPL ( permute_16__2_0, (int16_t)(uint16_t))
// {
//   using boost::simd::permute;
//   using boost::simd::tag::permute_;
//   using boost::simd::load; 
//   using boost::simd::native;
//   using boost::simd::meta::cardinal_of;
//   typedef BOOST_SIMD_DEFAULT_EXTENSION  ext_t;
//   typedef typename boost::dispatch::meta::upgrade<T>::type   u_t;
//   typedef native<T,ext_t>                        n_t;
//   typedef n_t                                     vT;

//   std::size_t n = vT::static_size-1; 
//   // specific values tests
//   T s =  0;
//   T h = 1;
//   vT a0 =  boost::simd::arith<vT>(s, h);
//   vT a1 = permute<7, 6, 5, 4, 3, 2, 1, 0>(a0);
//   vT a2 = permute<-3, -2, -1, -1, -3, -2, -1, -1>(a0); 
//   std::cout << a0 << " -> " << a1 << std::endl; 
//   for(std::size_t i=0; i < vT::static_size;++i)
//     {
//       NT2_TEST_EQUAL(a1[i], T(n-i));
//       NT2_TEST_EQUAL(a2[i], T(0)); 
//     }
// } // end of test
#endif

#ifdef BOOST_SIMD_HAS_AVX_SUPPORT
NT2_TEST_CASE_TPL ( permute_32l__2_0, (double)(int64_t)(uint64_t))
{
  using boost::simd::permute;
  using boost::simd::tag::permute_;
  using boost::simd::load; 
  using boost::simd::native;
  using boost::simd::meta::cardinal_of;
  typedef BOOST_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef typename boost::dispatch::meta::upgrade<T>::type   u_t;
  typedef native<T,ext_t>                        n_t;
  typedef n_t                                     vT;
  typedef typename boost::dispatch::meta::as_integer<T>::type iT;
  typedef native<iT,ext_t>                       ivT;

  std::size_t n = vT::static_size-1; 
  // specific values tests
  T s =  0;
  T h = 1;
  vT a0 =  boost::simd::arith<vT>(s, h); 
  vT a1 = permute<3, 2, 1, 0>(a0);
  vT a2 = permute<-3, -2, -1, -1>(a0); 
  std::cout << a0 << " -> " << a1 << std::endl; 
  for(std::size_t i=0; i < vT::static_size;++i)
    {
      NT2_TEST_EQUAL(a1[i], T(n-i));
      NT2_TEST_EQUAL(a2[i], T(0)); 
    }
} // end of test
#endif
