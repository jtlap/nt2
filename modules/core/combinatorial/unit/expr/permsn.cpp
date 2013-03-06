//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#define NT2_UNIT_MODULE "nt2 combinatorial toolbox - permsn"

#include <nt2/toolbox/combinatorial/include/functions/permsn.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/table.hpp>
#include <nt2/include/functions/transpose.hpp>
#include <nt2/include/functions/cons.hpp>
#include <nt2/include/functions/colon.hpp>

NT2_TEST_CASE ( permsn_)
{

  using nt2::permsn;
  using nt2::tag::permsn_;
  NT2_DISPLAY(nt2::permsn(3, 6));
  NT2_DISPLAY(nt2::permsn(3, 10));
  NT2_DISPLAY(nt2::permsn(3, 3));
  nt2::table<size_t> p = nt2::trans(nt2::cons(nt2::of_size(6, 3),
                                              1, 1, 2, 2, 3, 3,
                                              2, 3, 1, 3, 1, 2,
                                              3, 2, 3, 1, 2, 1
                                             ));
  NT2_TEST_EQUAL(nt2::permsn(3, 3), p(nt2::_, nt2::_(1, 3)));
  NT2_TEST_EQUAL(nt2::permsn(3, 10), p);
  NT2_TEST_EQUAL(nt2::permsn(3, 6), p);
}

