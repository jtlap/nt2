//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#define NT2_UNIT_MODULE "nt2 polynomials toolbox - unit/simd Mode"
#include <nt2/toolbox/polynomials/include/legendre.hpp>
#include <nt2/include/functions/random.hpp>
#include <nt2/include/functions/ulpdist.hpp>
#include <nt2/sdk/unit/tests.hpp>   
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/simd/native.hpp>
#include <nt2/sdk/memory/is_aligned.hpp>
#include <nt2/sdk/memory/aligned_type.hpp>
#include <nt2/sdk/memory/load.hpp>  
#include <nt2/sdk/functor/meta/call.hpp>
#include <boost/type_traits/is_same.hpp> 
#include <nt2/sdk/meta/as_integer.hpp>
#include <iostream>
//////////////////////////////////////////////////////////////////////////////
// Test behavior of arithmetic component legendre using NT2_TEST_CASE
//////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE_TPL(legendre, (float)(double)
                         )
{
 using nt2::legendre; 
 using nt2::tag::legendre_;
 using nt2::load;  
 using nt2::simd::native; 
 using nt2::meta::cardinal_of; 

 typedef NT2_SIMD_DEFAULT_EXTENSION  ext_t;
 typedef native<T,ext_t>             n_t;
 typedef typename nt2::meta::call<legendre_(int32_t, n_t)>::type call_type;
 typedef typename nt2::meta::as_real<T>::type rT; 
 typedef native<rT,ext_t>            rn_t;
  
 NT2_TEST( (boost::is_same<call_type, rn_t>::value) );
 NT2_ALIGNED_TYPE(T) data[1*cardinal_of<n_t>::value];

 for(std::size_t i=0;i<1*cardinal_of<n_t>::value;++i)
   data[i] =nt2::random(-1.0, 1.0); // good value here for legendre

 n_t a0 = load<n_t>(&data[0],0);  
 for(int ii = 0; ii < 5; ii++)
   {
      rn_t v  = nt2::legendre(ii, a0);
      for(std::size_t j=0;j<cardinal_of<n_t>::value;++j)
        { 
        NT2_TEST_LESSER_EQUAL( nt2::ulpdist(v[j], legendre(ii, a0[j])), 1);
	//        std::cout << a0[j] << "  " << v[j] << "  " << legendre(ii, a0[j]) << std::endl; 
        } 
   } 
} 
 
