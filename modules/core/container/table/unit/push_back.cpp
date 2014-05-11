//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/table.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>

NT2_TEST_CASE_TPL( table_push_back_value ,NT2_TYPES)
{
  using nt2::_2D;
  using nt2::table;
  using nt2::of_size;

  nt2::table<T,_2D> a(of_size(3, 5));
  nt2::table<T> ref(of_size(16));

  for(int i=1; i <= 15; i++) ref(i) = a(i) = T(i);
  ref(16) = T(42);

  a.push_back(T(42));

  NT2_TEST_EQUAL(a.extent(), of_size(16));
  NT2_TEST_EQUAL(a,ref);
}

NT2_TEST_CASE_TPL( table_push_back_table ,NT2_TYPES)
{
  using nt2::_2D;
  using nt2::table;
  using nt2::of_size;

  nt2::table<T,_2D> a(of_size(3, 5));
  nt2::table<T,_2D> b(of_size(3, 5));
  nt2::table<T,_2D> ref(of_size(3,10));

  for(int i=1; i <= 15; i++) ref(i)    = a(i) = T(2*i-1);
  for(int i=1; i <= 15; i++) ref(i+15) = b(i) = T(2*i);

  a.push_back(b);

  NT2_TEST_EQUAL(a.extent(), of_size(3,10));
  NT2_TEST_EQUAL(a,ref);

}
