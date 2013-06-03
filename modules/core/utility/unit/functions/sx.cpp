//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#define NT2_UNIT_MODULE "nt2::sx function"

#include <nt2/table.hpp>
#include <nt2/include/functions/sx.hpp>
#include <nt2/include/functions/fma.hpp>
#include <nt2/include/functions/if_else.hpp>
#include <nt2/include/functions/if_zero_else.hpp>
#include <nt2/include/functions/plus.hpp>
#include <nt2/include/functions/colon.hpp>
#include <nt2/include/functions/repnum.hpp>
#include <nt2/include/functions/is_lez.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/basic.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>


NT2_TEST_CASE_TPL( sx_0, (float) )//NT2_TYPES )
{
  nt2::table<T> a = nt2::reshape(nt2::_(T(0), T(8)), 3, 3);
  NT2_TEST_EQUAL( nt2::sx(nt2::tag::if_zero_else_(), nt2::is_lez(a), a), a);
}

NT2_TEST_CASE_TPL( sx_1, (float) )//NT2_TYPES )
{
  nt2::table<T> a = nt2::reshape(nt2::_(T(0), T(8)), 3, 3);
  NT2_TEST_EQUAL( nt2::sx(nt2::tag::fma_(), a, T(1), a), a+a);
}

NT2_TEST_CASE_TPL( sx_2, (float) )//NT2_TYPES )
{
  nt2::table<T> a = nt2::reshape(nt2::_(T(0), T(8)), 3, 3);
  NT2_TEST_EQUAL( nt2::sx(nt2::tag::if_else_(), nt2::is_lez(a), a, a), a);
}
NT2_TEST_CASE_TPL( sx_3, (float) )//NT2_TYPES )
{
  nt2::table<T> a = nt2::reshape(nt2::_(T(0), T(8)), 3, 3);
  nt2::table<T> b = nt2::repnum(T(1), 3, 1);
  NT2_TEST_EQUAL( nt2::sx(nt2::tag::fma_(), a, b, a), a+a);
}
NT2_TEST_CASE_TPL( sx_4, (float) )//NT2_TYPES )
{
  nt2::table<T> a = nt2::reshape(nt2::_(T(0), T(8)), 3, 3);
  nt2::table<T> b = nt2::repnum(T(1), 1, 3);
  NT2_TEST_EQUAL(nt2::sx(nt2::tag::fma_(), a, b, a), a+a);
}
NT2_TEST_CASE_TPL( sx_5, (float) )//NT2_TYPES )
{
  nt2::table<T> a = nt2::_(T(1), T(4));
  nt2::table<T> b =  nt2::reshape(a, 4, 1);
  nt2::table<T> c(nt2::of_size(4, 4));

 for(int i=1; i <= 4 ; ++i)
 {
   for(int j=1; j <= 4 ; ++j)
   {
     c(i, j) = i+j;
   }
 }
  NT2_TEST_EQUAL(nt2::sx(nt2::tag::plus_(), a, b), c);
}

