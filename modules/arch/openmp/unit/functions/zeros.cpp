/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#define NT2_UNIT_MODULE "nt2::zeros function"

#include <cstdio>
#include <nt2/table.hpp>
#include <nt2/include/functions/size.hpp>
#include <nt2/include/functions/zeros.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/basic.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>
#include <nt2/sdk/unit/tests/exceptions.hpp>

template<class T, int N> struct hierarchy_impl
{
  typedef typename hierarchy_impl<T,N-1>::type base;
  typedef typename base::parent           type;
};

template<class T> struct hierarchy_impl<T,0>
{
  typedef typename nt2::meta::hierarchy_of<T>::type type;
};

template<class T, class N>
struct hierarchy : hierarchy_impl<T,N::value>
{};

NT2_TEST_CASE( zeros_hierarchy )
{
  using boost::mpl::_;
  using boost::mpl::int_;

  NT2_TEST_EXPR_TYPE( (nt2::tag::zeros_() )
                    , (hierarchy<_,int_<0> >)
                    , (nt2::tag::zeros_)
                    );

  NT2_TEST_EXPR_TYPE( (nt2::tag::zeros_() )
                    , (hierarchy<_,int_<1> >)
                    , (nt2::ext::generative_< nt2::tag::zeros_>
                      )
                    );

  NT2_TEST_EXPR_TYPE( (nt2::tag::zeros_() )
                    , (hierarchy<_,int_<2> >)
                    , (nt2::ext::elementwise_<nt2::tag::zeros_>)
                    );

  NT2_TEST_EXPR_TYPE( (nt2::tag::zeros_() )
                    , (hierarchy<_,int_<3> >)
                    , (nt2::ext::unspecified_<nt2::tag::zeros_>)
                    );
}

NT2_TEST_CASE_TPL( zeros_value_type, NT2_TYPES )
{
  using boost::mpl::_;
  using nt2::meta::value_type_;

  NT2_TEST_EXPR_TYPE( (nt2::zeros(nt2::of_size(4,4)))
                    , (value_type_<_>)
                    , (double)
                    );

  NT2_TEST_EXPR_TYPE( (nt2::zeros(nt2::of_size(4,4),nt2::meta::as_<T>()))
                    , (value_type_<_>)
                    , (T)
                    );
}

NT2_TEST_CASE( zeros_size )
{
  NT2_TEST( nt2::extent( nt2::zeros(nt2::of_size(4,5)) ) == nt2::of_size(4,5) );
  NT2_TEST_EQUAL( nt2::size( nt2::zeros(nt2::of_size(4,5)), 1 ), 4u );
  NT2_TEST_EQUAL( nt2::size( nt2::zeros(nt2::of_size(4,5)), 2 ), 5u );

  NT2_TEST( nt2::extent( nt2::zeros(nt2::of_size(4,5,6)) ) == nt2::of_size(4,5,6) );
  NT2_TEST_EQUAL( nt2::size( nt2::zeros(nt2::of_size(4,5,6)), 1 ), 4u );
  NT2_TEST_EQUAL( nt2::size( nt2::zeros(nt2::of_size(4,5,6)), 2 ), 5u );
  NT2_TEST_EQUAL( nt2::size( nt2::zeros(nt2::of_size(4,5,6)), 3 ), 6u );

  NT2_TEST( nt2::extent( nt2::zeros(nt2::of_size(4,5,6,7)) ) == nt2::of_size(4,5,6,7) );
  NT2_TEST_EQUAL( nt2::size( nt2::zeros(nt2::of_size(4,5,6,7)), 1 ), 4u );
  NT2_TEST_EQUAL( nt2::size( nt2::zeros(nt2::of_size(4,5,6,7)), 2 ), 5u );
  NT2_TEST_EQUAL( nt2::size( nt2::zeros(nt2::of_size(4,5,6,7)), 3 ), 6u );
  NT2_TEST_EQUAL( nt2::size( nt2::zeros(nt2::of_size(4,5,6,7)), 4 ), 7u );
}

NT2_TEST_CASE( zeros_nd_untyped )
{
  nt2::table<double> x1 = nt2::zeros(8);
  for(int i=1;i<=64;++i) NT2_TEST_EQUAL( double(0), boost::proto::value(x1)[i-1] );

  nt2::table<double> x2 = nt2::zeros(8,8);
  for(int i=1;i<=64;++i) NT2_TEST_EQUAL( double(0), boost::proto::value(x2)[i-1] );

  nt2::table<double> x3 = nt2::zeros(8,4,2);
  for(int i=1;i<=64;++i) NT2_TEST_EQUAL( double(0), boost::proto::value(x3)[i-1] );

  nt2::table<double> x4 = nt2::zeros(4,4,2,2);
  for(int i=1;i<=64;++i) NT2_TEST_EQUAL( double(0), boost::proto::value(x4)[i-1] );
}

NT2_TEST_CASE_TPL( zeros_nd_typed, NT2_TYPES )
{
  nt2::table<T> x1 = nt2::zeros(8, nt2::meta::as_<T>() );
  for(int i=1;i<=64;++i) NT2_TEST_EQUAL( double(0), double(x1(i)) );

  nt2::table<T> x2 = nt2::zeros(8,8, nt2::meta::as_<T>() );
  for(int i=1;i<=64;++i) NT2_TEST_EQUAL( T(0), T(x2(i)) );

  nt2::table<T> x3 = nt2::zeros(8,4,2, nt2::meta::as_<T>() );
  for(int i=1;i<=64;++i) NT2_TEST_EQUAL( T(0), T(x3(i)) );

  nt2::table<T> x4 = nt2::zeros(4,4,2,2, nt2::meta::as_<T>() );
  for(int i=1;i<=64;++i) NT2_TEST_EQUAL( T(0), T(x1(i)) );
}

NT2_TEST_CASE( zeros_of_size )
{
  nt2::table<double> x2 = nt2::zeros(nt2::of_size(8,8) );
  for(int i=1;i<=64;++i) NT2_TEST_EQUAL( double(0), double(x2(i)) );

  nt2::table<double> x3 = nt2::zeros(nt2::of_size(8,4,2) );
  for(int i=1;i<=64;++i) NT2_TEST_EQUAL( double(0), double(x3(i)) );

  nt2::table<double> x4 = nt2::zeros(nt2::of_size(4,4,2,2) );
  for(int i=1;i<=64;++i) NT2_TEST_EQUAL( double(0), double(x4(i)) );
}

NT2_TEST_CASE_TPL( zeros_typed_of_size, NT2_TYPES )
{
  nt2::table<T> x2 = nt2::zeros(nt2::of_size(8,8), nt2::meta::as_<T>() );
  for(int i=1;i<=64;++i) NT2_TEST_EQUAL( T(0), T(x2(i)) );

  nt2::table<T> x3 = nt2::zeros(nt2::of_size(8,4,2), nt2::meta::as_<T>() );
  for(int i=1;i<=64;++i) NT2_TEST_EQUAL( T(0), T(x3(i)) );

  nt2::table<T> x4 = nt2::zeros(nt2::of_size(4,4,2,2), nt2::meta::as_<T>() );
  for(int i=1;i<=64;++i) NT2_TEST_EQUAL( T(0), T(x4(i)) );
}

NT2_TEST_CASE( zeros_expr )
{
  nt2::table<int> a( nt2::of_size(4,5) );

  nt2::table<double> x1 = nt2::zeros( nt2::size(a) );
  for(int i=1;i<=20;++i) NT2_TEST_EQUAL( double(0), double(x1(i)) );

  NT2_TEST_ASSERT( x1 = nt2::zeros(a) );
}

NT2_TEST_CASE_TPL( zeros_typed_expr, NT2_TYPES )
{
  nt2::table<int> a( nt2::of_size(4,5) );

  nt2::table<T> x1 = nt2::zeros( nt2::size(a), nt2::meta::as_<T>() );
  for(int i=1;i<=20;++i) NT2_TEST_EQUAL( T(0), T(x1(i)));

  NT2_TEST_ASSERT( x1 = nt2::zeros(a, nt2::meta::as_<T>()) );
}
