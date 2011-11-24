/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#define NT2_UNIT_MODULE "nt2::table "

#include <nt2/table.hpp>
#include <nt2/core/functions/of_size.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/basic.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>

NT2_TEST_CASE_TPL( table_dimensions ,NT2_TYPES)
{
  using nt2::table;
  using nt2::_1D;
  using nt2::_2D;
  using nt2::_3D;
  using nt2::_4D;
  using nt2::meta::dimensions_of;

  NT2_TEST_EQUAL( (dimensions_of<table<int,_1D> >::value), 1UL) ;
  NT2_TEST_EQUAL( (dimensions_of<table<int,_2D> >::value), 2UL) ;
  NT2_TEST_EQUAL( (dimensions_of<table<int,_3D> >::value), 3UL) ;
  NT2_TEST_EQUAL( (dimensions_of<table<int,_4D> >::value), 4UL) ;
}
