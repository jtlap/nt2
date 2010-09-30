//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#define NT2_UNIT_MODULE "nt2 arithmetic toolbox - sqrt1pm1/scalar Mode"

#include <nt2/sdk/functor/meta/call.hpp>
#include <boost/type_traits/is_same.hpp>
#include <nt2/toolbox/arithmetic/include/sqrt1pm1.hpp>
#include <nt2/sdk/unit/tests.hpp>
#include <nt2/sdk/unit/module.hpp>

//////////////////////////////////////////////////////////////////////////////
// Test behavior of arithmetic components using NT2_TEST_CASE
//////////////////////////////////////////////////////////////////////////////


NT2_TEST_CASE_TPL ( sqrt1pm1,  (double)(nt2::uint64_t)(nt2::int64_t) 
                          (float)(nt2::uint32_t)(nt2::int32_t)  
                          (nt2::uint16_t)(nt2::int16_t)         
                          (nt2::uint8_t)(nt2::int8_t)
<<<<<<< Updated upstream:include/nt2/toolbox/arithmetic/unit/scalar/sqrt1pm1.cpp
=======
                          (bool)
>>>>>>> Stashed changes:include/nt2/toolbox/arithmetic/unit/scalar/sqrt1pm1.cpp
                  )
{
  using nt2::sqrt1pm1;
  using nt2::functors::sqrt1pm1_;
<<<<<<< Updated upstream:include/nt2/toolbox/arithmetic/unit/scalar/sqrt1pm1.cpp
  NT2_TEST( (boost::is_same < typename nt2::meta::call<sqrt1pm1_(T)>::type
	     , typename boost::result_of<nt2::meta::floating(T)>::type
              >::value)
           );
  NT2_TEST_EQUAL(  sqrt1pm1( T(15) ), 3 );
  NT2_TEST_EQUAL(  sqrt1pm1( T(3) ), 1 );
=======

  //NT2_TEST( (boost::is_same < typename nt2::meta::call<sqrt1pm1_(T)>::type
  //            , bool
  //            >::value)
  //         );
  //NT2_TEST_EQUAL(  sqrt1pm1( T(42) ), T(42) );
  //NT2_TEST_EQUAL(  sqrt1pm1( T(-42) ), -T(-42) );
  //NT2_TEST(  sqrt1pm1(T(1337))  );
  //NT2_TEST( !sqrt1pm1(T(0))     );
>>>>>>> Stashed changes:include/nt2/toolbox/arithmetic/unit/scalar/sqrt1pm1.cpp
}
          
