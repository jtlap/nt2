//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#define NT2_UNIT_MODULE "nt2 linalg toolbox - normest computation"

#include <nt2/table.hpp>
#include <nt2/include/functions/normest.hpp>
#include <nt2/include/functions/ones.hpp>
#include <nt2/include/functions/sqrt.hpp>
#include <nt2/include/functions/pow.hpp>
#include <nt2/include/constants/one.hpp>
#include <nt2/include/constants/ten.hpp>
#include <nt2/include/constants/inf.hpp>
#include <nt2/include/constants/minf.hpp>

#include <nt2/include/functions/ulpdist.hpp>
#include <nt2/sdk/unit/tests.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/exceptions.hpp>

NT2_TEST_CASE_TPL(normest, NT2_REAL_TYPES)
{
  typedef T r_t;
  using nt2::normest;
  using nt2::tag::normest_;

  nt2::table<T> n = nt2::ones(10, 10, nt2::meta::as_<T>());
  NT2_TEST_ULP_EQUAL(normest(n, T(1.0e-6)), nt2::Ten<T>(), 0.5);
}
