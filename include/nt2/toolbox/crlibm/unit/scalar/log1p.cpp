//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#define NT2_UNIT_MODULE "nt2 crlibm toolbox - unit/scalar Mode"
#include <nt2/sdk/functor/meta/call.hpp> 
#include <boost/type_traits/is_same.hpp>
#include <nt2/toolbox/crlibm/include/log1p.hpp> 
#include <nt2/sdk/unit/tests.hpp> 
#include <nt2/sdk/unit/module.hpp>
#include <nt2/include/functions/is_nan.hpp>
#include <nt2/sdk/constant/real.hpp>
#include <nt2/sdk/constant/infinites.hpp>
#include <nt2/include/functions/ulpdist.hpp>
#include <nt2/include/functions/exp10.hpp>
#include <iostream>
#include <iomanip>

//////////////////////////////////////////////////////////////////////////////
// Test behavior of arithmetic components using NT2_TEST_CASE
//////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE_TPL ( log1p, (double) 
                (float) 
                )
{
  using nt2::crlibm::log1p; 
  using nt2::crlibm::tag::log1p_;
  const int N = 2; 
   NT2_TEST( (boost::is_same < typename nt2::meta::call<log1p_<nt2::rn>(T)>::type
            , T
            >::value)
           );
   typedef typename boost::result_of<nt2::meta::floating(T)>::type r_t; 
   NT2_TEST_EQUAL(  nt2::crlibm::log1p<nt2::rn>( T(0) )  , 0 );
   NT2_TEST_EQUAL(  nt2::crlibm::log1p<nt2::rn>( T(-1) )  , nt2::Minf<T>() );
   NT2_TEST_EQUAL(  nt2::crlibm::log1p<nt2::rn>( nt2::Inf<T>() )  , nt2::Inf<T>() );
   NT2_TEST_LESSER_EQUAL(  nt2::ulpdist(nt2::crlibm::log1p<nt2::rn>(nt2::Exp_1<T>()-1 ), T(1)), 1); 
   NT2_TEST_LESSER_EQUAL(  nt2::ulpdist(nt2::crlibm::log1p<nt2::rn>(nt2::Eps<T>()), nt2::Eps<T>()), 1); 
   NT2_TEST(  nt2::is_nan(log1p<nt2::rn>(nt2::Nan<T>() )));
   T t[] ={    6.931471805599453e-01,     9.985023295895228e-04,     4.996252914324852e-04,     3.331667530401490e-04, 
     2.499062864436910e-04,     1.999400186606686e-04,     1.666250107995764e-04,     1.428265374134045e-04, 
     1.249765670563763e-04,     1.110925957927527e-04  }; 
   T v[] ={    1.000000000000000e+00,     9.990009990009990e-04,     4.997501249375312e-04,     3.332222592469177e-04, 
     2.499375156210947e-04,     1.999600079984003e-04,     1.666388935177471e-04,     1.428367376089130e-04, 
     1.249843769528809e-04,     1.110987668036885e-04 };
 

   for(int i=0; i < 10; i++)  
     {
       NT2_TEST_LESSER_EQUAL(nt2::ulpdist(nt2::crlibm::log1p<nt2::rn>(v[i]), t[i]), 3);
       std::cout << std::setprecision(20) << v[i] << "  " << nt2::crlibm::log1p<nt2::rn>(v[i]) << "  " << t[i] << std::endl; 
     } }
