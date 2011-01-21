//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#define NT2_UNIT_MODULE "nt2 swar toolbox - unit/simd Mode"

#include <nt2/toolbox/swar/include/lookup.hpp>
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
#include <nt2/include/functions/lookup.hpp> 
#include <nt2/include/functions/boolean.hpp> 
#include <iostream>

//////////////////////////////////////////////////////////////////////////////
// Test behavior of arithmetic components using NT2_TEST_CASE
//////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE_TPL(lookup, NT2_SIMD_TYPES )
{
 using nt2::lookup;
 using nt2::tag::lookup_;    
 using nt2::load;  
 using nt2::simd::native; 
 using nt2::meta::cardinal_of;

 typedef NT2_SIMD_DEFAULT_EXTENSION  ext_t;
 typedef native<T,ext_t>             n_t;
 typedef typename nt2::meta::as_integer<T>::type iT;
 typedef native<iT,ext_t>             in_t;
 typedef typename nt2::meta::call<lookup_(n_t, in_t)>::type call_type;
 NT2_TEST( (boost::is_same<call_type, n_t>::value) );  
 NT2_ALIGNED_TYPE(T) data[1*cardinal_of<n_t>::value];
 NT2_ALIGNED_TYPE(iT) data1[1*cardinal_of<in_t>::value];
 for(int j =  0;  j < 10; j++)
   {
     for(std::size_t i=0;i<1*cardinal_of<n_t>::value;++i){
       data[i] = nt2::random(-10000.0, 10000.0); // good value here for lookup
     }
     for(std::size_t i=0;i<1*cardinal_of<in_t>::value;++i){
       data1[i] = i; // good value here for lookup
     } 
     n_t a0 = load<n_t>(&data[0],0); 
     in_t a1 = load<in_t>(&data1[0],0); 
     std::cout << a1 << std::endl; 
     std::cout << a0 << std::endl; 
     n_t v  = lookup(a0, a1); 
     for(std::size_t j=0;j<cardinal_of<n_t>::value;++j)
       {
       std::cout << j << "  " << v[j] << "  " << int(a1[j]) << "  " << a0[a1[j]] << std::endl; 
       NT2_TEST_EQUAL(v[j], a0[a1[j]]);
       }
   }
}
