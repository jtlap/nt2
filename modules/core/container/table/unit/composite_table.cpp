//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#define NT2_UNIT_MODULE "nt2::memory composite container"

#include <nt2/table.hpp>
#include <nt2/core/functions/of_size.hpp>

#include <complex>
#include <nt2/sdk/complex/complex.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
/*
//==============================================================================
// Test for container default ctor
//==============================================================================
NT2_TEST_CASE_TPL( composite_table, (float)(double) )
{
  using nt2::table;
  using nt2::of_size;
  using nt2::settings;
  using nt2::deinterleaved_;

  table<std::complex<T>,deinterleaved_> x( of_size(2,3) );

  for(std::size_t i=1;i<=2;++i)
    for(std::size_t j=1;j<=3;++j)
      x(i,j) = std::complex<T>(i,j);

  for(std::size_t i=1;i<=2;++i)
    for(std::size_t j=1;j<=3;++j)
      NT2_TEST_EQUAL(x(i,j), std::complex<T>(i,j));
}

NT2_TEST_CASE_TPL( composite_table_access, (float)(double) )
{
  using nt2::table;
  using nt2::of_size;
  using nt2::settings;
  using nt2::deinterleaved_;

  table<std::complex<T>,deinterleaved_> x( of_size(2,3) );

  for(std::size_t i=1;i<=2;++i)
    for(std::size_t j=1;j<=3;++j)
      x(i,j) = std::complex<T>(i,j);

  NT2_TEST_EQUAL( x(1)+x(2)+x(3), std::complex<T>(4,4));
}
*/
NT2_TEST_CASE_TPL( composite_table_expr, (float)/*(double)*/ )
{
  using nt2::table;
  using nt2::of_size;
  using nt2::settings;
  using nt2::deinterleaved_;

  table<std::complex<T>,deinterleaved_> y,x( of_size(2,3) );

  for(std::size_t i=1;i<=2;++i)
    for(std::size_t j=1;j<=3;++j)
      x(i,j) = std::complex<T>(i,j);

  y = x+x;//+ T(6);

  NT2_DISPLAY(x);
  NT2_DISPLAY(y);
/*  for(std::size_t i=1;i<=2;++i)
    for(std::size_t j=1;j<=3;++j)
      NT2_TEST_EQUAL(y(i,j), -x(i,j) * x(i,j) + T(6));*/
}
