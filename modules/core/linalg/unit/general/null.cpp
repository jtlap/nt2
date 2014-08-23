//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#define NT2_UNIT_MODULE "nt2 linalg toolbox - null space"

#include <nt2/table.hpp>
#include <nt2/include/functions/null.hpp>
#include <nt2/include/functions/eye.hpp>
#include <nt2/include/functions/zeros.hpp>
#include <nt2/include/functions/eps.hpp>
#include <nt2/include/functions/ctranspose.hpp>
#include <nt2/include/functions/mtimes.hpp>
#include <nt2/include/functions/mnorm.hpp>
#include <nt2/include/functions/isulpequal.hpp>
#include <nt2/include/constants/eps.hpp>

#include <nt2/sdk/unit/tests.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <vector>

NT2_TEST_CASE_TPL(null, NT2_REAL_TYPES)
{
  using nt2::_ ;

  nt2::table<T> n = nt2::eye(10, 10, nt2::meta::as_<T>());
  n(3, 5) = T(2);
  n(4, 4) = T(0);
  n(1, 1) = 5*nt2::Eps<T>();
  nt2::table<T> nulln = nt2::null(n);
  nt2::table<T> nulln1 = nt2::null(n,  100*nt2::Eps<T>());
  nt2::table<T> rn = nt2::zeros(10, 1, nt2::meta::as_<T>());
  rn(4) = T(-1);
  NT2_TEST(isulpequal(rn, nulln));
  nt2::table<T> rn1 = nt2::zeros(10, 2, nt2::meta::as_<T>());
  rn1(4, 1) = T(-1);
  rn1(1, 2) = T(1);
  NT2_TEST(isulpequal(rn1, nulln1));
 }

NT2_TEST_CASE_TPL(null_2, NT2_REAL_TYPES)
{
  using nt2::_ ;

  T t[] = {
    1,0,-1,0,0,
    -2,1,1,0,0,
    0,1,0,0,-1,
    1,-1,0,0,0,
    0,0,0,-1,1,
    0,0,-1,1,0,
    0,0,1,-1,0,
    0,0,0,1,-1,
    0,-1,0,0,1,
    0,0,0,1,-1 };
  nt2::table<T> u(nt2::of_size(5,10), &t[0], &t[50]);
  NT2_DISPLAY(u);
  nt2::table<T> n = nt2::null(nt2::ctrans(u));
  NT2_DISPLAY(n);
  NT2_TEST_LESSER(mnorm(nt2::mtimes(nt2::ctrans(u), n)), numel(u)*nt2::Eps<T>());

  T t1[] = {0,0,-1,0,1,0,0,0,0,0,0,0,
            0,0,0,-1,0,0,-1,0,1,0,1,-1,
            1,0,0,-1,0,0,0,0,0,-1,1,0,
            0,0,0,0,0,0,0,0,0,0,0,1,
            1,0,-1,0,0,0,0,0,0,0,0,0,
            0,0,0,0,0,0,0,0,0,1,-1,-1,
            0,1,0,0,0,-1,1,-1,-1,0,0,1,
            -1,-1,1,0,0,0,0,1,0,0,0,0,
            0,0,0,1,-1,0,1,0,-1,0,0,1,
            0,0,0,0,0,1,0,0,0,0,0,1
           };

  nt2::table<T> u1(nt2::of_size(12, 10), &t1[0], &t1[10*12]);
  NT2_DISPLAY(u1);
  nt2::table<T> n1 = nt2::null(nt2::ctrans(u1));
  NT2_DISPLAY(n1);
  NT2_TEST_LESSER(mnorm(nt2::mtimes(nt2::ctrans(u1), n1)), numel(u1)*nt2::Eps<T>());

//     T r[] = {     3.209550390547239e-01     2.520710040466531e-01,     1.071160543334454e-02,
//                  -2.957951069829756e-01     3.538507775257557e-01,     5.359989570226317e-01,
//                   3.209550390547224e-01     2.520710040466532e-01,     1.071160543334459e-02,
//                   3.209550390547217e-01     2.520710040466531e-01,     1.071160543334457e-02,
//                   3.209550390547223e-01     2.520710040466531e-01,     1.071160543334458e-02,
//                  -2.107335489394153e-15     3.262348023601090e-17,    -4.228345143537963e-17,
//                   3.216657324010018e-01    -4.291506192482478e-01,     4.608263258514775e-01,
//                  -2.957951069829730e-01     3.538507775257556e-01,     5.359989570226316e-01,
//                   3.216657324010025e-01    -4.291506192482478e-01,     4.608263258514775e-01,
//                   3.209550390547267e-01     2.520710040466529e-01,     1.071160543334447e-02,
//                   3.209550390547243e-01     2.520710040466533e-01,     1.071160543334461e-02,
//                   1.790234627208065e-15     1.387778780781446e-17,                         0,    };

 }


