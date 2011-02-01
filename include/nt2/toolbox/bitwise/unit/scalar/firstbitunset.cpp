//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#define NT2_UNIT_MODULE "nt2 bitwise toolbox - unit/scalar Mode"

#include <nt2/toolbox/bitwise/include/firstbitunset.hpp>
#include <nt2/sdk/unit/tests.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/meta/as_integer.hpp>
#include <nt2/sdk/functor/meta/call.hpp>

//////////////////////////////////////////////////////////////////////////////
// Test behavior of bitwise components using NT2_TEST_CASE
//////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE_TPL ( firstbitunset,  (double)(nt2::uint64_t)(nt2::int64_t) 
                (float)(nt2::uint32_t)(nt2::int32_t)  
                (nt2::uint16_t)(nt2::int16_t)         
                (nt2::uint8_t)(nt2::int8_t)
                  )
{
  using nt2::firstbitunset;
  using nt2::tag::firstbitunset_;

  NT2_TEST( (boost::is_same < typename nt2::meta::call<firstbitunset_(T)>::type
           , typename nt2::meta::as_integer<T, unsigned>::type
              >::value)
           );
}

NT2_TEST_CASE_TPL ( firstbitunset_1,  (nt2::uint64_t)(nt2::int64_t) 
                (nt2::uint32_t)(nt2::int32_t)  
                (nt2::uint16_t)(nt2::int16_t)         
                (nt2::uint8_t)(nt2::int8_t)
                  )
{
  using nt2::firstbitunset;
  using nt2::tag::firstbitunset_;

  NT2_TEST( (boost::is_same < typename nt2::meta::call<firstbitunset_(T)>::type
           , typename nt2::meta::as_integer<T, unsigned>::type
              >::value)
           );
  NT2_TEST_EQUAL(  firstbitunset( T(1)), 2 );
  NT2_TEST_EQUAL(  firstbitunset( T(2)), 1 );
  NT2_TEST_EQUAL(  firstbitunset( T(7)), 8 );
  NT2_TEST_EQUAL(  firstbitunset( T(15)), 16); 
}
  

