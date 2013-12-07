//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/include/functions/conv.hpp>
#include <nt2/include/functions/cons.hpp>
#include <nt2/include/functions/zeros.hpp>
#include <nt2/include/functions/colon.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/table.hpp>
#include <nt2/include/functions/complexify.hpp>
#include <boost/simd/sdk/simd/io.hpp>
#include <complex>
#include <nt2/sdk/meta/as.hpp>

NT2_TEST_CASE_TPL ( conv,  NT2_REAL_TYPES)
{
  typedef std::complex<T> cT;
  using nt2::conv;
  using nt2::tag::conv_;
  nt2::container::table<cT> a =  nt2::complexify(nt2::_(T(1), T(4)));
  nt2::container::table<cT> b =  nt2::complexify(nt2::_(T(1), T(3)));
  nt2::container::table<cT> c(nt2::of_size(1, 0));
  nt2::container::table<cT> ab = nt2::cons<cT>(nt2::of_size(1, 6), cT(1), cT(4), cT(10), cT(16), cT(17), cT(12));
  NT2_TEST_EQUAL(ab,conv(a, b));
  NT2_TEST_EQUAL(conv(a, c), nt2::zeros(1, 3, nt2::meta::as_<cT>()));
  NT2_TEST_EQUAL(conv(c, b), nt2::zeros(1, 2, nt2::meta::as_<cT>()));
  NT2_TEST_EQUAL(conv(b, b), nt2::cons<cT>(nt2::of_size(1, 5), cT(1), cT(4), cT(10), cT(12), cT(9)));
}

NT2_TEST_CASE_TPL ( conv_2,  NT2_REAL_TYPES)
{
  typedef std::complex<T> cT;
  using nt2::conv;
  using nt2::tag::conv_;
  cT a = T(1.0);
  cT b = T(0.0);
  cT c = T(2.0);
  nt2::container::table<cT> aa =  nt2::complexify(nt2::_(T(1), T(1)));
  nt2::container::table<cT> bb =  nt2::complexify(nt2::_(T(0), T(0)));
  nt2::container::table<cT> ab = cT(0);
  NT2_TEST_EQUAL(ab,conv(aa, bb));
  NT2_TEST_EQUAL(ab,conv(a, b));
  NT2_TEST_EQUAL(c,conv(a, c));
  NT2_TEST_EQUAL(ab,conv(aa, b));
  NT2_TEST_EQUAL(ab,conv(a, bb));
}

