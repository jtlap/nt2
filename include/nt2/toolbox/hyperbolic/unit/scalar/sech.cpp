//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#define NT2_UNIT_MODULE "nt2 hyperbolic toolbox - unit/scalar Mode"

#include <nt2/sdk/functor/meta/call.hpp> 
#include <boost/type_traits/is_same.hpp>
#include <nt2/toolbox/hyperbolic/include/sech.hpp> 
#include <nt2/sdk/unit/tests.hpp> 
#include <nt2/sdk/unit/module.hpp>
#include <nt2/include/functions/is_nan.hpp>
#include <nt2/sdk/constant/real.hpp>
#include <nt2/sdk/constant/infinites.hpp>
#include <nt2/include/functions/ulpdist.hpp>
#include <nt2/include/functions/asech.hpp>

//////////////////////////////////////////////////////////////////////////////
// Test behavior of arithmetic components using NT2_TEST_CASE
//////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE_TPL ( sech, (double) 
                (float) 
                )
{
  using nt2::sech; 
  using nt2::tag::sech_;
  const int N = 2; 
   NT2_TEST( (boost::is_same < typename nt2::meta::call<sech_(T)>::type
            , T
            >::value)
           );
   typedef typename boost::result_of<nt2::meta::floating(T)>::type r_t; 
NT2_TEST_EQUAL(  nt2::sech( T(0) ), T(1));
NT2_TEST_LESSER_EQUAL(  nt2::ulpdist(nt2::sech( T(1) )  , T(6.480542736638853e-01)), 1);
NT2_TEST_LESSER_EQUAL(  nt2::ulpdist(nt2::sech( T(0.5) )  , T(8.868188839700740e-01)), 1);
   NT2_TEST      (  nt2::is_nan(nt2::sech(nt2::Nan<T>()) )); 

   for(int i=1; i < 10; i++)
     {
       T x =  i; 
       NT2_TEST_LESSER_EQUAL(nt2::ulpdist(x, nt2::asech(nt2::sech(x))), 1); 
     }
}
