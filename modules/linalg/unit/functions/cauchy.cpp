//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#define NT2_UNIT_MODULE "nt2 linalg toolbox - cauchy function"

#include <nt2/table.hpp>
#include <nt2/include/functions/cauchy.hpp>
#include <nt2/sdk/unit/tests.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/exceptions.hpp>

NT2_TEST_CASE_TPL ( cauchy_ints, NT2_REAL_TYPES)
{
  //  nt2::display("cauchy(3, 4, nt2::meta::as_<T>())", nt2::cauchy(3, 4, nt2::meta::as_<T>()));
  nt2::table<T> a0 = nt2::_(T(1), 4); 
  nt2::display("cauchy(a0)", nt2::cauchy(a0)); 
}

