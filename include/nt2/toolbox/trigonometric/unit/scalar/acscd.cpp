//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#define NT2_UNIT_MODULE "nt2 trigonometric toolbox - unit/scalar Mode"

#include <nt2/sdk/functor/meta/call.hpp> 
#include <boost/type_traits/is_same.hpp>
#include <nt2/toolbox/trigonometric/include/acscd.hpp> 
#include <nt2/sdk/unit/tests.hpp> 
#include <nt2/sdk/unit/module.hpp>
#include <nt2/include/functions/is_nan.hpp>
#include <nt2/sdk/constant/real.hpp>
#include <nt2/include/functions/ulpdist.hpp>
//////////////////////////////////////////////////////////////////////////////
// Test behavior of arithmetic components using NT2_TEST_CASE
//////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE_TPL ( acscd, (double) 
                (float) 
                )
{
  using nt2::acscd; 
  using nt2::tag::acscd_;
  const int N = 1; 

   NT2_TEST( (boost::is_same < typename nt2::meta::call<acscd_(T)>::type
            , T
            >::value)
           );
   typedef typename boost::result_of<nt2::meta::floating(T)>::type r_t; 
   NT2_TEST(  nt2::is_nan(acscd( T(0) )) );
   NT2_TEST_EQUAL(  acscd( T(1) )  , 90 );
   NT2_TEST_EQUAL(  acscd( T(-1) )  , -90 );
   NT2_TEST_EQUAL(  acscd( T(nt2::Inf<T>()) ), 0 );
   NT2_TEST_EQUAL(  acscd( T(nt2::Minf<T>()) ), 0 );
NT2_TEST_LESSER(  nt2::ulpdist(acscd( T(2)), 30), N); 
NT2_TEST_LESSER(  nt2::ulpdist(acscd( T(-2)), -30), N); 
}
