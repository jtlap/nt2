//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/include/functions/csort.hpp>
#include <nt2/table.hpp>
#include <nt2/include/functions/tie.hpp>
#include <nt2/include/functions/colon.hpp>
#include <nt2/include/functions/reshape.hpp>
#include <nt2/include/functions/flipud.hpp>
#include <nt2/include/functions/rif.hpp>
#include <nt2/include/functions/cif.hpp>
#include <nt2/include/functions/ric.hpp>
#include <nt2/include/functions/cic.hpp>
#include <nt2/include/functions/fliplr.hpp>
#include <nt2/include/functions/isequal.hpp>
#include <nt2/include/functions/vertcat.hpp>
#include <nt2/include/functions/horzcat.hpp>
#include <nt2/include/functions/ones.hpp>
#include <nt2/include/functions/zeros.hpp>
#include <nt2/include/constants/nan.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/basic.hpp>
#include <string>

NT2_TEST_CASE_TPL( csort_scalar, (float)(double))//NT2_TYPES )
{
  T x = nt2::csort(T(42));
  NT2_TEST_EQUAL( x, T(42) );

  x = nt2::csort(T(42),1);
  NT2_TEST_EQUAL( x, T(42) );

  x = nt2::csort(T(42),0);
  NT2_TEST_EQUAL( x, T(42) );

}


NT2_TEST_CASE_TPL( indsort, NT2_TYPES )
{
  nt2::table<T> y(nt2::reshape(nt2::colon(T(12), T(-1), T(1)), 3, 4));
  nt2::table<T> sy;
  NT2_DISPLAY(y);
  sy =  csort(y);
  NT2_TEST_EQUAL(sy, nt2::flipud(y));
  sy =  csort(y, 2);
  NT2_TEST_EQUAL(sy, nt2::fliplr(y));
  sy =  csort(y, 2, [](T a, T b){ return b < a; });
  NT2_DISPLAY(sy);
  NT2_TEST_EQUAL(sy, y);
  sy =  csort(y, [](T a, T b){ return a < b; });
  nt2::table<std::size_t> idx;
  tie(sy, idx) =  csort(y, 2, [](T a, T b){ return a < b; });
  NT2_TEST_EQUAL(sy, nt2::fliplr(y));
  NT2_DISPLAY(idx);

//   nt2::table<int32_t> idx;
//   nt2::tie(sy, idx) =  csort(y);
//   NT2_DISPLAY(y);
//   NT2_DISPLAY(sy);
//   NT2_DISPLAY(idx);
//   NT2_TEST_EQUAL(idx, nt2::flipud(nt2::rif(3, 4, nt2::meta::as_<int32_t>())));
//   nt2::tie(sy, idx) =  csort(y, 2);
//   NT2_DISPLAY(y);
//   NT2_DISPLAY(sy);
//   NT2_DISPLAY(idx);
//   NT2_TEST_EQUAL(idx, nt2::fliplr(nt2::cif(3, 4, nt2::meta::as_<int32_t>())));

//   nt2::table<T, nt2::C_index_> y1(nt2::reshape(nt2::colon(T(12), T(-1), T(1)), 3, 4));
//   nt2::table<T, nt2::C_index_> sy1;
//   nt2::table<int32_t, nt2::C_index_> idx1;
//   nt2::tie(sy1, idx1) =  csort(y1);
//   NT2_DISPLAY(y1);
//   NT2_DISPLAY(sy1);
//   NT2_DISPLAY(idx1);
//   NT2_TEST_EQUAL(idx1, nt2::flipud(nt2::ric(3, 4, nt2::meta::as_<int32_t>())));


}




