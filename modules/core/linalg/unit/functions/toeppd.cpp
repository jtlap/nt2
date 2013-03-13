//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#define NT2_UNIT_MODULE "nt2 linalg toolbox - toeppd function"

#include <nt2/table.hpp>
#include <nt2/include/functions/toeppd.hpp>
#include <nt2/include/functions/cons.hpp>
#include <nt2/include/functions/transpose.hpp>
#include <nt2/include/functions/colon.hpp>
#include <nt2/include/functions/linspace.hpp>
#include <nt2/sdk/unit/tests/ulp.hpp>
#include <nt2/sdk/unit/module.hpp>


NT2_TEST_CASE_TPL ( toeppd, NT2_REAL_TYPES)
{
  typedef typename nt2::meta::as_<T> ta_t;
  nt2::table<T> m3 =nt2::trans(nt2::cons(nt2::of_size(3, 3),
                                         T(6),     T(2),     T(6),
                                         T(2),     T(6),     T(2),
                                         T(6),     T(2),     T(6)
                                        ));
  NT2_DISPLAY(m3);
  NT2_DISPLAY( nt2::toeppd(3,nt2::_(T(1), T(3)),
                             nt2::linspace(T(0),T(1),3)) );
  NT2_TEST_ULP_EQUAL(nt2::toeppd(3,nt2::_(T(1), T(3)), nt2::linspace(T(0),T(1),3)),
                     m3, 0.5);
  NT2_DISPLAY(nt2::toeppd(3, 3, nt2::meta::as_<T>())); //these 3 matrices are random and so not tested but for the build
  NT2_DISPLAY(nt2::toeppd<T>(3));
  NT2_DISPLAY(nt2::toeppd<T>(3, 4));
}





