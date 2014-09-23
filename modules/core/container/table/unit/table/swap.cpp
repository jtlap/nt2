//==============================================================================
//         Copyright 2009 - 2014   LRI UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012 - 2014   NumScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/table.hpp>
#include <nt2/include/functions/swap.hpp>
#include <nt2/include/functions/colon.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>

NT2_TEST_CASE(swap_table)
{
  nt2::table<float>  x(nt2::of_size(5,5)), ox, y(nt2::of_size(2,2)),oy;

  for(std::size_t i=1;i<=numel(x);++i) x(i) = 1.f+i;
  for(std::size_t i=1;i<=numel(y);++i) y(i) = 2.f*i;

  ox = x;
  oy = y;

  nt2::swap(x,y);

  NT2_TEST_EQUAL( x, oy);
  NT2_TEST_EQUAL( y, ox);
}

NT2_TEST_CASE( swap_different_table )
{
  nt2::table<float>           x(nt2::of_size(3,5)), ox;
  nt2::table<float,nt2::_2D>  y(nt2::of_size(5,6)),oy;

  for(std::size_t i=1;i<=numel(x);++i) x(i) = 1.f+i;
  for(std::size_t i=1;i<=numel(y);++i) y(i) = 2.f*i;

  ox = x;
  oy = y;

  nt2::swap(x,y);

  NT2_TEST_EQUAL( x, oy);
  NT2_TEST_EQUAL( y, ox);
}

NT2_TEST_CASE( swap_different_layour )
{
  nt2::table<float>           x(nt2::of_size(3,5)), ox;
  nt2::table<float, nt2::of_size_<3,5> >  y,oy;

  for(std::size_t i=1;i<=numel(x);++i) x(i) = 1.f+i;
  for(std::size_t i=1;i<=numel(y);++i) y(i) = 2.f*i;

  ox = x;
  oy = y;

  nt2::swap(x,y);

  NT2_TEST_EQUAL( x, oy);
  NT2_TEST_EQUAL( y, ox);
}

NT2_TEST_CASE( swap_sub_table )
{
  using nt2::_;

  nt2::table<float> x(nt2::of_size(5,5)), ox, y(nt2::of_size(5,5)),oy;

  for(std::size_t i=1;i<=numel(x);++i)
  {
    x(i) = 1.f+i;
    y(i) = 2.f*i;
  }

  oy = x;
  oy(_(2,4),_(2,4)) = y(_(2,4),_(2,4));

  ox = y;
  ox(_(2,4),_(2,4)) = x(_(2,4),_(2,4));

  nt2::swap(x(_(2,4),_(2,4)),y(_(2,4),_(2,4)));

  NT2_TEST_EQUAL( x, oy);
  NT2_TEST_EQUAL( y, ox);
}

NT2_TEST_CASE( swap_row_in_row )
{
  using nt2::_;

  nt2::table<float> x(nt2::of_size(5,5)), ox, y(nt2::of_size(5,5)),oy;

  for(std::size_t i=1;i<=numel(x);++i)
  {
    x(i) = 1.f+i;
    y(i) = 2.f*i;
  }

  oy = x;
  oy(_,3) = y(_,2);

  ox = y;
  ox(_,2) = x(_,3);

  nt2::swap(x(_,3),y(_,2));

  NT2_TEST_EQUAL( x, oy);
  NT2_TEST_EQUAL( y, ox);
}

NT2_TEST_CASE( swap_row_in_column )
{
  using nt2::_;

  nt2::table<float> x(nt2::of_size(5,5)), ox, y(nt2::of_size(5,5)),oy;

  for(std::size_t i=1;i<=numel(x);++i)
  {
    x(i) = 1.f+i;
    y(i) = 2.f*i;
  }

  oy = x;
  oy(_,3) = y(2,_);

  ox = y;
  ox(2,_) = x(_,3);

  nt2::swap(x(_,3),y(2,_));

  NT2_TEST_EQUAL( x, oy);
  NT2_TEST_EQUAL( y, ox);
}

NT2_TEST_CASE( swap_row_over_column )
{
  using nt2::_;

  nt2::table<float> x(nt2::of_size(5,5)), ox, r, c;

  for(std::size_t i=1;i<=numel(x);++i)
  {
    x(i) = 1.f+i;
  }

  ox = x;
  r = x(_,3);
  c = x(3,_);

  ox(_,3) = c;
  ox(3,_) = r;

  nt2::swap(x(_,3),x(3,_));

  NT2_TEST_EQUAL(x, ox);
}

NT2_TEST_CASE( swap_table_with_scalar )
{
  using nt2::_;

  nt2::table<float> x(nt2::of_size(3,3));
  float y = 13.37f;

  for(std::size_t i=1;i<=numel(x);++i)
  {
    x(i) = 1.f+i;
  }

  nt2::swap(y,x(1,_(1,1)));

  NT2_TEST_EQUAL( x(1), 13.37f);
  NT2_TEST_EQUAL( y, 2.f);

  nt2::swap(x(1,_(2,2)),y);

  NT2_TEST_EQUAL( x(4), 2.f);
  NT2_TEST_EQUAL( y, 5.f);
}
