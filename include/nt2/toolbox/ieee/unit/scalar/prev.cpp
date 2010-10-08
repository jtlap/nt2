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
#include <nt2/toolbox/ieee/include/prev.hpp>
#include <nt2/sdk/unit/tests.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/constant/real.hpp>
#include <nt2/sdk/constant/eps_related.hpp>
#include <nt2/sdk/meta/as_real.hpp>

//////////////////////////////////////////////////////////////////////////////
// Test behavior of arithmetic components using NT2_TEST_CASE
//////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE_TPL ( prev,   NT2_REAL_TYPES        
                  )
{
  using nt2::prev;
  using nt2::functors::prev_;

  NT2_TEST( (boost::is_same < typename nt2::meta::call<prev_(T)>::type
	     , T
              >::value)
           );
  NT2_TEST_EQUAL(  prev( T(2) ), T(2)-nt2::Eps<T>() );
  NT2_TEST_EQUAL(  prev( T(1) ), T(1)-nt2::Eps<T>()/2 );
  
    

}

NT2_TEST_CASE_TPL ( integral_prev,   NT2_INTEGRAL_TYPES        
                  )
{
  using nt2::prev;
  using nt2::functors::prev_;

  NT2_TEST( (boost::is_same < typename nt2::meta::call<prev_(T)>::type
	     , T
              >::value)
           );
  NT2_TEST_EQUAL(  prev( T(42) ), T(41) );
  NT2_TEST_EQUAL(  prev( T(-59) ), T(-60) );
  
    

}

