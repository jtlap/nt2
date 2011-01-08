//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#define NT2_UNIT_MODULE "nt2 ieee toolbox - unit/simd Mode"

#include <nt2/toolbox/ieee/include/ldexp.hpp>
#include <nt2/include/functions/random.hpp>
#include <nt2/sdk/unit/tests.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/simd/native.hpp>
#include <nt2/sdk/memory/is_aligned.hpp>
#include <nt2/sdk/memory/aligned_type.hpp>
#include <nt2/sdk/memory/load.hpp>
#include <nt2/sdk/functor/meta/call.hpp>
#include <boost/type_traits/is_same.hpp>

//////////////////////////////////////////////////////////////////////////////
// Test behavior of arithmetic components using NT2_TEST_CASE
//////////////////////////////////////////////////////////////////////////////

NT2_TEST_CASE_TPL(ldexp, NT2_SIMD_REAL_TYPES )
{
 using nt2::ldexp;
 using nt2::tag::ldexp_;    
 using nt2::load;  
 using nt2::simd::native; 
 using nt2::meta::cardinal_of;

 typedef NT2_SIMD_DEFAULT_EXTENSION  ext_t;
 typedef native<T,ext_t>             n_t;
 typedef typename nt2::meta::call<ldexp_(n_t, n_t)>::type call_type;
 typedef typename nt2::meta::as_integer<T>::type iT; 
 typedef typename nt2::meta::as_integer<n_t>::type in_t; 

  NT2_TEST( (boost::is_same<call_type, n_t>::value) );  
  NT2_ALIGNED_TYPE(T) data[1*cardinal_of<n_t>::value];
  NT2_ALIGNED_TYPE(iT) data1[1*cardinal_of<n_t>::value];
  for(int i=0;i<cardinal_of<n_t>::value;++i){    
    data[i] = nt2::random(-10.0, 10.0); // good value here for mantissa
    data1[i] = nt2::random(-10, 10); // good value here for exponent
  }
   n_t a0 = load<n_t>(&data[0],0);   
   in_t a1 = load<in_t>(&data1[0],0);
   n_t v  = ldexp(a0, a1);
   for(std::size_t j=0;j<cardinal_of<n_t>::value;++j) 
     {
       NT2_TEST_EQUAL( v[j], ldexp(a0[j], a1[j]) );
     }
 }
 
