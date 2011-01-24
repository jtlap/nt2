//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#define NT2_UNIT_MODULE "nt2 arithmetic toolbox - unit/simd Mode"

#include <nt2/toolbox/arithmetic/include/sqrt.hpp>
#include <nt2/toolbox/arithmetic/include/random.hpp> 
#include <nt2/sdk/unit/tests.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/simd/native.hpp>
#include <nt2/sdk/memory/is_aligned.hpp>
#include <nt2/sdk/memory/aligned_type.hpp>
#include <nt2/sdk/memory/load.hpp>
#include <nt2/sdk/functor/meta/call.hpp>
#include <boost/type_traits/is_same.hpp>
#include <nt2/sdk/constant/digits.hpp>

//////////////////////////////////////////////////////////////////////////////
// Test behavior of arithmetic components using NT2_TEST_CASE
//////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE_TPL(sqrt, NT2_SIMD_TYPES )
{
 using nt2::sqrt;
 using nt2::tag::sqrt_;     
 using nt2::load; 
 using nt2::simd::native;   
 using nt2::meta::cardinal_of; 

 typedef NT2_SIMD_DEFAULT_EXTENSION  ext_t;
 typedef native<T,ext_t>             n_t;
 typedef typename nt2::meta::call<sqrt_(n_t)>::type call_type;

 NT2_TEST( (boost::is_same<call_type, n_t>::value) );  
 NT2_ALIGNED_TYPE(T) data[1*cardinal_of<n_t>::value];
 for(int n = 0;  n <128; n+= 16){
   for(int i=0;i<1*cardinal_of<n_t>::value;++i){
     data[i] = nt2::random(0, 127); // good value here for sqrt
   }
   n_t a0 = load<n_t>(&data[0],0); 
   n_t v  = sqrt(a0);
   for(int j=0;j<cardinal_of<n_t>::value;++j)
     {
       NT2_TEST_EQUAL( v[j], T(nt2::sqrt(a0[j])) );
     }
 }

}
  
 
 
  
