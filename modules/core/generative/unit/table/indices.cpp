//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#define NT2_UNIT_MODULE "nt2::indices function"

#include <nt2/table.hpp>
#include <nt2/options.hpp>
#include <nt2/include/functions/size.hpp>
#include <nt2/include/functions/indices.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/basic.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>
#include <boost/dispatch/meta/nth_hierarchy.hpp>

NT2_TEST_CASE( hierarchy )
{
  using boost::mpl::_;
  using boost::mpl::int_;
  using boost::dispatch::meta::nth_hierarchy;

  NT2_TEST_EXPR_TYPE( (nt2::tag::indices_() )
                    , (nth_hierarchy<_,int_<0> >)
                    , (nt2::tag::indices_)
                    );

  NT2_TEST_EXPR_TYPE( (nt2::tag::indices_() )
                    , (nth_hierarchy<_,int_<1> >)
                    , (nt2::ext::state_constant_< nt2::tag::indices_ >
                      )
                    );

  NT2_TEST_EXPR_TYPE( (nt2::tag::indices_() )
                    , (nth_hierarchy<_,int_<2> >)
                    , (nt2::ext::constant_< nt2::tag::indices_ >
                      )
                    );

  NT2_TEST_EXPR_TYPE( (nt2::tag::indices_() )
                    , (nth_hierarchy<_,int_<3> >)
                    , (nt2::ext::elementwise_<nt2::tag::indices_>)
                    );

  NT2_TEST_EXPR_TYPE( (nt2::tag::indices_() )
                    , (nth_hierarchy<_,int_<4> >)
                    , (nt2::ext::unspecified_<nt2::tag::indices_>)
                    );
}

NT2_TEST_CASE( _0d )
{
  using boost::mpl::_;
  using nt2::meta::value_type_;

  nt2::table<double> x1 = nt2::indices( nt2::over(1,-1) );
  NT2_TEST_EXPR_TYPE((nt2::indices(nt2::over(1,-1))),(value_type_<_>),(double));
  NT2_TEST_EQUAL( nt2::extent(x1), nt2::of_size(1) );
  NT2_TEST_EQUAL( x1(1),-1. );
}

NT2_TEST_CASE_TPL( _0d_typed, NT2_TYPES )
{
  using boost::mpl::_;
  using nt2::meta::as_;
  using nt2::meta::value_type_;

  nt2::table<T> x1 = nt2::indices( nt2::over(1,7), as_<T>() );
  NT2_TEST_EXPR_TYPE( (nt2::indices(nt2::over(1,7), as_<T>()))
                    , (value_type_<_>)
                    , (T)
                    );

  NT2_TEST_EQUAL( nt2::extent(x1), nt2::of_size(1) );
  NT2_TEST_EQUAL( x1(1),T(7) );
}

NT2_TEST_CASE_TPL( square, NT2_TYPES )
{
  using boost::mpl::_;
  using nt2::meta::as_;
  using nt2::meta::value_type_;

  NT2_TEST_EXPR_TYPE( (nt2::indices(3, nt2::over(1,1), as_<T>()))
                    , (value_type_<_>)
                    , (T)
                    );

  nt2::table<T> ref( nt2::of_size(3,3) );
  for(int j=1;j<= 3;++j)
    for(int i=1;i<= 3;++i)
      ref(i,j) = i;

  nt2::table<T> x0 = nt2::indices(3, nt2::over(1,1), as_<T>());
  NT2_TEST_EQUAL( nt2::extent(x0), nt2::of_size(3,3) );
  NT2_TEST_EQUAL( x0,ref );

  for(int j=1;j<= 3;++j)
    for(int i=1;i<= 3;++i)
      ref(i,j) = j;
}

NT2_TEST_CASE_TPL( nd, NT2_TYPES )
{
  using boost::mpl::_;
  using nt2::meta::value_type_;

  NT2_TEST_EXPR_TYPE( (nt2::indices(3,4, nt2::over(1,1)))
                    , (value_type_<_>)
                    , (double)
                    );

  nt2::table<double> ref( nt2::of_size(3,4) );
  for(int j=1;j<= 4;++j)
    for(int i=1;i<= 3;++i)
      ref(i,j) = i;

  nt2::table<double> x0 = nt2::indices(3,4, nt2::over(1,1));
  NT2_TEST_EQUAL( nt2::extent(x0), nt2::of_size(3,4) );
  NT2_TEST_EQUAL( x0,ref );

  nt2::table<double> x0f = nt2::indices( nt2::of_size(3,4), nt2::over(1,1));
  NT2_TEST_EQUAL( nt2::extent(x0f), nt2::of_size(3,4) );
  NT2_TEST_EQUAL( x0f,ref );

  for(int j=1;j<= 4;++j)
    for(int i=1;i<= 3;++i)
      ref(i,j) = j;

  nt2::table<double> x1 = nt2::indices(3,4, nt2::over(2,1));
  NT2_TEST_EQUAL( nt2::extent(x1), nt2::of_size(3,4) );
  NT2_TEST_EQUAL( x1,ref );

  nt2::table<double> x1f = nt2::indices( nt2::of_size(3,4), nt2::over(2,1));
  NT2_TEST_EQUAL( nt2::extent(x1f), nt2::of_size(3,4) );
  NT2_TEST_EQUAL( x1f,ref );

  ref.resize( nt2::of_size(3,3,3) );
  for(int k=1;k<= 3;++k)
    for(int j=1;j<= 3;++j)
      for(int i=1;i<= 3;++i)
        ref(i,j,k) = k;

  nt2::table<double> x2 = nt2::indices(3, 3,3, nt2::over(3,1));
  NT2_TEST_EQUAL( nt2::extent(x2), nt2::of_size(3,3,3) );
  NT2_TEST_EQUAL( x2,ref );

  nt2::table<double> x2f = nt2::indices( nt2::of_size(3,3,3), nt2::over(3,1));
  NT2_TEST_EQUAL( nt2::extent(x2f), nt2::of_size(3,3,3) );
  NT2_TEST_EQUAL( x2f,ref );

  ref.resize( nt2::of_size(3,3,3,3) );
  for(int l=1;l<= 3;++l)
    for(int k=1;k<= 3;++k)
      for(int j=1;j<= 3;++j)
        for(int i=1;i<= 3;++i)
          ref(i,j,k,l) = l;

  nt2::table<double> x3 = nt2::indices(3,3,3,3, nt2::over(4,1));
  NT2_TEST_EQUAL( nt2::extent(x3), nt2::of_size(3,3,3,3) );
  NT2_TEST_EQUAL( x3,ref );

  nt2::table<double> x3f = nt2::indices( nt2::of_size(3,3,3,3), nt2::over(4,1));
  NT2_TEST_EQUAL( nt2::extent(x3f), nt2::of_size(3,3,3,3) );
  NT2_TEST_EQUAL( x3f,ref );
}

NT2_TEST_CASE_TPL( nd_typed, NT2_TYPES )
{
  using boost::mpl::_;
  using nt2::meta::as_;
  using nt2::meta::value_type_;

  NT2_TEST_EXPR_TYPE( (nt2::indices(3,4, nt2::over(1,1), as_<T>()))
                    , (value_type_<_>)
                    , (T)
                    );

  nt2::table<T> ref( nt2::of_size(3,4) );
  for(int j=1;j<= 4;++j)
    for(int i=1;i<= 3;++i)
      ref(i,j) = i;

  nt2::table<T> x0 = nt2::indices(3,4, nt2::over(1,1), as_<T>());
  NT2_TEST_EQUAL( nt2::extent(x0), nt2::of_size(3,4) );
  NT2_TEST_EQUAL( x0,ref );

  nt2::table<T> x0f = nt2::indices( nt2::of_size(3,4), nt2::over(1,1), as_<T>());
  NT2_TEST_EQUAL( nt2::extent(x0f), nt2::of_size(3,4) );
  NT2_TEST_EQUAL( x0f,ref );

  for(int j=1;j<= 4;++j)
    for(int i=1;i<= 3;++i)
      ref(i,j) = j;

  nt2::table<T> x1 = nt2::indices(3,4, nt2::over(2,1), as_<T>());
  NT2_TEST_EQUAL( nt2::extent(x1), nt2::of_size(3,4) );
  NT2_TEST_EQUAL( x1,ref );

  nt2::table<T> x1f = nt2::indices( nt2::of_size(3,4), nt2::over(2,1), as_<T>());
  NT2_TEST_EQUAL( nt2::extent(x1f), nt2::of_size(3,4) );
  NT2_TEST_EQUAL( x1f,ref );

  ref.resize( nt2::of_size(3,3,3) );
  for(int k=1;k<= 3;++k)
    for(int j=1;j<= 3;++j)
      for(int i=1;i<= 3;++i)
        ref(i,j,k) = k;

  nt2::table<T> x2 = nt2::indices(3, 3,3, nt2::over(3,1), as_<T>());
  NT2_TEST_EQUAL( nt2::extent(x2), nt2::of_size(3,3,3) );
  NT2_TEST_EQUAL( x2,ref );

  nt2::table<T> x2f = nt2::indices( nt2::of_size(3,3,3), nt2::over(3,1), as_<T>());
  NT2_TEST_EQUAL( nt2::extent(x2f), nt2::of_size(3,3,3) );
  NT2_TEST_EQUAL( x2f,ref );

  ref.resize( nt2::of_size(3,3,3,3) );
  for(int l=1;l<= 3;++l)
    for(int k=1;k<= 3;++k)
      for(int j=1;j<= 3;++j)
        for(int i=1;i<= 3;++i)
          ref(i,j,k,l) = l;

  nt2::table<T> x3 = nt2::indices(3,3,3,3, nt2::over(4,1), as_<T>());
  NT2_TEST_EQUAL( nt2::extent(x3), nt2::of_size(3,3,3,3) );
  NT2_TEST_EQUAL( x3,ref );

  nt2::table<T> x3f = nt2::indices( nt2::of_size(3,3,3,3), nt2::over(4,1), as_<T>());
  NT2_TEST_EQUAL( nt2::extent(x3f), nt2::of_size(3,3,3,3) );
  NT2_TEST_EQUAL( x3f,ref );
}
