//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/table.hpp>
#include <nt2/include/functions/size.hpp>
#include <nt2/include/functions/blkdiag.hpp>
#include <nt2/include/functions/rif.hpp>
#include <nt2/include/functions/cif.hpp>
#include <nt2/include/functions/zeros.hpp>
#include <nt2/include/functions/isequal.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/basic.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>
#include <nt2/sdk/unit/tests/exceptions.hpp>


NT2_TEST_CASE( blkdiag_size2 )
{
  typedef float T;
  typedef std::complex<T> cT;
  using nt2::_;
  using nt2::end_;
  nt2::table<cT> a = nt2::rif(nt2::of_size(7, 6), nt2::meta::as_<cT>());
  nt2::table<cT> b = nt2::cif(nt2::of_size(9, 8), nt2::meta::as_<cT>());

  nt2::table<cT> c = blkdiag(a, b);
  NT2_TEST_EQUAL(a, c(_(1u, size(a, 1)), _(1u, size(a, 2))));
  NT2_TEST_EQUAL(b, c(_(size(a, 1)+1, end_), _(size(a, 2)+1, end_)));
  nt2::table<cT> z1 = c(_(1u, size(a, 1)), _(1u, size(a, 2)));
  nt2::table<cT> z2 = c(_(size(a, 1)+1, end_), _(size(a, 2)+1, end_));
  NT2_TEST_EQUAL(a, z1);
  NT2_TEST_EQUAL(b, z2);

  NT2_TEST_EQUAL(nt2::zeros(size(b, 1), size(a, 2), nt2::meta::as_<T>()),
                 c(_(size(a, 1)+1, end_), _(1u, size(a, 2))));
  nt2::table<cT> k1 = nt2::zeros(size(b, 1), size(a, 2), nt2::meta::as_<T>());
  nt2::table<cT> k2 = c(_(size(a, 1)+1, end_), _(1u, size(a, 2)));
  NT2_TEST_EQUAL(k1, k2);

  NT2_TEST_EQUAL(nt2::zeros(size(a, 1), size(b, 2), nt2::meta::as_<T>()),
                 c(_(1u, size(a, 1)), _(size(a, 2)+1, end_)));
  nt2::table<cT> l1 = nt2::zeros(size(a, 1), size(b, 2), nt2::meta::as_<T>());
  nt2::table<cT> l2 = c(_(1u, size(a, 1)), _(size(a, 2)+1, end_));
  NT2_TEST_EQUAL(l1, l2);

  nt2::table<cT> d = blkdiag(a);
  NT2_TEST_EQUAL(a, d);

  nt2::table<cT> e(nt2::of_size(0, 1));
  std::cout << "empty first" << std::endl;
  d = blkdiag(e, a);
  NT2_TEST_EQUAL(d, a);
  std::cout << "empty second" << std::endl;
  d = blkdiag(a, e);
  NT2_TEST_EQUAL(d, a);
}
