/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#define NT2_UNIT_MODULE "nt2::global function"

#include <nt2/table.hpp>
// #include <nt2/include/functions/toint.hpp>
#include <nt2/include/functions/of_size.hpp>
#include <nt2/include/functions/global.hpp>
#include <nt2/include/functions/is_true.hpp>
#include <nt2/include/functions/is_nez.hpp>
#include <nt2/include/constants/true.hpp>
#include <nt2/include/functions/all.hpp>
#include <nt2/include/functions/sum.hpp>
#include <nt2/include/functions/prod.hpp>
#include <nt2/include/functions/reshape.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/basic.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>
#include <nt2/sdk/unit/tests/exceptions.hpp>
#include <nt2/table.hpp>

NT2_TEST_CASE_TPL( global, NT2_TYPES )
{
  nt2::table<T> a = nt2::reshape(nt2::_(T(1), T(9)), 3, 3);
  NT2_TEST_EQUAL( nt2::global(nt2::functor<nt2::tag::all_>(), a), true);
  NT2_TEST_EQUAL( nt2::global(nt2::functor<nt2::tag::sum_>(), a), T(45)); 
  NT2_TEST_EQUAL( nt2::global(nt2::functor<nt2::tag::all_>(), T(1)), true); 
  NT2_TEST_EQUAL( nt2::global(nt2::functor<nt2::tag::sum_>(), T(1)), T(1));
  a(3, 3) = T(0); 
  NT2_TEST_EQUAL( nt2::global(nt2::functor<nt2::tag::all_>(), a), false);
  NT2_TEST_EQUAL( nt2::global(nt2::functor<nt2::tag::sum_>(), a), T(45-9)); 
  NT2_TEST_EQUAL( nt2::global(nt2::functor<nt2::tag::all_>(), T(0)), false); 
  NT2_TEST_EQUAL( nt2::global(nt2::functor<nt2::tag::sum_>(), T(0)), T(0));
  a = nt2::reshape(nt2::_(T(1), T(4)), 2, 2);  
  NT2_TEST_EQUAL( nt2::global(nt2::functor<nt2::tag::prod_>(), a), T(24));
}

