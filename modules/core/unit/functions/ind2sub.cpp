/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#define NT2_UNIT_MODULE "nt2::ind2sub function"

#include <iostream>
#include <nt2/include/functions/ind2sub.hpp>
#include <nt2/include/functions/unaligned_load.hpp>

#include <boost/array.hpp>
#include <boost/fusion/include/make_vector.hpp>
#include <boost/mpl/int.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/basic.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>

NT2_TEST_CASE( ind2sub_1D )
{
  using boost::fusion::make_vector;
  using boost::mpl::int_;

  for(int i=0;i<3;++i)
  {
    boost::array<int, 1> a = nt2::ind2sub( make_vector(3), i );
    boost::array<int, 1> b = {{i+1}};
    for(int n=0;n<1;++n) NT2_TEST_EQUAL( a[n], b[n] );
  }
}

NT2_TEST_CASE( ind2sub_1D_simd )
{
  using boost::simd::native;
  using boost::fusion::make_vector;
  using boost::mpl::int_;

  typedef native<std::size_t, BOOST_SIMD_DEFAULT_EXTENSION> idx_t;
  static const std::size_t sz = boost::simd::meta::cardinal_of<idx_t>::value;

  std::size_t va[sz];
  for(int i=0;i<sz;++i) va[i] = 4*i;

  boost::array<idx_t, 1> a = nt2::ind2sub( make_vector(16), nt2::unaligned_load<idx_t>(&va[0]) );
  for(int n=0;n<1;++n)
    for(int j=0;j<sz;++j)
      NT2_TEST_EQUAL( a[n][j], va[j]+1 );
}

NT2_TEST_CASE( ind2sub_1D_base1 )
{
  using boost::fusion::make_vector;
  using boost::mpl::int_;

  for(int i=0;i<5;++i)
  {
    boost::array<int, 1> a = nt2::ind2sub( make_vector(5), i, make_vector(1) );
    boost::array<int, 1> b = {{i+1}};
    for(int n=0;n<1;++n) NT2_TEST_EQUAL( a[n], b[n] );
  }
}

NT2_TEST_CASE( ind2sub_1D_base )
{
  using boost::fusion::make_vector;
  using boost::mpl::int_;

  for(int i=0;i<4;++i)
  {
    boost::array<int, 1> a = nt2::ind2sub( make_vector(4), i, make_vector(-1) );
    boost::array<int, 1> b = {{i-1}};
    for(int n=0;n<1;++n) NT2_TEST_EQUAL( a[n], b[n] );
  }
}

NT2_TEST_CASE( ind2sub_2D_simd )
{
  using boost::simd::native;
  using boost::fusion::make_vector;
  using boost::mpl::int_;

  typedef native<std::size_t, BOOST_SIMD_DEFAULT_EXTENSION> idx_t;
  static const std::size_t sz = boost::simd::meta::cardinal_of<idx_t>::value;

  for(int j=0;j<2;++j)
  {
    for(int i=0;i<3;++i)
    {
      std::size_t va[sz], vb[sz];
      for(int k=0;k<sz;++k) va[k] = (i+3*j+k) % 6;

      boost::array<idx_t, 2>
      a = nt2::ind2sub( make_vector(3,2), nt2::unaligned_load<idx_t>(&va[0]) );

      std::cout << nt2::unaligned_load<idx_t>(&va[0]) << " => "
                << a[0] << ", " << a[1]
                << "\n";

      for(int k=0;k<sz;++k)
      {
        NT2_TEST_EQUAL( a[0][k], i+1 );
        NT2_TEST_EQUAL( a[1][k], j+1 );
      }
    }
  }
}

NT2_TEST_CASE( ind2sub_2D )
{
  using boost::fusion::make_vector;
  using boost::mpl::int_;

  for(int j=0;j<2;++j)
  {
    for(int i=0;i<3;++i)
    {
      boost::array<int, 2> a = nt2::ind2sub( make_vector(3,2), i + 3*j );
      boost::array<int, 2> b = {{i+1,j+1}};
      for(int n=0;n<2;++n) NT2_TEST_EQUAL( a[n], b[n] );
    }
  }
}

NT2_TEST_CASE( ind2sub_2D_base1 )
{
  using boost::fusion::make_vector;
  using boost::mpl::int_;

  for(int j=0;j<2;++j)
  {
    for(int i=0;i<3;++i)
    {
      boost::array<int, 2> a = nt2::ind2sub( make_vector(3,2), i + 3*j, make_vector(1,1) );
      boost::array<int, 2> b = {{i+1,j+1}};
      for(int n=0;n<2;++n) NT2_TEST_EQUAL( a[n], b[n] );
    }
  }
}

NT2_TEST_CASE( ind2sub_2D_base )
{
  using boost::fusion::make_vector;
  using boost::mpl::int_;

  for(int j=0;j<2;++j)
  {
    for(int i=0;i<3;++i)
    {
      boost::array<int, 2> a = nt2::ind2sub( make_vector(3,2), i + 3*j, make_vector(-1,1) );
      boost::array<int, 2> b = {{i-1,j+1}};
      for(int n=0;n<2;++n) NT2_TEST_EQUAL( a[n], b[n] );
    }
  }
}

NT2_TEST_CASE( ind2sub_3D )
{
  using boost::fusion::make_vector;
  using boost::mpl::int_;

  for(int k=0;k<5;++k)
  {
    for(int j=0;j<2;++j)
    {
      for(int i=0;i<3;++i)
      {
        boost::array<int, 3> a = nt2::ind2sub( make_vector(3,2,5), i + 3*(j+2*k) );
        boost::array<int, 3> b = {{i+1,j+1,k+1}};
        for(int n=0;n<3;++n) NT2_TEST_EQUAL( a[n], b[n] );
      }
    }
  }
}

NT2_TEST_CASE( ind2sub_3D_base1 )
{
  using boost::fusion::make_vector;
  using boost::mpl::int_;

  for(int k=0;k<5;++k)
  {
    for(int j=0;j<2;++j)
    {
      for(int i=0;i<3;++i)
      {
        boost::array<int, 3> a = nt2::ind2sub( make_vector(3,2,5), i + 3*(j+2*k), make_vector(1,1,1) );
        boost::array<int, 3> b = {{i+1,j+1,k+1}};
        for(int n=0;n<3;++n) NT2_TEST_EQUAL( a[n], b[n] );
      }
    }
  }
}

NT2_TEST_CASE( ind2sub_3D_base )
{
  using boost::fusion::make_vector;
  using boost::mpl::int_;

  for(int k=0;k<5;++k)
  {
    for(int j=0;j<2;++j)
    {
      for(int i=0;i<3;++i)
      {
        boost::array<int, 3> a = nt2::ind2sub( make_vector(3,2,5), i + 3*(j+2*k), make_vector(-1,1,2) );
        boost::array<int, 3> b = {{i-1,j+1,k+2}};
        for(int n=0;n<3;++n) NT2_TEST_EQUAL( a[n], b[n] );
      }
    }
  }
}

NT2_TEST_CASE( ind2sub_4D )
{
  using boost::fusion::make_vector;
  using boost::mpl::int_;

  for(int l=0;l<3;++l)
  {
    for(int k=0;k<5;++k)
    {
      for(int j=0;j<2;++j)
      {
        for(int i=0;i<3;++i)
        {
          boost::array<int, 4> a = nt2::ind2sub( make_vector(3,2,5,3), i + 3*(j+2*(k+5*l)) );
          boost::array<int, 4> b = {{i+1,j+1,k+1,l+1}};
          for(int n=0;n<4;++n) NT2_TEST_EQUAL( a[n], b[n] );
        }
      }
    }
  }
}

NT2_TEST_CASE( ind2sub_4D_base1 )
{
  using boost::fusion::make_vector;
  using boost::mpl::int_;

  for(int l=0;l<3;++l)
  {
    for(int k=0;k<5;++k)
    {
      for(int j=0;j<2;++j)
      {
        for(int i=0;i<3;++i)
        {
          boost::array<int, 4> a = nt2::ind2sub( make_vector(3,2,5,3), i + 3*(j+2*(k+5*l)), make_vector(1,1,1,1) );
          boost::array<int, 4> b = {{i+1,j+1,k+1,l+1}};
          for(int n=0;n<4;++n) NT2_TEST_EQUAL( a[n], b[n] );
        }
      }
    }
  }
}

NT2_TEST_CASE( ind2sub_4D_base )
{
  using boost::fusion::make_vector;
  using boost::mpl::int_;

  for(int l=0;l<3;++l)
  {
    for(int k=0;k<5;++k)
    {
      for(int j=0;j<2;++j)
      {
        for(int i=0;i<3;++i)
        {
          boost::array<int, 4> a = nt2::ind2sub( make_vector(3,2,5,3), i + 3*(j+2*(k+5*l)), make_vector(-1,1,-2,2) );
          boost::array<int, 4> b = {{i-1,j+1,k-2,l+2}};
          for(int n=0;n<4;++n) NT2_TEST_EQUAL( a[n], b[n] );
        }
      }
    }
  }
}
