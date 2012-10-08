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

  NT2_TEST_EQUAL( sub2ind( make_vector(), make_vector() ), 0u);
}

NT2_TEST_CASE( sub2ind_0D_base )
{
  using nt2::sub2ind;
  using boost::fusion::make_vector;

  NT2_TEST_EQUAL( sub2ind( make_vector(), make_vector(), make_vector(-1) ), 0u);
}

NT2_TEST_CASE( sub2ind_1D )
{
  using nt2::sub2ind;
  using boost::fusion::make_vector;

  NT2_TEST_EQUAL( sub2ind( make_vector(5), make_vector(1) ), 0u);
  NT2_TEST_EQUAL( sub2ind( make_vector(5), make_vector(2) ), 1u);
  NT2_TEST_EQUAL( sub2ind( make_vector(5), make_vector(3) ), 2u);
  NT2_TEST_EQUAL( sub2ind( make_vector(5), make_vector(4) ), 3u);
  NT2_TEST_EQUAL( sub2ind( make_vector(5), make_vector(5) ), 4u);
}

NT2_TEST_CASE( sub2ind_1D_base )
{
  using nt2::sub2ind;
  using boost::fusion::make_vector;

  NT2_TEST_EQUAL( sub2ind( make_vector(5), make_vector(-2), make_vector(-2) ), 0u);
  NT2_TEST_EQUAL( sub2ind( make_vector(5), make_vector(-1), make_vector(-2) ), 1u);
  NT2_TEST_EQUAL( sub2ind( make_vector(5), make_vector( 0), make_vector(-2) ), 2u);
  NT2_TEST_EQUAL( sub2ind( make_vector(5), make_vector( 1), make_vector(-2) ), 3u);
  NT2_TEST_EQUAL( sub2ind( make_vector(5), make_vector( 2), make_vector(-2) ), 4u);
}

NT2_TEST_CASE( sub2ind_2D )
{
  using nt2::sub2ind;
  using boost::fusion::make_vector;

  NT2_TEST_EQUAL( sub2ind( make_vector(3,5), make_vector(1,1) ), 0u);
  NT2_TEST_EQUAL( sub2ind( make_vector(3,5), make_vector(2,1) ), 1u);
  NT2_TEST_EQUAL( sub2ind( make_vector(3,5), make_vector(3,1) ), 2u);

  NT2_TEST_EQUAL( sub2ind( make_vector(3,5), make_vector(1,2) ), 3u);
  NT2_TEST_EQUAL( sub2ind( make_vector(3,5), make_vector(2,2) ), 4u);
  NT2_TEST_EQUAL( sub2ind( make_vector(3,5), make_vector(3,2) ), 5u);

  NT2_TEST_EQUAL( sub2ind( make_vector(3,5), make_vector(1,3) ), 6u);
  NT2_TEST_EQUAL( sub2ind( make_vector(3,5), make_vector(2,3) ), 7u);
  NT2_TEST_EQUAL( sub2ind( make_vector(3,5), make_vector(3,3) ), 8u);

  NT2_TEST_EQUAL( sub2ind( make_vector(3,5), make_vector(1,4) ), 9u);
  NT2_TEST_EQUAL( sub2ind( make_vector(3,5), make_vector(2,4) ), 10u);
  NT2_TEST_EQUAL( sub2ind( make_vector(3,5), make_vector(3,4) ), 11u);

  NT2_TEST_EQUAL( sub2ind( make_vector(3,5), make_vector(1,5) ), 12u);
  NT2_TEST_EQUAL( sub2ind( make_vector(3,5), make_vector(2,5) ), 13u);
  NT2_TEST_EQUAL( sub2ind( make_vector(3,5), make_vector(3,5) ), 14u);
}

NT2_TEST_CASE( sub2ind_2D_base )
{
  using nt2::sub2ind;
  using boost::fusion::make_vector;

  NT2_TEST_EQUAL( sub2ind( make_vector(3,5), make_vector(-1,-2), make_vector(-1,-2) ), 0u);
  NT2_TEST_EQUAL( sub2ind( make_vector(3,5), make_vector( 0,-2), make_vector(-1,-2) ), 1u);
  NT2_TEST_EQUAL( sub2ind( make_vector(3,5), make_vector( 1,-2), make_vector(-1,-2) ), 2u);

  NT2_TEST_EQUAL( sub2ind( make_vector(3,5), make_vector(-1,-1), make_vector(-1,-2) ), 3u);
  NT2_TEST_EQUAL( sub2ind( make_vector(3,5), make_vector( 0,-1), make_vector(-1,-2) ), 4u);
  NT2_TEST_EQUAL( sub2ind( make_vector(3,5), make_vector( 1,-1), make_vector(-1,-2) ), 5u);

  NT2_TEST_EQUAL( sub2ind( make_vector(3,5), make_vector(-1, 0), make_vector(-1,-2) ), 6u);
  NT2_TEST_EQUAL( sub2ind( make_vector(3,5), make_vector( 0, 0), make_vector(-1,-2) ), 7u);
  NT2_TEST_EQUAL( sub2ind( make_vector(3,5), make_vector( 1, 0), make_vector(-1,-2) ), 8u);

  NT2_TEST_EQUAL( sub2ind( make_vector(3,5), make_vector(-1, 1), make_vector(-1,-2) ), 9u);
  NT2_TEST_EQUAL( sub2ind( make_vector(3,5), make_vector( 0, 1), make_vector(-1,-2) ), 10u);
  NT2_TEST_EQUAL( sub2ind( make_vector(3,5), make_vector( 1, 1), make_vector(-1,-2) ), 11u);

  NT2_TEST_EQUAL( sub2ind( make_vector(3,5), make_vector(-1, 2), make_vector(-1,-2) ), 12u);
  NT2_TEST_EQUAL( sub2ind( make_vector(3,5), make_vector( 0, 2), make_vector(-1,-2) ), 13u);
  NT2_TEST_EQUAL( sub2ind( make_vector(3,5), make_vector( 1, 2), make_vector(-1,-2) ), 14u);
}

NT2_TEST_CASE( sub2ind_3D )
{
  using nt2::sub2ind;
  using boost::fusion::make_vector;

  NT2_TEST_EQUAL( sub2ind( make_vector(2,2,2), make_vector(1,1,1) ), 0u);
  NT2_TEST_EQUAL( sub2ind( make_vector(2,2,2), make_vector(2,1,1) ), 1u);

  NT2_TEST_EQUAL( sub2ind( make_vector(2,2,2), make_vector(1,2,1) ), 2u);
  NT2_TEST_EQUAL( sub2ind( make_vector(2,2,2), make_vector(2,2,1) ), 3u);

  NT2_TEST_EQUAL( sub2ind( make_vector(2,2,2), make_vector(1,1,2) ), 4u);
  NT2_TEST_EQUAL( sub2ind( make_vector(2,2,2), make_vector(2,1,2) ), 5u);

  NT2_TEST_EQUAL( sub2ind( make_vector(2,2,2), make_vector(1,2,2) ), 6u);
  NT2_TEST_EQUAL( sub2ind( make_vector(2,2,2), make_vector(2,2,2) ), 7u);
}

NT2_TEST_CASE( sub2ind_3D_base )
{
  using nt2::sub2ind;
  using boost::fusion::make_vector;

  NT2_TEST_EQUAL( sub2ind( make_vector(2,2,2), make_vector(-1,1,2), make_vector(-1,1,2) ), 0u);
  NT2_TEST_EQUAL( sub2ind( make_vector(2,2,2), make_vector( 0,1,2), make_vector(-1,1,2) ), 1u);

  NT2_TEST_EQUAL( sub2ind( make_vector(2,2,2), make_vector(-1,2,2), make_vector(-1,1,2) ), 2u);
  NT2_TEST_EQUAL( sub2ind( make_vector(2,2,2), make_vector( 0,2,2), make_vector(-1,1,2) ), 3u);

  NT2_TEST_EQUAL( sub2ind( make_vector(2,2,2), make_vector(-1,1,3), make_vector(-1,1,2) ), 4u);
  NT2_TEST_EQUAL( sub2ind( make_vector(2,2,2), make_vector( 0,1,3), make_vector(-1,1,2) ), 5u);

  NT2_TEST_EQUAL( sub2ind( make_vector(2,2,2), make_vector(-1,2,3), make_vector(-1,1,2) ), 6u);
  NT2_TEST_EQUAL( sub2ind( make_vector(2,2,2), make_vector( 0,2,3), make_vector(-1,1,2) ), 7u);
}

NT2_TEST_CASE( sub2ind_4D )
{
  using nt2::sub2ind;
  using boost::fusion::make_vector;

  NT2_TEST_EQUAL( sub2ind( make_vector(2,2,2,2), make_vector(1,1,1,1) ), 0u);
  NT2_TEST_EQUAL( sub2ind( make_vector(2,2,2,2), make_vector(2,1,1,1) ), 1u);

  NT2_TEST_EQUAL( sub2ind( make_vector(2,2,2,2), make_vector(1,2,1,1) ), 2u);
  NT2_TEST_EQUAL( sub2ind( make_vector(2,2,2,2), make_vector(2,2,1,1) ), 3u);

  NT2_TEST_EQUAL( sub2ind( make_vector(2,2,2,2), make_vector(1,1,2,1) ), 4u);
  NT2_TEST_EQUAL( sub2ind( make_vector(2,2,2,2), make_vector(2,1,2,1) ), 5u);

  NT2_TEST_EQUAL( sub2ind( make_vector(2,2,2,2), make_vector(1,2,2,1) ), 6u);
  NT2_TEST_EQUAL( sub2ind( make_vector(2,2,2,2), make_vector(2,2,2,1) ), 7u);

  NT2_TEST_EQUAL( sub2ind( make_vector(2,2,2,2), make_vector(1,1,1,2) ), 8u);
  NT2_TEST_EQUAL( sub2ind( make_vector(2,2,2,2), make_vector(2,1,1,2) ), 9u);

  NT2_TEST_EQUAL( sub2ind( make_vector(2,2,2,2), make_vector(1,2,1,2) ), 10u);
  NT2_TEST_EQUAL( sub2ind( make_vector(2,2,2,2), make_vector(2,2,1,2) ), 11u);

  NT2_TEST_EQUAL( sub2ind( make_vector(2,2,2,2), make_vector(1,1,2,2) ), 12u);
  NT2_TEST_EQUAL( sub2ind( make_vector(2,2,2,2), make_vector(2,1,2,2) ), 13u);

  NT2_TEST_EQUAL( sub2ind( make_vector(2,2,2,2), make_vector(1,2,2,2) ), 14u);
  NT2_TEST_EQUAL( sub2ind( make_vector(2,2,2,2), make_vector(2,2,2,2) ), 15u);
}

NT2_TEST_CASE( sub2ind_4D_base )
{
  using nt2::sub2ind;
  using boost::fusion::make_vector;

  NT2_TEST_EQUAL( sub2ind( make_vector(2,2,2,2), make_vector(-1,1,2,0), make_vector(-1,1,2,0) ), 0u);
  NT2_TEST_EQUAL( sub2ind( make_vector(2,2,2,2), make_vector( 0,1,2,0), make_vector(-1,1,2,0) ), 1u);

  NT2_TEST_EQUAL( sub2ind( make_vector(2,2,2,2), make_vector(-1,2,2,0), make_vector(-1,1,2,0) ), 2u);
  NT2_TEST_EQUAL( sub2ind( make_vector(2,2,2,2), make_vector( 0,2,2,0), make_vector(-1,1,2,0) ), 3u);

  NT2_TEST_EQUAL( sub2ind( make_vector(2,2,2,2), make_vector(-1,1,3,0), make_vector(-1,1,2,0) ), 4u);
  NT2_TEST_EQUAL( sub2ind( make_vector(2,2,2,2), make_vector( 0,1,3,0), make_vector(-1,1,2,0) ), 5u);

  NT2_TEST_EQUAL( sub2ind( make_vector(2,2,2,2), make_vector(-1,2,3,0), make_vector(-1,1,2,0) ), 6u);
  NT2_TEST_EQUAL( sub2ind( make_vector(2,2,2,2), make_vector( 0,2,3,0), make_vector(-1,1,2,0) ), 7u);

  NT2_TEST_EQUAL( sub2ind( make_vector(2,2,2,2), make_vector(-1,1,2,1), make_vector(-1,1,2,0) ), 8u);
  NT2_TEST_EQUAL( sub2ind( make_vector(2,2,2,2), make_vector( 0,1,2,1), make_vector(-1,1,2,0) ), 9u);

  NT2_TEST_EQUAL( sub2ind( make_vector(2,2,2,2), make_vector(-1,2,2,1), make_vector(-1,1,2,0) ), 10u);
  NT2_TEST_EQUAL( sub2ind( make_vector(2,2,2,2), make_vector( 0,2,2,1), make_vector(-1,1,2,0) ), 11u);

  NT2_TEST_EQUAL( sub2ind( make_vector(2,2,2,2), make_vector(-1,1,3,1), make_vector(-1,1,2,0) ), 12u);
  NT2_TEST_EQUAL( sub2ind( make_vector(2,2,2,2), make_vector( 0,1,3,1), make_vector(-1,1,2,0) ), 13u);

  NT2_TEST_EQUAL( sub2ind( make_vector(2,2,2,2), make_vector(-1,2,3,1), make_vector(-1,1,2,0) ), 14u);
  NT2_TEST_EQUAL( sub2ind( make_vector(2,2,2,2), make_vector( 0,2,3,1), make_vector(-1,1,2,0) ), 15u);
}
