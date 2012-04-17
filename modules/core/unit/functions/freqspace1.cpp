/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#define NT2_UNIT_MODULE "nt2::freqspace1 function"

#include <nt2/table.hpp>
#include <nt2/include/functions/size.hpp>
#include <nt2/include/functions/colon.hpp>
#include <nt2/include/functions/freqspace1.hpp>
#include <nt2/include/functions/log10.hpp>
#include <nt2/include/functions/exp10.hpp>
#include <boost/fusion/include/make_vector.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests.hpp>

NT2_TEST_CASE_TPL( freqspace1, (double)(float) )
{
  typedef T r_t;
  double ulpd;
  {
    const int n = 4; 
    nt2::table<T> xd = nt2::freqspace1(n,nt2::meta::as_<T>());
    nt2::table<T> yd = nt2::colon(T(0),T(2)/n, T(1));
    NT2_TEST( xd.extent() == nt2::of_size(1,n-1) );
    
     for(int i=1;i<=n-1;++i)
       NT2_TEST_ULP_EQUAL( xd(i), yd(i), 0.5 );
   }
  {
    const int n = 4; 
    nt2::table<T> xd = nt2::freqspace1(n, nt2::whole_, nt2::meta::as_<T>()); 
    nt2::table<T> yd = nt2::colon(T(0),T(2)/n, T(2)*(n-1)/n);

     NT2_TEST( xd.extent() == nt2::of_size(1,n) );
    
     for(int i=1;i<=n;++i)
       NT2_TEST_ULP_EQUAL( xd(i), yd(i), 0.5 );
   }
}
NT2_TEST_CASE( freqspace1_no_type )
{
  typedef double T;
  typedef double r_t; 
  double ulpd;
  {
    for(int n = 1; n <= 10; ++n)
      {
        nt2::table<T> xd = nt2::freqspace1(n);
        nt2::table<T> yd = nt2::colon(T(0),T(2)/n, T(1));
        NT2_TEST( xd.extent() == nt2::of_size(1,n/2+1) );
        
        for(int i=1;i<=n/2+1;++i)
          NT2_TEST_ULP_EQUAL( xd(i), yd(i), 0.5 );
      }
  }
  {
    for(int n = 1; n <= 10; ++n)
      {
        nt2::table<T> xd = nt2::freqspace1(n, nt2::whole_); 
        nt2::table<T> yd = nt2::colon(T(0),T(2)/n, T(2)*(n-1)/n);
        
        NT2_TEST( xd.extent() == nt2::of_size(1,n) );
        
        for(int i=1;i<=n;++i)
          NT2_TEST_ULP_EQUAL( xd(i), yd(i), 0.5 );
      }
  }
}

