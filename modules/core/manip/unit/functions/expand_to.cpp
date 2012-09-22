/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#define NT2_UNIT_MODULE "nt2::expand_to function"

#include <nt2/table.hpp>
#include <nt2/include/functions/size.hpp>
#include <nt2/include/functions/expand_to.hpp>
#include <nt2/include/functions/rif.hpp>
#include <nt2/include/functions/cif.hpp>
#include <nt2/include/functions/ones.hpp>
#include <nt2/include/functions/mean.hpp>
#include <nt2/include/functions/isequal.hpp>
#include <nt2/include/functions/reshape.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/basic.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>
#include <nt2/sdk/unit/tests/exceptions.hpp>

NT2_TEST_CASE_TPL( expand_to_1, NT2_TYPES)
{
  nt2::table<T> a = nt2::rif(nt2::of_size(3, 1), nt2::meta::as_<T>()),
    b = nt2::rif(nt2::of_size(3, 4), nt2::meta::as_<T>()),
    e;
  NT2_DISPLAY(a);

  e = expand_to(a, nt2::of_size(3, 4));
  NT2_DISPLAY(e);
  NT2_TEST(nt2::isequal(e, b));

  e = expand_to(a, size(b));
  NT2_DISPLAY(e);
  NT2_TEST(nt2::isequal(e, b));

  e = expand_to(a, 3u, 4u);
  NT2_DISPLAY(e);
  NT2_TEST(nt2::isequal(e, b));
}
NT2_TEST_CASE_TPL( expand_to_2, NT2_TYPES)
{
  nt2::table<T> a = nt2::rif(nt2::of_size(3, 1, 2, 1), nt2::meta::as_<T>()),
    b = nt2::rif(nt2::of_size(3, 4, 2, 3), nt2::meta::as_<T>()),
    e;
  //  NT2_DISPLAY(a);

  e = expand_to(a, nt2::of_size(3, 4, 2, 3));
  NT2_DISPLAY(e);
  NT2_TEST(nt2::isequal(e, b));

  e = expand_to(a, size(b));
  NT2_DISPLAY(e);
  NT2_TEST(nt2::isequal(e, b));

   e = expand_to(a, 3u, 4u, 2u, 3u);
   NT2_DISPLAY(e);
   NT2_TEST(nt2::isequal(e, b));
}

NT2_TEST_CASE_TPL( expand_to_3, NT2_TYPES)
{
  nt2::table<T> b = nt2::ones(3, 4, nt2::meta::as_<T>());
  T a = T(1);
  nt2::table<T> f = nt2::expand_to(a, nt2::of_size(3, 4));
  nt2::table<T> g = nt2::expand_to(a, size(b));
  nt2::table<T> h = nt2::expand_to(a, 3, 4);
  NT2_TEST(nt2::isequal(g, b));
  NT2_TEST(nt2::isequal(f, b));
  NT2_TEST(nt2::isequal(h, b));
}

