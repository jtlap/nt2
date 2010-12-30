//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#define NT2_UNIT_MODULE "nt2 arithmetic toolbox - round/scalar Mode"

#include <nt2/sdk/functor/meta/call.hpp>
#include <boost/type_traits/is_same.hpp>
#include <nt2/toolbox/arithmetic/include/round.hpp>
#include <nt2/sdk/unit/tests.hpp>
#include <nt2/sdk/unit/module.hpp>

//////////////////////////////////////////////////////////////////////////////
// Test behavior of arithmetic components using NT2_TEST_CASE
//////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE_TPL ( round_int,  (nt2::uint64_t)(nt2::int64_t) 
                          (nt2::uint32_t)(nt2::int32_t)  
                          (nt2::uint16_t)(nt2::int16_t)         
                          (nt2::uint8_t)(nt2::int8_t)
                  )
{
  using nt2::round;
  using nt2::tag::round_;

 NT2_TEST( (boost::is_same < typename nt2::meta::call<round_(T)>::type
             ,T
             >::value)
          );
   NT2_TEST_EQUAL(  round( T(42) ), 42 );
   NT2_TEST_EQUAL(  round( T(-42) ), T(-42) );

}

NT2_TEST_CASE_TPL ( real_round,  (double)(float)
                  )
{
  using nt2::round;
  using nt2::tag::round_;

 NT2_TEST( (boost::is_same < typename nt2::meta::call<round_(T)>::type
             ,T
             >::value)
          );
 NT2_TEST_EQUAL(  round( T(42.1) ), T(42) );
 NT2_TEST_EQUAL(  round( T(-42.1) ), T(-42) );
 NT2_TEST_EQUAL(  round( T(46.7) ), T(47) );
 NT2_TEST_EQUAL(  round( T(-46.7) ), T(-47) );
}
          
