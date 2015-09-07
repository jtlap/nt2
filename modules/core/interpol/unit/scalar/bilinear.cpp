//==============================================================================
//         Copyright 2015 J.T. Lapreste
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================

#include <nt2/table.hpp>
#include <nt2/include/functions/bilinear.hpp>
#include <nt2/include/functions/cons.hpp>
#include <nt2/include/functions/repmat.hpp>
#include <nt2/include/functions/linspace.hpp>
#include <nt2/include/functions/isequal.hpp>
#include <nt2/include/functions/transpose.hpp>
#include <nt2/include/functions/expand_to.hpp>
#include <nt2/include/functions/of_size.hpp>
#include <nt2/include/constants/nan.hpp>
#include <boost/core/ignore_unused.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/ulp.hpp>
#include <nt2/sdk/unit/tests/basic.hpp>
#include <nt2/sdk/unit/tests/exceptions.hpp>
#include <nt2/sdk/complex/meta/as_complex.hpp>

#include <nt2/include/functions/tocomplex.hpp>
#include <nt2/include/functions/of_size.hpp>


NT2_TEST_CASE_TPL( bilinear, NT2_REAL_TYPES )
{
  using nt2::_;
  nt2::table<T> x =  nt2::linspace(T(1),  T(3), 3);
  nt2::table<T> y =  nt2::linspace(T(1),  T(4), 4);
  nt2::table<T> z =  reshape(nt2::linspace(T(1),  T(12), 12), 4, 3);
  nt2::table<T> xi =  nt2::linspace(T(1),  T(3), 12);
  nt2::table<T> yi =  nt2::linspace(T(1),  T(3), 12);
  nt2::table<T> ri =  nt2::cons<T>(nt2::of_size(1, 12),
                                   1.00000000000000,    1.90909090909091,    2.81818181818182,    3.72727272727273,
                                   4.63636363636364,    5.54545454545455,    6.45454545454545,    7.36363636363636,
                                   8.27272727272727,    9.18181818181818,   10.09090909090909,   11.00000000000000);

  nt2::table<T> zi = nt2::bilinear(x, y, z, xi, yi);
  NT2_DISPLAY(  nt2::bilinear(x, y, z, xi, yi));
  NT2_TEST_ULP_EQUAL(ri, zi, 3.5);

  xi =  nt2::linspace(T(1),  T(4), 12);
  yi =  nt2::linspace(T(0),  T(3), 12);
  zi = nt2::bilinear(x, y, z, xi, yi);
  ri =  nt2::cons<T>( nt2::Nan<T>(), nt2::Nan<T>(), nt2::Nan<T>(), nt2::Nan<T>(),
                      5.45454545454545,   6.81818181818182,   8.18181818181818,   9.54545454545454,
                     nt2::Nan<T>(), nt2::Nan<T>(), nt2::Nan<T>(), nt2::Nan<T>());
  NT2_TEST_ULP_EQUAL(ri, zi, 3.5);
}




 NT2_TEST_CASE_TPL( bilinear2, NT2_REAL_TYPES )
{
  using nt2::_;
  nt2::table<T> x =  nt2::linspace(T(1),  T(3), 3);
  nt2::table<T> y =  nt2::linspace(T(1),  T(4), 4);
  nt2::table<T> z =  reshape(nt2::linspace(T(1),  T(12), 12), 4, 3);
  nt2::table<T> xi =  nt2::linspace(T(1),  T(3), 5);
  nt2::table<T> yi =  nt2::linspace(T(1),  T(4), 5);

  nt2::table<T> xxi, yyi;
  nt2::tie(xxi, yyi) = nt2::meshgrid(xi, yi);
  nt2::table<T> zi = nt2::bilinear(x, y, z, xxi, yyi);
  nt2::table<T> ri =  nt2::trans(
    nt2::cons<T>(nt2::of_size(5, 5),
                 1.00000000000000,    3.00000000000000,    5.00000000000000,    7.00000000000000,    9.00000000000000,
                 1.75000000000000,    3.75000000000000,    5.75000000000000,    7.75000000000000,    9.75000000000000,
                 2.50000000000000,    4.50000000000000,    6.50000000000000,    8.50000000000000,   10.50000000000000,
                 3.25000000000000,    5.25000000000000,    7.25000000000000,    9.25000000000000,   11.25000000000000,
                 4.00000000000000,    6.00000000000000,    8.00000000000000,   10.00000000000000,   12.00000000000000));
  NT2_TEST_EQUAL(ri, zi);
  NT2_TEST_EQUAL(ri, nt2::bilinear(x, y, z, xxi, yyi));
}


NT2_TEST_CASE_TPL( bilinearc, NT2_REAL_TYPES )
{
  using nt2::_;
  using cT = typename nt2::meta::as_complex<T>::type;
  nt2::table<T> x =  nt2::linspace(T(1),  T(3), 3);
  nt2::table<T> y =  nt2::linspace(T(1),  T(4), 4);
  nt2::table<cT> z =  reshape(nt2::linspace(cT(T(1), T(1)),  cT(12, 12), 12), 4, 3);
  nt2::table<T> xi =  nt2::linspace(T(1),  T(3), 5);
  nt2::table<T> yi =  nt2::linspace(T(1),  T(4), 5);

  nt2::table<T> xxi, yyi;
  nt2::tie(xxi, yyi) = nt2::meshgrid(xi, yi);
  nt2::table<cT> zi = nt2::bilinear(x, y, z, xxi, yyi);
  nt2::table<T> ri =  nt2::trans(
    nt2::cons<T>(nt2::of_size(5, 5),
                 1.00000000000000,    3.00000000000000,    5.00000000000000,    7.00000000000000,    9.00000000000000,
                 1.75000000000000,    3.75000000000000,    5.75000000000000,    7.75000000000000,    9.75000000000000,
                 2.50000000000000,    4.50000000000000,    6.50000000000000,    8.50000000000000,   10.50000000000000,
                 3.25000000000000,    5.25000000000000,    7.25000000000000,    9.25000000000000,   11.25000000000000,
                 4.00000000000000,    6.00000000000000,    8.00000000000000,   10.00000000000000,   12.00000000000000)
  );

  NT2_TEST_EQUAL(nt2::tocomplex(ri, ri), zi);
}


NT2_TEST_CASE_TPL( bilinearc2, NT2_REAL_TYPES )
{
  using nt2::_;
  using cT = typename nt2::meta::as_complex<T>::type;
  nt2::table<T> x =  nt2::linspace(T(1),  T(3), 3);
  nt2::table<T> y =  nt2::linspace(T(1),  T(4), 4);
  nt2::table<cT> z =  reshape(nt2::linspace(cT(1, 1),  cT(12, 12), 12), 4, 3);
  nt2::table<T> xi =  nt2::linspace(T(1),  T(3), 12);
  nt2::table<T> yi =  nt2::linspace(T(1),  T(3), 12);
  nt2::table<T> ri =  nt2::cons<T>(nt2::of_size(1, 12),
                                   1.00000000000000,    1.90909090909091,    2.81818181818182,    3.72727272727273,
                                   4.63636363636364,    5.54545454545455,    6.45454545454545,    7.36363636363636,
                                   8.27272727272727,    9.18181818181818,   10.09090909090909,   11.00000000000000);

  nt2::table<cT> zi = nt2::bilinear(x, y, z, xi, yi);
  NT2_TEST_ULP_EQUAL(tocomplex(ri, ri), zi, 3.5);


}

NT2_TEST_CASE_TPL( bilinear0, NT2_REAL_TYPES )
{
  using nt2::_;
  nt2::table<T> x =  nt2::linspace(T(1),  T(3), 3);
  nt2::table<T> y =  nt2::linspace(T(1),  T(4), 4);
  nt2::table<T> z =  reshape(nt2::linspace(T(1),  T(12), 12), 4, 3);
  nt2::table<T> xi =  nt2::linspace(T(1),  T(3), 12);
  nt2::table<T> yi =  nt2::linspace(T(1),  T(3), 12);
  nt2::table<T> ri =  nt2::trans(
    nt2::cons<T>(nt2::of_size(5, 7),
                 1.00000000000000,    3.00000000000000,    5.00000000000000,    7.00000000000000,    9.00000000000000,
                 1.50000000000000,   3.50000000000000,    5.50000000000000,    7.50000000000000,    9.50000000000000,
                 2.00000000000000,    4.00000000000000,    6.00000000000000,    8.00000000000000,   10.00000000000000,
                 2.50000000000000,    4.50000000000000,    6.50000000000000,    8.50000000000000,   10.50000000000000,
                 3.00000000000000,    5.00000000000000,    7.00000000000000,    9.00000000000000,   11.00000000000000,
                 3.50000000000000,    5.50000000000000,    7.50000000000000,    9.50000000000000,   11.50000000000000,
                 4.00000000000000,    6.00000000000000,    8.00000000000000,   10.00000000000000,   12.00000000000000
                )
  );

  nt2::table<T> zi = nt2::bilinear(z, 1);
  NT2_TEST_EQUAL(ri, zi);
  NT2_TEST_EQUAL(ri, nt2::bilinear(z));

}




