//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#define NT2_UNIT_MODULE "nt2 ieee toolbox - unit/simd Mode"
#include <boost/fusion/include/at.hpp>
#include <boost/fusion/include/vector.hpp>
 
#include <nt2/include/functions/frexp.hpp>
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
// Test behavior of arithmetic component frexp using NT2_TEST_CASE
//////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE_TPL(frexp, 
              NT2_SIMD_REAL_TYPES
                         )
{
 using nt2::frexp; 
 using nt2::tag::frexp_;
 using nt2::load;  
 using nt2::simd::native;
 using nt2::meta::cardinal_of; 

 typedef NT2_SIMD_DEFAULT_EXTENSION  ext_t;
 typedef native<T,ext_t>             n_t;
 typedef n_t                                                     mantissa;
 typedef typename nt2::meta::as_integer<T,signed>::type         sexponent;
 typedef native<sexponent,ext_t>                                 exponent;
 
 typedef boost::fusion::vector<mantissa,exponent>                     rn_t;
 typedef boost::fusion::vector<T,sexponent>                           sn_t;

 typedef typename nt2::meta::call<frexp_(n_t)>::type call_type;

  
 NT2_TEST( (boost::is_same<call_type, rn_t>::value) );
 NT2_ALIGNED_TYPE(T) data[1*cardinal_of<n_t>::value];
 for(std::size_t i=0;i<1*cardinal_of<n_t>::value;++i)
   data[i] = nt2::random(-10.0, 10.0); // good value here for frexp

 n_t a0 = load<n_t>(&data[0],0);  
 rn_t r = nt2::frexp(a0);
 for(std::size_t j=0;j<cardinal_of<n_t>::value;++j)
   {
     sn_t m =  frexp(a0[j]); 
     NT2_TEST_EQUAL(  boost::fusion::at_c<0>(r)[j], boost::fusion::at_c<0>(m));
     NT2_TEST_EQUAL(  boost::fusion::at_c<1>(r)[j], boost::fusion::at_c<1>(m));
   } 
}

