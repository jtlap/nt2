//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/table.hpp>
#include <nt2/include/functions/spline.hpp>
#include <nt2/include/functions/linspace.hpp>
#include <nt2/include/functions/sqr.hpp>
#include <nt2/include/functions/cons.hpp>
#include <nt2/include/functions/horzcat.hpp>
#include <boost/core/ignore_unused.hpp>

#include <nt2/include/functions/ones.hpp>
#include <nt2/include/functions/zeros.hpp>
#include <nt2/table.hpp>


#include <nt2/sdk/unit/tests.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/basic.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/ulp.hpp>
#include <nt2/sdk/unit/tests/exceptions.hpp>



NT2_TEST_CASE_TPL( spline0, NT2_REAL_TYPES)
{
  using nt2::_;
  nt2::table<T> x =  nt2::linspace(T(1),  T(2), 2);
  nt2::table<T> y =  nt2::sqr(nt2::linspace(T(1),  T(2), 2));
  nt2::table<T> xi=  nt2::linspace(T(1),  T(2), 7);

  nt2::table<T> r0 = nt2::cons<T>(nt2::of_size(1, 7), 1.0000, 1.5000, 2.0000, 2.5000, 3.0000, 3.5000, 4.0000);
  nt2::table<T> r1 = nt2::cons<T>(nt2::of_size(1, 7), 1.000000000000000,   1.222222222222222,   1.777777777777777,   2.500000000000000,
                                  3.222222222222221,   3.777777777777778,   4.000000000000000);
  nt2::table<T> yi;

  yi = nt2::spline(x, y, xi);
  NT2_TEST_ULP_EQUAL(yi, r0, 10.0);

  nt2::table<T> y1 =  nt2::cath(nt2::cath(T(0), y), T(0));
  yi = nt2::spline(x, y1, xi);
  NT2_TEST_ULP_EQUAL(yi, r1, 10.0);

  x =  nt2::linspace(T(1),  T(3), 3);
  y = sqr(x);
  xi=  nt2::linspace(T(1),  T(3), 7);
  nt2::table<T> r2 = nt2::cons<T>(nt2::of_size(1, 7),1.000000000000000,   1.777777777777777,   2.777777777777777,   4.000000000000000,
                                  5.444444444444443,   7.111111111111112,   9.000000000000000);
  yi = nt2::spline(x, y, xi);
  NT2_TEST_ULP_EQUAL(yi, r2, 10.0);

  x =  nt2::linspace(T(1),  T(5), 5);
  y = sqr(x);
  xi=  nt2::linspace(T(1),  T(5), 7);
  nt2::table<T> r3 = nt2::cons<T>(nt2::of_size(1, 7),  1.000000000000000,   2.777777777777777,   5.444444444444443,   9.000000000000000,
                                  13.444444444444443,  18.777777777777782,  25.000000000000000);

  yi = nt2::spline(x, y, xi);
  NT2_TEST_ULP_EQUAL(yi, r3, 10.0);

  nt2::table<T> y2 =  nt2::cath(nt2::cath(T(0), y), T(0));
  xi=  nt2::linspace(T(1),  T(5), 7);
  nt2::table<T> r4 = nt2::cons<T>(nt2::of_size(1, 7),   1.000000000000000,   2.523809523809523,   5.613756613756612,   9.000000000000000,
                                  12.978835978835978,  19.920634920634928,  25.000000000000000 );

  std::cout << 1 << std::endl;
  yi = nt2::spline(x, y2, xi);
  std::cout << 2 << std::endl;
  NT2_TEST_ULP_EQUAL(yi, r4, 10.0);
}

NT2_TEST_CASE_TPL( nearest5, NT2_REAL_TYPES )
{
  using nt2::_;
  nt2::table<T> x =  nt2::linspace(T(1),  T(5), 5);
  nt2::table<T> y = sqr(x);
  nt2::table<T> xi=  nt2::linspace(T(1),  T(5), 7);
  nt2::table<T> r = nt2::cons<T>(nt2::of_size(1, 7),  1.000000000000000,   2.777777777777777,   5.444444444444443,   9.000000000000000,
                                  13.444444444444443,  18.777777777777782,  25.000000000000000);
  nt2::table<T> y3 =  repmat(y, 3, 1);
  nt2::table<T> r3 =  repmat(r, 3, 1);


  nt2::table<T> yi = nt2::spline(x, y3, xi);
  NT2_TEST_ULP_EQUAL(r3(_), yi, 1);
}












