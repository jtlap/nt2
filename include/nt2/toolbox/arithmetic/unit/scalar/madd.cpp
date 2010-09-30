//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#define NT2_UNIT_MODULE "nt2 arithmetic toolbox - madd/scalar Mode"

#include <nt2/sdk/functor/meta/call.hpp>
#include <boost/type_traits/is_same.hpp>
#include <nt2/toolbox/arithmetic/include/madd.hpp>
#include <nt2/sdk/unit/tests.hpp>
#include <nt2/sdk/unit/module.hpp>

//////////////////////////////////////////////////////////////////////////////
// Test behavior of arithmetic components using NT2_TEST_CASE
//////////////////////////////////////////////////////////////////////////////


NT2_TEST_CASE_TPL ( madd,  (double)(nt2::uint64_t)(nt2::int64_t) 
                          (float)(nt2::uint32_t)(nt2::int32_t)  
                          (nt2::uint16_t)(nt2::int16_t)         
                          (nt2::uint8_t)(nt2::int8_t)
<<<<<<< Updated upstream:include/nt2/toolbox/arithmetic/unit/scalar/madd.cpp
=======
                          (bool)
>>>>>>> Stashed changes:include/nt2/toolbox/arithmetic/unit/scalar/madd.cpp
                  )
{
  using nt2::madd;
  using nt2::functors::madd_;

<<<<<<< Updated upstream:include/nt2/toolbox/arithmetic/unit/scalar/madd.cpp
  NT2_TEST( (boost::is_same < typename nt2::meta::call<madd_(T, T, T)>::type
	     ,typename boost::result_of<nt2::meta::arithmetic(T, T, T)>::type
              >::value)
           );
  NT2_TEST_EQUAL(  madd( T(1), T(2), T(3)), T(5) );
=======
  //NT2_TEST( (boost::is_same < typename nt2::meta::call<madd_(T)>::type
  //            , bool
  //            >::value)
  //         );
  //NT2_TEST_EQUAL(  madd( T(42) ), T(42) );
  //NT2_TEST_EQUAL(  madd( T(-42) ), -T(-42) );
  //NT2_TEST(  madd(T(1337))  );
  //NT2_TEST( !madd(T(0))     );
>>>>>>> Stashed changes:include/nt2/toolbox/arithmetic/unit/scalar/madd.cpp
}
          
