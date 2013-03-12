//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#define NT2_UNIT_MODULE "nt2 linalg toolbox - smoke function"

#include <nt2/table.hpp>
#include <nt2/include/functions/smoke.hpp>
#include <nt2/include/functions/cons.hpp>
#include <nt2/include/functions/transpose.hpp>
#include <nt2/include/functions/cast.hpp>
#include <nt2/sdk/unit/tests/ulp.hpp>
#include <nt2/sdk/unit/module.hpp>


NT2_TEST_CASE_TPL ( smoke, NT2_REAL_TYPES)
{
  typedef std::complex<T> cT;
  typedef typename nt2::meta::as_<T> ta_t;
  nt2::table<cT> m3 =nt2::trans(nt2::cons(nt2::of_size(3, 3),
                                         cT(-0.5,  0.866025403784439),  cT( 1.000000000000000                     ), cT( 0),
                                         cT( 0.0                    ),  cT(-0.500000000000000, - 0.866025403784438), cT( 1),
                                         cT( 1.0                    ),  cT(                 0                     ), cT( 1)
                                        ));
  NT2_DISPLAY(nt2::smoke(3,ta_t()));
  NT2_TEST_ULP_EQUAL(nt2::smoke(3,ta_t()), m3, 5);
  NT2_TEST_ULP_EQUAL(nt2::smoke(3,1,ta_t()), m3, 5);
  NT2_TEST_ULP_EQUAL(nt2::smoke<T>(3), m3, 5);
  NT2_TEST_ULP_EQUAL(nt2::smoke<T>(3, 1), m3, 5);
  m3(3, 1) = T(0);
  NT2_TEST_ULP_EQUAL(nt2::smoke(3,0,ta_t()), m3, 5);
}




