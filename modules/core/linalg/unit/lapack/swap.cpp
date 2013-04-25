//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/include/functions/swap.hpp>
#include <nt2/include/functions/rand.hpp>
#include <nt2/include/functions/colon.hpp>
#include <nt2/table.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>

NT2_TEST_CASE_TPL(swap, NT2_REAL_TYPES )
{
  using nt2::_;

  typedef nt2::table<T>           t_t;
  typedef nt2::table<nt2_la_int>  t_i;

  t_t a = nt2::rand(8);

  t_t y,x;

  x = a( _ , 1 );
  y = a( _ , 7 ) ;

  t_t x1(x);
  t_t y1(y);

  nt2::swap(x,y);
  NT2_TEST_EQUAL( x, y1);
  NT2_TEST_EQUAL( y, x1);

}
