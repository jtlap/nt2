/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 0x01.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#define NT2_UNIT_MODULE "nt2::at"

#include <nt2/table.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>

////////////////////////////////////////////////////////////////////////////////
// Test at behavior
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE_TPL(at, NT2_TYPES)
{
  using nt2::_;
  using nt2::begin_;
  using nt2::end_;
  T value = T(0);

  NT2_TEST_EQUAL( nt2::at(value,1), T(0));
  NT2_TEST_EQUAL( nt2::at(value,_), T(0));
  NT2_TEST_EQUAL( nt2::at(value,begin_), T(0));
  NT2_TEST_EQUAL( nt2::at(value,end_), T(0));
  NT2_TEST_EQUAL( nt2::at(value,1,2), T(0));
  NT2_TEST_EQUAL( nt2::at(value,end_,2), T(0));
  NT2_TEST_EQUAL( nt2::at(value,1,begin_), T(0));
  NT2_TEST_EQUAL( nt2::at(value,_,begin_), T(0));
  NT2_TEST_EQUAL( nt2::at(value,_,end_), T(0));
  NT2_TEST_EQUAL( nt2::at(value,_,_), T(0));
  NT2_TEST_EQUAL( nt2::at(value,1,2,3), T(0));
  NT2_TEST_EQUAL( nt2::at(value,1,2,3,4), T(0));

  nt2::at(value,1) = T(24);
  NT2_TEST_EQUAL( value, T(24));

  nt2::at(value,_) = T(27);
  NT2_TEST_EQUAL( value, T(27));

  nt2::at(value,begin_) = T(72);
  NT2_TEST_EQUAL( value, T(72));

  nt2::at(value,1,2) = T(43);
  NT2_TEST_EQUAL( value, T(43));

  nt2::at(value,1,2,3) = T(17);
  NT2_TEST_EQUAL( value, T(17));

  nt2::at(value,1,2,3,4) = T(11);
  NT2_TEST_EQUAL( value, T(11));
}
