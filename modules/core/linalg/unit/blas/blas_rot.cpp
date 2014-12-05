//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/include/functions/blas_rot.hpp>
#include <nt2/include/functions/mtimes.hpp>
#include <nt2/include/functions/cons.hpp>
#include <nt2/include/functions/colon.hpp>
#include <nt2/include/functions/vertcat.hpp>
#include <nt2/include/constants/zero.hpp>
#include <nt2/include/constants/sqrt_2o_2.hpp>


#include <nt2/table.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/ulp.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>


NT2_TEST_CASE_TPL(blas_rot, NT2_REAL_TYPES )
{
  using nt2::blas_rot;

  T c  = nt2::Sqrt_2o_2<T>();
  T s  = nt2::Sqrt_2o_2<T>();
  nt2::table<T> x = nt2::_(T(0), T(10));
  nt2::table<T> y = nt2::_(T(0), T(10));
  nt2::table<T> r = nt2::cons<T>(nt2::of_size(2, 2), c, -s, s, c);
  nt2::table<T> v = nt2::catv(x, y);

  blas_rot(numel(x), boost::proto::value(x), 1,  boost::proto::value(y), 1, c, s);

  NT2_TEST_ULP_EQUAL(nt2::mtimes(r, v), catv(x, y), 0.5);

}

NT2_TEST_CASE_TPL(blas_rot2, NT2_REAL_TYPES )
{
  using nt2::blas_rot;
  using nt2::_;
  using nt2::end_;

  T c  = nt2::Sqrt_2o_2<T>();
  T s  = nt2::Sqrt_2o_2<T>();
  nt2::table<T> x = _(T(0), T(11));
  nt2::table<T> y = _(T(0), T(11));
  nt2::table<T> r = nt2::cons<T>(nt2::of_size(2, 2), c, -s, s, c);
  nt2::table<T> v = nt2::catv(x, y);

  blas_rot(numel(x)/2,  boost::proto::value(x), 2,  boost::proto::value(y), 2, c, s);
  nt2::table<T> rv = v;
  rv(_, _(1, 2, end_)) = nt2::mtimes(r, v(_, _(1, 2, end_)));
  NT2_TEST_ULP_EQUAL(rv, catv(x, y), 0.5);

}
