//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2014   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012 - 2014   NumScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/include/functions/blkdiag.hpp>
#include <nt2/include/functions/zeros.hpp>
#include <nt2/include/functions/size.hpp>
#include <nt2/include/functions/rif.hpp>
#include <nt2/include/functions/cif.hpp>

#include <nt2/table.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>

NT2_TEST_CASE( blkdiag_scalar )
{
  using T = float;

  nt2::table<T> d = nt2::blkdiag( T(42) );
  NT2_TEST_EQUAL(d(1),T(42));

  nt2::table<T> e = nt2::blkdiag( T(13), T(37) );
  NT2_TEST_EQUAL(e(1,1),T(13));
  NT2_TEST_EQUAL(e(2,2),T(37));
}

NT2_TEST_CASE( blkdiag_single )
{
  using T = float;

  nt2::table<T> a = nt2::rif(nt2::of_size(7, 6), nt2::meta::as_<T>());
  nt2::table<T> d = blkdiag(a);

  NT2_TEST_EQUAL(a, d);
}

NT2_TEST_CASE( blkdiag )
{
  using T = float;

  using nt2::_;
  using nt2::end_;

  nt2::table<T> a = nt2::rif(nt2::of_size(7, 6), nt2::meta::as_<T>());
  nt2::table<T> b = nt2::cif(nt2::of_size(9, 8), nt2::meta::as_<T>());
  nt2::table<T> c = blkdiag(a, b);

  NT2_TEST_EQUAL(a, c(_(1u, size(a, 1))     , _(1u, size(a, 2)) )     );
  NT2_TEST_EQUAL(b, c(_(size(a, 1)+1, end_) , _(size(a, 2)+1, end_) ) );

  NT2_TEST_EQUAL( nt2::zeros(size(b, 1), size(a, 2), nt2::meta::as_<T>())
                , c(_(size(a, 1)+1, end_), _(1u, size(a, 2)))
                );

  NT2_TEST_EQUAL( nt2::zeros(size(a, 1), size(b, 2), nt2::meta::as_<T>())
                , c(_(1u, size(a, 1)), _(size(a, 2)+1, end_))
                );
}

NT2_TEST_CASE( blkdiag_empty )
{
  using T = float;

  using nt2::_;
  using nt2::end_;

  nt2::table<T> a = nt2::rif(nt2::of_size(7, 6), nt2::meta::as_<T>());
  nt2::table<T> b;

  nt2::table<T> c = blkdiag(a, b);
  NT2_TEST_EQUAL(c,a);

  c = blkdiag(b,a);
  NT2_TEST_EQUAL(c,a);

  c = blkdiag(b,b);
  NT2_TEST_EQUAL(c,b);
}
