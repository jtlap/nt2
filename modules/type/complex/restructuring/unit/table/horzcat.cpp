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
#include <nt2/include/functions/horzcat.hpp>
#include <nt2/include/functions/rif.hpp>
#include <nt2/include/functions/cif.hpp>
#include <nt2/include/functions/zeros.hpp>
#include <nt2/include/functions/colon.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>
#include <nt2/sdk/unit/tests/exceptions.hpp>

NT2_TEST_CASE( horzcat_scalar )
{
  typedef std::complex<float> cT;
  nt2::table<cT> d = nt2::horzcat(1.3f, 3.f);
  NT2_TEST_EQUAL( d(1,1), 1.3f );
  NT2_TEST_EQUAL( d(1,2), 3.f  );

  double f = nt2::horzcat(1.5);
  NT2_TEST_EQUAL( f, 1.5 );
}

NT2_TEST_CASE( horzcat_expr_scalar )
{
  typedef std::complex<float> cT;
  using nt2::_;
  nt2::table<cT> a = nt2::rif(nt2::of_size(1, 8), nt2::meta::as_<cT>());
  nt2::table<cT> d = horzcat(a, cT(3.f));
  NT2_TEST_EQUAL( d(1, _(1, size(a, 2))), a  );
  NT2_TEST_EQUAL( d(1, size(a, 2)+1),3.f);

  nt2::table<cT> e = horzcat(cT(5.f),a);
  NT2_TEST_EQUAL( e(1, 1), cT(5.f)  );
  NT2_TEST_EQUAL( e(1, _(2, nt2::end_)), a);

  NT2_TEST_ASSERT ( horzcat ( cT(5.f)
                            , nt2::rif( nt2::of_size(3, 1)
                                      , nt2::meta::as_<cT>()
                                      )
                            )
                  );

  NT2_TEST_ASSERT ( horzcat ( nt2::rif( nt2::of_size(3, 1)
                                      , nt2::meta::as_<cT>()
                                      )
                            , cT(0.f)
                            )
                  );
}

NT2_TEST_CASE( horzcat_expr )
{
  typedef std::complex<float> cT;
  using nt2::_;
  nt2::table<cT> a = nt2::rif(nt2::of_size(3, 2), nt2::meta::as_<cT>());
  nt2::table<cT> b = nt2::cif(nt2::of_size(3, 4), nt2::meta::as_<cT>());

  nt2::table<cT> c = horzcat(a);
  NT2_TEST_EQUAL(c, a);

  nt2::table<cT> d = horzcat(a, b);
  NT2_TEST_EQUAL( d(_, _(1, size(a, 2))), a  )        ;
  NT2_TEST_EQUAL( d(_, _(size(a, 2)+1, nt2::end_)),b) ;

  NT2_TEST_ASSERT ( horzcat ( nt2::rif( nt2::of_size(3, 2)
                                      , nt2::meta::as_<cT>()
                                      )
                            , nt2::rif( nt2::of_size(4, 2)
                                      , nt2::meta::as_<cT>()
                                      )
                            )
                  );
}

