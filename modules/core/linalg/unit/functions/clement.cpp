//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#define NT2_UNIT_MODULE "nt2 linalg toolbox - clement function"

#include <nt2/table.hpp>
#include <nt2/include/functions/clement.hpp>
#include <nt2/include/functions/trans.hpp>
#include <nt2/include/functions/ones.hpp>
#include <nt2/include/functions/cons.hpp>
#include <nt2/include/functions/cast.hpp>
#include <nt2/include/constants/i.hpp>
#include <nt2/sdk/unit/tests.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/exceptions.hpp>

NT2_TEST_CASE_TPL ( clement, NT2_REAL_TYPES)
{
  nt2::table<T> a = nt2::_(T(1), T(3));
  nt2::table<T> t30 =nt2::trans(nt2::reshape(nt2::cons(
                                               T(0), T(1), T(0),
                                               T(2), T(0), T(2),
                                               T(0), T(1), T(0)),
                                             nt2::of_size(3, 3)));
  nt2::table<T> t31 =nt2::trans(nt2::reshape(nt2::cons(
                                              T(0),             nt2::Sqrt_2<T>(), T(0),
                                              nt2::Sqrt_2<T>(), T(0),             nt2::Sqrt_2<T>(),
                                              T(0),             nt2::Sqrt_2<T>(), T(0)),
                                            nt2::of_size(3, 3)));
   nt2::table<T> v = nt2::clement(3, 0, nt2::meta::as_<T>());
  nt2::table<T> v1=  nt2::clement(3, 1,nt2::meta::as_<T>());
  NT2_TEST_ULP_EQUAL(v, t30, 0.5);
  NT2_TEST_ULP_EQUAL(v1, t31, 0.5);

}




