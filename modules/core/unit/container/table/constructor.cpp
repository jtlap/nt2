/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#define NT2_UNIT_MODULE "nt2::table constructor checks"

#include <nt2/table.hpp>
#include <nt2/include/functions/size.hpp>
#include <nt2/include/functions/extent.hpp>
#include <nt2/include/functions/first_index.hpp>
#include <nt2/include/functions/last_index.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/basic.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>

NT2_TEST_CASE( default_ctor )
{
  using nt2::table;
  using nt2::of_size;

  table<float> x;

  NT2_TEST( nt2::extent(x) == of_size(0) );
}

NT2_TEST_CASE( of_size_ctor )
{
  using nt2::table;
  using nt2::of_size;
  using nt2::of_size_;

  {
    table<float> x( of_size(2,3) );
    NT2_TEST( nt2::extent(x) == of_size(2,3) );

    table<float, of_size_<5, 1>  > b;
    NT2_TEST( nt2::extent(b) == of_size(5, 1) );

    table<float, of_size_<5>  > c;
    NT2_TEST( nt2::extent(c) == of_size(5) );
  }

  {
    table<float> x( of_size(2,3,4) );
    NT2_TEST( nt2::extent(x) == of_size(2,3,4) );
  }

  {
    table<float> x( of_size(2,3,4,5) );
    NT2_TEST( nt2::extent(x) == of_size(2,3,4,5) );
  }

  {
    table<float, of_size_<2,3> > x;
    NT2_TEST( nt2::extent(x) == of_size(2,3) );
  }

  {
    table<float, of_size_<2,3,4> > x;
    NT2_TEST( nt2::extent(x) == of_size(2,3,4) );
  }

  {
    table<float, of_size_<2,3,4,5> > x;
    NT2_TEST( nt2::extent(x) == of_size(2,3,4,5) );
  }
}

NT2_TEST_CASE( range_ctor )
{
  using nt2::table;
  using nt2::of_size;
  using nt2::first_index;
  using nt2::last_index;

  float data[] =  {
                    1,2,3
                  , 4,5,6
                  };

  table<float> x( of_size(3,2), &data[0], &data[0] + 6 );
  NT2_TEST( nt2::extent(x) == of_size(3,2) );

  for(int j=first_index<2>(x);j<=last_index<2>(x);++j)
   for(int i=first_index<1>(x);i<=last_index<1>(x);++i)
      NT2_TEST_EQUAL( float(x(i,j)), data[(i-1) + (j-1)*3]) ;
}

struct adhoc_
{
  typedef boost::mpl::true_ padding_status;

  template<class Sig> struct result;
  template<class T, int N> struct result_impl;

  template<class This, class T, class N, class V>
  struct  result<This(T,N,V)> { typedef std::size_t type; };

  template<class T, class N, class V>
  typename result<adhoc_(T const&, N const&, V const&)>::type
  operator()(T const& t, N const& n, V const& v) const
  {
    return eval(t,n,v,boost::mpl::bool_<N::value==0>());
  }

  template<class T, class N, class V>
  typename result<adhoc_(T const&, N const&, V const&)>::type
  eval(T const& t, N const&, V const&, boost::mpl::true_ const&) const
  {
    return 4;
  }

  template<class T, class N, class V>
  typename result<adhoc_(T const&, N const&, V const&)>::type
  eval(T const& t, N const&, V const&, boost::mpl::false_ const&) const
  {
    return t;
  }
};

NT2_TEST_CASE( shared_ctor )
{
  using nt2::table;
  using nt2::of_size;
  using nt2::shared_;
  using nt2::settings;
  using nt2::no_padding_;
  using nt2::padding_;
  using nt2::share;
  using nt2::first_index;
  using nt2::last_index;

  float data[] =  {
                    1,2,3,0
                  , 4,5,6,0
                  , 0,0,0,0
                  , 0,0,0,0
                  };
  {
    table<float, settings(shared_,no_padding_)>
    x(of_size(4,2), share(&data[0], &data[0] + 8));

    NT2_TEST( nt2::extent(x) == of_size(4,2) );

  for(int j=first_index<2>(x);j<=last_index<2>(x);++j)
   for(int i=first_index<1>(x);i<=last_index<1>(x);++i)
        NT2_TEST_EQUAL( float(x(i,j)), data[(i-1) + (j-1)*4]) ;
  }

  {
    table<float, settings(shared_,padding_<adhoc_>)>
    x(of_size(3,2), share(&data[0], &data[0] + 8));

    NT2_TEST( nt2::extent(x) == of_size(3,2) );

    for(int j=1;j<=2;++j)
     for(int i=1;i<=3;++i)
        NT2_TEST_EQUAL( float(x(i,j)), data[(i-1) + (j-1)*4]) ;
  }

  {
    float f = 1.f;

    table < float, settings ( shared_ , no_padding_ )
          > x(nt2::extent(f), share(&f, &f + 1));

    NT2_TEST( nt2::extent(x) == of_size(1) );

    NT2_TEST_EQUAL( float(x(1,1)), 1.f );
    x = 2.f;
    NT2_TEST_EQUAL( float(x(1,1)), 2.f );
  }
}
