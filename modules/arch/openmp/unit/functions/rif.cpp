/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#define NT2_UNIT_MODULE "nt2::rif function"

#include <nt2/table.hpp>
#include <nt2/include/functions/rif.hpp>
#include <nt2/include/functions/size.hpp>

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

  NT2_TEST_EXPR_TYPE( (nt2::tag::rif_() )
                    , (nth_hierarchy<_,int_<0> >)
                    , (nt2::tag::rif_)
                    );

  NT2_TEST_EXPR_TYPE( (nt2::tag::rif_() )
                    , (nth_hierarchy<_,int_<1> >)
                    , (nt2::ext::pure_constant_< nt2::tag::rif_ >
                      )
                    );

  NT2_TEST_EXPR_TYPE( (nt2::tag::rif_() )
                    , (nth_hierarchy<_,int_<2> >)
                    , (nt2::ext::constant_< nt2::tag::rif_ >
                      )
                    );

  NT2_TEST_EXPR_TYPE( (nt2::tag::rif_() )
                    , (nth_hierarchy<_,int_<3> >)
                    , (nt2::ext::elementwise_<nt2::tag::rif_>)
                    );

  NT2_TEST_EXPR_TYPE( (nt2::tag::rif_() )
                    , (nth_hierarchy<_,int_<4> >)
                    , (nt2::ext::unspecified_<nt2::tag::rif_>)
                    );
}

NT2_TEST_CASE_TPL( _0d_typed, NT2_TYPES )
{
  using boost::mpl::_;
  using nt2::meta::as_;
  using nt2::meta::value_type_;
  nt2::table<T> x1 = nt2::rif( as_<T>() );

  NT2_TEST_EXPR_TYPE( (nt2::rif( as_<T>() )), (value_type_<_>), (T) );
  NT2_TEST_EQUAL( nt2::extent(x1), nt2::of_size(1) );
  NT2_TEST_EQUAL( x1(1), T(1) );
}

NT2_TEST_CASE( untyped_square )
{
  using boost::mpl::_;
  using nt2::meta::value_type_;

  nt2::table<double> ref( nt2::of_size(3,3) );
  for(int i=1;i<= 3;++i)
    for(int j=1;j<= 3;++j)
      ref(i,j) = i;

  nt2::table<double> x0 = nt2::rif(3);

  NT2_TEST_EXPR_TYPE( (nt2::rif( 3 )), (value_type_<_>), (double) );
  NT2_TEST_EQUAL( nt2::extent(x0), nt2::of_size(3,3) );
  NT2_TEST_EQUAL( x0,ref );
}

NT2_TEST_CASE( nd_untyped )
{
  using boost::mpl::_;
  using nt2::meta::value_type_;

  nt2::table<double> ref( nt2::of_size(8,4) );
  for(int j=1;j<= 4;++j)
    for(int i=1;i<= 8;++i)
      ref(i,j) = i;

  nt2::table<double> x1 = nt2::rif(8, 4);

  NT2_TEST_EXPR_TYPE( (nt2::rif(8,4)), (value_type_<_>), (double) );
  NT2_TEST_EQUAL( nt2::extent(x1), nt2::of_size(8,4) );
  NT2_TEST_EQUAL(x1,ref);

  ref.resize( nt2::of_size(1,4) );
    for(int j=1;j<= 4;++j)
      ref(1,j) = 1;

  nt2::table<double> x2 = nt2::rif(1, 4);
  NT2_TEST_EQUAL( nt2::extent(x2), nt2::of_size(1,4) );
  NT2_TEST_EQUAL(x2,ref);

  ref.resize( nt2::of_size(7,1) );
    for(int i=1;i<= 7;++i)
      ref(i,1) = i;

  nt2::table<double> x3 = nt2::rif(7,1);
  NT2_TEST_EQUAL( nt2::extent(x3), nt2::of_size(7,1) );
  NT2_TEST_EQUAL(x3,ref);
}

NT2_TEST_CASE_TPL( nd_typed, NT2_TYPES )
{
  using boost::mpl::_;
  using nt2::meta::as_;
  using nt2::meta::value_type_;

  nt2::table<T> ref( nt2::of_size(8,8) );
  for(int j=1;j<= 8;++j)
    for(int i=1;i<= 8;++i)
      ref(i,j) = i;

  nt2::table<T> x1 = nt2::rif(nt2::of_size(8, 8), as_<T>() );

  NT2_TEST_EXPR_TYPE( (nt2::rif( nt2::of_size(8, 8), as_<T>() )), (value_type_<_>), (T) );
  NT2_TEST_EQUAL(x1,ref);

  nt2::table<T> x2 = nt2::rif(8, 8, as_<T>() );
  NT2_TEST_EQUAL(x2,ref);

  nt2::table<T> x3 = nt2::rif(8, as_<T>() );
  NT2_TEST_EQUAL(x3,ref);
}

NT2_TEST_CASE( expr )
{
  using boost::mpl::_;
  using nt2::meta::value_type_;

  nt2::table<double> ref( nt2::of_size(8,8) );
  for(int j=1;j<= 8;++j)
    for(int i=1;i<= 8;++i)
      ref(i,j) = i;

  nt2::table<int> t1(nt2::of_size(1) );
  t1(1) = 8;

  nt2::table<double> x1 = nt2::rif( t1 );

  NT2_TEST_EXPR_TYPE( (nt2::rif( t1 )), (value_type_<_>), (double) );
  NT2_TEST_EQUAL(x1,ref);

  nt2::table<int> t2(nt2::of_size(1,2) );
  t2(1) = 4;
  t2(2) = 3;

  ref.resize( nt2::of_size(4,3) );
  for(int j=1;j<= 3;++j)
    for(int i=1;i<= 4;++i)
      ref(i,j) = i;

  nt2::table<double> x2 = nt2::rif( t2 );
  NT2_TEST_EQUAL(x2,ref);

  NT2_TEST_ASSERT( x1 = nt2::rif(x2) );
}

NT2_TEST_CASE_TPL( typed_expr, NT2_TYPES )
{
  using boost::mpl::_;
  using nt2::meta::as_;
  using nt2::meta::value_type_;

  nt2::table<T> ref( nt2::of_size(8,8) );
  for(int j=1;j<= 8;++j)
    for(int i=1;i<= 8;++i)
      ref(i,j) = i;

  nt2::table<int> t1(nt2::of_size(1) );
  t1(1) = 8;

  nt2::table<T> x1 = nt2::rif( t1, as_<T>() );

  NT2_TEST_EXPR_TYPE( (nt2::rif( t1, as_<T>() )), (value_type_<_>), (T) );
  NT2_TEST_EQUAL(x1,ref);

  nt2::table<int> t2(nt2::of_size(1,2) );
  t2(1) = 4;
  t2(2) = 3;

  ref.resize( nt2::of_size(4,3) );
  for(int j=1;j<= 3;++j)
    for(int i=1;i<= 4;++i)
      ref(i,j) = i;

  nt2::table<T> x2 = nt2::rif( t2, as_<T>() );
  NT2_TEST_EQUAL(x2,ref);

  NT2_TEST_ASSERT( x1 = nt2::rif(x2, as_<T>()) );
}
