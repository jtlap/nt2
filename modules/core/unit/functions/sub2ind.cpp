/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#define NT2_UNIT_MODULE "nt2::sub2ind function"

#include <nt2/include/functions/sub2ind.hpp>

#include <boost/array.hpp>
#include <boost/fusion/include/make_vector.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/basic.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>

NT2_TEST_CASE( sub2ind_0D )
{
  using nt2::sub2ind;
  using boost::fusion::make_vector;

  NT2_TEST_EQUAL( sub2ind( make_vector(), make_vector() ), 1);
}

NT2_TEST_CASE( sub2ind_0D_base )
{
  using nt2::sub2ind;
  using boost::fusion::make_vector;

  NT2_TEST_EQUAL( sub2ind( make_vector(), make_vector(), make_vector(-1) ), -1);
}

NT2_TEST_CASE( sub2ind_1D )
{
  using nt2::sub2ind;
  using boost::fusion::make_vector;

  NT2_TEST_EQUAL( sub2ind( make_vector(5), make_vector(1) ), 1);
  NT2_TEST_EQUAL( sub2ind( make_vector(5), make_vector(2) ), 2);
  NT2_TEST_EQUAL( sub2ind( make_vector(5), make_vector(3) ), 3);
  NT2_TEST_EQUAL( sub2ind( make_vector(5), make_vector(4) ), 4);
  NT2_TEST_EQUAL( sub2ind( make_vector(5), make_vector(5) ), 5);
}

NT2_TEST_CASE( sub2ind_1D_base )
{
  using nt2::sub2ind;
  using boost::fusion::make_vector;

  NT2_TEST_EQUAL( sub2ind( make_vector(5), make_vector(-2), make_vector(-1) ), -2);
  NT2_TEST_EQUAL( sub2ind( make_vector(5), make_vector(-1), make_vector(-1) ), -1);
  NT2_TEST_EQUAL( sub2ind( make_vector(5), make_vector( 0), make_vector(-1) ),  0);
  NT2_TEST_EQUAL( sub2ind( make_vector(5), make_vector( 1), make_vector(-1) ),  1);
  NT2_TEST_EQUAL( sub2ind( make_vector(5), make_vector( 2), make_vector(-1) ),  2);
}

NT2_TEST_CASE( sub2ind_2D )
{
  using nt2::sub2ind;
  using boost::fusion::make_vector;

  NT2_TEST_EQUAL( sub2ind( make_vector(3,5), make_vector(1,1) ), 1);
  NT2_TEST_EQUAL( sub2ind( make_vector(3,5), make_vector(2,1) ), 2);
  NT2_TEST_EQUAL( sub2ind( make_vector(3,5), make_vector(3,1) ), 3);

  NT2_TEST_EQUAL( sub2ind( make_vector(3,5), make_vector(1,2) ), 4);
  NT2_TEST_EQUAL( sub2ind( make_vector(3,5), make_vector(2,2) ), 5);
  NT2_TEST_EQUAL( sub2ind( make_vector(3,5), make_vector(3,2) ), 6);

  NT2_TEST_EQUAL( sub2ind( make_vector(3,5), make_vector(1,3) ), 7);
  NT2_TEST_EQUAL( sub2ind( make_vector(3,5), make_vector(2,3) ), 8);
  NT2_TEST_EQUAL( sub2ind( make_vector(3,5), make_vector(3,3) ), 9);

  NT2_TEST_EQUAL( sub2ind( make_vector(3,5), make_vector(1,4) ), 10);
  NT2_TEST_EQUAL( sub2ind( make_vector(3,5), make_vector(2,4) ), 11);
  NT2_TEST_EQUAL( sub2ind( make_vector(3,5), make_vector(3,4) ), 12);

  NT2_TEST_EQUAL( sub2ind( make_vector(3,5), make_vector(1,5) ), 13);
  NT2_TEST_EQUAL( sub2ind( make_vector(3,5), make_vector(2,5) ), 14);
  NT2_TEST_EQUAL( sub2ind( make_vector(3,5), make_vector(3,5) ), 15);
}

NT2_TEST_CASE( sub2ind_2D_base )
{
  using nt2::sub2ind;
  using boost::fusion::make_vector;

  NT2_TEST_EQUAL( sub2ind( make_vector(3,5), make_vector(-1,-2), make_vector(-1,-2) ), -1);
  NT2_TEST_EQUAL( sub2ind( make_vector(3,5), make_vector( 0,-2), make_vector(-1,-2) ),  0);
  NT2_TEST_EQUAL( sub2ind( make_vector(3,5), make_vector( 1,-2), make_vector(-1,-2) ),  1);

  NT2_TEST_EQUAL( sub2ind( make_vector(3,5), make_vector(-1,-1), make_vector(-1,-2) ), 2);
  NT2_TEST_EQUAL( sub2ind( make_vector(3,5), make_vector( 0,-1), make_vector(-1,-2) ), 3);
  NT2_TEST_EQUAL( sub2ind( make_vector(3,5), make_vector( 1,-1), make_vector(-1,-2) ), 4);

  NT2_TEST_EQUAL( sub2ind( make_vector(3,5), make_vector(-1, 0), make_vector(-1,-2) ), 5);
  NT2_TEST_EQUAL( sub2ind( make_vector(3,5), make_vector( 0, 0), make_vector(-1,-2) ), 6);
  NT2_TEST_EQUAL( sub2ind( make_vector(3,5), make_vector( 1, 0), make_vector(-1,-2) ), 7);

  NT2_TEST_EQUAL( sub2ind( make_vector(3,5), make_vector(-1, 1), make_vector(-1,-2) ), 8);
  NT2_TEST_EQUAL( sub2ind( make_vector(3,5), make_vector( 0, 1), make_vector(-1,-2) ), 9);
  NT2_TEST_EQUAL( sub2ind( make_vector(3,5), make_vector( 1, 1), make_vector(-1,-2) ), 10);

  NT2_TEST_EQUAL( sub2ind( make_vector(3,5), make_vector(-1, 2), make_vector(-1,-2) ), 11);
  NT2_TEST_EQUAL( sub2ind( make_vector(3,5), make_vector( 0, 2), make_vector(-1,-2) ), 12);
  NT2_TEST_EQUAL( sub2ind( make_vector(3,5), make_vector( 1, 2), make_vector(-1,-2) ), 13);
}

NT2_TEST_CASE( sub2ind_3D )
{
  using nt2::sub2ind;
  using boost::fusion::make_vector;

  NT2_TEST_EQUAL( sub2ind( make_vector(2,2,2), make_vector(1,1,1) ), 1);
  NT2_TEST_EQUAL( sub2ind( make_vector(2,2,2), make_vector(2,1,1) ), 2);

  NT2_TEST_EQUAL( sub2ind( make_vector(2,2,2), make_vector(1,2,1) ), 3);
  NT2_TEST_EQUAL( sub2ind( make_vector(2,2,2), make_vector(2,2,1) ), 4);

  NT2_TEST_EQUAL( sub2ind( make_vector(2,2,2), make_vector(1,1,2) ), 5);
  NT2_TEST_EQUAL( sub2ind( make_vector(2,2,2), make_vector(2,1,2) ), 6);

  NT2_TEST_EQUAL( sub2ind( make_vector(2,2,2), make_vector(1,2,2) ), 7);
  NT2_TEST_EQUAL( sub2ind( make_vector(2,2,2), make_vector(2,2,2) ), 8);
}
