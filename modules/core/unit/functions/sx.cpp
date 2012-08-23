/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#define NT2_UNIT_MODULE "nt2::sx function"

#include <nt2/table.hpp>
#include <nt2/include/functions/of_size.hpp>
#include <nt2/include/functions/sx.hpp>
#include <nt2/include/functions/bsxfun.hpp>
#include <nt2/include/functions/tsxfun.hpp>
#include <nt2/include/functions/isequal.hpp>
#include <nt2/include/functions/fma.hpp>
#include <nt2/include/functions/if_else.hpp>
#include <nt2/include/functions/if_zero_else.hpp>
#include <nt2/include/functions/is_lez.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/basic.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>
#include <nt2/sdk/unit/tests/exceptions.hpp>
#include <nt2/table.hpp>

NT2_TEST_CASE_TPL( sx, NT2_TYPES )
{
  nt2::table<T> a = nt2::reshape(nt2::_(T(0), T(8)), 3, 3);
  NT2_TEST( nt2::isequal(nt2::sx(nt2::tag::plus_(), a, a), a+a));
  NT2_TEST( nt2::isequal(nt2::sx(nt2::tag::plus_(), a, a),  nt2::bsxfun(nt2::functor<nt2::tag::plus_>(), a, a))); 
}
NT2_TEST_CASE_TPL( sx_0, NT2_TYPES )
{
  nt2::table<T> a = nt2::reshape(nt2::_(T(0), T(8)), 3, 3);
  NT2_TEST( nt2::isequal(nt2::sx(nt2::tag::if_zero_else_(), nt2::is_lez(a), a), a));
  NT2_TEST( nt2::isequal(nt2::sx(nt2::tag::if_zero_else_(), nt2::is_lez(a), a),  nt2::bsxfun(nt2::functor<nt2::tag::if_zero_else_>(), nt2::is_lez(a), a))); 
}

NT2_TEST_CASE_TPL( sx_1, NT2_TYPES )
{
  nt2::table<T> a = nt2::reshape(nt2::_(T(0), T(8)), 3, 3);
  NT2_TEST( nt2::isequal(nt2::sx(nt2::tag::fma_(), a, a, a), a*a+a));
  NT2_TEST( nt2::isequal(nt2::sx(nt2::tag::fma_(), a, a, a),  nt2::tsxfun(nt2::functor<nt2::tag::fma_>(), a, a, a))); 
}

NT2_TEST_CASE_TPL( sx_2, NT2_TYPES )
{
  nt2::table<T> a = nt2::reshape(nt2::_(T(0), T(8)), 3, 3);
  NT2_TEST( nt2::isequal(nt2::sx(nt2::tag::if_else_(), nt2::is_lez(a), a, a), a));
  NT2_TEST( nt2::isequal(nt2::sx(nt2::tag::if_else_(), nt2::is_lez(a), a, a),  nt2::tsxfun(nt2::functor<nt2::tag::if_else_>(), nt2::is_lez(a), a, a))); 
}
