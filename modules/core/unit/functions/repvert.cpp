/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#define NT2_UNIT_MODULE "nt2::repvert function"

#include <nt2/table.hpp>
#include <nt2/include/functions/size.hpp>
#include <nt2/include/functions/repvert.hpp>
#include <nt2/include/functions/rif.hpp>
#include <nt2/include/functions/cif.hpp>
#include <nt2/include/functions/isequal.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/basic.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>
#include <nt2/sdk/unit/tests/exceptions.hpp>

NT2_TEST_CASE( repvert_size )
{
  nt2::table<float> a = nt2::rif(nt2::of_size(7,1,2), nt2::meta::as_<float>()), b;
  a(3,1,2) = 99;
  NT2_DISPLAY(a);
  b = repvert(a,  2);
  NT2_DISPLAY(b);
  a = nt2::cif(nt2::of_size(1, 7), nt2::meta::as_<float>());
  NT2_DISPLAY(a);
  b = repvert(a,  2);
  NT2_DISPLAY(b);
  a = nt2::cif(nt2::of_size(7, 7), nt2::meta::as_<float>());
  NT2_DISPLAY(a);
  b = repvert(a,  2);
  NT2_DISPLAY(b);
}
NT2_TEST_CASE( repvert_ )
{
  using nt2::_;
  using nt2::end_; 
  nt2::table<float> a = nt2::rif(nt2::of_size(7, 1), nt2::meta::as_<float>()), b;
  b = repvert(a,  2);
  NT2_TEST(nt2::isequal(b,  repvert(a,  2)));
  NT2_TEST(nt2::isequal(b(_(1u, size(a, 1)), _), a));
  NT2_TEST(nt2::isequal(b(_(size(a, 1)+1, end_), _), a)); 
  a = nt2::cif(nt2::of_size(7, 7), nt2::meta::as_<float>());
  b = repvert(a,  2);
  NT2_TEST(nt2::isequal(b,  repvert(a,  2)));
  NT2_TEST(nt2::isequal(b(_(1u, size(a, 1)), _), a));
  NT2_TEST(nt2::isequal(b(_(size(a, 1)+1, end_), _), a)); 
 
}
