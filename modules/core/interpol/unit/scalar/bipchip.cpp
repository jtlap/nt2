//==============================================================================
//         Copyright 2015 J.T. Lapreste
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/table.hpp>
#include <nt2/include/functions/bipchip.hpp>
#include <nt2/include/functions/cons.hpp>
#include <nt2/include/functions/meshgrid.hpp>
#include <nt2/include/functions/repmat.hpp>
#include <nt2/include/functions/linspace.hpp>
#include <nt2/include/functions/isequal.hpp>
#include <nt2/include/functions/meshgrid.hpp>
#include <nt2/include/functions/transpose.hpp>
#include <nt2/include/functions/expand_to.hpp>
#include <nt2/include/functions/of_size.hpp>
#include <nt2/include/constants/nan.hpp>
#include <boost/core/ignore_unused.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/basic.hpp>
#include <nt2/sdk/unit/tests/exceptions.hpp>
#include <nt2/sdk/unit/tests/ulp.hpp>

NT2_TEST_CASE_TPL( bipchip, (double))//NT2_REAL_TYPES )
{
  using nt2::_;
  nt2::table<T> x =  nt2::linspace(T(1),  T(4), 4);
  nt2::table<T> y =  nt2::linspace(T(1),  T(5), 5);
  nt2::table<T> z =  reshape(nt2::linspace(T(1),  T(20), 20), 5, 4);
  nt2::table<T> xi =  nt2::linspace(T(1),  T(3), 12);
  nt2::table<T> yi =  nt2::linspace(T(1),  T(3), 12);
  nt2::table<T> ri =  nt2::cons<T>( nt2::of_size(1, 12),
                                    1.00000000000000,    2.09090909090909,
                                    3.18181818181818,    4.27272727272727,
                                    5.36363636363636,    6.45454545454546,
                                    7.54545454545455,    8.63636363636363,
                                    9.72727272727273,   10.81818181818182,
                                    11.90909090909091,  13.00000000000000);

  nt2::table<T> zi = nt2::bipchip(x, y, z, xi, yi);
  NT2_TEST_ULP_EQUAL(ri, zi, 3);

  nt2::table<T> xx,  yy;
  xi = nt2::linspace(T(1),  T(3), 4);
  yi = nt2::linspace(T(1),  T(5), 3);
  nt2::table<T> xxi, yyi;
  tie(xxi, yyi) = meshgrid(xi, yi);
  zi = nt2::bipchip(x, y, z, xxi, yyi);
  nt2::table<T> r2i =  nt2::trans(
    nt2::cons<T>(nt2::of_size(4, 3),
                 1, 4.333333333333333, 7.66666666666666, 11,
                 3, 6.333333333333333, 9.66666666666666, 13,
                 5, 8.333333333333333, 11.66666666666666, 15));

  NT2_TEST_ULP_EQUAL(r2i, zi, 3);

  zi = nt2::bipchip(x, y, z, xi, nt2::trans(yi));
  NT2_TEST_ULP_EQUAL(r2i, zi, 3);

}


NT2_TEST_CASE_TPL( bipchip2, NT2_REAL_TYPES )
{
  using nt2::_;
  nt2::table<T> x =  nt2::linspace(T(1),  T(3), 3);
  nt2::table<T> y =  nt2::linspace(T(1),  T(4), 4);
  nt2::table<T> z =  reshape(nt2::linspace(T(1),  T(12), 12), 4, 3);
  nt2::table<T> xi =  nt2::linspace(T(1),  T(3), 5);
  nt2::table<T> yi =  nt2::linspace(T(1),  T(4), 5);

  nt2::table<T> xxi, yyi;
  nt2::tie(xxi, yyi) = nt2::meshgrid(xi, yi);
  nt2::table<T> zi = nt2::bipchip(x, y, z, xxi, yyi);
  nt2::table<T> ri =  nt2::trans(nt2::cons<T>(nt2::of_size(5, 5),
                                              1.00000000000000,    3.00000000000000,    5.00000000000000,    7.00000000000000,    9.00000000000000,
                                              1.75000000000000,    3.75000000000000,    5.75000000000000,    7.75000000000000,    9.75000000000000,
                                              2.50000000000000,    4.50000000000000,    6.50000000000000,    8.50000000000000,   10.50000000000000,
                                              3.25000000000000,    5.25000000000000,    7.25000000000000,    9.25000000000000,   11.25000000000000,
                                              4.00000000000000,    6.00000000000000,    8.00000000000000,   10.00000000000000,   12.00000000000000));
  NT2_TEST_EQUAL(ri, zi);
}





