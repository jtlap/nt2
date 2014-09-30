//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#define NT2_UNIT_MODULE "nt2 gallery toolbox - randsvd function"

#include <nt2/table.hpp>
#include <nt2/include/functions/randsvd.hpp>
#include <nt2/include/functions/cond.hpp>
#include <nt2/sdk/unit/tests/ulp.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/module.hpp>


NT2_TEST_CASE_TPL ( randsvd, NT2_REAL_TYPES)
{
  typedef  nt2::table<T> tab_t;
  tab_t rc;

  for(int i=1; i <= 4 ; i++)
  {
    rc = nt2::randsvd(4, 4, T(2.5), i);
    NT2_TEST_LESSER(nt2::abs(nt2::cond(rc)-T(2.5)), T(1.0e-3));
  }
  rc = nt2::randsvd(4, 4, T(2.5), 5);
  NT2_TEST_LESSER(nt2::cond(rc), T(2.5));
}






