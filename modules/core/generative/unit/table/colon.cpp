/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#define NT2_UNIT_MODULE "nt2::colon function"

#include <nt2/table.hpp>
#include <nt2/include/functions/size.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>
#include <nt2/core/container/colon/colon.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests.hpp>
#include <boost/dispatch/meta/nth_hierarchy.hpp>

NT2_TEST_CASE( hierarchy )
{
  using boost::mpl::_;
  using boost::mpl::int_;
  using boost::dispatch::meta::nth_hierarchy;

  NT2_TEST_EXPR_TYPE( (nt2::tag::colon_() )
                    , (nth_hierarchy<_,int_<0> >)
                    , (nt2::tag::colon_)
                    );

  NT2_TEST_EXPR_TYPE( (nt2::tag::colon_() )
                    , (nth_hierarchy<_,int_<1> >)
                    , (nt2::ext::state_constant_< nt2::tag::colon_ >
                      )
                    );

  NT2_TEST_EXPR_TYPE( (nt2::tag::colon_() )
                    , (nth_hierarchy<_,int_<2> >)
                    , (nt2::ext::constant_< nt2::tag::colon_ >
                      )
                    );

  NT2_TEST_EXPR_TYPE( (nt2::tag::colon_() )
                    , (nth_hierarchy<_,int_<3> >)
                    , (nt2::ext::elementwise_<nt2::tag::colon_>)
                    );

  NT2_TEST_EXPR_TYPE( (nt2::tag::colon_() )
                    , (nth_hierarchy<_,int_<4> >)
                    , (nt2::ext::unspecified_<nt2::tag::colon_>)
                    );
}

NT2_TEST_CASE_TPL( empty_colon, NT2_TYPES )
{
  using nt2::_;
  nt2::table<T> xr = _(T(9),T(0));
  NT2_TEST_EQUAL( xr.extent(), nt2::of_size(1,0 ) );

  nt2::table<int> xsr = _(boost::mpl::int_<9>(),boost::mpl::int_<0>());
  NT2_TEST_EQUAL( xsr.extent(), nt2::of_size(1,0 ) );
}

NT2_TEST_CASE_TPL( colon, NT2_TYPES )
{
  using nt2::_;
  using nt2::meta::value_type_;
  nt2::table<T> ref(nt2::of_size(1,10));
  for(int i=1;i<=10;++i)
    ref(i) = T(i-1);

  NT2_TEST_EXPR_TYPE( (_(T(0),T(9))), (value_type_<boost::mpl::_>), (T) );

  nt2::table<T> xd = _(T(0),T(9));
  NT2_TEST_EQUAL( xd.extent(), nt2::of_size(1,10 ) );
  NT2_TEST_EQUAL( xd, ref );
}

NT2_TEST_CASE_TPL( colon_integers_step, NT2_INTEGRAL_SIGNED_TYPES )
{
  using nt2::_;
  using nt2::meta::value_type_;
  nt2::table<T> ref(nt2::of_size(1,5));

  NT2_TEST_EXPR_TYPE( (_(T(0),T(2),T(9))), (value_type_<boost::mpl::_>), (T) );
  NT2_TEST_EXPR_TYPE( (_(T(0),T(-2),T(9))), (value_type_<boost::mpl::_>), (T) );

  for(int i=1;i<=5;++i)
    ref(i) = 2*T(i-1);

  nt2::table<T> xd = _(T(0),T(2),T(9));
  NT2_TEST_EQUAL( xd.extent(), nt2::of_size(1,5 ) );
  NT2_TEST_EQUAL( xd, ref );

  for(int i=1;i<=5;++i)
    ref(i) = T(9) -T(2)*T(i-1);

  nt2::table<T> yd = _(T(9),T(-2),T(1));
  NT2_TEST_EQUAL( yd.extent(), nt2::of_size(1,5 ) );
  NT2_TEST_EQUAL( yd, ref );
}

NT2_TEST_CASE_TPL( colon_unsigned_step, NT2_UNSIGNED_TYPES )
{
  using nt2::_;
  using nt2::meta::value_type_;
  nt2::table<T> ref(nt2::of_size(1,5));

  NT2_TEST_EXPR_TYPE( (_(T(0),T(2),T(9))), (value_type_<boost::mpl::_>), (T) );
  NT2_TEST_EXPR_TYPE( (_(T(9),T(2),T(1))), (value_type_<boost::mpl::_>), (T) );
  NT2_TEST_EXPR_TYPE( (_(T(5),T(0),T(9))), (value_type_<boost::mpl::_>), (T) );

  for(int i=1;i<=5;++i)
    ref(i) = 2*T(i-1);

  nt2::table<T> xd = _(T(0),T(2),T(9));
  NT2_TEST_EQUAL( xd.extent(), nt2::of_size(1,5 ) );
  NT2_TEST_EQUAL( xd, ref );

  for(int i=1;i<=5;++i)
    ref(i) = T(9) -T(2)*T(i-1);

  nt2::table<T> yd = _(T(9),T(-2),T(1));
  NT2_TEST_EQUAL( yd.extent(), nt2::of_size(1,0 ) );

  ref.resize( nt2::of_size(1,9 ) );
  for(int i=1;i<=9;++i)
    ref(i) = T(5);

  nt2::table<T> zd = _(T(5),T(0),T(9));

  NT2_TEST_EQUAL( zd.extent(), nt2::of_size(1,9 ) );
  NT2_TEST_EQUAL( zd, ref );
}

NT2_TEST_CASE_TPL( colon_real_step, NT2_REAL_TYPES )
{
  using nt2::_;
  using nt2::meta::value_type_;
  nt2::table<T> ref(nt2::of_size(1,4));

  NT2_TEST_EXPR_TYPE( (_(T(0),T(0.3),T(1))), (value_type_<boost::mpl::_>), (T) );
  NT2_TEST_EXPR_TYPE( (_(T(9),T(2),T(1))), (value_type_<boost::mpl::_>), (T) );
  NT2_TEST_EXPR_TYPE( (_(T(5),T(0),T(9))), (value_type_<boost::mpl::_>), (T) );

  for(int i=1;i<=4;++i) ref(i) = T(0) + T(0.3)*T(i-1);

  nt2::table<T> xd = _(T(0),T(0.3),T(1));
  NT2_TEST_EQUAL( xd.extent(), nt2::of_size(1,4) );
  NT2_TEST_ULP_EQUAL( xd, ref, 0.5 );

  for(int i=1;i<=4;++i) ref(i) = T(1) + T(-0.3)*T(i-1);

  nt2::table<T> yd = _(T(1),T(-0.3),T(0));
  NT2_TEST_EQUAL( yd.extent(), nt2::of_size(1,4) );
  NT2_TEST_ULP_EQUAL( yd, ref, 0.5 );

  ref.resize(nt2::of_size(1,6));
  for(int i=1;i<=6;++i) ref(i) = T(0.5);

  nt2::table<T> zd = _(T(0.5),T(0),T(6));
  NT2_TEST_EQUAL( zd.extent(), nt2::of_size(1,6) );
  NT2_TEST_ULP_EQUAL( zd, ref, 0.5 );
}
