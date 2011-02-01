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
#include <nt2/toolbox/fdlibm/include/exp.hpp>
#include <nt2/toolbox/exponential/include/exp.hpp>
#include <nt2/sdk/unit/tests.hpp> 
#include <nt2/sdk/unit/module.hpp>
#include <nt2/include/functions/is_nan.hpp>
#include <nt2/sdk/constant/real.hpp>
#include <nt2/sdk/constant/infinites.hpp>
#include <nt2/include/functions/ulpdist.hpp>
#include <nt2/include/functions/log.hpp>
  extern "C"{
    extern double fd_exp ( double );
    extern double fd___ieee754_exp( double ); 
  }


//////////////////////////////////////////////////////////////////////////////
// Test behavior of arithmetic components using NT2_TEST_CASE
//////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE_TPL ( exp, (double)  
                )
{
  using nt2::fdlibm::exp; 
  using nt2::fdlibm::tag::exp_;
  const int N = 2; 
   NT2_TEST( (boost::is_same < typename nt2::meta::call<exp_(T)>::type
            , T
            >::value)
           );
   typedef typename boost::result_of<nt2::meta::floating(T)>::type r_t; 
   NT2_TEST_EQUAL(  nt2::fdlibm::exp( T(0) )  , 1 );
   std::cout << nt2::fdlibm::exp( 1.0 ) << std::endl;
   std::cout << nt2::fdlibm::exp( 0.1) << std::endl;
   NT2_TEST_EQUAL(  nt2::fdlibm::exp( T(1) )  , nt2::Exp_1<T>() );
   NT2_TEST_EQUAL(  nt2::fdlibm::exp(nt2::Minf<T>() ), T(0.0)); 

   for(int i=0; i < 10; i++)
     {
       T x =  i; 
       NT2_TEST_LESSER(nt2::ulpdist(x, nt2::log(nt2::fdlibm::exp(x))), 1);
       std::cout << std::exp(x) << "  " << nt2::exp(x) << "  " << nt2::fdlibm::exp(x) << "  " <<  fd_exp(x)<< "  "  << fd___ieee754_exp(x) << std::endl;
       x =  1.0/(x+1);
        std::cout << std::exp(x) << "  " << nt2::exp(x) << "  " << nt2::fdlibm::exp(x) << "  " <<  fd_exp(x)<< "  "  << fd___ieee754_exp(x) << std::endl;     
    }
}
  
