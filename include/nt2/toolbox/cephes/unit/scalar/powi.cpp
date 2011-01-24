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
#include <nt2/toolbox/cephes/include/powi.hpp> 
#include <nt2/sdk/unit/tests.hpp> 
#include <nt2/sdk/unit/module.hpp>
#include <nt2/include/functions/is_nan.hpp>
#include <nt2/sdk/constant/real.hpp>
#include <nt2/sdk/constant/infinites.hpp>
#include <nt2/include/functions/ulpdist.hpp>
#include <nt2/include/functions/sqrt.hpp>


//////////////////////////////////////////////////////////////////////////////
// Test behavior of arithmetic components using NT2_TEST_CASE
//////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE_TPL ( powi, (double) 
                (float) 
                )
{
  using nt2::cephes::powi; 
  using nt2::cephes::tag::powi_;
   typedef typename boost::result_of<nt2::meta::floating(T)>::type r_t; 
   NT2_TEST( (boost::is_same < typename nt2::meta::call<powi_(T, T)>::type
            , r_t
            >::value)
           );
   NT2_TEST_EQUAL(  nt2::cephes::powi( T(0), 0)  , 1 );
   NT2_TEST_EQUAL(  nt2::cephes::powi( T(1), 28)  , nt2::One<T>() );
   NT2_TEST_EQUAL(  nt2::cephes::powi(T(2),3), nt2::Eight<T>());
   T x =  1.5;
   T y =  1;
   for(int i=1; i < 100; i++)
     {
       T z = nt2::cephes::powi(x, i);
       y *=  x; 
       NT2_TEST_LESSER_EQUAL(nt2::ulpdist(z, y), 5); 
     }
}
