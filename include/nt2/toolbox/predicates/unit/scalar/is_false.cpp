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
#include <nt2/include/functions/is_false.hpp>
#include <nt2/sdk/unit/tests.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/include/functions/is_nan.hpp>
#include <nt2/sdk/constant/real.hpp>

NT2_TEST_CASE_TPL ( is_false, (double)(nt2::int64_t) 
                (float)(nt2::int32_t)  
                (nt2::int16_t)         
                (nt2::int8_t)
                )
{
  using nt2::is_false;
  using nt2::tag::is_false_;

   NT2_TEST( (boost::is_same < typename nt2::meta::call<is_false_(T)>::type
            , bool
            >::value)
           );

  NT2_TEST_EQUAL(  is_false( T(42) ), 0 );
  NT2_TEST_EQUAL(  is_false( T(-43) ), 0 );
  NT2_TEST_EQUAL(  is_false( T(0) ), 1 );
}
NT2_TEST_CASE_TPL ( real_is_false, (double)(float) )
{
  using nt2::is_false;
  using nt2::tag::is_false_;

   NT2_TEST( (boost::is_same < typename nt2::meta::call<is_false_(T)>::type
            , bool
            >::value)
           );

  NT2_TEST_EQUAL(  is_false( T(42) ), 0 );
  NT2_TEST_EQUAL(  is_false( T(-42.5) ), 0 );
  NT2_TEST_EQUAL(  is_false( T(0) ), 1 );
}
NT2_TEST_CASE_TPL ( bool_is_false, (bool) )
{
  using nt2::is_false;
  using nt2::tag::is_false_;

   NT2_TEST( (boost::is_same < typename nt2::meta::call<is_false_(T)>::type
            , bool
            >::value)
           );

   NT2_TEST_EQUAL(  is_false( 1 ), 0 );
   NT2_TEST_EQUAL(  is_false( 0 ), 1);

}

