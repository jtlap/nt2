/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#define NT2_UNIT_MODULE "nt2::blkdiag function"

#include <nt2/table.hpp>
#include <nt2/include/functions/size.hpp>
#include <nt2/include/functions/blkdiag.hpp>
#include <nt2/include/functions/rif.hpp>
#include <nt2/include/functions/cif.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/basic.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>
#include <nt2/sdk/unit/tests/exceptions.hpp>

NT2_TEST_CASE( blkdiag_size )
{
  nt2::table<float> a = nt2::rif(nt2::of_size(3, 2), nt2::meta::as_<float>());
  nt2::table<float> b = nt2::cif(nt2::of_size(2, 4), nt2::meta::as_<float>());
  NT2_DISPLAY(a);
  NT2_DISPLAY(b);
  nt2::table<float> c = blkdiag(a);
  NT2_DISPLAY(c);
  nt2::table<float> d = blkdiag(a, b);
  NT2_DISPLAY(d);
}
NT2_TEST_CASE( blkdiag_size2 )
{
  nt2::table<float> a = nt2::rif(nt2::of_size(7, 6), nt2::meta::as_<float>());
  nt2::table<float> b = nt2::cif(nt2::of_size(9, 8), nt2::meta::as_<float>());
  NT2_DISPLAY(a);
  NT2_DISPLAY(b);
  nt2::table<float> c = blkdiag(a);
  NT2_DISPLAY(c);
  nt2::table<float> d = blkdiag(a, b);
  NT2_DISPLAY(d);
}
