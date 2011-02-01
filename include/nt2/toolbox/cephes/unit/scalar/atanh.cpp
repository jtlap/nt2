//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#define NT2_UNIT_MODULE "nt2 cephes toolbox - unit/scalar Mode"

#include <nt2/sdk/functor/meta/call.hpp> 
#include <boost/type_traits/is_same.hpp>
#include <nt2/toolbox/cephes/include/atanh.hpp> 
#include <nt2/sdk/unit/tests.hpp> 
#include <nt2/sdk/unit/module.hpp>
#include <nt2/include/functions/is_nan.hpp>
#include <nt2/sdk/constant/real.hpp>
#include <nt2/sdk/constant/infinites.hpp>
#include <nt2/include/functions/ulpdist.hpp>
#include <nt2/include/functions/tanh.hpp>
#include <iostream>
#include <iomanip>

//////////////////////////////////////////////////////////////////////////////
// Test behavior of arithmetic components using NT2_TEST_CASE
//////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE_TPL ( atanh, (double) 
                (float) 
                )
{
  using nt2::cephes::atanh; 
  using nt2::cephes::tag::atanh_;
  const int N = 2; 
   NT2_TEST( (boost::is_same < typename nt2::meta::call<atanh_(T)>::type
            , T
            >::value)
           );
   typedef typename boost::result_of<nt2::meta::floating(T)>::type r_t; 
   NT2_TEST_EQUAL(  nt2::cephes::atanh( T(0) )  , 0 );
   NT2_TEST_EQUAL(  nt2::cephes::atanh( T(1) )  , nt2::Inf<T>());
   NT2_TEST      (  nt2::is_nan(nt2::cephes::atanh(nt2::Nan<T>()) )); 
   NT2_TEST_LESSER_EQUAL(  nt2::ulpdist(nt2::cephes::atanh( T(0.5) )  , T(0.549306144334055)), 1);

T t[] ={   9.990013313365279e-04,     4.997501665417665e-04,     3.332222715802601e-04, 
         2.499375208255240e-04,     1.999600106634677e-04,     1.666388950601856e-04,     1.428367385803140e-04, 
         1.249843776036784e-04,     1.110987672607835e-04}; 


T v[] ={  9.990009990009990e-04,     4.997501249375312e-04,     3.332222592469177e-04, 
        2.499375156210947e-04,     1.999600079984003e-04,     1.666388935177471e-04,     1.428367376089130e-04, 
        1.249843769528809e-04,     1.110987668036885e-04}; 

 

   for(int i=0; i < 9; i++) 
     {
       NT2_TEST_LESSER_EQUAL(nt2::ulpdist(nt2::cephes::atanh(v[i]), t[i]), 3);
       std::cout << std::setprecision(16) << v[i] << "  " << nt2::cephes::atanh(v[i]) << "  " << t[i] << std::endl; 
     }
}
