//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#define NT2_UNIT_MODULE "nt2 linalg toolbox - orthog function"

#include <nt2/table.hpp>
#include <nt2/include/functions/orthog.hpp>
#include <nt2/include/functions/cons.hpp>
#include <nt2/include/functions/transpose.hpp>
#include <nt2/include/functions/cast.hpp>
#include <nt2/sdk/unit/tests/ulp.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <boost/mpl/int.hpp>


NT2_TEST_CASE_TPL ( orthog, NT2_REAL_TYPES)
{
  typedef typename std::complex<T> cT;
  typedef typename nt2::meta::as_<T> ta_t;
  nt2::table<T> m31 =nt2::trans(nt2::cons(nt2::of_size(3, 3),
                                         T(0.500000000000000),   T( 0.707106781186548),   T( 0.500000000000000),
                                         T(0.707106781186548),   T( 0.000000000000000),   T(-0.707106781186548),
                                         T(0.500000000000000),   T(-0.707106781186548),   T( 0.500000000000000)
                                        ));

  nt2::table<T> m32 =nt2::trans(nt2::cons(nt2::of_size(3, 3),
                                          T(0.591009048506103),  T( 0.736976229099578),  T( 0.327985277605682),
                                          T(0.736976229099578),  T(-0.327985277605682),  T(-0.591009048506104),
                                          T(0.327985277605682),  T(-0.591009048506104),  T( 0.736976229099578)
                                         ));

  nt2::table<cT> m33 =nt2::trans(nt2::cons(nt2::of_size(3, 3),
                                           cT(0.577350269189626), cT( 0.577350269189626     ), cT( 0.577350269189626      ),
                                           cT(0.577350269189626), cT(-0.288675134594813, 0.5), cT(-0.288675134594813, - 0.5),
                                           cT(0.577350269189626), cT(-0.288675134594813,-0.5), cT(-0.288675134594812, + 0.5)
                                          ));

  nt2::table<T> m34 =nt2::trans(nt2::cons(nt2::of_size(3, 3),
                                           T(0.577350269189626),  T( 0.577350269189626),   T(0.577350269189626),
                                           T(0.707106781186547),  T(-0.707106781186547),   T(                0),
                                           T(0.408248290463863),  T( 0.408248290463863),  -T(0.816496580927726)
                                          ));

  nt2::table<T> m35 =nt2::trans(nt2::cons(nt2::of_size(3, 3),
                                          T(0.577350269189626),  T( 0.577350269189626),  T( 0.577350269189626),
                                          T(0.577350269189626),  T( 0.211324865405187),  T(-0.788675134594813),
                                          T(0.577350269189626),  T(-0.788675134594813),  T( 0.211324865405188)
                                         ));
  nt2::table<T> m36 =nt2::trans(nt2::cons(nt2::of_size(3, 3),
                                          T(0.788675134594813),   T( 0.577350269189626),   T( 0.211324865405187),
                                          T(0.577350269189626),   T(-0.577350269189626),   T(-0.577350269189626),
                                          T(0.211324865405187),   T(-0.577350269189626),   T( 0.788675134594813)
                                         ));
  nt2::table<T> m3m1 =nt2::trans(nt2::cons(nt2::of_size(3, 3),
                                          T(1),   T(1),   T(1),
                                          T(1),   T(0),  T(-1),
                                          T(1),  T(-1),   T(1)
                                         ));

  nt2::table<T> m3m2 =nt2::trans(nt2::cons(nt2::of_size(3, 3),
                                          T(1),   T(1),   T(1),
                                          T( 0.866025403784439),   T(0),  T(-0.866025403784438),
                                          T(0.5),  T(-1),   T(0.5)
                                         ));
  NT2_TEST_ULP_EQUAL((nt2::orthog1(3, ta_t())), m31, 2);
  NT2_TEST_ULP_EQUAL((nt2::orthog2(3, ta_t())), m32, 4);
  NT2_TEST_ULP_EQUAL((nt2::orthog3(3, ta_t())), m33, 4);
  NT2_TEST_ULP_EQUAL((nt2::orthog4(3, ta_t())), m34, 10);
  NT2_TEST_ULP_EQUAL((nt2::orthog5(3, ta_t())), m35, 10);
  NT2_TEST_ULP_EQUAL((nt2::orthog6(3, ta_t())), m36, 10);
  NT2_TEST_ULP_EQUAL((nt2::orthog7(3, ta_t())), m35, 16);
  NT2_TEST_ULP_EQUAL((nt2::orthogm1(3, ta_t())), m3m1, 16);
  NT2_TEST_ULP_EQUAL((nt2::orthogm2(3, ta_t())), m3m2, 16);

  NT2_TEST_ULP_EQUAL((nt2::orthog<1, T>(3)), m31,2);
  NT2_TEST_ULP_EQUAL((nt2::orthog<2, T>(3)), m32,4);
  NT2_TEST_ULP_EQUAL((nt2::orthog<3, T>(3)), m33,4);
  NT2_TEST_ULP_EQUAL((nt2::orthog<4, T>(3)), m34,4);
  NT2_TEST_ULP_EQUAL((nt2::orthog<5, T>(3)), m35,10);
  NT2_TEST_ULP_EQUAL((nt2::orthog<6, T>(3)), m36,10);
  NT2_TEST_ULP_EQUAL((nt2::orthog<7, T>(3)), m35,16);
  NT2_TEST_ULP_EQUAL((nt2::orthog<-1, T>(3)), m3m1,16);
  NT2_TEST_ULP_EQUAL((nt2::orthog<-2, T>(3)), m3m2,16);
}




