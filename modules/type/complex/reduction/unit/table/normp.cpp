//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#define NT2_UNIT_MODULE "nt2::normp function"

#include <nt2/table.hpp>
#include <nt2/include/functions/normp.hpp>
#include <nt2/include/functions/asum1.hpp>
#include <nt2/include/functions/pow.hpp>
#include <nt2/include/functions/pow_abs.hpp>
#include <nt2/include/functions/rec.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>

NT2_TEST_CASE_TPL( normp_scalar, (float)(double))//NT2_TYPES )
{
  typedef std::complex<T>  cT;
  T x = nt2::normp(cT(42), T(2));
  NT2_TEST_EQUAL( x, T(42) );

  x = nt2::normp(cT(42),T(2), 1);
  NT2_TEST_EQUAL( x, T(42) );

  x = nt2::normp(cT(42),T(2), 2);
  NT2_TEST_EQUAL( x, T(42) );

}
NT2_TEST_CASE_TPL( normp, (float)(double))//NT2_TYPES )
{
  typedef std::complex<T>  cT;
  using nt2::_;
  nt2::table<cT> y( nt2::of_size(5,3) );
  nt2::table<T> sy( nt2::of_size(1,3) );
  nt2::table<T> sz( nt2::of_size(1,3) );

  for(size_t j=1;j<=size(y, 2);j++)
    for(size_t i=1;i<=size(y, 1);i++)
      y(i,j) = i + 10*j;
  sy = nt2::normp(y, nt2::Three<T>());
  sz = nt2::pow(nt2::asum(nt2::pow_abs(y, nt2::Three<T>())), nt2::rec(nt2::Three<T>()));
  for(size_t j=1;j<=size(sy,2);j++)
    for(size_t i=1;i<=size(sy,1);i++)
      NT2_TEST_EQUAL(sz(i, j), sy(i, j));
  sy = nt2::normp(y, nt2::Three<T>(), 1);
  sz = nt2::pow(nt2::asum(nt2::pow_abs(y, nt2::Three<T>()), 1), nt2::rec(nt2::Three<T>()));
   for(size_t j=1;j<=size(sy,2);j++)
     for(size_t i=1;i<=size(sy,1);i++)
       NT2_TEST_EQUAL(sz(i, j), sy(j));
  sy = nt2::normp(y, nt2::Three<T>(), 2);
  sz = nt2::pow(nt2::asum(nt2::pow_abs(y, nt2::Three<T>()), 2), nt2::rec(nt2::Three<T>()));
  for(size_t j=1;j<=size(sy,2);j++)
    for(size_t i=1;i<=size(sy,1);i++)
      NT2_TEST_EQUAL(sz(i, j), sy(i));
  sy = nt2::normp(y, nt2::Three<T>(), size(y,2));
  sz = nt2::pow(nt2::asum(nt2::pow_abs(y, nt2::Three<T>()), 3), nt2::rec(nt2::Three<T>()));
  for(size_t j=1;j<=size(sy,2);j++)
    for(size_t i=1;i<=size(sy,1);i++)
      NT2_TEST_EQUAL(sz(i, j), sy(i, j));


  sy = nt2::normp(y(_), nt2::Three<T>());
  sz = nt2::pow(nt2::sum(nt2::pow_abs(y(_), nt2::Three<T>())),nt2::rec(nt2::Three<T>() ));
  display(sy);
  NT2_TEST_EQUAL(sy(1), sz(1));

}

