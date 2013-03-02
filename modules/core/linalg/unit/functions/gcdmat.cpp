//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#define NT2_UNIT_MODULE "nt2 linalg toolbox - gcdmat function"

#include <nt2/table.hpp>
#include <nt2/include/functions/gcdmat.hpp>
#include <nt2/include/functions/transpose.hpp>
#include <nt2/include/functions/cons.hpp>
#include <nt2/include/functions/mtimes.hpp>
#include <nt2/include/functions/triw.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/exceptions.hpp>
#include <nt2/table.hpp>

NT2_TEST_CASE_TPL ( gcdmat, NT2_REAL_TYPES)
{
  nt2::table<T> gcd6 =nt2::reshape(nt2::cons(
                                   T(1),     T(1),      T(1),      T(1),      T(1),      T(1),
                                   T(1),     T(2),      T(1),      T(2),      T(1),      T(2),
                                   T(1),     T(1),      T(3),      T(1),      T(1),      T(3),
                                   T(1),     T(2),      T(1),      T(4),      T(1),      T(2),
                                   T(1),     T(1),      T(1),      T(1),      T(5),      T(1),
                                   T(1),     T(2),      T(3),      T(2),      T(1),      T(6)),
                                 nt2::of_size(6, 6));
  NT2_DISPLAY(gcd6);
  nt2::table<T> v = nt2::gcdmat(6, nt2::meta::as_<T>());
  NT2_DISPLAY(v);
  NT2_TEST_EQUAL(v, gcd6);

}


