//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#define NT2_UNIT_MODULE "nt2 linalg toolbox - lotkin function"

#include <nt2/table.hpp>
#include <nt2/include/functions/lotkin.hpp>
#include <nt2/include/functions/cons.hpp>
#include <nt2/include/functions/transpose.hpp>
#include <nt2/include/functions/cast.hpp>
#include <nt2/sdk/unit/tests/ulp.hpp>
#include <nt2/sdk/unit/module.hpp>


NT2_TEST_CASE_TPL ( lotkin, NT2_REAL_TYPES)
{
  typedef typename nt2::meta::as_<T> ta_t;
  nt2::table<T> l3 =nt2::trans(nt2::cons(nt2::of_size(3, 3),
                                         T(60),    T(60),    T(60),
                                         T(30),    T(20),    T(15),
                                         T(20),    T(15),    T(12))/T(60));
  NT2_DISPLAY(l3);
  NT2_DISPLAY(nt2::lotkin(3,ta_t()));
  NT2_TEST_ULP_EQUAL(nt2::lotkin(3,ta_t()), l3, 0.5);
//    NT2_TEST_ULP_EQUAL(nt2::lotkin<T>(3), l3, 0.5);
//  NT2_TEST_ULP_EQUAL(nt2::cast<T>(nt2::lotkin(3)), l3, 0.5);
}




