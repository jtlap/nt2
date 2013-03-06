//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#define NT2_UNIT_MODULE "nt2::falses function"

#include <nt2/table.hpp>
#include <nt2/include/functions/size.hpp>
#include <nt2/include/functions/falses.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/basic.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>
#include <nt2/sdk/unit/tests/exceptions.hpp>
#include <boost/dispatch/meta/nth_hierarchy.hpp>

NT2_TEST_CASE( hierarchy )
{
  using boost::mpl::_;
  using boost::mpl::int_;
  using boost::dispatch::meta::nth_hierarchy;

  NT2_TEST_EXPR_TYPE( (nt2::tag::False() )
                    , (nth_hierarchy<_,int_<0> >)
                    , (nt2::tag::False)
                    );

  NT2_TEST_EXPR_TYPE( (nt2::tag::False() )
                    , (nth_hierarchy<_,int_<1> >)
                    , (nt2::ext::pure_constant_< nt2::tag::False >
                      )
                    );

  NT2_TEST_EXPR_TYPE( (nt2::tag::False() )
                    , (nth_hierarchy<_,int_<2> >)
                    , (nt2::ext::constant_< nt2::tag::False >
                      )
                    );

  NT2_TEST_EXPR_TYPE( (nt2::tag::False() )
                    , (nth_hierarchy<_,int_<3> >)
                    , (nt2::ext::elementwise_<nt2::tag::False>)
                    );

  NT2_TEST_EXPR_TYPE( (nt2::tag::False() )
                    , (nth_hierarchy<_,int_<4> >)
                    , (nt2::ext::unspecified_<nt2::tag::False>)
                    );
}

NT2_TEST_CASE_TPL( _0d_typed, NT2_TYPES )
{
  using boost::mpl::_;
  using nt2::meta::as_;
  using nt2::meta::value_type_;
  nt2::table< nt2::logical<T> > x1 = nt2::falses( as_< nt2::logical<T> >() );

  NT2_TEST_EXPR_TYPE( x1, (value_type_<_>), (nt2::logical<T>) );
  NT2_TEST_EQUAL( nt2::extent(x1), nt2::of_size(1) );
  NT2_TEST_EQUAL( x1(1), false );
}

NT2_TEST_CASE( untyped_square )
{
  using boost::mpl::_;
  using nt2::meta::value_type_;

  nt2::table< nt2::logical<double> > ref( nt2::of_size(3,3) );
  for(int i=1;i<= 3;++i)
    for(int j=1;j<= 3;++j)
      ref(i,j) = false;

  nt2::table< nt2::logical<double> > x0 = nt2::falses(3);

  NT2_TEST_EXPR_TYPE( (nt2::falses( 3 )), (value_type_<_>), (nt2::logical<double>) );
  NT2_TEST_EQUAL( nt2::extent(x0), nt2::of_size(3,3) );
  NT2_TEST_EQUAL( x0,ref );
}

NT2_TEST_CASE( nd_untyped )
{
  using boost::mpl::_;
  using nt2::meta::value_type_;

  nt2::table< nt2::logical<double> > ref( nt2::of_size(8,4) );
  for(int j=1;j<= 4;++j)
    for(int i=1;i<= 8;++i)
      ref(i,j) = false;

  nt2::table< nt2::logical<double> > x1 = nt2::falses(8, 4);

  NT2_TEST_EXPR_TYPE( (nt2::falses(8,4)), (value_type_<_>), (nt2::logical<double>) );
  NT2_TEST_EQUAL( nt2::extent(x1), nt2::of_size(8,4) );
  NT2_TEST_EQUAL(x1,ref);

  ref.resize( nt2::of_size(1,4) );
    for(int j=1;j<= 4;++j)
      ref(1,j) = false;

  nt2::table< nt2::logical<double> > x2 = nt2::falses(1, 4);
  NT2_TEST_EQUAL( nt2::extent(x2), nt2::of_size(1,4) );
  NT2_TEST_EQUAL(x2,ref);

  ref.resize( nt2::of_size(7,1) );
    for(int i=1;i<= 7;++i)
      ref(i,1) = false;

  nt2::table< nt2::logical<double> > x3 = nt2::falses(7,1);
  NT2_TEST_EQUAL( nt2::extent(x3), nt2::of_size(7,1) );
  NT2_TEST_EQUAL(x3,ref);
}

NT2_TEST_CASE_TPL( nd_typed, NT2_TYPES )
{
  using boost::mpl::_;
  using nt2::meta::as_;
  using nt2::meta::value_type_;

  nt2::table< nt2::logical<T> > ref( nt2::of_size(8,8) );
  for(int j=1;j<= 8;++j)
    for(int i=1;i<= 8;++i)
      ref(i,j) = false;

  nt2::table< nt2::logical<T> > x1 = nt2::falses(nt2::of_size(8, 8), as_< nt2::logical<T> >() );

  NT2_TEST_EXPR_TYPE( (nt2::falses( nt2::of_size(8, 8), as_< nt2::logical<T> >() )), (value_type_<_>), (nt2::logical<T>) );
  NT2_TEST_EQUAL(x1,ref);

  nt2::table< nt2::logical<T> > x2 = nt2::falses(8, 8, as_< nt2::logical<T> >() );
  NT2_TEST_EQUAL(x2,ref);

  nt2::table< nt2::logical<T> > x3 = nt2::falses(8, as_< nt2::logical<T> >() );
  NT2_TEST_EQUAL(x3,ref);
}

NT2_TEST_CASE( expr )
{
  using boost::mpl::_;
  using nt2::meta::value_type_;

  nt2::table< nt2::logical<double> > ref( nt2::of_size(8,8) );
  for(int j=1;j<= 8;++j)
    for(int i=1;i<= 8;++i)
      ref(i,j) = false;

  nt2::table<int> t1(nt2::of_size(1) );
  t1(1) = 8;

  nt2::table< nt2::logical<double> > x1 = nt2::falses( t1 );

  NT2_TEST_EXPR_TYPE( (nt2::falses( t1 )), (value_type_<_>), (nt2::logical<double>) );
  NT2_TEST_EQUAL(x1,ref);

  nt2::table<int> t2(nt2::of_size(1,2) );
  t2(1) = 4;
  t2(2) = 3;

  ref.resize( nt2::of_size(4,3) );
  for(int j=1;j<= 3;++j)
    for(int i=1;i<= 4;++i)
      ref(i,j) = false;

  nt2::table< nt2::logical<double> > x2 = nt2::falses( t2 );
  NT2_TEST_EQUAL(x2,ref);

  NT2_TEST_ASSERT( x1 = nt2::falses(x2) );
}

NT2_TEST_CASE_TPL( typed_expr, NT2_TYPES )
{
  using boost::mpl::_;
  using nt2::meta::as_;
  using nt2::meta::value_type_;

  nt2::table< nt2::logical<T> > ref( nt2::of_size(8,8) );
  for(int j=1;j<= 8;++j)
    for(int i=1;i<= 8;++i)
      ref(i,j) = false;

  nt2::table<int> t1(nt2::of_size(1) );
  t1(1) = 8;

  nt2::table< nt2::logical<T> > x1 = nt2::falses( t1, as_< nt2::logical<T> >() );

  NT2_TEST_EXPR_TYPE( (nt2::falses( t1, as_< nt2::logical<T> >() )), (value_type_<_>), (nt2::logical<T>) );
  NT2_TEST_EQUAL(x1,ref);

  nt2::table<int> t2(nt2::of_size(1,2) );
  t2(1) = 4;
  t2(2) = 3;

  ref.resize( nt2::of_size(4,3) );
  for(int j=1;j<= 3;++j)
    for(int i=1;i<= 4;++i)
      ref(i,j) = false;

  nt2::table< nt2::logical<T> > x2 = nt2::falses( t2, as_< nt2::logical<T> >() );
  NT2_TEST_EQUAL(x2,ref);

  NT2_TEST_ASSERT( x1 = nt2::falses(x2, as_< nt2::logical<T> >()) );
}
