//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#define NT2_UNIT_MODULE "nt2 linalg toolbox - impower factorization"

#include <nt2/table.hpp>
#include <nt2/include/functions/impower.hpp>
#include <nt2/include/functions/eye.hpp>
#include <nt2/include/constants/one.hpp>
#include <nt2/include/constants/ten.hpp>

#include <nt2/include/functions/isulpequal.hpp>
#include <nt2/sdk/unit/tests.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/exceptions.hpp>

NT2_TEST_CASE_TPL(impower, NT2_REAL_TYPES)
{
  typedef T r_t;
  using nt2::impower;
  using nt2::tag::impower_;

  nt2::table<T> n(nt2::of_size(2, 2)), n3;
  n(1, 1) = n(1, 2) = n(2, 2) = 1;
  n(2, 1) = T(0);
  n3 = n;
  n3(1, 2) = T(3);
  NT2_DISPLAY(n);
  NT2_DISPLAY(n3);
  nt2::table<T> impowern3 = nt2::impower(n, 3);
  NT2_DISPLAY(impowern3);
  NT2_TEST(nt2::isulpequal(impowern3, n3, 0.5));
 }
