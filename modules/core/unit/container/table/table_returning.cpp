/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#define NT2_UNIT_MODULE "nt2::table_returning "

#include <nt2/table.hpp>
#include <nt2/include/functions/first_index.hpp>

#include <nt2/sdk/unit/tests.hpp>
#include <nt2/sdk/unit/module.hpp>

NT2_TEST_CASE_TPL( table_dimensions ,NT2_TYPES)
{
  using nt2::table;
  double ulpd = 0.0;
  typedef T r_t;
  nt2::table<T> a(nt2::of_size(3, 3));

 for(int i=1; i <= 3; i++)
   for(int j=1; j <= 3; j++)
     a(i, j) = T(i + j);

  nt2::table<T, nt2::C_index_> b(nt2::of_size(3, 3));

  b =  a;
  int fa = nt2::first_index<1>(a);
  int fb = nt2::first_index<1>(b);

  for(int i=0; i < 3; i++)
    for(int j=0; j < 3; j++)
      NT2_TEST_EQUAL( T(a(i+fa, j+fa)), T(b(i+fb, j+fb)));
}
