//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/table.hpp>
#include <nt2/include/functions/ppval.hpp>
#include <nt2/include/functions/linspace.hpp>
#include <nt2/include/functions/transpose.hpp>
#include <nt2/include/functions/cons.hpp>

#include <nt2/sdk/unit/tests.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/basic.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/exceptions.hpp>

NT2_TEST_CASE_TPL( ppval, NT2_REAL_TYPES)
{
  using nt2::_;
  nt2::table<T> breaks = nt2::linspace(T(1),  T(4), 4);
  nt2::table<T> coefs = nt2::trans(nt2::cons<T>(nt2::of_size(4, 3),
                                                0, 0, 2, 2,
                                                0, 0, 2, 4,
                                                0, 0, 2, 6));
  nt2::table<T> xi=  nt2::linspace(T(1),  T(4), 7);
  nt2::ext::ppval<T> pp(breaks, coefs);
  NT2_DISPLAY(pp.getbreaks());
  NT2_DISPLAY(pp.getcoefs());
  NT2_DISPLAY(pp.getorder());
  NT2_DISPLAY(pp.getpieces());
  nt2::table<T> yi =pp.eval(xi);
  NT2_DISPLAY(yi);

}

