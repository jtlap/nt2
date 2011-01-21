//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#define NT2_UNIT_MODULE "nt2 predicates toolbox - unit/scalar Mode"

#include <nt2/sdk/functor/meta/call.hpp>
#include <boost/type_traits/is_same.hpp>
#include <nt2/include/functions/is_even.hpp>
#include <nt2/sdk/unit/tests.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/include/functions/is_nan.hpp>
#include <nt2/sdk/constant/real.hpp>

//////////////////////////////////////////////////////////////////////////////
// Test behavior of arithmetic components using NT2_TEST_CASE
//////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE_TPL ( is_even, (double)(nt2::int64_t) 
                (float)(nt2::int32_t)  
                (nt2::int16_t)         
                (nt2::int8_t)
                )
{
  using nt2::is_even;
  using nt2::tag::is_even_;

   NT2_TEST( (boost::is_same < typename nt2::meta::call<is_even_(T)>::type
            , bool
            >::value)
           );

  NT2_TEST_EQUAL(  is_even( T(42) ), 1 );
  NT2_TEST_EQUAL(  is_even( T(-43) ), 0 );
  NT2_TEST_EQUAL(  is_even( T(0) ), 1 );
}
NT2_TEST_CASE_TPL ( real_is_even, (double)(float) )
{
  using nt2::is_even;
  using nt2::tag::is_even_;

   NT2_TEST( (boost::is_same < typename nt2::meta::call<is_even_(T)>::type
            , bool
            >::value)
           );

  NT2_TEST_EQUAL(  is_even( T(42) ), 1 );
  NT2_TEST_EQUAL(  is_even( T(-42.5) ), 0 );
  NT2_TEST_EQUAL(  is_even( T(0) ), 1 );
}
NT2_TEST_CASE_TPL ( bool_is_even, (bool) )
{
  using nt2::is_even;
  using nt2::tag::is_even_;

   NT2_TEST( (boost::is_same < typename nt2::meta::call<is_even_(T)>::type
            , bool
            >::value)
           );

   NT2_TEST_EQUAL(  is_even( 1 ), 0 );
   NT2_TEST_EQUAL(  is_even( 0 ), 1);

}



