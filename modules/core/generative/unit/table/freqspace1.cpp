//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#define NT2_UNIT_MODULE "nt2::freqspace1 function"

#include <nt2/table.hpp>
#include <nt2/options.hpp>
#include <nt2/include/functions/colon.hpp>
#include <nt2/include/functions/freqspace1.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests.hpp>

NT2_TEST_CASE( untyped )
{
  const int n = 4;
  nt2::table<double> xd  = nt2::freqspace1(n);
  nt2::table<double> ref = nt2::colon(0.,2./n, 1.);
  NT2_TEST_EQUAL( xd.extent(), nt2::of_size(1,n-1 ) );

  NT2_TEST_ULP_EQUAL( xd, ref, 0.5 );

  xd  = nt2::freqspace1(n, nt2::whole_);
  ref = nt2::colon(0.,2./n, 2.*(n-1)/n);

  NT2_TEST_EQUAL( xd.extent(), nt2::of_size(1,n ) );

  NT2_TEST_ULP_EQUAL( xd, ref, 0.5 );
}

NT2_TEST_CASE_TPL( typed, (double)(float) )
{
  const int n = 4;
  nt2::table<T> xd  = nt2::freqspace1(n,nt2::meta::as_<T>());
  nt2::table<T> ref = nt2::colon(T(0),T(2)/n, T(1));
  NT2_TEST_EQUAL( xd.extent(), nt2::of_size(1,n-1 ) );

  NT2_TEST_ULP_EQUAL( xd, ref, 0.5 );

  xd = nt2::freqspace1(n, nt2::whole_, nt2::meta::as_<T>());
  ref = nt2::colon(T(0),T(2)/n, T(2)*(n-1)/n);

  NT2_TEST_EQUAL( xd.extent(), nt2::of_size(1,n ) );

  NT2_TEST_ULP_EQUAL( xd, ref, 0.5 );
}
