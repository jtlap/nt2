/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#define NT2_UNIT_MODULE "nt2::logspace function"

#include <nt2/table.hpp>
#include <nt2/include/functions/size.hpp>
#include <nt2/include/functions/linspace.hpp>
#include <nt2/include/functions/logspace.hpp>
#include <nt2/include/functions/log10.hpp>
#include <nt2/include/functions/exp10.hpp>
#include <nt2/include/constants/pi.hpp>
#include <nt2/include/constants/log10_pi.hpp>
#include <boost/fusion/include/make_vector.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests.hpp>

NT2_TEST_CASE_TPL( logspace, (double)(float) )
{
  typedef T r_t;
  double ulpd;
  {
    nt2::table<T> xd = nt2::logspace(T(2),T(3), 50);
    nt2::table<T> yd = nt2::exp10(nt2::linspace(T(2),T(3), 50));
    
    NT2_TEST_EQUAL( xd.extent(), nt2::of_size(1,50 ) );
    
    for(int i=1;i<=50;++i)
      NT2_TEST_ULP_EQUAL( xd(i), yd(i), 0.5 );
  }
  {
    nt2::table<T> xd = nt2::logspace(T(2),T(3));
    nt2::table<T> yd = nt2::exp10(nt2::linspace(T(2),T(3), 50));
    
    NT2_TEST_EQUAL( xd.extent(), nt2::of_size(1,50 ) );
    
    for(int i=1;i<=50;++i)
      NT2_TEST_ULP_EQUAL( xd(i), yd(i), 0.5 );
  }
  {
    nt2::table<T> xd = nt2::logspace(T(2),T(3),7);
    nt2::table<T> yd = nt2::exp10(nt2::linspace(T(2), T(3), 7));
    
    NT2_TEST_EQUAL( xd.extent(), nt2::of_size(1,7 ) );
    
    for(int i=1;i<=7;++i)
      NT2_TEST_ULP_EQUAL( xd(i), yd(i), 0.5 );
  }
  {
    nt2::table<T> xd = nt2::logspace(T(2),nt2::Pi<T>(),7);
    nt2::table<T> yd = nt2::exp10(nt2::linspace(T(2),nt2::Log10_pi<T>(), 7));
    
    NT2_TEST_EQUAL( xd.extent(), nt2::of_size(1,7 ) );
    
    for(int i=1;i<=7;++i)
      NT2_TEST_ULP_EQUAL( xd(i), yd(i), 0.5 );
  }
  {
    nt2::table<T> xd = nt2::logspace(T(2),nt2::Pi<T>(),7, nt2::regular_);
    nt2::table<T> yd = nt2::exp10(nt2::linspace(T(2),nt2::Pi<T>(), 7));
    
    NT2_TEST_EQUAL( xd.extent(), nt2::of_size(1,7 ) );
    
    for(int i=1;i<=7;++i)
      NT2_TEST_ULP_EQUAL( xd(i), yd(i), 0.5 );
  }
  {
    nt2::table<T> xd1 = nt2::logspace(T(2),nt2::Pi<T>(),1, nt2::regular_);
    nt2::table<T> xd2 = nt2::logspace(T(2),nt2::Pi<T>(),1);    
     NT2_TEST_EQUAL( xd1.extent(), nt2::of_size(1,1 ) );
     NT2_TEST_EQUAL( xd2.extent(), nt2::of_size(1,1 ) );
    
    NT2_TEST_ULP_EQUAL( xd1(1), nt2::exp10(nt2::Pi<T>()), 0.5 );
    NT2_TEST_ULP_EQUAL( xd2(1), nt2::Pi<T>(), 0.5); 
  }
}

