//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#define NT2_UNIT_MODULE "nt2 cephes toolbox - unit/scalar Mode"
#include <nt2/sdk/functor/meta/call.hpp> 
#include <boost/type_traits/is_same.hpp>
#include <nt2/toolbox/cephes/include/cbrt.hpp> 
#include <nt2/sdk/unit/tests.hpp> 
#include <nt2/sdk/unit/module.hpp>
#include <nt2/include/functions/is_nan.hpp>
#include <nt2/sdk/constant/real.hpp>
#include <nt2/sdk/constant/infinites.hpp>
#include <nt2/include/functions/ulpdist.hpp>
#include <nt2/include/functions/exp.hpp>

//////////////////////////////////////////////////////////////////////////////
// Test behavior of arithmetic components using NT2_TEST_CASE
//////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE_TPL ( cbrt, (double) 
                (float) 
                )
{
  using nt2::cephes::cbrt; 
  using nt2::cephes::tag::cbrt_;
  const int N = 2; 
   NT2_TEST( (boost::is_same < typename nt2::meta::call<cbrt_(T)>::type
            , T
            >::value)
           );
   typedef typename boost::result_of<nt2::meta::floating(T)>::type r_t; 
   NT2_TEST_EQUAL(  nt2::cephes::cbrt( T(0) )  , 0 );
   NT2_TEST_EQUAL(  nt2::cephes::cbrt( T(1) )  , nt2::One<T>() );
   NT2_TEST_EQUAL(  nt2::cephes::cbrt(T(8) ), nt2::Two<T>()); 
   for(int i=1; i < 100; i++)
     {
       T x =  i;
       T z = nt2::cephes::cbrt(x);
       T y =  z*z*z; 
       NT2_TEST_LESSER_EQUAL(nt2::ulpdist(x, y), 2); 
     }
}
