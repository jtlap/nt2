/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#define NT2_UNIT_MODULE "nt2::logspace function"

#include <nt2/table.hpp>
#include <nt2/include/functions/logspace.hpp>
#include <nt2/include/functions/linspace.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests.hpp>
#include <boost/dispatch/meta/nth_hierarchy.hpp>

NT2_TEST_CASE( hierarchy )
{
  using boost::mpl::_;
  using boost::mpl::int_;
  using boost::dispatch::meta::nth_hierarchy;

  NT2_TEST_EXPR_TYPE( (nt2::tag::logspace_() )
                    , (nth_hierarchy<_,int_<0> >)
                    , (nt2::tag::logspace_)
                    );

  NT2_TEST_EXPR_TYPE( (nt2::tag::logspace_() )
                    , (nth_hierarchy<_,int_<1> >)
                    , (nt2::ext::state_constant_< nt2::tag::logspace_ >
                      )
                    );

  NT2_TEST_EXPR_TYPE( (nt2::tag::logspace_() )
                    , (nth_hierarchy<_,int_<2> >)
                    , (nt2::ext::constant_< nt2::tag::logspace_ >
                      )
                    );

  NT2_TEST_EXPR_TYPE( (nt2::tag::logspace_() )
                    , (nth_hierarchy<_,int_<3> >)
                    , (nt2::ext::elementwise_<nt2::tag::logspace_>)
                    );

  NT2_TEST_EXPR_TYPE( (nt2::tag::logspace_() )
                    , (nth_hierarchy<_,int_<4> >)
                    , (nt2::ext::unspecified_<nt2::tag::logspace_>)
                    );
}

NT2_TEST_CASE_TPL( logspace, NT2_REAL_TYPES )
{
  using nt2::meta::value_type_;

  nt2::table<T> ref = nt2::exp10(nt2::linspace(T(0),T(1),50));

  NT2_TEST_EXPR_TYPE( (nt2::logspace(T(0),T(1)))
                    , (value_type_<boost::mpl::_>)
                    , (T)
                    );

  nt2::table<T> x = nt2::logspace(T(0),T(1));
  NT2_TEST_EQUAL( x.extent(), nt2::of_size(1,50) );
  NT2_TEST_ULP_EQUAL( x, ref, 1 );

  ref = nt2::exp10(nt2::linspace(T(1),T(0),50));
  nt2::table<T> xr = nt2::logspace(T(1),T(0));
  NT2_TEST_EQUAL( xr.extent(), nt2::of_size(1,50) );
  NT2_TEST_ULP_EQUAL( xr, ref, 1 );
}

NT2_TEST_CASE_TPL( logspace_with_size, NT2_REAL_TYPES )
{
  using nt2::meta::value_type_;

  nt2::table<T> ref = nt2::exp10(nt2::linspace(T(0),T(1),7));

  NT2_TEST_EXPR_TYPE( (nt2::logspace(T(0),T(1),7))
                    , (value_type_<boost::mpl::_>)
                    , (T)
                    );

  nt2::table<T> x = nt2::logspace(T(0),T(1),7);
  NT2_TEST_EQUAL( x.extent(), nt2::of_size(1,7) );
  NT2_TEST_ULP_EQUAL( x, ref, 1 );

  ref = nt2::exp10(nt2::linspace(T(1),T(0),7));
  nt2::table<T> xr = nt2::logspace(T(1),T(0),7);
  NT2_TEST_EQUAL( xr.extent(), nt2::of_size(1,7) );
  NT2_TEST_ULP_EQUAL( xr, ref, 1 );
}

NT2_TEST_CASE_TPL( logspace_pi, NT2_REAL_TYPES )
{
  nt2::table<T> x = nt2::logspace(T(2),nt2::Pi<T>(),7);
  nt2::table<T> ref = nt2::exp10(nt2::linspace(T(2),nt2::Log10_pi<T>(), 7));

  NT2_TEST_EQUAL( x.extent(), nt2::of_size(1,7 ) );
  NT2_TEST_ULP_EQUAL( x, ref, 1 );

  nt2::table<T> xr = nt2::logspace(T(2),nt2::Pi<T>(),7, nt2::regular_);
  ref = nt2::exp10(nt2::linspace(T(2),nt2::Pi<T>(), 7));

  NT2_TEST_EQUAL( xr.extent(), nt2::of_size(1,7 ) );
  NT2_TEST_ULP_EQUAL( xr, ref, 1 );

  nt2::table<T> xd1 = nt2::logspace(T(2),nt2::Pi<T>(),1, nt2::regular_);
  nt2::table<T> xd2 = nt2::logspace(T(2),nt2::Pi<T>(),1);
  NT2_TEST_EQUAL( xd1.extent(), nt2::of_size(1,1 ) );
  NT2_TEST_EQUAL( xd2.extent(), nt2::of_size(1,1 ) );

  NT2_TEST_ULP_EQUAL( xd1(1), nt2::exp10(nt2::Pi<T>()), 1 );
  NT2_TEST_ULP_EQUAL( xd2(1), nt2::Pi<T>(), 1);
}
