//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#define NT2_UNIT_MODULE "nt2 arithmetic toolbox - idivceil/scalar Mode"

#include <nt2/sdk/functor/meta/call.hpp>
#include <boost/type_traits/is_same.hpp>
#include <nt2/toolbox/arithmetic/include/idivceil.hpp>
#include <nt2/sdk/unit/tests.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/include/functions/ceil.hpp>

//////////////////////////////////////////////////////////////////////////////
// Test behavior of arithmetic components using NT2_TEST_CASE
//////////////////////////////////////////////////////////////////////////////


<<<<<<< Updated upstream:include/nt2/toolbox/arithmetic/unit/scalar/idivceil.cpp

NT2_TEST_CASE_TPL ( real_idivceil,  (double)
                          (float)
                  )
{
  using nt2::idivceil;
  using nt2::functors::idivceil_;

  NT2_TEST( (boost::is_same < typename nt2::meta::call<idivceil_(T, T)>::type
              , typename boost::result_of<nt2::meta::arithmetic(T, T)>::type
              >::value)
           );
  NT2_TEST_EQUAL(  idivceil( T(22), T(3)), T(nt2::ceil(22.0/3.0)) );
  NT2_TEST_EQUAL(  idivceil( T(-22), T(3) ), T(nt2::ceil(-22.0/3.0)) );
  NT2_TEST_EQUAL(  idivceil( T(22), T(-3) ), T(nt2::ceil(22.0/-3.0)) );

}
NT2_TEST_CASE_TPL ( signed_idivceil,  (nt2::int64_t)(nt2::int32_t)  
                          (nt2::int16_t)(nt2::int8_t)
                  )
{
  using nt2::idivceil;
  using nt2::functors::idivceil_;

  NT2_TEST( (boost::is_same < typename nt2::meta::call<idivceil_(T, T)>::type
              , typename boost::result_of<nt2::meta::arithmetic(T, T)>::type
              >::value)
           );
  NT2_TEST_EQUAL(  idivceil( T(22), T(3)), T(nt2::ceil(22.0/3.0)) );
  NT2_TEST_EQUAL(  idivceil( T(-22), T(3) ), T(nt2::ceil(-22.0/3.0)) );
  NT2_TEST_EQUAL(  idivceil( T(22), T(-3) ), T(nt2::ceil(22.0/-3.0)) );
  NT2_TEST_EQUAL(  idivceil( T(-22), T(-3) ), T(nt2::ceil(-22.0/-3.0)) );

}
NT2_TEST_CASE_TPL ( unsigned_idivceil,  (nt2::uint64_t)(nt2::uint32_t)  
                          (nt2::uint16_t)(nt2::uint8_t)
=======
NT2_TEST_CASE_TPL ( idivceil,  (double)(nt2::uint64_t)(nt2::int64_t) 
                          (float)(nt2::uint32_t)(nt2::int32_t)  
                          (nt2::uint16_t)(nt2::int16_t)         
                          (nt2::uint8_t)(nt2::int8_t)
                          (bool)
>>>>>>> Stashed changes:include/nt2/toolbox/arithmetic/unit/scalar/idivceil.cpp
                  )
{
  using nt2::idivceil;
  using nt2::functors::idivceil_;

<<<<<<< Updated upstream:include/nt2/toolbox/arithmetic/unit/scalar/idivceil.cpp
  NT2_TEST( (boost::is_same < typename nt2::meta::call<idivceil_(T, T)>::type
	     , typename boost::result_of<nt2::meta::arithmetic(T, T)>::type
              >::value)
           );
  NT2_TEST_EQUAL(  idivceil( T(22), T(3)), T(nt2::ceil(22.0/3.0)) );
}
             
=======
  //NT2_TEST( (boost::is_same < typename nt2::meta::call<idivceil_(T)>::type
  //            , bool
  //            >::value)
  //         );
  //NT2_TEST_EQUAL(  idivceil( T(42) ), T(42) );
  //NT2_TEST_EQUAL(  idivceil( T(-42) ), -T(-42) );
  //NT2_TEST(  idivceil(T(1337))  );
  //NT2_TEST( !idivceil(T(0))     );
}
          
>>>>>>> Stashed changes:include/nt2/toolbox/arithmetic/unit/scalar/idivceil.cpp
