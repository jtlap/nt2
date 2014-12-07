//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/include/functions/blas_rotm.hpp>
#include <nt2/include/functions/blas_rotmg.hpp>
#include <nt2/include/functions/mtimes.hpp>
#include <nt2/include/functions/cons.hpp>
#include <nt2/include/functions/colon.hpp>
#include <nt2/include/functions/sqrt.hpp>
#include <nt2/include/functions/vertcat.hpp>
#include <nt2/include/functions/reshape.hpp>
#include <nt2/include/functions/repnum.hpp>
#include <nt2/include/functions/transpose.hpp>
#include <nt2/include/constants/zero.hpp>
#include <nt2/include/constants/nan.hpp>
#include <nt2/include/constants/mone.hpp>


#include <nt2/table.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/ulp.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>


NT2_TEST_CASE_TPL(blas_rotm, NT2_REAL_TYPES )
{
  using nt2::blas_rotm;

  T d1 = T(1);
  T d2 = T(1);
  T x1 = T(2);
  T y1 = T(2);
  nt2::table<T> v = nt2::cons<T>( nt2::of_size(2, 1)
                                , nt2::sqrt(d1)*x1,nt2::sqrt(d2)*y1);
  nt2::table<T> dparam = nt2::repnum(nt2::Nan<T>(), 1, 5);
  nt2::blas_rotmg(d1, d2, x1, y1, boost::proto::value(dparam));
  NT2_DISPLAY(dparam);
  nt2::table<T> r =  nt2::cons<T>( nt2::of_size(2, 2)
                                 , dparam(2), T(-1.0), T(1.0), dparam(5));
  NT2_DISPLAY(r);
  NT2_DISPLAY(v);
  NT2_TEST_ULP_EQUAL(nt2::mtimes(r, v)(2), nt2::Zero<T>(), 0.5);
//   nt2::table<T> v1 = nt2::cons<T>( nt2::of_size(2, 1), x1, T(0.0));
//   nt2::table<T> xx = v(1, nt2::_);
//   nt2::table<T> yy = v(2, nt2::_);
//   nt2::blas_rotm(1
//                 , boost::proto::value(xx), 1
//                 , boost::proto::value(yy), 1
//                 , boost::proto::value(dparam));
//   NT2_TEST_ULP_EQUAL( nt2::catv(xx, yy)
//                     , boost::proto::value(v1), 0.5);
}

