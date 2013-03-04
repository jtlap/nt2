//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#define NT2_UNIT_MODULE "nt2 combinatorial toolbox - perms"

#include <nt2/toolbox/combinatorial/include/functions/perms.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/table.hpp>
#include <nt2/include/functions/linspace.hpp>
#include <nt2/include/functions/transpose.hpp>
#include <nt2/include/functions/cons.hpp>
#include <nt2/include/functions/colon.hpp>

NT2_TEST_CASE_TPL ( perms_integer__1_0,  NT2_REAL_TYPES)
{

  using nt2::perms;
  using nt2::tag::perms_;
  nt2::table<T> v = nt2::linspace(T(0.5), T(3.5), 3);
  NT2_DISPLAY(nt2::perms(v, 3));
  NT2_DISPLAY(nt2::perms(v, 10));
  NT2_DISPLAY(nt2::perms(v));
  nt2::table<T> p = nt2::trans(nt2::cons(nt2::of_size(6, 3),
                                         T(0.5), T(0.5), T(  2), T(2  ), T( 3.5), T( 3.5),
                                         T(2  ), T(3.5), T(0.5), T(3.5), T( 0.5), T(   2),
                                         T(3.5), T(2),   T(3.5), T(0.5), T( 2  ), T( 0.5)
                                        ));
  NT2_TEST_EQUAL(nt2::perms(v, 3), p(nt2::_, nt2::_(1, 3)));
  NT2_TEST_EQUAL(nt2::perms(v, 10), p);
  NT2_TEST_EQUAL(nt2::perms(v), p);
}

