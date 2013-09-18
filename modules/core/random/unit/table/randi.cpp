//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/table.hpp>
#include <nt2/include/functions/globalmax.hpp>
#include <nt2/include/functions/globalmin.hpp>
#include <nt2/include/functions/randi.hpp>
#include <nt2/include/functions/size.hpp>
#include <nt2/include/functions/cons.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/basic.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/exceptions.hpp>

NT2_TEST_CASE_TPL( randi_scalar, NT2_INTEGRAL_TYPES)
{
  T k = nt2::randi(T(100));
  NT2_TEST_GREATER_EQUAL(k, T(1) );
  NT2_TEST_LESSER_EQUAL(k, T(100));

  nt2::table<T> tg = 100;

  k = nt2::randi(tg);
  NT2_TEST_GREATER_EQUAL(k, T(1) );
  NT2_TEST_LESSER_EQUAL(k, T(100));

  boost::array<T,2> rg = {{13,37}};

  k = nt2::randi(rg);
  NT2_TEST_GREATER_EQUAL(k, T(13) );
  NT2_TEST_LESSER_EQUAL(k, T(37));

  nt2::table<T> rgs = nt2::cons(T(13),T(37));

  k = nt2::randi(rgs);
  NT2_TEST_GREATER_EQUAL(k, T(13) );
  NT2_TEST_LESSER_EQUAL(k, T(37));
}

NT2_TEST_CASE( randi_size )
{
  // randi(i,ext)
  NT2_TEST_EQUAL( nt2::extent( nt2::randi(5,nt2::of_size(4,5)) )
                , nt2::of_size(4,5)
                );

  NT2_TEST_EQUAL( nt2::extent( nt2::randi(5,nt2::of_size(4,5,6)) )
                , nt2::of_size(4,5,6)
                );

  NT2_TEST_EQUAL( nt2::extent( nt2::randi(5,nt2::of_size(4,5,6,7)) )
                , nt2::of_size(4,5,6,7)
                );

  // randi([i j],ext)
  boost::array<int,2> rg = {{13,37}};

  NT2_TEST_EQUAL( nt2::extent( nt2::randi(rg,nt2::of_size(4,5)) )
                , nt2::of_size(4,5)
                );

  NT2_TEST_EQUAL( nt2::extent( nt2::randi(rg,nt2::of_size(4,5,6)) )
                , nt2::of_size(4,5,6)
                );

  NT2_TEST_EQUAL( nt2::extent( nt2::randi(rg,nt2::of_size(4,5,6,7)) )
                , nt2::of_size(4,5,6,7)
                );

  // randi([i j],ext)
  nt2::table<int> tg = nt2::cons(13,37);
  NT2_TEST_EQUAL( nt2::extent( nt2::randi(tg,nt2::of_size(4,5)) )
                , nt2::of_size(4,5)
                );

  NT2_TEST_EQUAL( nt2::extent( nt2::randi(tg,nt2::of_size(4,5,6)) )
                , nt2::of_size(4,5,6)
                );

  NT2_TEST_EQUAL( nt2::extent( nt2::randi(tg,nt2::of_size(4,5,6,7)) )
                , nt2::of_size(4,5,6,7)
                );

  // randi(i,size)
  NT2_TEST_EQUAL( nt2::extent( nt2::randi(5, nt2::size(tg)) )
                , tg.extent()
                );

  // randi([i j],size)
  NT2_TEST_EQUAL( nt2::extent( nt2::randi(rg, nt2::size(tg)) )
                , tg.extent()
                );

  // randi([i j],size)
  NT2_TEST_EQUAL( nt2::extent( nt2::randi(tg, nt2::size(tg)) )
                , tg.extent()
                );

  // randi(i,size...)
  NT2_TEST_EQUAL( nt2::extent( nt2::randi(5,7) )
                , nt2::of_size(7,7)
                );

  NT2_TEST_EQUAL( nt2::extent( nt2::randi(5,4,5) )
                , nt2::of_size(4,5)
                );

  NT2_TEST_EQUAL( nt2::extent( nt2::randi(5,4,5,6) )
                , nt2::of_size(4,5,6)
                );

  NT2_TEST_EQUAL( nt2::extent( nt2::randi(5,4,5,6,7) )
                , nt2::of_size(4,5,6,7 )
                );

  // randi([i j],size...)
  NT2_TEST_EQUAL( nt2::extent( nt2::randi(rg,7) )
                , nt2::of_size(7,7)
                );

  NT2_TEST_EQUAL( nt2::extent( nt2::randi(rg,4,5) )
                , nt2::of_size(4,5)
                );

  NT2_TEST_EQUAL( nt2::extent( nt2::randi(rg,4,5,6) )
                , nt2::of_size(4,5,6)
                );

  NT2_TEST_EQUAL( nt2::extent( nt2::randi(rg,4,5,6,7) )
                , nt2::of_size(4,5,6,7 )
                );

  // randi([i j],size...)
  NT2_TEST_EQUAL( nt2::extent( nt2::randi(tg,7) )
                , nt2::of_size(7,7)
                );

  NT2_TEST_EQUAL( nt2::extent( nt2::randi(tg,4,5) )
                , nt2::of_size(4,5)
                );

  NT2_TEST_EQUAL( nt2::extent( nt2::randi(tg,4,5,6) )
                , nt2::of_size(4,5,6)
                );

  NT2_TEST_EQUAL( nt2::extent( nt2::randi(tg,4,5,6,7) )
                , nt2::of_size(4,5,6,7 )
                );
}

NT2_TEST_CASE_TPL( randi_sizes, NT2_INTEGRAL_TYPES )
{
  // Single imax
  {
    nt2::table<T> x1 = nt2::randi(T(10), 8);
    NT2_TEST_GREATER_EQUAL(nt2::globalmin(x1), T(1));
    NT2_TEST_LESSER_EQUAL(nt2::globalmax(x1), T(10));

    nt2::table<T> x2 = nt2::randi(T(10), 8,8 );
    NT2_TEST_GREATER_EQUAL(nt2::globalmin(x2), T(1));
    NT2_TEST_LESSER_EQUAL(nt2::globalmax(x2), T(10));

    nt2::table<T> x3 = nt2::randi(T(10), 8,4,2 );
    NT2_TEST_GREATER_EQUAL(nt2::globalmin(x3), T(1));
    NT2_TEST_LESSER_EQUAL(nt2::globalmax(x3), T(10));

    nt2::table<T> x4 = nt2::randi(T(10), 4,4,2,2 );
    NT2_TEST_GREATER_EQUAL(nt2::globalmin(x4), T(1));
    NT2_TEST_LESSER_EQUAL(nt2::globalmax(x4), T(10));
  }

  // Range as fusion sequence
  {
    boost::array<T,2> rg = {{13,37}};

    nt2::table<T> x1 = nt2::randi(rg, 8);
    NT2_TEST_GREATER_EQUAL(nt2::globalmin(x1), T(13));
    NT2_TEST_LESSER_EQUAL(nt2::globalmax(x1), T(37));

    nt2::table<T> x2 = nt2::randi(rg, 8,8 );
    NT2_TEST_GREATER_EQUAL(nt2::globalmin(x2), T(13));
    NT2_TEST_LESSER_EQUAL(nt2::globalmax(x2), T(37));

    nt2::table<T> x3 = nt2::randi(rg, 8,4,2 );
    NT2_TEST_GREATER_EQUAL(nt2::globalmin(x3), T(13));
    NT2_TEST_LESSER_EQUAL(nt2::globalmax(x3), T(37));

    nt2::table<T> x4 = nt2::randi(rg, 4,4,2,2 );
    NT2_TEST_GREATER_EQUAL(nt2::globalmin(x4), T(13));
    NT2_TEST_LESSER_EQUAL(nt2::globalmax(x4), T(37));
  }

  // Range as table
  {
    nt2::table<T> rg = nt2::cons(T(13),T(37));

    nt2::table<T> x1 = nt2::randi(rg, 8);
    NT2_TEST_GREATER_EQUAL(nt2::globalmin(x1), T(13));
    NT2_TEST_LESSER_EQUAL(nt2::globalmax(x1), T(37));

    nt2::table<T> x2 = nt2::randi(rg, 8,8 );
    NT2_TEST_GREATER_EQUAL(nt2::globalmin(x2), T(13));
    NT2_TEST_LESSER_EQUAL(nt2::globalmax(x2), T(37));

    nt2::table<T> x3 = nt2::randi(rg, 8,4,2 );
    NT2_TEST_GREATER_EQUAL(nt2::globalmin(x3), T(13));
    NT2_TEST_LESSER_EQUAL(nt2::globalmax(x3), T(37));

    nt2::table<T> x4 = nt2::randi(rg, 4,4,2,2 );
    NT2_TEST_GREATER_EQUAL(nt2::globalmin(x4), T(13));
    NT2_TEST_LESSER_EQUAL(nt2::globalmax(x4), T(37));
  }
}

NT2_TEST_CASE_TPL( randi_typed_extent, NT2_INTEGRAL_TYPES )
{
  nt2::table<T> x = nt2::randi(T(10), nt2::of_size(8,8) );
  NT2_TEST_GREATER_EQUAL(nt2::globalmin(x), T(1));
  NT2_TEST_LESSER_EQUAL(nt2::globalmax(x), T(10));

  boost::array<T,2> rg = {{13,37}};
  nt2::table<T> y = nt2::randi(rg, nt2::of_size(8,8) );
  NT2_TEST_GREATER_EQUAL(nt2::globalmin(y), T(13));
  NT2_TEST_LESSER_EQUAL(nt2::globalmax(y), T(37));

  nt2::table<T> tg = nt2::cons(T(13),T(37));

  nt2::table<T> x1 = nt2::randi(tg,  nt2::of_size(8,8) );
  NT2_TEST_GREATER_EQUAL(nt2::globalmin(x1), T(13));
  NT2_TEST_LESSER_EQUAL(nt2::globalmax(x1), T(37));
}

NT2_TEST_CASE_TPL( randi_typed_size, NT2_INTEGRAL_TYPES )
{
  nt2::table<T> a( nt2::of_size(4,5) );

  nt2::table<T> x = nt2::randi(T(10), nt2::size(a) );
  NT2_TEST_GREATER_EQUAL(nt2::globalmin(x), T(1));
  NT2_TEST_LESSER_EQUAL(nt2::globalmax(x), T(10));

  boost::array<T,2> rg = {{13,37}};
  nt2::table<T> y = nt2::randi(rg, nt2::size(a) );
  NT2_TEST_GREATER_EQUAL(nt2::globalmin(y), T(13));
  NT2_TEST_LESSER_EQUAL(nt2::globalmax(y), T(37));

  nt2::table<T> tg = nt2::cons(T(13),T(37));

  nt2::table<T> x1 = nt2::randi(tg, nt2::size(a) );
  NT2_TEST_GREATER_EQUAL(nt2::globalmin(x1), T(13));
  NT2_TEST_LESSER_EQUAL(nt2::globalmax(x1), T(37));
}
