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
#include <nt2/toolbox/fdlibm/include/ldexp.hpp>
#include <nt2/sdk/unit/tests.hpp>
#include <nt2/sdk/unit/module.hpp>

//////////////////////////////////////////////////////////////////////////////
// Test behavior of arithmetic components using NT2_TEST_CASE
//////////////////////////////////////////////////////////////////////////////


NT2_TEST_CASE_TPL ( ldexp, (double)
                  )
{
  using nt2::fdlibm::ldexp; 
  using nt2::fdlibm::tag::ldexp_;

  NT2_TEST( (boost::is_same < typename nt2::meta::call<ldexp_(T, T)>::type
           , T
              >::value)
           );
  NT2_TEST_EQUAL(  ldexp( T(1), 2), T(4) );
  NT2_TEST_EQUAL(  ldexp( T(-1), 3 ), T(-8) );
  NT2_TEST_EQUAL(  ldexp( T(1), -3 ), T(1.0/8) );
  NT2_TEST_EQUAL(  ldexp( T(0),  4) , T(0)  ); 
}

