//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#define NT2_UNIT_MODULE "nt2::max_extent function"

#include <nt2/table.hpp>
#include <nt2/core/utility/max_extent.hpp>
#include <nt2/include/functions/enumerate.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/basic.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>

NT2_TEST_CASE( dynamic_extent_max )
{
  using nt2::_1D;
  using nt2::_2D;
  using nt2::_3D;
  using nt2::_4D;
  using nt2::utility::max_extent;
  using nt2::table;

  table<float, _1D> x1(_1D(5))        , y1(_1D(7));
  table<float, _2D> x2(_2D(3,5))      , y2(_2D(7,2));
  table<float, _3D> x3(_3D(3,5,2))    , y3(_3D(7,2,4));
  table<float, _4D> x4(_4D(3,5,2,9))  , y4(_4D(7,2,4,8));

  NT2_TEST_EQUAL( max_extent(x1,y1), _1D(7));
  NT2_TEST_EQUAL( max_extent(x1,x2), _2D(5,5));
  NT2_TEST_EQUAL( max_extent(x1,x3), _3D(5,5,2));
  NT2_TEST_EQUAL( max_extent(x1,x4), _4D(5,5,2,9));

  NT2_TEST_EQUAL( max_extent(x2,x1,y2), _2D(7,5));
  NT2_TEST_EQUAL( max_extent(x2,x1,y2), _2D(7,5));
  NT2_TEST_EQUAL( max_extent(x2,x1,y3), _3D(7,5,4));
  NT2_TEST_EQUAL( max_extent(x2,x1,y4), _4D(7,5,4,8));

  NT2_TEST_EQUAL( max_extent(x3,x1,x2,y3), _3D(7,5,4));
  NT2_TEST_EQUAL( max_extent(x3,x1,x2,y4), _4D(7,5,4,8));

  NT2_TEST_EQUAL( max_extent(x4,x1,x2,y4), _4D(7,5,4,9));
}

NT2_TEST_CASE( static_extent_max )
{
  using nt2::of_size_;
  using nt2::utility::max_extent;
  using nt2::table;

  table<float, of_size_<5>       > x1;
  table<float, of_size_<7>       > y1;
  table<float, of_size_<3,5>     > x2;
  table<float, of_size_<7,2>     > y2;
  table<float, of_size_<3,5,2>   > x3;
  table<float, of_size_<7,2,4>   > y3;
  table<float, of_size_<3,5,2,9> > x4;
  table<float, of_size_<7,2,4,8> > y4;

  NT2_TEST_EQUAL( max_extent(x1,y1), (of_size_<7>()));
  NT2_TEST_EQUAL( max_extent(x1,x2), (of_size_<5,5>()));
  NT2_TEST_EQUAL( max_extent(x1,x3), (of_size_<5,5,2>()));
  NT2_TEST_EQUAL( max_extent(x1,x4), (of_size_<5,5,2,9>()));

  NT2_TEST_EQUAL( max_extent(x2,y2,x1), (of_size_<7,5>()));
  NT2_TEST_EQUAL( max_extent(x2,y3,x1), (of_size_<7,5,4>()));
  NT2_TEST_EQUAL( max_extent(x2,y4,x1), (of_size_<7,5,4,8>()));

  NT2_TEST_EQUAL( max_extent(x3,x2,y3,x1), (of_size_<7,5,4>()));
  NT2_TEST_EQUAL( max_extent(x3,x2,y4,x1), (of_size_<7,5,4,8>()));

  NT2_TEST_EQUAL( max_extent(x4,x2,y4,x1), (of_size_<7,5,4,9>()));
}
