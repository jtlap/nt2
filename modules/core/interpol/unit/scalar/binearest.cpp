//==============================================================================
//         Copyright 2015 J.T. Lapreste
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/table.hpp>
#include <nt2/include/functions/binearest.hpp>
#include <nt2/include/functions/cons.hpp>
#include <nt2/include/functions/meshgrid.hpp>
#include <nt2/include/functions/repmat.hpp>
#include <nt2/include/functions/linspace.hpp>
#include <nt2/include/functions/isequal.hpp>
#include <nt2/include/functions/transpose.hpp>
#include <nt2/include/functions/expand_to.hpp>
#include <nt2/include/functions/tocomplex.hpp>
#include <nt2/include/functions/of_size.hpp>
#include <nt2/include/constants/nan.hpp>


#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/basic.hpp>
#include <nt2/sdk/unit/tests/exceptions.hpp>
#include <nt2/sdk/complex/meta/as_complex.hpp>



NT2_TEST_CASE_TPL( binearest, NT2_REAL_TYPES )
{
  using nt2::_;
  nt2::table<T> x =  nt2::linspace(T(1),  T(3), 3);
  nt2::table<T> y =  nt2::linspace(T(1),  T(4), 4);
  nt2::table<T> z =  reshape(nt2::linspace(T(1),  T(12), 12), 4, 3);
  nt2::table<T> xi =  nt2::linspace(T(1),  T(3), 12);
  nt2::table<T> yi =  nt2::linspace(T(1),  T(3), 12);
  nt2::table<T> ri =  nt2::cons<T>(   1,    1,    1,    6,    6,    6,    6,    6,    6,   11,   11,   11);

  nt2::table<T> zi = nt2::binearest(x, y, z, xi, yi);
  NT2_TEST_EQUAL(ri, zi);
  NT2_TEST_EQUAL(ri, nt2::binearest(x, y, z, xi, yi));

  xi =  nt2::linspace(T(1),  T(4), 12);
  yi =  nt2::linspace(T(0),  T(3), 12);
  zi = nt2::binearest(x, y, z, xi, yi);
  NT2_DISPLAY(zi);
  ri =  nt2::cons<T>( nt2::Nan<T>(), nt2::Nan<T>(), nt2::Nan<T>(), nt2::Nan<T>(), 5, 5, 10, 10
                    , nt2::Nan<T>(), nt2::Nan<T>(), nt2::Nan<T>(), nt2::Nan<T>());
  NT2_TEST_EQUAL(ri, zi);
  NT2_TEST_EQUAL(ri, nt2::binearest(x, y, z, xi, yi));
}


NT2_TEST_CASE_TPL( binearest2, NT2_REAL_TYPES )
{
  using nt2::_;
  nt2::table<T> x =  nt2::linspace(T(1),  T(3), 3);
  nt2::table<T> y =  nt2::linspace(T(1),  T(4), 4);
  nt2::table<T> z =  reshape(nt2::linspace(T(1),  T(12), 12), 4, 3);
  nt2::table<T> xi =  nt2::linspace(T(1),  T(3), 5);
  nt2::table<T> yi =  nt2::linspace(T(1),  T(4), 5);

  nt2::table<T> xxi, yyi;
  nt2::tie(xxi, yyi) = nt2::meshgrid(xi, yi);
  NT2_DISPLAY(xxi);
  NT2_DISPLAY(yyi);
  nt2::table<T> zi = nt2::binearest(x, y, z, xxi, yyi);
  NT2_DISPLAY(zi);
  nt2::table<T> ri =  nt2::trans(nt2::cons<T>(nt2::of_size(5, 5),
                                              1,    5,    5,    9,    9,
                                              2,    6,    6,   10,   10,
                                              3,    7,    7,   11,   11,
                                              3,    7,    7,   11,   11,
                                              4,    8,    8,   12,   12));
  NT2_TEST_EQUAL(ri, zi);
  NT2_TEST_EQUAL(ri, nt2::binearest(x, y, z, xxi, yyi));
}


NT2_TEST_CASE_TPL( binearestc, NT2_REAL_TYPES )
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
  NT2_DISPLAY(xxi);
  NT2_DISPLAY(yyi);
  nt2::table<cT> zi = nt2::binearest(x, y, z, xxi, yyi);
  NT2_DISPLAY(zi);
  nt2::table<T> ri =  nt2::trans(nt2::cons<T>(nt2::of_size(5, 5),
                                              1,    5,    5,    9,    9,
                                              2,    6,    6,   10,   10,
                                              3,    7,    7,   11,   11,
                                              3,    7,    7,   11,   11,
                                              4,    8,    8,   12,   12));
  NT2_TEST_EQUAL(nt2::tocomplex(ri, ri), zi);
}


NT2_TEST_CASE_TPL( binearestc2, NT2_REAL_TYPES )
{
  using nt2::_;
  using cT = typename nt2::meta::as_complex<T>::type;
  nt2::table<T> x =  nt2::linspace(T(1),  T(3), 3);
  nt2::table<T> y =  nt2::linspace(T(1),  T(4), 4);
  nt2::table<cT> z =  reshape(nt2::linspace(cT(1, 1),  cT(12, 12), 12), 4, 3);
  nt2::table<T> xi =  nt2::linspace(T(1),  T(3), 12);
  nt2::table<T> yi =  nt2::linspace(T(1),  T(3), 12);
  nt2::table<T> ri =  nt2::cons<T>(   1,    1,    1,    6,    6,    6,    6,    6,    6,   11,   11,   11);

  nt2::table<cT> zi = nt2::binearest(x, y, z, xi, yi);
  NT2_TEST_EQUAL(tocomplex(ri, ri), zi);


}

NT2_TEST_CASE_TPL( binearest0, NT2_REAL_TYPES )
{
  using nt2::_;
  nt2::table<T> x =  nt2::linspace(T(1),  T(3), 3);
  nt2::table<T> y =  nt2::linspace(T(1),  T(4), 4);
  nt2::table<T> z =  reshape(nt2::linspace(T(1),  T(12), 12), 4, 3);
  nt2::table<T> xi =  nt2::linspace(T(1),  T(3), 12);
  nt2::table<T> yi =  nt2::linspace(T(1),  T(3), 12);
  nt2::table<T> ri =  nt2::trans(
    nt2::cons<T>(nt2::of_size(5, 7),
                 1,    5,    5,    9,    9,
                 2,    6,    6,   10,   10,
                 2,    6,    6,   10,   10,
                 3,    7,    7,   11,   11,
                 3,    7,    7,   11,   11,
                 4,    8,    8,   12,   12,
                 4,    8,    8,   12,   12
                )
  );

  nt2::table<T> zi = nt2::binearest(z, 1);
  NT2_TEST_EQUAL(ri, zi);
  NT2_TEST_EQUAL(ri, nt2::binearest(z));

}


