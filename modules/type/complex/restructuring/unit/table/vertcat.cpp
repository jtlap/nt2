//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
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
  typedef std::complex<float> cT;
  NT2_TEST_EQUAL( nt2::vertcat(cT(1.3f), cT(3.f))(1,1), 1.3f );
  NT2_TEST_EQUAL( nt2::vertcat(cT(1.3f), cT(3.f))(2,1), 3.f  );
  NT2_TEST_EQUAL( nt2::vertcat(cT(1.5)), cT(1.5) );
}

NT2_TEST_CASE( vertcat_expr_scalar )
{
  typedef std::complex<float> cT;
  using nt2::_;
  nt2::table<cT> a = nt2::rif(nt2::of_size(8,1), nt2::meta::as_<cT>());
  NT2_TEST_EQUAL( vertcat(a, cT(3.f))(_(1, size(a, 1)),1), a  );
  NT2_TEST_EQUAL( vertcat(a, cT(3.f))(size(a, 1)+1,1),cT(3.f));

  NT2_TEST_EQUAL( vertcat(cT(5.f),a)(1, 1), cT(5.f)  );
  NT2_TEST_EQUAL( vertcat(cT(5.f),a)(_(2, nt2::end_),1), a);

  NT2_TEST_ASSERT ( vertcat ( cT(5.f)
                            , nt2::rif( nt2::of_size(1, 3)
                                      , nt2::meta::as_<cT>()
                                      )
                            )
                  );

  NT2_TEST_ASSERT ( vertcat ( nt2::rif( nt2::of_size(1, 3)
                                      , nt2::meta::as_<cT>()
                                      )
                            , cT(0.f)
                            )
                  );
}

NT2_TEST_CASE( vertcat_expr )
{
  typedef std::complex<float> cT;
  using nt2::_;

  nt2::table<cT> a = nt2::rif(nt2::of_size(2, 3), nt2::meta::as_<cT>());
  nt2::table<cT> b = nt2::cif(nt2::of_size(4, 3), nt2::meta::as_<cT>());

  NT2_TEST_EQUAL(vertcat(a), a                                  );
  NT2_TEST_EQUAL(vertcat(a, b)(_(1, size(a, 1)),_), a           );
  NT2_TEST_EQUAL(vertcat(a, b)(_(size(a, 1)+1, nt2::end_),_),b  );

  NT2_TEST_ASSERT ( vertcat ( nt2::rif( nt2::of_size(2, 3)
                                      , nt2::meta::as_<cT>()
                                      )
                            , nt2::rif( nt2::of_size(2, 4)
                                      , nt2::meta::as_<cT>()
                                      )
                            )
                  );
}


NT2_TEST_CASE_TPL( vertcat_3,NT2_TYPES )
{
  typedef std::complex<double> cT;

  nt2::table<cT> c0 = nt2::zeros(0, 1, nt2::meta::as_<cT>());
  nt2::table<cT> c1 = nt2::zeros(1, 1, nt2::meta::as_<cT>());
  nt2::table<cT> c2 = nt2::vertcat(c0, c1);
  nt2::table<cT> c3 = nt2::vertcat(c1, c0);
  NT2_TEST_EQUAL(c2, c1);
  NT2_TEST_EQUAL(c3, c1);
}
