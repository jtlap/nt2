/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#define NT2_UNIT_MODULE "nt2::cat function"

#include <nt2/table.hpp>
#include <nt2/include/functions/size.hpp>
#include <nt2/include/functions/cat.hpp>
#include <nt2/include/functions/rif.hpp>
#include <nt2/include/functions/cif.hpp>
#include <nt2/include/functions/isequal.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/basic.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>

NT2_TEST_CASE_TPL( cat, (float)(double) )
{
  {
    nt2::table<T> a = nt2::rif(nt2::of_size(3, 2), nt2::meta::as_<T>());
    nt2::table<T> b = nt2::cif(nt2::of_size(3, 4), nt2::meta::as_<T>());
    NT2_DISPLAY(a);
    NT2_DISPLAY(b);

    nt2::table<T> d = cat(2, a, b);
    NT2_DISPLAY(d);
    NT2_TEST(isequal(a, d(nt2::_, nt2::_(1u, size(a, 2)))));
    NT2_TEST(isequal(b, d(nt2::_, nt2::_(size(a, 2)+1, nt2::end_))));
  }

  {
    nt2::table<T> a = nt2::rif(nt2::of_size(2, 3), nt2::meta::as_<T>());
    nt2::table<T> b = nt2::cif(nt2::of_size(4, 3), nt2::meta::as_<T>());
    NT2_DISPLAY(a);
    NT2_DISPLAY(b);

    nt2::table<T> d = cat(1, a, b);
    NT2_DISPLAY(d);
    NT2_TEST(isequal(a, d(nt2::_(1u, size(a, 1)),nt2::_ )));
    NT2_TEST(isequal(b, d(nt2::_(size(a, 1)+1, nt2::end_),nt2::_)));
  }

  {
    nt2::table<T> a = nt2::rif(nt2::of_size(4, 3), nt2::meta::as_<T>());
    nt2::table<T> b = nt2::cif(nt2::of_size(4, 3), nt2::meta::as_<T>());
    NT2_DISPLAY(a);
    NT2_DISPLAY(b);

    nt2::table<T> d = cat(3, a, b);
    NT2_DISPLAY(d);
    NT2_TEST(isequal(a, d(nt2::_,nt2::_,1)));
    NT2_TEST(isequal(b, d(nt2::_,nt2::_,2)));
  }
}

