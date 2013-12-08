//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/include/functions/deconv.hpp>
#include <nt2/include/functions/cons.hpp>
#include <nt2/include/functions/zeros.hpp>
#include <nt2/include/functions/colon.hpp>
#include <nt2/include/functions/polyadd.hpp>
#include <nt2/include/functions/conv.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/meta/as.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/ulp.hpp>
#include <nt2/core/container/table/table.hpp>

NT2_TEST_CASE_TPL ( deconv_1_0,  NT2_REAL_TYPES)
{

  using nt2::deconv;
  using nt2::tag::deconv_;
  nt2::container::table<T, nt2::_2D> a =  nt2::_(T(1), T(4));
  nt2::container::table<T, nt2::_2D> b =  nt2::_(T(1), T(2));
  nt2::container::table<T, nt2::_2D> c(nt2::of_size(1, 0));
  nt2::container::table<T, nt2::_2D> q1, q, r;
  nt2::tie(q, r) = deconv(a, b);

  NT2_TEST_ULP_EQUAL(polyadd(conv(b, q), r), a, 0.5);
  q1 =  deconv(a, b);
  NT2_TEST_ULP_EQUAL(q, q1, 0.5);

}


NT2_TEST_CASE_TPL ( deconv_real__2_0,  NT2_REAL_TYPES)
{
  using nt2::deconv;
  using nt2::tag::deconv_;
  T b = T(1.0);
  T a = T(0.0);
  T c = T(2.0);
  nt2::container::table<T> bb =  nt2::_(T(1), T(1));
  nt2::container::table<T> aa =  nt2::_(T(0), T(0));
  nt2::container::table<T> ab = T(0);
  NT2_TEST_EQUAL(ab,deconv(a, b));
  NT2_TEST_EQUAL(ab,deconv(aa, bb));
  NT2_TEST_EQUAL(c,deconv(b, T(0.5)));
  NT2_TEST_EQUAL(ab,deconv(aa, b));
  NT2_TEST_EQUAL(ab,deconv(a, bb));
}

