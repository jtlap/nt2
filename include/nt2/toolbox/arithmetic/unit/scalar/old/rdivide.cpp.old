//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#define NT2_UNIT_MODULE "nt2 arithmetic toolbox - rdivide/scalar Mode"

#include <nt2/sdk/functor/meta/call.hpp>
#include <boost/type_traits/is_same.hpp>
#include <nt2/toolbox/arithmetic/include/rdivide.hpp>
#include <nt2/sdk/unit/tests.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/constant/infinites.hpp>

//////////////////////////////////////////////////////////////////////////////
// Test behavior of arithmetic components using NT2_TEST_CASE
//////////////////////////////////////////////////////////////////////////////

NT2_TEST_CASE_TPL ( rdivide,  (nt2::uint64_t)(nt2::int64_t) 
                          (nt2::uint32_t)(nt2::int32_t)  
                          (nt2::uint16_t)(nt2::int16_t)         
                          (nt2::uint8_t)(nt2::int8_t)

                  )
{
  using nt2::rdivide;
  using nt2::functors::rdivide_;

  NT2_TEST( (boost::is_same < typename nt2::meta::call<rdivide_(T, T)>::type
	     ,  typename boost::result_of<nt2::meta::arithmetic(T, T)>::type
              >::value)
           );
  NT2_TEST_EQUAL(  rdivide( T(42), T(3)), T(42)/T(3) );
  NT2_TEST_EQUAL(  rdivide( T(-42), T(3)),T(-42)/T(3) );
  NT2_TEST_EQUAL(  rdivide( T(1),   T(0)), T(0));
}
NT2_TEST_CASE_TPL ( real_rdivide,  (double) 
                          (float)  
                  )
{
  using nt2::rdivide;
  using nt2::functors::rdivide_;

  NT2_TEST( (boost::is_same < typename nt2::meta::call<rdivide_(T, T)>::type
              ,   typename boost::result_of<nt2::meta::arithmetic(T, T)>::type
              >::value)
           );
  NT2_TEST_EQUAL(  rdivide( T(42), T(3)), T(42)/T(3) );
  NT2_TEST_EQUAL(  rdivide( T(-42), T(3)),T(-42)/T(3) );
  NT2_TEST_EQUAL(  rdivide( T(1),   T(0)), nt2::Inf<T>()); 
}
          
 
