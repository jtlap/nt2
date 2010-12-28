//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#define NT2_UNIT_MODULE "nt2 fdlibm toolbox - unit/scalar Mode"

#include <nt2/sdk/functor/meta/call.hpp> 
#include <boost/type_traits/is_same.hpp>
#include <nt2/toolbox/fdlibm/include/tanh.hpp> 
#include <nt2/sdk/unit/tests.hpp> 
#include <nt2/sdk/unit/module.hpp>
#include <nt2/include/functions/is_nan.hpp>
#include <nt2/sdk/constant/real.hpp>
#include <nt2/sdk/constant/infinites.hpp>
#include <nt2/include/functions/ulpdist.hpp>
#include <nt2/include/functions/atanh.hpp>
#include <iostream>
#include <iomanip>
//////////////////////////////////////////////////////////////////////////////
// Test behavior of arithmetic components using NT2_TEST_CASE
//////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE_TPL ( tanh, (double) 
                )
{
  using nt2::fdlibm::tanh; 
  using nt2::fdlibm::tag::tanh_;
  const int N = 2; 
   NT2_TEST( (boost::is_same < typename nt2::meta::call<tanh_(T)>::type
            , T
            >::value)
           );
   typedef typename boost::result_of<nt2::meta::floating(T)>::type r_t; 
   NT2_TEST_EQUAL(  nt2::fdlibm::tanh( T(0) ), 0);
   NT2_TEST_LESSER_EQUAL(  nt2::ulpdist(nt2::fdlibm::tanh( T(1) )  , T(0.761594155955765)), 1);
   NT2_TEST_EQUAL(  nt2::fdlibm::tanh(nt2::Inf<T>() ), nt2::One<T>());
   NT2_TEST_EQUAL(  nt2::fdlibm::tanh(nt2::Minf<T>() ), nt2::Mone<T>());
   NT2_TEST      (  nt2::is_nan(nt2::fdlibm::tanh(nt2::Nan<T>()) )); 

     T t[] ={  0.761594155955765,   0.462117157260010,   0.321512737531634,   0.244918662403709,   0.197375320224904, 
             0.165140412924629,   0.141893193766933,   0.124353001771596,   0.110656110524738,   0.099667994624956}; 


   for(int i=0; i < 9; i++) 
     {
       T x =  1.0/(i+1); 
       NT2_TEST_LESSER_EQUAL(nt2::ulpdist(nt2::fdlibm::tanh(x), t[i]), 10);
       std::cout << std::setprecision(16) << x << "  " << nt2::fdlibm::tanh(x) << "  " << t[i] << std::endl; 
     }

}
  

