//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#define NT2_UNIT_MODULE "nt2 exponential toolbox - unit/simd Mode"

#include <nt2/toolbox/exponential/include/powi.hpp>
#include <nt2/sdk/unit/tests.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/simd/native.hpp>
#include <nt2/sdk/memory/is_aligned.hpp>
#include <nt2/sdk/memory/aligned_type.hpp>
#include <nt2/sdk/memory/load.hpp>
#include <nt2/sdk/functor/meta/call.hpp>
#include <boost/type_traits/is_same.hpp>
#include <nt2/include/functions/random.hpp>
#include <nt2/include/functions/ulpdist.hpp>
#include <iostream>

//////////////////////////////////////////////////////////////////////////////
// Test behavior of arithmetic components using NT2_TEST_CASE
//////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE_TPL(powi, (double)(float))//NT2_SIMD_REAL_CONVERTIBLE_TYPES )
{
 using nt2::powi;
 using nt2::tag::powi_;    
 using nt2::load; 
 using nt2::simd::native; 
 using nt2::meta::cardinal_of;

 typedef NT2_SIMD_DEFAULT_EXTENSION  ext_t;
 typedef native<T,ext_t>             n_t;
 typedef typename nt2::meta::as_real<T>::type rT;
 typedef native<rT,ext_t>             rn_t;
 typedef typename nt2::meta::as_integer<T>::type iT;
 typedef native<iT,ext_t>             in_t;
 typedef typename nt2::meta::call<powi_(n_t, in_t)>::type call_type;
 
   
 NT2_TEST( (boost::is_same<call_type, rn_t>::value) );  
 NT2_ALIGNED_TYPE(T) data[1*cardinal_of<n_t>::value];
 NT2_ALIGNED_TYPE(iT) datai[1*cardinal_of<n_t>::value];
 double z, m = 0; 
 for(int num = 0; num < 10; num++)
   {
     for(std::size_t i=0;i<1*cardinal_of<n_t>::value;++i){
       data[i] = nt2::random(0.0, 5.0); // good value here for powi
     }
     for(std::size_t i=0;i<1*cardinal_of<n_t>::value;++i){
       datai[i] = nt2::random(0, 10); // good value here for nthroot
     }
     n_t a0 = load<n_t>(&data[0],0); 
     in_t a1 = load<in_t>(&datai[0],0); 
     rn_t v  = powi(a0, a1);
     for(std::size_t j=0;j<cardinal_of<n_t>::value;++j)
       {
       NT2_TEST_LESSER( z = nt2::ulpdist(v[j], powi(a0[j], a1[j])), 10);
       if (z > m) m = z; 
       }
   }
std::cout << "ulp max = " << m << std::endl;
}

