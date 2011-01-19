//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#define NT2_UNIT_MODULE "nt2 fdlibm toolbox - remainder/scalar Mode"

#include <nt2/sdk/functor/meta/call.hpp>
#include <boost/type_traits/is_same.hpp>
#include <nt2/toolbox/fdlibm/include/remainder.hpp>
#include <nt2/sdk/unit/tests.hpp>
#include <nt2/sdk/unit/module.hpp>

//////////////////////////////////////////////////////////////////////////////
// Test behavior of fdlibm components using NT2_TEST_CASE
//////////////////////////////////////////////////////////////////////////////


NT2_TEST_CASE_TPL ( remainder,  (double)(nt2::uint64_t)(nt2::int64_t) 
                          (float)(nt2::uint32_t)(nt2::int32_t)  
                          (nt2::uint16_t)(nt2::int16_t)         
                          (nt2::uint8_t)(nt2::int8_t)
                  )
{
  using nt2::fdlibm::remainder;
  using nt2::fdlibm::tag::remainder_;

  NT2_TEST( (boost::is_same < typename nt2::meta::call<remainder_(T, T)>::type
              , typename boost::result_of<nt2::meta::floating(T, T)>::type
              >::value)
           );
  NT2_TEST_EQUAL(  remainder( T(4), T(3)), 1 );
  NT2_TEST_EQUAL(  remainder( T(5), T(3)), -1);
  NT2_TEST_EQUAL(  remainder( T(6), T(3)), 0 );
  NT2_TEST_EQUAL(  remainder( T(14), T(3)), -1 );
  NT2_TEST_EQUAL(  remainder( T(14), T(6)), 2 );
}
          
