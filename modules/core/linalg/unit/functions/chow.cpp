//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#define NT2_UNIT_MODULE "nt2 linalg toolbox - chow function"

#include <nt2/table.hpp>
#include <nt2/include/functions/chow.hpp>
#include <nt2/include/functions/transpose.hpp>
#include <nt2/include/functions/ones.hpp>
#include <nt2/include/functions/cons.hpp>
#include <nt2/include/constants/i.hpp>
#include <nt2/sdk/unit/tests.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/exceptions.hpp>

NT2_TEST_CASE_TPL ( chow, NT2_REAL_TYPES)
{
  nt2::table<T> t3 = nt2::ones(3, nt2::meta::as_<T>());  t3(1, 3) = T(0);
  nt2::table<T> v =  nt2::chow(3, nt2::meta::as_<T>());
  NT2_DISPLAY(v);
  NT2_DISPLAY(t3);
  NT2_TEST_EQUAL(v, t3);
}



