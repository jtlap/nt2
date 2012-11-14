/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#define NT2_UNIT_MODULE "nt2::of_size max function"

#include <nt2/core/utility/of_size.hpp>
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
  namespace utility = nt2::utility;

  _1D x1(5)       , y1(7);
  _2D x2(3,5)     , y2(7,2);
  _3D x3(3,5,2)   , y3(7,2,4);
  _4D x4(3,5,2,9) , y4(7,2,4,8);

  NT2_TEST_EQUAL( utility::max(x1,y1), y1);
  NT2_TEST_EQUAL( utility::max(x1,x2), _2D(5,5));
  NT2_TEST_EQUAL( utility::max(x1,x3), _3D(5,5,2));
  NT2_TEST_EQUAL( utility::max(x1,x4), _4D(5,5,2,9));

  NT2_TEST_EQUAL( utility::max(x2,y2), _2D(7,5));
  NT2_TEST_EQUAL( utility::max(x2,y3), _3D(7,5,4));
  NT2_TEST_EQUAL( utility::max(x2,y4), _4D(7,5,4,8));

  NT2_TEST_EQUAL( utility::max(x3,y3), _3D(7,5,4));
  NT2_TEST_EQUAL( utility::max(x3,y4), _4D(7,5,4,8));

  NT2_TEST_EQUAL( utility::max(x4,y4), _4D(7,5,4,9));

  NT2_TEST_EQUAL( utility::max(_1D(),_4D()), _4D());
}

NT2_TEST_CASE( static_extent_max )
{
  using nt2::of_size_;
  namespace utility = nt2::utility;

  of_size_<5>       x1;
  of_size_<7>       y1;
  of_size_<3,5>     x2;
  of_size_<7,2>     y2;
  of_size_<3,5,2>   x3;
  of_size_<7,2,4>   y3;
  of_size_<3,5,2,9> x4;
  of_size_<7,2,4,8> y4;

  NT2_TEST_EQUAL( utility::max(x1,y1), y1);
  NT2_TEST_EQUAL( utility::max(x1,x2), (of_size_<5,5>()));
  NT2_TEST_EQUAL( utility::max(x1,x3), (of_size_<5,5,2>()));
  NT2_TEST_EQUAL( utility::max(x1,x4), (of_size_<5,5,2,9>()));

  NT2_TEST_EQUAL( utility::max(x2,y2), (of_size_<7,5>()));
  NT2_TEST_EQUAL( utility::max(x2,y3), (of_size_<7,5,4>()));
  NT2_TEST_EQUAL( utility::max(x2,y4), (of_size_<7,5,4,8>()));

  NT2_TEST_EQUAL( utility::max(x3,y3), (of_size_<7,5,4>()));
  NT2_TEST_EQUAL( utility::max(x3,y4), (of_size_<7,5,4,8>()));

  NT2_TEST_EQUAL( utility::max(x4,y4), (of_size_<7,5,4,9>()));
}
