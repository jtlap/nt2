//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#define NT2_UNIT_MODULE "nt2 reduction toolbox - unit/simd Mode"

#include <nt2/toolbox/reduction/include/sum.hpp>
#include <nt2/sdk/constant/digits.hpp>
#include <nt2/sdk/unit/tests.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/simd/native.hpp>
#include <nt2/sdk/memory/is_aligned.hpp>
#include <nt2/sdk/memory/aligned_type.hpp>
#include <nt2/sdk/memory/load.hpp>
#include <nt2/sdk/functor/meta/call.hpp>
#include <boost/type_traits/is_same.hpp>
#include <nt2/include/functions/random.hpp>
#include <nt2/include/functions/boolean.hpp>
#include <nt2/include/functions/hmsb.hpp>
#include <nt2/include/functions/is_eqz.hpp> 
#include <nt2/include/functions/ulpdist.hpp> 
#include <iostream>

//////////////////////////////////////////////////////////////////////////////
// Test behavior of arithmetic components using NT2_TEST_CASE
//////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE_TPL(sum, NT2_SIMD_INTEGRAL_TYPES )
{
 using nt2::sum;
 using nt2::tag::sum_;    
 using nt2::load;  
 using nt2::simd::native; 
 using nt2::meta::cardinal_of;

 typedef NT2_SIMD_DEFAULT_EXTENSION  ext_t;    
 typedef native<T,ext_t>             n_t;
 typedef typename nt2::meta::call<sum_(n_t)>::type call_type;
 typedef typename boost::result_of<nt2::meta::arithmetic(T)>::type rn_t; 

 NT2_TEST( (boost::is_same<call_type, rn_t>::value) );
 std::cout <<" type_id <rn_t>()       "<< nt2::type_id <rn_t>()      << std::endl;
 std::cout <<" type_id <call_type>()  "<< nt2::type_id <call_type>() << std::endl; 
 NT2_ALIGNED_TYPE(T) data[1*cardinal_of<n_t>::value];
 for(int j =  0;  j < 10; j++)
   {
     for(std::size_t i=0;i<1*cardinal_of<n_t>::value;++i){
       data[i] = nt2::random(-10000.0, 10000.0); // good value here for sum
     }
     n_t a0 = load<n_t>(&data[0],0); 
     T v = sum(a0);
     T z = 0; 
     for(std::size_t j=0;j<cardinal_of<n_t>::value;++j)
       { 
       z += (a0[j]); 
       }
     NT2_TEST_EQUAL(z, v);
     std::cout << z-v << std::endl;
     std::cout << nt2::ulpdist(z, v) << std::endl; 
   }
}
NT2_TEST_CASE_TPL(real_sum, NT2_REAL_TYPES )
{
 using nt2::sum;
 using nt2::tag::sum_;    
 using nt2::load;  
 using nt2::simd::native; 
 using nt2::meta::cardinal_of;

 typedef NT2_SIMD_DEFAULT_EXTENSION  ext_t;    
 typedef native<T,ext_t>             n_t;
 typedef typename nt2::meta::call<sum_(n_t)>::type call_type;
 typedef typename boost::result_of<nt2::meta::arithmetic(T)>::type rn_t; 

 NT2_TEST( (boost::is_same<call_type, rn_t>::value) );
 std::cout <<" type_id <rn_t>()       "<< nt2::type_id <rn_t>()      << std::endl;
 std::cout <<" type_id <call_type>()  "<< nt2::type_id <call_type>() << std::endl; 
 NT2_ALIGNED_TYPE(T) data[1*cardinal_of<n_t>::value];
 for(int j =  0;  j < 10; j++)
   {
     for(std::size_t i=0;i<1*cardinal_of<n_t>::value;++i){
       data[i] = nt2::random(-1000.0, 1000.0); // good value here for sum
     }
     n_t a0 = load<n_t>(&data[0],0); 
     T v  = sum(a0);
     T z = 0; 
     for(std::size_t j=0;j<cardinal_of<n_t>::value;++j)
       { 
       z += (a0[j]); 
       }
     NT2_TEST_LESSER_EQUAL(nt2::ulpdist(z, v), 1);
   }
}

 

 
