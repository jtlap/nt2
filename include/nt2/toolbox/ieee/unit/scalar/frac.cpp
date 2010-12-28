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
#include <nt2/toolbox/ieee/include/frac.hpp>
#include <nt2/sdk/unit/tests.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/constant/real.hpp>
#include <nt2/sdk/meta/as_real.hpp>

//////////////////////////////////////////////////////////////////////////////
// Test behavior of arithmetic components using NT2_TEST_CASE
//////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE_TPL ( frac,   (double)(float)//NT2_REAL_TYPES        
                  )
{
  using nt2::frac;
  using nt2::tag::frac_;

  NT2_TEST( (boost::is_same < typename nt2::meta::call<frac_(T)>::type
           , T
              >::value)
           );
  NT2_TEST_EQUAL(  frac( T(23.50) ), T(0.5) );
  NT2_TEST_EQUAL(  frac( T(-12.5) ), T(-0.5) );
  
    

}

NT2_TEST_CASE_TPL ( integral_frac,   NT2_INTEGRAL_TYPES        
                  )
{
  using nt2::frac;
  using nt2::tag::frac_;

  NT2_TEST( (boost::is_same < typename nt2::meta::call<frac_(T)>::type
           , T
              >::value)
           );
  NT2_TEST_EQUAL(  frac( T(42) ), T(0) );
  NT2_TEST_EQUAL(  frac( T(-59) ), T(0) );
  
    

}
