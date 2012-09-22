/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#define NT2_UNIT_MODULE "nt2::sum1 function"

#include <nt2/table.hpp>
#include <nt2/include/functions/tie.hpp>
#include <nt2/include/functions/sort.hpp>
#include <nt2/include/functions/colon.hpp>
#include <nt2/include/functions/reshape.hpp>
#include <nt2/include/functions/flipud.hpp>
#include <nt2/include/functions/fliplr.hpp>
#include <nt2/include/functions/isequal.hpp>
#include <nt2/include/functions/vertcat.hpp>
#include <nt2/include/functions/ones.hpp>
#include <nt2/include/constants/nan.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/basic.hpp>
#include <string>

// NT2_TEST_CASE_TPL( sort_scalar, (float)(double))//NT2_TYPES )
// {
//   T x = nt2::sort(T(42));
//   NT2_TEST_EQUAL( x, T(42) );

//   x = nt2::sort(T(42),1);
//   NT2_TEST_EQUAL( x, T(42) );

//   x = nt2::sort(T(42),0);
//   NT2_TEST_EQUAL( x, T(42) );

// }

NT2_TEST_CASE_TPL( sort, (float)(double))//NT2_TYPES )
{
  using nt2::_;
  nt2::table<T> y(nt2::reshape(nt2::colon(T(16), T(-1), T(1)), 4, 4));
  nt2::table<T> sy = sort(y);
  NT2_DISPLAY(y);
  NT2_DISPLAY(sy);
  NT2_TEST(isequal(sy, nt2::flipud(y)));
  nt2::table<T> sy1 = sort(sy, 1, 'd');
  NT2_DISPLAY(sy1);
  NT2_TEST(isequal(y, sy1));
  nt2::table<T> sy2 = sort(sy,'d');
  NT2_DISPLAY(sy2);
  NT2_TEST(isequal(y, sy2));
//    {
//      //  Doesnot work erreur: function returning an array
//      nt2::table<T> sy1 = sort(sy, 1, "d");
//      NT2_DISPLAY(sy1);
//      NT2_TEST(isequal(y, sy1));
//      nt2::table<T> sy2 = sort(sy,"d");
//      NT2_DISPLAY(sy2);
//      NT2_TEST(isequal(y, sy2));
//    }
  {
    nt2::table<T> y1 = nt2::fliplr(y);
    nt2::table<T> sy = sort(y1, 2, 'd');
    NT2_DISPLAY(y1);
    NT2_DISPLAY(sy);
    nt2::table<T> sy1 = sort(y, 2, 'a');
    NT2_DISPLAY(y);
    NT2_DISPLAY(sy1);
  }
  {
  nt2::table<T> y(nt2::reshape(nt2::colon(T(27), T(-1), T(1)), 3, 3, 3));
  //    nt2::table<T> y1 = nt2::fliplr(y);
  nt2::table<T> sy = sort(y);
  NT2_DISPLAY(y);
  NT2_DISPLAY(sy);
  nt2::table<T> sy1 = sort(y, 2);
  NT2_DISPLAY(y);
  NT2_DISPLAY(sy1);
  }
  {
    nt2::table<T> y(nt2::reshape(nt2::colon(T(24*3-1), T(-1), T(0)), 2, 3, 4, 3));
    //    nt2::table<T> y1 = nt2::fliplr(y);
    nt2::table<T> sy = sort(y);
    NT2_DISPLAY(y);
    NT2_DISPLAY(sy);
    nt2::table<T> sy1 = sort(y, 2);
    NT2_DISPLAY(y);
    NT2_DISPLAY(sy1);
    nt2::table<T> sy2 = sort(y, 3);
    NT2_DISPLAY(y);
    NT2_DISPLAY(sy2);
    nt2::table<T> sy3 = sort(y, 4);
    NT2_DISPLAY(y);
    NT2_DISPLAY(sy3);
  }
}
NT2_TEST_CASE_TPL( indsort, (float)(double))//NT2_TYPES )
{
  nt2::table<T> y(nt2::reshape(nt2::colon(T(24*3-1), T(-1), T(0)), 2, 3, 4, 3));
  nt2::table<T> sy;
  nt2::table<int32_t> idx;
  nt2::tie(sy, idx) =  sort(y);
  NT2_DISPLAY(y);
  NT2_DISPLAY(sy);
  NT2_DISPLAY(idx);
  nt2::tie(sy, idx) =  sort(y, 2);
  NT2_DISPLAY(y);
  NT2_DISPLAY(sy);
  NT2_DISPLAY(idx);

  nt2::table<T, nt2::C_index_> y1(nt2::reshape(nt2::colon(T(24*3-1), T(-1), T(0)), 2, 3, 4, 3));
  nt2::table<T, nt2::C_index_> sy1;
  nt2::table<int32_t, nt2::C_index_> idx1;
  nt2::tie(sy1, idx1) =  sort(y1);
  NT2_DISPLAY(y1);
  NT2_DISPLAY(sy1);
  NT2_DISPLAY(idx1);

 //  nt2::table<T> y2(nt2::reshape(nt2::colon(T(24*3-1), T(-1), T(0)), 2, 3, 4, 3));
//   nt2::table<T> sy2;
//   nt2::table<int32_t, nt2::C_index_> idx2;
//   nt2::tie(nt2::_ , idx2) =  sort(y2);
//   NT2_DISPLAY(y2);
//   NT2_DISPLAY(idx2);

}
NT2_TEST_CASE_TPL( sortnan, (float)(double))//NT2_TYPES )
{
  nt2::table<T> y;
  y =  nt2::vertcat(nt2::ones(1, 4, nt2::meta::as_<T>()), nt2::Nan<T>()*nt2::ones(1, 4, nt2::meta::as_<T>()))(nt2::_);

  nt2::table<T> sy;
  sy =  sort(y);
  NT2_DISPLAY(y);
  NT2_DISPLAY(sy);

}
