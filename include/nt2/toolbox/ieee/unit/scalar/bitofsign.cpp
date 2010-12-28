//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#define NT2_UNIT_MODULE "nt2 ieee toolbox - unit/scalar Mode"

#include <nt2/sdk/functor/meta/call.hpp>
#include <boost/type_traits/is_same.hpp>
#include <nt2/sdk/meta/supported_types.hpp>
#include <nt2/toolbox/ieee/include/bitofsign.hpp>
#include <nt2/sdk/unit/tests.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/constant/real.hpp>
#include <nt2/sdk/meta/as_real.hpp>

//////////////////////////////////////////////////////////////////////////////
// Test behavior of arithmetic components using NT2_TEST_CASE
//////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE_TPL ( bitofsign,   (double)(float) )
{
  using nt2::bitofsign;
  using nt2::tag::bitofsign_;
  
  NT2_TEST( (boost::is_same < typename nt2::meta::call<bitofsign_(T)>::type
           , T
           >::value)
    );
NT2_TEST_EQUAL(  bitofsign( T(1) ), T(0) );
NT2_TEST_EQUAL(  bitofsign( T(-1) ), -T(0) );
             
}

NT2_TEST_CASE_TPL ( unsigned_bitofsign,   NT2_UNSIGNED_TYPES        )
{
  using nt2::bitofsign;
  using nt2::tag::bitofsign_;

  NT2_TEST( (boost::is_same < typename nt2::meta::call<bitofsign_(T)>::type
           , T
              >::value)
           );
  NT2_TEST_EQUAL(  bitofsign( T(1) ), T(0) );
    

}
NT2_TEST_CASE_TPL ( signed_bitofsign,   NT2_INTEGRAL_SIGNED_TYPES         )
{
  using nt2::bitofsign;
  using nt2::tag::bitofsign_;

  NT2_TEST( (boost::is_same < typename nt2::meta::call<bitofsign_(T)>::type
           , T
              >::value)
           );
  NT2_TEST_EQUAL(  bitofsign( T(1) ), T(0) );
  NT2_TEST_EQUAL(  bitofsign( T(-1) ), T(1ull << sizeof(T)*8-1) );
  
    

}
