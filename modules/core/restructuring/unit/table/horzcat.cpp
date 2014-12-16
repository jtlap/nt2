//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2014   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012 - 2014   NumScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/table.hpp>
#include <nt2/include/functions/rif.hpp>
#include <nt2/include/functions/cif.hpp>
#include <nt2/include/functions/cons.hpp>
#include <nt2/include/functions/size.hpp>
#include <nt2/include/functions/horzcat.hpp>
#include <nt2/include/functions/ones.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/basic.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>
#include <nt2/sdk/unit/tests/exceptions.hpp>

NT2_TEST_CASE( horzcat_scalar )
{
  nt2::table<float> d = nt2::horzcat(1.3f, 3.f);
  NT2_TEST_EQUAL( d(1,1), 1.3f );
  NT2_TEST_EQUAL( d(1,2), 3.f  );

  double f = nt2::horzcat(1.5);
  NT2_TEST_EQUAL( f, 1.5 );
}

NT2_TEST_CASE( horzcat_expr_scalar )
{
  using nt2::_;
  nt2::table<float> a = nt2::rif(nt2::of_size(1, 8), nt2::meta::as_<float>());
  nt2::table<float> d = horzcat(a, 3.f);
  NT2_TEST_EQUAL( d(1, _(1, size(a, 2))), a);
  NT2_TEST_EQUAL( d(1, size(a, 2)+1),3.f);

  nt2::table<float> e = horzcat(5.f,a);
  NT2_TEST_EQUAL( e(1, 1), 5.f  );
  NT2_TEST_EQUAL( e(1, _(2, nt2::end_)), a);

  NT2_TEST_ASSERT ( horzcat ( 5.f
                            , nt2::rif( nt2::of_size(3, 1)
                                      , nt2::meta::as_<float>()
                                      )
                            )
                  );

  NT2_TEST_ASSERT ( horzcat ( nt2::rif( nt2::of_size(3, 1)
                                      , nt2::meta::as_<float>()
                                      )
                            , 0.f
                            )
                  );
}

NT2_TEST_CASE( horzcat_expr )
{
  using nt2::_;
  nt2::table<float> a = nt2::rif(nt2::of_size(2,2,2,2), nt2::meta::as_<float>());
  nt2::table<float> b = nt2::cif(nt2::of_size(2,2,2,2), nt2::meta::as_<float>());

  nt2::table<float> c = horzcat(a);
  NT2_TEST_EQUAL(c, a);

  nt2::table<float> d = horzcat(a, b);
  NT2_TEST_EQUAL( d(_, _(1, size(a, 2)),_,_), a );
  NT2_TEST_EQUAL( d(_, _(size(a, 2)+1, nt2::end_),_,_),b);

  NT2_TEST_ASSERT ( horzcat ( nt2::rif( nt2::of_size(3, 2)
                                      , nt2::meta::as_<float>()
                                      )
                            , nt2::rif( nt2::of_size(4, 2)
                                      , nt2::meta::as_<float>()
                                      )
                            )
                  );
}

NT2_TEST_CASE( horzcat_empty )
{
  nt2::table<double> c0;
  nt2::table<double> c1 = nt2::ones(3, 3);

  NT2_TEST_EQUAL(nt2::horzcat(c0, c0), c0);
  NT2_TEST_EQUAL(nt2::horzcat(c0, c1), c1);
  NT2_TEST_EQUAL(nt2::horzcat(c1, c0), c1);
  NT2_TEST_EQUAL(nt2::horzcat(c0, 1.), 1.);
  NT2_TEST_EQUAL(nt2::horzcat(1., c0), 1.);
}

NT2_TEST_CASE( horzcat_alias )
{
  nt2::table<double> c1  = nt2::ones(3, 3);
  nt2::table<double> ref = nt2::ones(3, 6);

  c1 = horzcat(c1,c1);

  NT2_TEST_EQUAL(c1, ref);
}
