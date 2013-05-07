//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#define NT2_UNIT_MODULE "nt2 linalg toolbox - lauchli function"

#include <nt2/table.hpp>
#include <nt2/include/functions/lauchli.hpp>
#include <nt2/sdk/unit/tests.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/exceptions.hpp>

NT2_TEST_CASE_TPL ( lauchli, NT2_REAL_TYPES)
{
  typedef typename nt2::meta::as_<T> ta_t;
  nt2::table<T> l3 =nt2::catv(nt2::ones(1, 3, ta_t()), nt2::Sqrteps<T>()*nt2::eye(3, ta_t()));


  NT2_TEST_ULP_EQUAL(nt2::lauchli(3, nt2::Sqrteps<T>()), l3, 0.5);
  NT2_TEST_ULP_EQUAL(nt2::lauchli(3, nt2::meta::as_<T>()), l3, 0.5);
  NT2_TEST_ULP_EQUAL(nt2::lauchli<T>(3), l3, 0.5);
}




