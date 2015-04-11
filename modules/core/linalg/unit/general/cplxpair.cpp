//==============================================================================
//         Copyright 2015 J.T. Lapreste
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/table.hpp>
#include <nt2/include/functions/cplxpair.hpp>
#include <nt2/include/functions/reshape.hpp>
#include <nt2/include/functions/zeros.hpp>
#include <nt2/include/functions/repnum.hpp>
#include <nt2/include/functions/cons.hpp>
#include <nt2/include/functions/tocomplex.hpp>
#include <nt2/include/functions/flipud.hpp>
#include <nt2/include/constants/eps.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/ulp.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>

NT2_TEST_CASE_TPL( cplxpair_scalar, NT2_REAL_TYPES )
{
  T x = nt2::cplxpair(T(42));
  NT2_TEST_EQUAL( x, T(42) );

}

NT2_TEST_CASE_TPL( cplxpair, NT2_REAL_TYPES )
{
  nt2::table<T> y;
  nt2::table<T> c, v;
  y = nt2::reshape(nt2::_(T(15), T(-1), T(1)), 3, 5);
  NT2_DISPLAY(y);
  c = nt2::cplxpair(y);
  NT2_TEST_ULP_EQUAL(c, nt2::flipud(y), 1.5);
  NT2_DISPLAY(c);
}


NT2_TEST_CASE_TPL( cplxpairc1, NT2_REAL_TYPES )
{
  typedef std::complex<T> cT;
  nt2::table<cT> y;
  nt2::table<cT> c, v;
  y = nt2::reshape(nt2::_(T(15), T(-1), T(1)), 3, 5);
  NT2_DISPLAY(y);
  c = nt2::cplxpair(y);
  NT2_DISPLAY(c);
  NT2_TEST_ULP_EQUAL(c, nt2::flipud(y), 1.5);
  nt2::table<T> yr = nt2::cons <T>(nt2::of_size(1, 17),  1,  1,  1,  1, 2, 4,  2,  4, 2,-1, 5, 3,  3, 7,-1, 10, 8);
  nt2::table<T> yi = nt2::cons <T>(nt2::of_size(1, 17),  1, -1,  1, -1, 2, 3, -2, -3, 0, 0, 0, 3, -3, 0, 0, 0, 0);
  y = tocomplex(yr, yi);
  NT2_DISPLAY(y);
  c = nt2::cplxpair(y);
  NT2_DISPLAY(c);
  nt2::table<cT> res = nt2::cons <cT>(nt2::of_size(1, 17),
                                      cT(1,-1), cT(1,1), cT(1,-1), cT(1,1), cT(2,-2),
                                      cT(2,2), cT(3,-3), cT(3,3), cT(4,-3), cT(4,3),
                                      cT(-1,0), cT(-1,0), cT(2,0), cT(5,0), cT(7,0),
                                      cT(8,0), cT(10,0));

  NT2_TEST_ULP_EQUAL(c, res, 1.5);
}

NT2_TEST_CASE_TPL( cplxpairc, NT2_REAL_TYPES )
{
  typedef std::complex<T> cT;
  nt2::table<cT> y;
  nt2::table<cT> c, v;
  y = nt2::reshape(nt2::_(T(15), T(-1), T(1)), 3, 5);
  NT2_DISPLAY(y);
  c = nt2::cplxpair(y);
  NT2_DISPLAY(c);
  NT2_TEST_ULP_EQUAL(c, nt2::flipud(y), 1.5);
  nt2::table<T> yr = nt2::cons <T>(nt2::of_size(1, 10),  1,  1,  1,  1, 2, 4,  2,  4, 3,  3);
  nt2::table<T> yi = nt2::cons <T>(nt2::of_size(1, 10),  1, -1,  1, -1, 2, 3, -2, -3, 3, -3);
  y = tocomplex(yr, yi);
  NT2_DISPLAY(y);
  c = nt2::cplxpair(y);
  nt2::table<cT> res = nt2::cons <cT>(nt2::of_size(1, 10),
                                      cT(1,-1), cT(1,1), cT(1,-1), cT(1,1), cT(2,-2),
                                      cT(2,2), cT(3,-3), cT(3,3), cT(4,-3), cT(4,3)
                                     );
  NT2_TEST_ULP_EQUAL(c, res, 1.5);
  NT2_DISPLAY(c);

  c = nt2::cplxpair(trans(y), nt2::Eps<T>(), 2);
  NT2_DISPLAY(c);

}


