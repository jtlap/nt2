/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#define NT2_UNIT_MODULE "nt2::globalasum2 function"

#include <nt2/table.hpp>
#include <nt2/include/functions/globalasum2.hpp>
#include <nt2/include/functions/asum2.hpp>
#include <nt2/include/functions/reshape.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/basic.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>
#include <nt2/sdk/unit/tests/exceptions.hpp>
#include <nt2/table.hpp>

NT2_TEST_CASE_TPL( globalasum2, NT2_REAL_TYPES )
{
  using nt2::_;
  using nt2::asum2;
  nt2::table<T> a = nt2::reshape(nt2::_(T(1), T(9)), 3, 3);
  NT2_TEST_EQUAL( nt2::globalasum2(a), asum2(a(_))(1));
}
