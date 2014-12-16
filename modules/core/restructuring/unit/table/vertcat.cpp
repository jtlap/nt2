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
#include <nt2/include/functions/vertcat.hpp>
#include <nt2/include/functions/ones.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/basic.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/exceptions.hpp>

NT2_TEST_CASE( vertcat_scalar )
{
  nt2::table<float> ref = nt2::cons(1.3f, 3.f);

  NT2_TEST_EQUAL( nt2::vertcat(1.3f, 3.f), ref );
  NT2_TEST_EQUAL( nt2::vertcat(1.5), 1.5 );
}

NT2_TEST_CASE( vertcat_expr_scalar )
{
  using nt2::_;
  nt2::table<float> a = nt2::rif(nt2::of_size(8,1), nt2::meta::as_<float>());

  NT2_TEST_EQUAL( vertcat(a, 3.f)(_(1, size(a, 1)),1) , a   );
  NT2_TEST_EQUAL( vertcat(a, 3.f)(size(a, 1)+1,1)     , 3.f );

  NT2_TEST_EQUAL( vertcat(5.f,a)(1, 1)              , 5.f );
  NT2_TEST_EQUAL( vertcat(5.f,a)(_(2, nt2::end_),1) , a   );

  NT2_TEST_ASSERT ( vertcat ( 5.f
                            , nt2::rif( nt2::of_size(1, 3)
                                      , nt2::meta::as_<float>()
                                      )
                            )
                  );

  NT2_TEST_ASSERT ( vertcat ( nt2::rif( nt2::of_size(1, 3)
                                      , nt2::meta::as_<float>()
                                      )
                            , 0.f
                            )
                  );
}

NT2_TEST_CASE( vertcat_expr )
{
  using nt2::_;

  nt2::table<float> a = nt2::rif(nt2::of_size(2,2,2,2), nt2::meta::as_<float>());
  nt2::table<float> b = nt2::cif(nt2::of_size(2,2,2,2), nt2::meta::as_<float>());

  NT2_TEST_EQUAL(vertcat(a), a);
  NT2_TEST_EQUAL(vertcat(a, b)(_(1, size(a, 1)),_,_,_), a  );
  NT2_TEST_EQUAL(vertcat(a, b)(_(size(a, 1)+1, nt2::end_),_,_,_),b);

  NT2_TEST_ASSERT ( vertcat ( nt2::rif( nt2::of_size(2, 3)
                                      , nt2::meta::as_<float>()
                                      )
                            , nt2::rif( nt2::of_size(2, 4)
                                      , nt2::meta::as_<float>()
                                      )
                            )
                  );
}

NT2_TEST_CASE( vertcat_empty )
{
  nt2::table<double> c0;
  nt2::table<double> c1 = nt2::ones(3, 3);

  NT2_TEST_EQUAL(nt2::vertcat(c0, c0), c0);
  NT2_TEST_EQUAL(nt2::vertcat(c0, c1), c1);
  NT2_TEST_EQUAL(nt2::vertcat(c1, c0), c1);
  NT2_TEST_EQUAL(nt2::vertcat(c0, 1.), 1.);
  NT2_TEST_EQUAL(nt2::vertcat(1., c0), 1.);
}
