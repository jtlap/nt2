//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#define NT2_UNIT_MODULE "nt2 ieee toolbox - unit/scalar Mode"
#include <nt2/sdk/functor/meta/call.hpp>
#include <boost/type_traits/is_same.hpp> 
#include <nt2/toolbox/ieee/include/exponent.hpp>
#include <nt2/sdk/unit/tests.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/constant/properties.hpp>
#include <nt2/sdk/meta/as_real.hpp>
#include <nt2/sdk/meta/as_integer.hpp>
#include <nt2/sdk/constant/eps_related.hpp>
#include <iostream>
 
//////////////////////////////////////////////////////////////////////////////
// Test behavior of arithmetic components using NT2_TEST_CASE
//////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE_TPL ( exponent,   (double)(float)        
                  )
{
  using nt2::exponent;
  using nt2::functors::exponent_;

  NT2_TEST( (boost::is_same < typename nt2::meta::call<exponent_(T)>::type
	     ,  typename nt2::meta::as_integer<T, signed>::type
              >::value)
           );
  NT2_TEST_EQUAL(  exponent( T(1) ), 0 );
  NT2_TEST_EQUAL(  exponent( T(-1) ), 0 );
  NT2_TEST_EQUAL(  exponent( T(2) ), 1 );
  NT2_TEST_EQUAL(  exponent( T(-2) ),1 );
  NT2_TEST_EQUAL(  exponent( T(0) ),0 );
  

}
