//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#define NT2_UNIT_MODULE "nt2 linalg toolbox - expm"

#include <nt2/table.hpp>
#include <nt2/include/functions/expm.hpp>
#include <nt2/include/functions/eye.hpp>
#include <nt2/include/constants/one.hpp>
#include <nt2/include/constants/ten.hpp>
#include <nt2/include/constants/exp_1.hpp>

#include <nt2/include/functions/isulpequal.hpp>
#include <nt2/sdk/unit/tests.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/exceptions.hpp>

NT2_TEST_CASE_TPL(expm, NT2_REAL_TYPES)
{
  typedef T r_t;
  using nt2::expm;
  using nt2::tag::expm_;

  nt2::table<T> n(nt2::of_size(2, 2));
  n(1, 1) = n(1, 2) = n(2, 2) = 1;
  n(2, 1) = T(0);
  nt2::table<T> r = n*nt2::Exp_1<T>();
  nt2::table<T> expmn = nt2::expm(n);
  NT2_DISPLAY(n);
  NT2_DISPLAY(expmn);
  NT2_TEST(nt2::isulpequal(expmn, r, 0.5));
 }
