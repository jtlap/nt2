//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#define NT2_UNIT_MODULE "nt2 linalg toolbox - qmult function"

#include <nt2/table.hpp>
#include <nt2/include/functions/qmult.hpp>
#include <nt2/include/functions/cons.hpp>
#include <nt2/include/functions/transpose.hpp>
#include <nt2/include/functions/colon.hpp>
#include <nt2/include/functions/linspace.hpp>
#include <nt2/include/functions/svd.hpp>
#include <nt2/sdk/unit/tests/ulp.hpp>
#include <nt2/sdk/unit/module.hpp>


NT2_TEST_CASE_TPL ( qmult, NT2_REAL_TYPES)
{
  typedef typename nt2::meta::as_<T> ta_t;
  nt2::table<T> qa =  nt2::qmult(nt2::eye(4, nt2::meta::as_<T>()));
  NT2_TEST_ULP_EQUAL(nt2::mtimes(nt2::transpose(qa), qa), nt2::eye(4, nt2::meta::as_<T>()), 5); //check qa is orthogonal
  qa = nt2::qmult<T>(3);
  NT2_TEST_ULP_EQUAL(nt2::mtimes(nt2::transpose(qa), qa), nt2::eye(3, nt2::meta::as_<T>()), 5); //check qa is orthogonal
}

NT2_TEST_CASE_TPL ( qmult1, NT2_REAL_TYPES)
{
  typedef typename nt2::meta::as_<T> ta_t;
  nt2::table<T> a = nt2::from_diag(nt2::cons(T(1), T(0.736806), T(0.542883), T(0.4)));
  nt2::table<T> qa =  nt2::qmult(a);
  nt2::table<T> wa =  nt2::svd(qa);
  nt2::table<T> tqaq =  nt2::qmult(qa);
   nt2::table<T> waa =  nt2::svd(qa);
  NT2_DISPLAY(a);
  NT2_DISPLAY(qa);
  NT2_DISPLAY(wa);
  NT2_DISPLAY(waa);
}




