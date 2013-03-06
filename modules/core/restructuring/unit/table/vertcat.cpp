//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#define NT2_UNIT_MODULE "nt2::vertcat function"

#include <nt2/table.hpp>
#include <nt2/include/functions/rif.hpp>
#include <nt2/include/functions/cif.hpp>
#include <nt2/include/functions/size.hpp>
#include <nt2/include/functions/vertcat.hpp>
#include <nt2/include/functions/isequal.hpp>
#include <nt2/include/functions/zeros.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/basic.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/exceptions.hpp>

NT2_TEST_CASE( vertcat_scalar )
{
  NT2_TEST_EQUAL( nt2::vertcat(1.3f, 3.f)(1,1), 1.3f );
  NT2_TEST_EQUAL( nt2::vertcat(1.3f, 3.f)(2,1), 3.f  );
  NT2_TEST_EQUAL( nt2::vertcat(1.5), 1.5 );
}

NT2_TEST_CASE( vertcat_expr_scalar )
{
  using nt2::_;
  nt2::table<float> a = nt2::rif(nt2::of_size(8,1), nt2::meta::as_<float>());
  NT2_TEST( nt2::isequal( vertcat(a, 3.f)(_(1, size(a, 1)),1), a  ) );
  NT2_TEST_EQUAL( vertcat(a, 3.f)(size(a, 1)+1,1),3.f);

  NT2_TEST_EQUAL( vertcat(5.f,a)(1, 1), 5.f  );
  NT2_TEST( nt2::isequal( vertcat(5.f,a)(_(2, nt2::end_),1), a) );

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

  nt2::table<float> a = nt2::rif(nt2::of_size(2, 3), nt2::meta::as_<float>());
  nt2::table<float> b = nt2::cif(nt2::of_size(4, 3), nt2::meta::as_<float>());

  NT2_TEST( nt2::isequal( vertcat(a), a)                                  );
  NT2_TEST( nt2::isequal( vertcat(a, b)(_(1, size(a, 1)),_), a  )         );
  NT2_TEST( nt2::isequal( vertcat(a, b)(_(size(a, 1)+1, nt2::end_),_),b)  );

  NT2_TEST_ASSERT ( vertcat ( nt2::rif( nt2::of_size(2, 3)
                                      , nt2::meta::as_<float>()
                                      )
                            , nt2::rif( nt2::of_size(2, 4)
                                      , nt2::meta::as_<float>()
                                      )
                            )
                  );
}

NT2_TEST_CASE( vertcat_2 )
{

  nt2::table<double> c0 = nt2::zeros(0, 1);
  nt2::table<double> c1 = nt2::zeros(1, 1);
  nt2::table<double> c2 = nt2::vertcat(c0, c1);
  NT2_TEST( nt2::isequal(c2, c1));
  typedef float iT;
  nt2::table<iT> dc1 = nt2::colvect(nt2::_(iT(2), iT(4)));
  nt2::table<iT> dc2 = nt2::colvect(nt2::_(iT(2), iT(3)));
  nt2::table<iT> dc3 = nt2::vertcat(dc1, dc2);


}
NT2_TEST_CASE_TPL( vertcat_3,NT2_TYPES )
{

  nt2::table<double> c0 = nt2::zeros(0, 1);
  nt2::table<double> c1 = nt2::zeros(1, 1);
  nt2::table<double> c2 = nt2::vertcat(c0, c1);
  nt2::table<double> c3 = nt2::vertcat(c1, c0);
  NT2_DISPLAY(c0);
  NT2_DISPLAY(c1);
  NT2_DISPLAY(c2);
  NT2_DISPLAY(c3);
  NT2_TEST( nt2::isequal(c2, c1));
  NT2_TEST( nt2::isequal(c3, c1));

  typedef float iT;
  nt2::table<iT> dc1 = nt2::colvect(nt2::_(iT(2), iT(4)));
  nt2::table<iT> dc2 = nt2::colvect(nt2::_(iT(2), iT(3)));
  nt2::table<iT> dc3 = nt2::vertcat(dc1, dc2);
  NT2_DISPLAY(dc1);
  NT2_DISPLAY(dc2);
  NT2_DISPLAY(dc3);


}
