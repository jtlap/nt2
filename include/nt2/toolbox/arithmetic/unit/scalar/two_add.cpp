//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#define NT2_UNIT_MODULE "nt2 arithmetic toolbox - two_add/scalar Mode"

#include <nt2/sdk/functor/meta/call.hpp>
#include <boost/type_traits/is_same.hpp>
#include <nt2/toolbox/arithmetic/include/two_add.hpp>
#include <nt2/sdk/unit/tests.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <boost/fusion/tuple.hpp>

//////////////////////////////////////////////////////////////////////////////
// Test behavior of arithmetic components using NT2_TEST_CASE
//////////////////////////////////////////////////////////////////////////////


<<<<<<< Updated upstream:include/nt2/toolbox/arithmetic/unit/scalar/two_add.cpp
NT2_TEST_CASE_TPL ( two_add,  (double)
                          (float)
=======
NT2_TEST_CASE_TPL ( two_add,  (double)(nt2::uint64_t)(nt2::int64_t) 
                          (float)(nt2::uint32_t)(nt2::int32_t)  
                          (nt2::uint16_t)(nt2::int16_t)         
                          (nt2::uint8_t)(nt2::int8_t)
                          (bool)
>>>>>>> Stashed changes:include/nt2/toolbox/arithmetic/unit/scalar/two_add.cpp
                  )
{
  using nt2::two_add;
  using nt2::functors::two_add_;

<<<<<<< Updated upstream:include/nt2/toolbox/arithmetic/unit/scalar/two_add.cpp
  typedef typename boost::result_of<nt2::meta::floating(T, T)>::type rtype;
  typedef typename boost::fusion::tuple<rtype,rtype>              type;
  NT2_TEST( (boost::is_same < typename nt2::meta::call<two_add_(T, T)>::type
              , type
              >::value)
           );
  
=======
  //NT2_TEST( (boost::is_same < typename nt2::meta::call<two_add_(T)>::type
  //            , bool
  //            >::value)
  //         );
  //NT2_TEST_EQUAL(  two_add( T(42) ), T(42) );
  //NT2_TEST_EQUAL(  two_add( T(-42) ), -T(-42) );
  //NT2_TEST(  two_add(T(1337))  );
  //NT2_TEST( !two_add(T(0))     );
>>>>>>> Stashed changes:include/nt2/toolbox/arithmetic/unit/scalar/two_add.cpp
}
          
