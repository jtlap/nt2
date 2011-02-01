//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#define NT2_UNIT_MODULE "nt2 ieee toolbox - unit/simd Mode"

#include <nt2/include/functions/nextpow2.hpp>
#include <nt2/sdk/unit/tests.hpp>   
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/simd/native.hpp>
#include <nt2/sdk/memory/is_aligned.hpp>
#include <nt2/sdk/memory/aligned_type.hpp>
#include <nt2/sdk/memory/load.hpp> 
#include <nt2/sdk/functor/meta/call.hpp>
#include <boost/type_traits/is_same.hpp> 
#include <nt2/sdk/meta/as_real.hpp>
#include <nt2/include/functions/random.hpp>

#include <iostream>
//////////////////////////////////////////////////////////////////////////////
// Test behavior of arithmetic component nextpow2 using NT2_TEST_CASE
//////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE_TPL(nextpow2, 
              NT2_SIMD_TYPES
                         )
{ 
 using nt2::nextpow2; 
 using nt2::tag::nextpow2_;  
 using nt2::load;  
 using nt2::simd::native;  
 using nt2::meta::cardinal_of; 

 typedef NT2_SIMD_DEFAULT_EXTENSION  ext_t;
 typedef native<T,ext_t>             n_t;
 typedef typename nt2::meta::call<nextpow2_(n_t)>::type call_type;

 NT2_TEST( (boost::is_same<call_type, n_t>::value) );
 NT2_ALIGNED_TYPE(T) data[1*cardinal_of<n_t>::value];
 for(int i=0;i<1*cardinal_of<n_t>::value;++i) 
   data[i] = i; //nt2::random(0.0, 100.0); // good value here for nextpow2

 n_t a0 = load<n_t>(&data[0],0);  
 n_t v  = nt2::nextpow2(a0); 
 for(std::size_t j=0;j<cardinal_of<n_t>::value;++j)
   { 
     NT2_TEST_EQUAL( v[j], nextpow2(a0[j]) );
     std::cout << "a0[" << j << "] " << int(a0[j]) << std::endl; 
     std::cout << "v[" << j << "]  " << int(v[j]) << "scal " << int(nextpow2(a0[j])) << std::endl; 
   } 
} 

// NT2_TEST_CASE_TPL(signed_nextpow2, 
//               NT2_SIMD_SIGNED_TYPES
//                          ) 
// {
//  using nt2::nextpow2; 
//  using nt2::tag::nextpow2_;
//  using nt2::load;  
//  using nt2::simd::native;
//  using nt2::meta::cardinal_of; 

//  typedef NT2_SIMD_DEFAULT_EXTENSION  ext_t;
//  typedef native<T,ext_t>             n_t;
//  typedef typename nt2::meta::call<nextpow2_(n_t)>::type call_type;

//  NT2_TEST( (boost::is_same<call_type, n_t>::value) );
//  NT2_ALIGNED_TYPE(T) data[1*cardinal_of<n_t>::value];
//  for(int i=0;i<1*cardinal_of<n_t>::value;++i) 
//    data[i] =nt2::random(-100.0, 100.0); // good value here for nextpow2

//  n_t a0 = load<n_t>(&data[0],0);  
//  n_t v  = nt2::nextpow2(a0); 
//  for(std::size_t j=0;j<cardinal_of<n_t>::value;++j)
//    { 
//      NT2_TEST_EQUAL( v[j], nextpow2(a0[j]) );
//      std::cout << "a0[" << j << "] " << int(a0[j]) << std::endl; 
//      std::cout << "v[" << j << "]  " << int(v[j]) << "scal " << int(nextpow2(a0[j])) << std::endl; 
//    } 
// }

 
 
 
 
