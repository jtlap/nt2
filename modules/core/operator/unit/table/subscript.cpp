/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#define NT2_UNIT_MODULE "nt2 container subscript"

#include <nt2/table.hpp>
#include <nt2/include/functions/extent.hpp>
#include <nt2/include/functions/of_size.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/basic.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>

template<class T>
struct size_of
{
  typedef typename nt2::meta::settings_of<T>::type settings;
  typedef typename nt2::meta::option<settings, nt2::tag::of_size_>::type type;
};

template<class T>
void vectorizable_0(T const&)
{
  typedef typename boost::proto::result_of::child_c<T, 1>::value_type aggregate;
  typedef boost::simd::native<double, BOOST_SIMD_DEFAULT_EXTENSION> Data;
  typedef typename nt2::meta::cardinal_of<Data>::type Cardinal;

  typedef typename boost::proto::result_of::child_c<aggregate, 0>::value_type idx0;
  NT2_TEST(( nt2::ext::is_vectorizable_indexer<idx0, Cardinal>::value ));

  typedef typename boost::proto::result_of::child_c<aggregate, 1>::value_type idx1;
  NT2_TEST(( !nt2::ext::is_vectorizable_indexer<idx1, Cardinal>::value ));

  typedef typename boost::proto::result_of::child_c<aggregate, 2>::value_type idx2;
  NT2_TEST(( nt2::ext::is_vectorizable_indexer<idx2, Cardinal>::value ));

  typedef typename boost::proto::result_of::child_c<aggregate, 3>::value_type idx3;
  NT2_TEST(( !nt2::ext::is_vectorizable_indexer<idx3, Cardinal>::value ));

  NT2_TEST(( !nt2::ext::is_vectorizable_indexers<aggregate, Data>::type::value ));
}

template<class T>
void vectorizable_1(T const&)
{
  typedef typename boost::proto::result_of::child_c<T, 1>::value_type aggregate;
  typedef boost::dispatch::meta::as_< boost::simd::native<double, BOOST_SIMD_DEFAULT_EXTENSION> > Data;
  typedef typename nt2::meta::cardinal_of<typename boost::dispatch::meta::target_value<Data>::type>::type Cardinal;

  typedef typename boost::proto::result_of::child_c<aggregate, 0>::value_type idx0;
  NT2_TEST(( nt2::ext::is_vectorizable_indexer<idx0, Cardinal>::value ));

  typedef typename boost::proto::result_of::child_c<aggregate, 1>::value_type idx1;
  NT2_TEST(( nt2::ext::is_vectorizable_indexer<idx1, Cardinal>::value ));

  typedef typename boost::proto::result_of::child_c<aggregate, 2>::value_type idx2;
  NT2_TEST(( nt2::ext::is_vectorizable_indexer<idx2, Cardinal>::value ));

  typedef typename boost::proto::result_of::child_c<aggregate, 3>::value_type idx3;
  NT2_TEST(( !nt2::ext::is_vectorizable_indexer<idx3, Cardinal>::value ));

  NT2_TEST(( nt2::ext::is_vectorizable_indexers<aggregate, Data>::type::value ));

}

NT2_TEST_CASE( vectorizable )
{
  using nt2::_;
  namespace mpl = boost::mpl;
  using nt2::of_size_;
  using nt2::of_size;
  typedef double T;

  nt2::table<T> a;
  vectorizable_0( a(_, _(1, 4), _(mpl::int_<1>(), mpl::int_<4>()), 1) );
  vectorizable_1( a(_, _, _, _(mpl::int_<1>(), mpl::int_<7>())) );
}

NT2_TEST_CASE( dimensions )
{
  using nt2::_;
  namespace mpl = boost::mpl;
  using nt2::of_size_;
  using nt2::of_size;
  typedef double T;

  nt2::table<T, nt2::_4D> a(of_size(5, 4, 3, 2));
  nt2::table<T, nt2::of_size_<2, 2> > b;

  NT2_TEST_EXPR_TYPE( a()
                    , size_of<mpl::_>
                    , nt2::_4D
                    );
  NT2_TEST_EQUAL( a().extent(), of_size(5, 4, 3, 2 ) );

  NT2_TEST_EXPR_TYPE( a(_, _, _, _)
                    , size_of<mpl::_>
                    , nt2::_4D
                    );
  NT2_TEST_EQUAL( a(_, _, _, _).extent(), of_size(5, 4, 3, 2 ) );

  NT2_TEST_EXPR_TYPE( a(_, _, _)
                    , size_of<mpl::_>
                    , nt2::_3D
                    );
  NT2_TEST_EQUAL( a(_, _, _).extent(), of_size(5, 4, 6 ) );

  NT2_TEST_EXPR_TYPE( a(_, _)
                    , size_of<mpl::_>
                    , nt2::_2D
                    );
  NT2_TEST_EQUAL( a(_, _).extent(), of_size(5, 24 ) );

  NT2_TEST_EXPR_TYPE( a(_)
                    , size_of<mpl::_>
                    , nt2::_1D
                    );
  NT2_TEST_EQUAL( a(_).extent(), of_size(120 ) );
  NT2_TEST_EXPR_TYPE( b(_)
                    , size_of<mpl::_>
                    , nt2::of_size_<4>
                    );

  NT2_TEST_EXPR_TYPE( a(1)
                    , size_of<mpl::_>
                    , nt2::_0D
                    );

  NT2_TEST_EXPR_TYPE( a(_, 1)
                    , size_of<mpl::_>
                    , nt2::_1D
                    );
  NT2_TEST_EQUAL( a(_, 1).extent(), of_size(5 ) );

  NT2_TEST_EXPR_TYPE( a(1, _)
                    , size_of<mpl::_>
                    , ( of_size_<1, -1> )
                    );
  NT2_TEST_EQUAL( a(1, _).extent(), of_size(1, 24 ) );

  NT2_TEST_EXPR_TYPE( a(_, 1, _, 1)
                    , size_of<mpl::_>
                    , ( of_size_<-1, 1, -1, 1> )
                    );
  NT2_TEST_EQUAL( a(1, _).extent(), of_size(1, 24 ) );

  NT2_TEST_EXPR_TYPE( a(b)
                    , size_of<mpl::_>
                    , ( of_size_<2, 2> )
                    );

  NT2_TEST_EXPR_TYPE( a(b, 1)
                    , size_of<mpl::_>
                    , ( of_size_<4> )
                    );

  NT2_TEST_EXPR_TYPE( a(b, b)
                    , size_of<mpl::_>
                    , ( of_size_<4, 4> )
                    );

  nt2::table<T, nt2::_3D> c;
  NT2_TEST_EXPR_TYPE( c(_, _, _)
                    , size_of<mpl::_>
                    , nt2::_3D
                    );
}

NT2_TEST_CASE( integral_subscript )
{
  using nt2::table;
  using nt2::of_size;
  typedef double T;

  table<T> a0( of_size(5,4,3,2) );

  //============================================================================
  // 1D subscript
  //============================================================================
  for(int j=1;j<=5*4*3*2;j++) a0(j) = j;

  int ii(1);
  for(int l=1;l<=2;l++)
    for(int k=1;k<=3;k++)
      for(int j=1;j<=4;j++)
        for(int i=1;i<=5;i++)
        {
          NT2_TEST_EQUAL( a0(i,j,k,l) , ii);
          ii++;
        }

  //============================================================================
  // 2D subscript
  //============================================================================
  for(int j=1;j<=4*3*2;j++)
    for(int i=1;i<=5;i++)
      a0(i,j) = i + 10*j;

  int jj(1);

  for(int l=1;l<=2;l++)
    for(int k=1;k<=3;k++)
      for(int j=1;j<=4;j++)
      {
        ii = 1;
        for(int i=1;i<=5;i++)
        {
          NT2_TEST_EQUAL( a0(i,j,k,l) , ii + 10*jj );
          ii++;
        }
        jj++;
      }

  //============================================================================
  // 3D subscript
  //============================================================================
  for(int k=1;k<=3*2;k++)
    for(int j=1;j<=4;j++)
      for(int i=1;i<=5;i++)
        a0(i,j,k) = i + 10*j + 100*k;

  int kk(1);

  for(int l=1;l<=2;l++)
    for(int k=1;k<=3;k++)
    {
      jj = 1;
      for(int j=1;j<=4;j++)
      {
        ii = 1;
        for(int i=1;i<=5;i++)
        {
          NT2_TEST_EQUAL( a0(i,j,k,l) , ii + 10*jj + 100*kk );
          ii++;
        }
        jj++;
      }
      kk++;
    }

  //============================================================================
  // 4D subscript
  //============================================================================
  for(int l=1;l<=2;l++)
    for(int k=1;k<=3;k++)
      for(int j=1;j<=4;j++)
        for(int i=1;i<=5;i++)
          a0(i,j,k,l) = i + 10*j + 100*k + 1000*l;

  for(int l=1;l<=2;l++)
    for(int k=1;k<=3;k++)
      for(int j=1;j<=4;j++)
        for(int i=1;i<=5;i++)
          NT2_TEST_EQUAL( a0(i,j,k,l) , i + 10*j + 100*k + 1000*l );
}

NT2_TEST_CASE( integral_subscript_expr )
{
  using nt2::table;
  using nt2::of_size;
  typedef double T;

  table<T> a0( of_size(5,4,3,2) );
  for(int j=1;j<=5*4*3*2;j++) a0(j) = j;

  int ii(1);
  for(int l=1;l<=2;l++)
    for(int k=1;k<=3;k++)
      for(int j=1;j<=4;j++)
        for(int i=1;i<=5;i++)
        {
          NT2_TEST_EQUAL( (a0+a0(3)*a0)(i,j,k,l) , ii+a0(3)*ii);
          ii++;
        }
}

NT2_TEST_CASE( integral_subscript_extent )
{
  using nt2::table;
  using nt2::of_size;
  typedef double T;

  table<T> a0( of_size(5,4,3,2) );

  NT2_TEST_EQUAL( nt2::extent( a0(1)       ), of_size(1 ) );
  NT2_TEST_EQUAL( nt2::extent( a0(1,1)     ), of_size(1 ) );
  NT2_TEST_EQUAL( nt2::extent( a0(1,1,1)   ), of_size(1 ) );
  NT2_TEST_EQUAL( nt2::extent( a0(1,1,1,1) ), of_size(1 ) );

  NT2_TEST_EQUAL( nt2::extent( (a0+a0)(1)       ), of_size(1 ) );
  NT2_TEST_EQUAL( nt2::extent( (a0-a0)(1,1)     ), of_size(1 ) );
  NT2_TEST_EQUAL( nt2::extent( (a0*a0)(1,1,1)   ), of_size(1 ) );
  NT2_TEST_EQUAL( nt2::extent( (a0/a0)(1,1,1,1) ), of_size(1 ) );
}

NT2_TEST_CASE( colon_subscript )
{
  using nt2::table;
  using nt2::of_size;
  using nt2::_;
  typedef double T;

  table<T> a0( of_size(5,4,3,2) );

  for(int l=1;l<=2;l++)
   for(int k=1;k<=3;k++)
    for(int j=1;j<=4;j++)
     for(int i=1;i<=5;i++)
      a0(i,j,k,l) = i + 10*j + 100*k + 1000*l;

  //============================================================================
  // 1D subscript
  //============================================================================
  {
    table<T> a1 = a0(_);
    NT2_TEST_EQUAL( a1(1) , 1111 );
    NT2_TEST_EQUAL( a1(5) , 1115 );
    NT2_TEST_EQUAL( a1(10), 1125 );
    NT2_TEST_EQUAL( a1(15), 1135 );
    NT2_TEST_EQUAL( a1(20), 1145 );
  }

  //============================================================================
  // 2D subscript
  //============================================================================
  {
    table<T> a1 = a0(_,_);

    NT2_TEST_EQUAL( nt2::extent( a1 ), of_size(5,24 ) );
    for(int j=1;j<=24;j++)
     for(int i=1;i<=5;i++)
      NT2_TEST_EQUAL( a1(i,j), a0(i,j) );

    for(int r=1;r<=5;r++)
    {
      table<T> a2 = a0(r,_);
      NT2_TEST_EQUAL( nt2::extent( a2 ), of_size(1,24 ) );

      for(int i=1;i<=24;i++)
        NT2_TEST_EQUAL( a2(1,i), a0(r,i) );
    }

    for(int r=1;r<=24;r++)
    {
      table<T> a3 = a0(_,r);
      NT2_TEST_EQUAL( nt2::extent( a3 ), of_size(5,1 ) );

      for(int i=1;i<=5;i++)
        NT2_TEST_EQUAL( a3(i,1), a0(i,r) );
    }
  }

  //============================================================================
  // 3D subscript
  //============================================================================
  {
    table<T> a1 = a0(_,_,_);

    NT2_TEST_EQUAL( nt2::extent( a1 ), of_size(5,4,6 ) );
    for(int k=1;k<=6;k++)
     for(int j=1;j<=4;j++)
      for(int i=1;i<=5;i++)
       NT2_TEST_EQUAL( a1(i,j,k), a0(i,j,k) );

    for(int r=1;r<=5;r++)
    {
      table<T> a2 = a0(r,_,_);
      NT2_TEST_EQUAL( nt2::extent( a2 ), of_size(1,4,6 ) );

      for(int j=1;j<=6;j++)
       for(int i=1;i<=4;i++)
        NT2_TEST_EQUAL( a2(1,i,j), a0(r,i,j) );
    }

    for(int r=1;r<=4;r++)
    {
      table<T> a2 = a0(_,r,_);
      NT2_TEST_EQUAL( nt2::extent( a2 ), of_size(5,1,6 ) );

      for(int j=1;j<=6;j++)
       for(int i=1;i<=5;i++)
        NT2_TEST_EQUAL( a2(i,1,j), a0(i,r,j) );
    }

    for(int r=1;r<=6;r++)
    {
      table<T> a2 = a0(_,_,r);
      NT2_TEST_EQUAL( nt2::extent( a2 ), of_size(5,4,1 ) );

      for(int j=1;j<=4;j++)
       for(int i=1;i<=5;i++)
        NT2_TEST_EQUAL( a2(i,j,1), a0(i,j,r) );
    }
  }

  //============================================================================
  // 4D subscript
  //============================================================================
  {
    table<T> a1 = a0(_,_,_,_);

    NT2_TEST_EQUAL( nt2::extent( a1 ), of_size(5,4,3,2 ) );
    for(int l=1;l<=2;l++)
      for(int k=1;k<=3;k++)
        for(int j=1;j<=4;j++)
          for(int i=1;i<=5;i++)
            NT2_TEST_EQUAL( a1(i,j,k,l), a0(i,j,k,l) );

    for(int r=1;r<=5;r++)
    {
      table<T> a2 = a0(r,_,_,_);
      NT2_TEST_EQUAL( nt2::extent( a2 ), of_size(1,4,3,2 ) );

      for(int k=1;k<=2;k++)
        for(int j=1;j<=3;j++)
          for(int i=1;i<=4;i++)
            NT2_TEST_EQUAL( a2(1,i,j,k), a0(r,i,j,k) );
    }

    for(int r=1;r<=4;r++)
    {
      table<T> a2 = a0(_,r,_,_);
      NT2_TEST_EQUAL( nt2::extent( a2 ), of_size(5,1,3,2 ) );

      for(int k=1;k<=2;k++)
        for(int j=1;j<=3;j++)
          for(int i=1;i<=5;i++)
            NT2_TEST_EQUAL( a2(i,1,j,k), a0(i,r,j,k) );
    }

    for(int r=1;r<=3;r++)
    {
      table<T> a2 = a0(_,_,r,_);
      NT2_TEST_EQUAL( nt2::extent( a2 ), of_size(5,4,1,2 ) );

      for(int k=1;k<=2;k++)
        for(int j=1;j<=4;j++)
          for(int i=1;i<=5;i++)
            NT2_TEST_EQUAL( a2(i,j,1,k), a0(i,j,r,k) );
    }

    for(int r=1;r<=2;r++)
    {
      table<T> a2 = a0(_,_,_,r);
      NT2_TEST_EQUAL( nt2::extent( a2 ), of_size(5,4,3,1 ) );

      for(int k=1;k<=3;k++)
        for(int j=1;j<=4;j++)
          for(int i=1;i<=5;i++)
            NT2_TEST_EQUAL( a2(i,j,k,1), a0(i,j,k,r) );
    }
  }
}

NT2_TEST_CASE( colon_subscript_extent )
{
  using nt2::table;
  using nt2::of_size;
  using nt2::_;
  typedef double T;

  table<T> a0( of_size(5,4,3,2) );

  NT2_TEST_EQUAL( nt2::extent( a0(_)       ), of_size(120 )     );

  NT2_TEST_EQUAL( nt2::extent( a0(_,1,1)   ), of_size(5 )       );
  NT2_TEST_EQUAL( nt2::extent( a0(1,_,_)   ), of_size(1,4,6 )   );
  NT2_TEST_EQUAL( nt2::extent( a0(1,_,1)   ), of_size(1,4 )     );
  NT2_TEST_EQUAL( nt2::extent( a0(1,1,_)   ), of_size(1,1,6 )   );

  NT2_TEST_EQUAL( nt2::extent( a0(_,_,_,_) ), of_size(5,4,3,2 ) );
  NT2_TEST_EQUAL( nt2::extent( a0(_,_,_,1) ), of_size(5,4,3 )   );
  NT2_TEST_EQUAL( nt2::extent( a0(_,_,1,_) ), of_size(5,4,1,2 ) );
  NT2_TEST_EQUAL( nt2::extent( a0(_,_,1,1) ), of_size(5,4 )     );
  NT2_TEST_EQUAL( nt2::extent( a0(_,1,_,_) ), of_size(5,1,3,2 ) );
  NT2_TEST_EQUAL( nt2::extent( a0(_,1,_,1) ), of_size(5,1,3 )   );
  NT2_TEST_EQUAL( nt2::extent( a0(_,1,1,_) ), of_size(5,1,1,2 ) );
  NT2_TEST_EQUAL( nt2::extent( a0(_,1,1,1) ), of_size(5 )       );
  NT2_TEST_EQUAL( nt2::extent( a0(1,_,_,_) ), of_size(1,4,3,2 ) );
  NT2_TEST_EQUAL( nt2::extent( a0(1,_,_,1) ), of_size(1,4,3 )   );
  NT2_TEST_EQUAL( nt2::extent( a0(1,_,1,_) ), of_size(1,4,1,2 ) );
  NT2_TEST_EQUAL( nt2::extent( a0(1,_,1,1) ), of_size(1,4 )     );
  NT2_TEST_EQUAL( nt2::extent( a0(1,1,_,_) ), of_size(1,1,3,2 ) );
  NT2_TEST_EQUAL( nt2::extent( a0(1,1,_,1) ), of_size(1,1,3 )   );
  NT2_TEST_EQUAL( nt2::extent( a0(1,1,1,_) ), of_size(1,1,1,2 ) );
}

NT2_TEST_CASE_TPL( colon_values_subscript, (float)(double) )
{
  using nt2::table;
  using nt2::of_size;
  using nt2::_;

  table<T> a0( of_size(15,4,3,2) );

  for(int l=1;l<=2;l++)
   for(int k=1;k<=3;k++)
    for(int j=1;j<=4;j++)
     for(int i=1;i<=15;i++)
      a0(i,j,k,l) = i + 10*j + 100*k + 1000*l;

  table<T> a1 = a0(_(2,14), _(2, 3), _(2, 2), _(1, 1));
  NT2_TEST_EQUAL( nt2::extent( a1 ), of_size(13,2 ) );
  for(int j=1;j<=2;j++)
    for(int i=1;i<=13;i++)
      NT2_TEST_EQUAL( a1(i,j), a0(i+1,j+1,2,1) );
}
