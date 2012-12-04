/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#define NT2_UNIT_MODULE "nt2::globalprod function"

#include <nt2/table.hpp>
#include <nt2/include/functions/globalprod.hpp>
#include <nt2/include/functions/zeros.hpp>
#include <nt2/include/constants/true.hpp>
#include <nt2/include/constants/false.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/basic.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>
#include <nt2/sdk/unit/tests/exceptions.hpp>
#include <nt2/table.hpp>

NT2_TEST_CASE_TPL( globalprod, NT2_TYPES )
{
  nt2::table<T> a = nt2::reshape(nt2::_(T(1), T(4)), 2, 2);
  NT2_TEST_EQUAL( nt2::globalprod(a), T(24));
  NT2_TEST_EQUAL( nt2::globalprod(T(1)), T(1));
  a(2, 2) = T(0);
  NT2_TEST_EQUAL( nt2::globalprod(a), T(0));
  NT2_TEST_EQUAL( nt2::globalprod(T(0)), T(0));
}

