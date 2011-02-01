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
#include <nt2/include/functions/is_gez.hpp>
#include <nt2/sdk/unit/tests.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/include/functions/is_nan.hpp>
#include <nt2/sdk/constant/real.hpp>

//////////////////////////////////////////////////////////////////////////////
// Test behavior of arithmetic components using NT2_TEST_CASE
//////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE_TPL ( is_gez, (double)(nt2::int64_t) 
                (float)(nt2::int32_t)  
                (nt2::int16_t)         
                (nt2::int8_t)
                )
{
  using nt2::is_gez;
  using nt2::tag::is_gez_;

   NT2_TEST( (boost::is_same < typename nt2::meta::call<is_gez_(T)>::type
            , bool
            >::value)
           );

  NT2_TEST_EQUAL(  is_gez( T(42) ), 1 );
  NT2_TEST_EQUAL(  is_gez( T(-42) ), 0 );
  NT2_TEST_EQUAL(  is_gez( T(0) ), 1 );
}
NT2_TEST_CASE_TPL ( unsigned_is_gez, (nt2::uint64_t) 
                (nt2::uint32_t)  
                (nt2::uint16_t)         
                (nt2::uint8_t)
                )
{
  using nt2::is_gez;
  using nt2::tag::is_gez_;

   NT2_TEST( (boost::is_same < typename nt2::meta::call<is_gez_(T)>::type
            , bool
            >::value)
           );

  NT2_TEST_EQUAL(  is_gez( T(42) ), 1 );
  NT2_TEST_EQUAL(  is_gez( T(0) ), 1 );
}
NT2_TEST_CASE_TPL ( real_is_gez, (double)(float) )
{
  using nt2::is_gez;
  using nt2::tag::is_gez_;

   NT2_TEST( (boost::is_same < typename nt2::meta::call<is_gez_(T)>::type
            , bool
            >::value)
           );

   NT2_TEST_EQUAL(  is_gez( T(nt2::Nan<T>()) ), 0 );

}

