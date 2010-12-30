//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#define NT2_UNIT_MODULE "nt2 arithmetic toolbox - iround2even/scalar Mode"

#include <nt2/sdk/functor/meta/call.hpp>
#include <boost/type_traits/is_same.hpp>
#include <nt2/toolbox/arithmetic/include/iround2even.hpp>
#include <nt2/sdk/unit/tests.hpp>
#include <nt2/sdk/unit/module.hpp>

//////////////////////////////////////////////////////////////////////////////
// Test behavior of arithmetic components using NT2_TEST_CASE
//////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE_TPL ( signed_iround2even,  (double)(nt2::int64_t) 
                          (float)(nt2::int32_t)  
                          (nt2::int16_t)         
                          (nt2::int8_t)
                  )
{
  using nt2::iround2even;
  using nt2::tag::iround2even_;

 NT2_TEST( (boost::is_same < typename nt2::meta::call<iround2even_(T)>::type
             ,typename nt2::meta::as_integer<T>::type
             >::value)
          );
 NT2_TEST_EQUAL(  iround2even( T(42) ), T(42) );
 NT2_TEST_EQUAL(  iround2even( T(46) ), T(46) );
 NT2_TEST_EQUAL(  iround2even( T(-42) ), T(-42) );
 NT2_TEST_EQUAL(  iround2even( T(-46) ), T(-46) );
}
                    
NT2_TEST_CASE_TPL ( unsigned_iround2even,  (nt2::uint64_t)(nt2::uint32_t)
                (nt2::uint16_t)(nt2::uint8_t)
                  )
{
  using nt2::iround2even;
  using nt2::tag::iround2even_;

 NT2_TEST( (boost::is_same < typename nt2::meta::call<iround2even_(T)>::type
             ,typename nt2::meta::as_integer<T>::type
             >::value)
          );
 NT2_TEST_EQUAL(  iround2even( T(42) ), T(42) );
 NT2_TEST_EQUAL(  iround2even( T(47) ), T(47) );
}
                    
NT2_TEST_CASE_TPL ( real_iround2even,  (double)(float)
                  )
{
  using nt2::iround2even;
  using nt2::tag::iround2even_;

 NT2_TEST( (boost::is_same < typename nt2::meta::call<iround2even_(T)>::type
             ,typename nt2::meta::as_integer<T>::type
             >::value)
          );
 NT2_TEST_EQUAL(  iround2even( T(42.1) ), T(42) );
 NT2_TEST_EQUAL(  iround2even( T(46.7) ), T(47) );
 NT2_TEST_EQUAL(  iround2even( T(-42.1) ), T(-42) );
 NT2_TEST_EQUAL(  iround2even( T(-46.7) ), T(-47) );
}
  
