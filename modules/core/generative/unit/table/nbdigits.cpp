//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012 - 2013   MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/table.hpp>
#include <nt2/include/functions/size.hpp>
#include <nt2/include/functions/nbdigits.hpp>

#include <nt2/include/constants/nbdigits.hpp>

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

  NT2_TEST_EXPR_TYPE( (nt2::tag::Nbdigits() )
                    , (nth_hierarchy<_,int_<0> >)
                    , (nt2::tag::Nbdigits)
                    );

  NT2_TEST_EXPR_TYPE( (nt2::tag::Nbdigits() )
                    , (nth_hierarchy<_,int_<1> >)
                    , (nt2::ext::pure_constant_< nt2::tag::Nbdigits >
                      )
                    );

  NT2_TEST_EXPR_TYPE( (nt2::tag::Nbdigits() )
                    , (nth_hierarchy<_,int_<2> >)
                    , (nt2::ext::constant_< nt2::tag::Nbdigits >
                      )
                    );

  NT2_TEST_EXPR_TYPE( (nt2::tag::Nbdigits() )
                    , (nth_hierarchy<_,int_<3> >)
                    , (nt2::ext::elementwise_<nt2::tag::Nbdigits>)
                    );

  NT2_TEST_EXPR_TYPE( (nt2::tag::Nbdigits() )
                    , (nth_hierarchy<_,int_<4> >)
                    , (nt2::ext::unspecified_<nt2::tag::Nbdigits>)
                    );
}

NT2_TEST_CASE_TPL( _0d_typed, NT2_TYPES )
{
  using boost::mpl::_;
  using nt2::meta::as_;
  using nt2::meta::value_type_;

  typedef typename boost::dispatch::meta::as_integer<T>::type type;

  nt2::table< type > x1 = nt2::nbdigits( as_< T >() );

  NT2_TEST_EXPR_TYPE( x1, (value_type_<_>), (type) );
  NT2_TEST_EQUAL( nt2::extent(x1), nt2::of_size(1) );
  NT2_TEST_EQUAL( x1(1), nt2::Nbdigits<T>() );
}

NT2_TEST_CASE( untyped_square )
{
  using boost::mpl::_;
  using nt2::meta::value_type_;

  typedef boost::dispatch::meta::as_integer<double>::type type;

  nt2::table< type > ref( nt2::of_size(3,3) );
  for(int i=1;i<= 3;++i)
   for(int j=1;j<= 3;++j)
      ref(i,j) = nt2::Nbdigits<double>();

  nt2::table< type > x0 = nt2::nbdigits(3);

  NT2_TEST_EXPR_TYPE( (nt2::nbdigits( 3 )), (value_type_<_>), (type) );
  NT2_TEST_EQUAL( nt2::extent(x0), nt2::of_size(3,3) );
  NT2_TEST_EQUAL( x0,ref );
}

NT2_TEST_CASE( nd_untyped )
{
  using boost::mpl::_;
  using nt2::meta::value_type_;

  typedef boost::dispatch::meta::as_integer<double>::type type;

  nt2::table< type > ref( nt2::of_size(8,4) );
  for(int j=1;j<= 4;++j)
    for(int i=1;i<= 8;++i)
      ref(i,j) = nt2::Nbdigits<double>();

  nt2::table< type > x1 = nt2::nbdigits(8, 4);

  NT2_TEST_EXPR_TYPE( (nt2::nbdigits(8,4)), (value_type_<_>), (type) );
  NT2_TEST_EQUAL( nt2::extent(x1), nt2::of_size(8,4) );
  NT2_TEST_EQUAL(x1,ref);

  ref.resize( nt2::of_size(1,4) );
    for(int j=1;j<= 4;++j)
      ref(1,j) = nt2::Nbdigits<double>();

  nt2::table< type > x2 = nt2::nbdigits(1, 4);
  NT2_TEST_EQUAL( nt2::extent(x2), nt2::of_size(1,4) );
  NT2_TEST_EQUAL(x2,ref);

  ref.resize( nt2::of_size(7,1) );
    for(int i=1;i<= 7;++i)
      ref(i,1) = nt2::Nbdigits<double>();

  nt2::table< type > x3 = nt2::nbdigits(7,1);
  NT2_TEST_EQUAL( nt2::extent(x3), nt2::of_size(7,1) );
  NT2_TEST_EQUAL(x3,ref);
}

NT2_TEST_CASE_TPL( nd_typed, NT2_TYPES )
{
  using boost::mpl::_;
  using nt2::meta::as_;
  using nt2::meta::value_type_;

  typedef typename boost::dispatch::meta::as_integer<T>::type type;

  nt2::table< type > ref( nt2::of_size(8,8) );
  for(int j=1;j<= 8;++j)
    for(int i=1;i<= 8;++i)
      ref(i,j) = nt2::Nbdigits<T>();

  nt2::table< type > x1 = nt2::nbdigits(nt2::of_size(8, 8), as_< T >() );

  NT2_TEST_EXPR_TYPE( (nt2::nbdigits( nt2::of_size(8, 8), as_< T >() ))
                    , (value_type_<_>)
                    , (type)
                    );

  NT2_TEST_EQUAL(x1,ref);

  nt2::table< type > x2 = nt2::nbdigits(8, 8, as_< T >() );
  NT2_TEST_EQUAL(x2,ref);

  nt2::table< type > x3 = nt2::nbdigits(8, as_< T >() );
  NT2_TEST_EQUAL(x3,ref);
}

NT2_TEST_CASE( expr )
{
  using boost::mpl::_;
  using nt2::meta::value_type_;

  typedef boost::dispatch::meta::as_integer<double>::type type;

  nt2::table< type > ref( nt2::of_size(8,8) );
  for(int j=1;j<= 8;++j)
    for(int i=1;i<= 8;++i)
      ref(i,j) = nt2::Nbdigits<double>();

  nt2::table<int> t1(nt2::of_size(1) );
  t1(1) = 8;

  nt2::table< type > x1 = nt2::nbdigits( t1 );

  NT2_TEST_EXPR_TYPE( (nt2::nbdigits( t1 )), (value_type_<_>), (type) );
  NT2_TEST_EQUAL(x1,ref);

  nt2::table<int> t2(nt2::of_size(1,2) );
  t2(1) = 4;
  t2(2) = 3;

  ref.resize( nt2::of_size(4,3) );
  for(int j=1;j<= 3;++j)
    for(int i=1;i<= 4;++i)
      ref(i,j) = nt2::Nbdigits<double>();

  nt2::table< type > x2 = nt2::nbdigits( t2 );
  NT2_TEST_EQUAL(x2,ref);

  NT2_TEST_ASSERT( x1 = nt2::nbdigits(x2) );
}

NT2_TEST_CASE_TPL( typed_expr, NT2_TYPES )
{
  using boost::mpl::_;
  using nt2::meta::as_;
  using nt2::meta::value_type_;

  typedef typename boost::dispatch::meta::as_integer<T>::type type;

  nt2::table< type > ref( nt2::of_size(8,8) );
  for(int j=1;j<= 8;++j)
    for(int i=1;i<= 8;++i)
      ref(i,j) = nt2::Nbdigits<T>();

  nt2::table<int> t1(nt2::of_size(1) );
  t1(1) = 8;

  nt2::table< type > x1 = nt2::nbdigits( t1, as_< T >() );

  NT2_TEST_EXPR_TYPE( (nt2::nbdigits( t1, as_< T >() )), (value_type_<_>), (type) );
  NT2_TEST_EQUAL(x1,ref);

  nt2::table<int> t2(nt2::of_size(1,2) );
  t2(1) = 4;
  t2(2) = 3;

  ref.resize( nt2::of_size(4,3) );
  for(int j=1;j<= 3;++j)
    for(int i=1;i<= 4;++i)
      ref(i,j) = nt2::Nbdigits<T>();

  nt2::table< type > x2 = nt2::nbdigits( t2, as_< T >() );
  NT2_TEST_EQUAL(x2,ref);

  NT2_TEST_ASSERT( x1 = nt2::nbdigits(x2, as_< T >()) );
}
