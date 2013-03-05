//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#define NT2_UNIT_MODULE "nt2::ind2sub function"

#include <iostream>
#include <nt2/include/functions/ind2sub.hpp>
#include <nt2/include/functions/enumerate.hpp>
#include <nt2/include/functions/arith.hpp>
#include <nt2/include/functions/unaligned_load.hpp>

#include <boost/array.hpp>
#include <boost/fusion/include/io.hpp>
#include <boost/fusion/include/as_vector.hpp>
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

    std::cout << boost::fusion::as_vector(a) << " == ";
    std::cout << boost::fusion::as_vector(b) << "\n";

    for(int n=0;n<1;++n) NT2_TEST_EQUAL( a[n], b[n] );
  }
}

NT2_TEST_CASE_TPL( ind2sub_1D_simd, (nt2::int32_t)(nt2::uint32_t)(nt2::int64_t)(nt2::uint64_t) )
{
  using boost::simd::meta::vector_of;
  using boost::fusion::make_vector;
  using boost::mpl::int_;

  typedef typename vector_of<T, BOOST_SIMD_BYTES/sizeof(T)>::type idx_t;
  typedef typename boost::dispatch::meta::as_signed<idx_t>::type sidx_t;
  static const int sz = boost::simd::meta::cardinal_of<idx_t>::value;

  boost::array<sidx_t, 1> a = nt2::ind2sub( make_vector(16), nt2::enumerate<idx_t>(0) );

  std::cout << boost::fusion::as_vector(a) << "\n";

  for(int n=0;n<1;++n)
    for(int j=0;j<sz;++j)
      NT2_TEST_EQUAL( a[n][j], j+1 );
}

NT2_TEST_CASE( ind2sub_1D_base )
{
  using boost::fusion::make_vector;
  using boost::mpl::int_;

  for(int i=0;i<4;++i)
  {
    boost::array<int, 1> a = nt2::ind2sub( make_vector(4), i, make_vector(-1) );
    boost::array<int, 1> b = {{i-1}};

    std::cout << boost::fusion::as_vector(a) << " == ";
    std::cout << boost::fusion::as_vector(b) << "\n";

    for(int n=0;n<1;++n) NT2_TEST_EQUAL( a[n], b[n] );
  }
}

NT2_TEST_CASE_TPL( ind2sub_1D_simd_base, (nt2::int32_t)(nt2::uint32_t)(nt2::int64_t)(nt2::uint64_t) )
{
  using boost::simd::meta::vector_of;
  using boost::fusion::make_vector;
  using boost::mpl::int_;

  typedef typename vector_of<T, BOOST_SIMD_BYTES/sizeof(T)>::type idx_t;
  typedef typename boost::dispatch::meta::as_signed<idx_t>::type sidx_t;
  static const int sz = boost::simd::meta::cardinal_of<idx_t>::value;

  boost::array<sidx_t, 1>
  a = nt2::ind2sub( make_vector(16), nt2::enumerate<idx_t>(0), make_vector(-1) );

  std::cout << boost::fusion::as_vector(a) << "\n";

  for(int n=0;n<1;++n)
    for(int j=0;j<sz;++j)
      NT2_TEST_EQUAL( a[n][j], j-1 );
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

      std::cout << boost::fusion::as_vector(a) << " == ";
      std::cout << boost::fusion::as_vector(b) << "\n";
      for(int n=0;n<2;++n) NT2_TEST_EQUAL( a[n], b[n] );
    }
  }
}

NT2_TEST_CASE_TPL( ind2sub_2D_simd, (nt2::int32_t)(nt2::uint32_t)(nt2::int64_t)(nt2::uint64_t) )
{
  using boost::simd::meta::vector_of;
  using boost::fusion::make_vector;
  using boost::mpl::int_;

  typedef typename vector_of<T, BOOST_SIMD_BYTES/sizeof(T)>::type idx_t;
  typedef typename boost::dispatch::meta::as_signed<idx_t>::type sidx_t;
  static const int sz = boost::simd::meta::cardinal_of<idx_t>::value;

  for(int j=0;j<2;++j)
  {
    boost::array<sidx_t, 2>
    a = nt2::ind2sub( make_vector(sz,2), nt2::arith<idx_t>(j*sz,1) );

    std::cout << boost::fusion::as_vector(a);

    for(int k=0;k<sz;++k)
    {
      NT2_TEST_EQUAL( a[0][k], k+1 );
      NT2_TEST_EQUAL( a[1][k], j+1 );
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

      std::cout << boost::fusion::as_vector(a) << " == ";
      std::cout << boost::fusion::as_vector(b) << "\n";

      for(int n=0;n<2;++n)  NT2_TEST_EQUAL( a[n], b[n] );
    }
  }
}

NT2_TEST_CASE_TPL( ind2sub_2D_simd_base, (nt2::int32_t)(nt2::uint32_t)(nt2::int64_t)(nt2::uint64_t) )
{
  using boost::simd::meta::vector_of;
  using boost::fusion::make_vector;
  using boost::mpl::int_;

  typedef typename vector_of<T, BOOST_SIMD_BYTES/sizeof(T)>::type idx_t;
  typedef typename boost::dispatch::meta::as_signed<idx_t>::type sidx_t;
  static const int sz = boost::simd::meta::cardinal_of<idx_t>::value;

  for(std::ptrdiff_t j=0;j<5;++j)
  {
    boost::array<sidx_t, 2>
    a = nt2::ind2sub(make_vector(sz,5),nt2::arith<idx_t>(j*sz,1),make_vector(-1,-2));

    std::cout << boost::fusion::as_vector(a) << "\n";
    for(std::ptrdiff_t k=0;k<sz;++k)
    {
      NT2_TEST_EQUAL( a[0][k], k-1 );
      NT2_TEST_EQUAL( a[1][k], j-2 );
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

        std::cout << boost::fusion::as_vector(a) << " == ";
        std::cout << boost::fusion::as_vector(b) << "\n";

        for(int n=0;n<3;++n) NT2_TEST_EQUAL( a[n], b[n] );
      }
    }
  }
}

NT2_TEST_CASE_TPL( ind2sub_3D_simd, (nt2::int32_t)(nt2::uint32_t)(nt2::int64_t)(nt2::uint64_t) )
{
  using boost::simd::meta::vector_of;
  using boost::fusion::make_vector;
  using boost::mpl::int_;

  typedef typename vector_of<T, BOOST_SIMD_BYTES/sizeof(T)>::type idx_t;
  typedef typename boost::dispatch::meta::as_signed<idx_t>::type sidx_t;
  static const int sz = boost::simd::meta::cardinal_of<idx_t>::value;

  for(int k=0;k<5;++k)
  {
    for(int j=0;j<2;++j)
    {
      boost::array<sidx_t, 3>
      a = nt2::ind2sub( make_vector(sz,2,5), nt2::arith<idx_t>(sz*(j+2*k),1) );

      std::cout << boost::fusion::as_vector(a) << "\n";

      for(std::ptrdiff_t n=0;n<sz;++n)
      {
        NT2_TEST_EQUAL( a[0][n], n+1 );
        NT2_TEST_EQUAL( a[1][n], j+1 );
        NT2_TEST_EQUAL( a[2][n], k+1 );
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
        boost::array<int, 3>
        a = nt2::ind2sub( make_vector(3,2,5), i + 3*(j+2*k), make_vector(-1,1,2) );

        boost::array<int, 3> b = {{i-1,j+1,k+2}};

        std::cout << boost::fusion::as_vector(a) << " == ";
        std::cout << boost::fusion::as_vector(b) << "\n";

        for(int n=0;n<3;++n) NT2_TEST_EQUAL( a[n], b[n] );
      }
    }
  }
}

NT2_TEST_CASE_TPL( ind2sub_3D_simd_base, (nt2::int32_t)(nt2::uint32_t)(nt2::int64_t)(nt2::uint64_t) )
{
  using boost::simd::meta::vector_of;
  using boost::fusion::make_vector;
  using boost::mpl::int_;

  typedef typename vector_of<T, BOOST_SIMD_BYTES/sizeof(T)>::type idx_t;
  typedef typename boost::dispatch::meta::as_signed<idx_t>::type sidx_t;
  static const int sz = boost::simd::meta::cardinal_of<idx_t>::value;

  for(int k=0;k<5;++k)
  {
    for(int j=0;j<2;++j)
    {
      boost::array<sidx_t, 3>
      a = nt2::ind2sub( make_vector(sz,2,5), nt2::arith<idx_t>(sz*(j+2*k),1), make_vector(-1,-1,-2) );

      std::cout << boost::fusion::as_vector(a) << "\n";

      for(std::ptrdiff_t n=0;n<sz;++n)
      {
        NT2_TEST_EQUAL( a[0][n], n-1 );
        NT2_TEST_EQUAL( a[1][n], j-1 );
        NT2_TEST_EQUAL( a[2][n], k-2 );
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
          boost::array<int, 4>
          a = nt2::ind2sub( make_vector(3,2,5,3), i + 3*(j+2*(k+5*l)) );

          boost::array<int, 4> b = {{i+1,j+1,k+1,l+1}};

          std::cout << boost::fusion::as_vector(a) << " == ";
          std::cout << boost::fusion::as_vector(b) << "\n";

          for(int n=0;n<4;++n) NT2_TEST_EQUAL( a[n], b[n] );
        }
      }
    }
  }
}

NT2_TEST_CASE_TPL( ind2sub_4D_simd, (nt2::int32_t)(nt2::uint32_t)(nt2::int64_t)(nt2::uint64_t) )
{
  using boost::simd::meta::vector_of;
  using boost::fusion::make_vector;
  using boost::mpl::int_;

  typedef typename vector_of<T, BOOST_SIMD_BYTES/sizeof(T)>::type idx_t;
  typedef typename boost::dispatch::meta::as_signed<idx_t>::type sidx_t;
  static const int sz = boost::simd::meta::cardinal_of<idx_t>::value;

  for(int l=0;l<3;++l)
  {
    for(int k=0;k<5;++k)
    {
      for(int j=0;j<2;++j)
      {
        boost::array<sidx_t, 4>
        a = nt2::ind2sub( make_vector(sz,2,5,3), nt2::arith<idx_t>(sz*(j+2*(k+5*l)),1) );

        std::cout << boost::fusion::as_vector(a) << "\n";

        for(std::ptrdiff_t n=0;n<sz;++n)
        {
          NT2_TEST_EQUAL( a[0][n], n+1 );
          NT2_TEST_EQUAL( a[1][n], j+1 );
          NT2_TEST_EQUAL( a[2][n], k+1 );
          NT2_TEST_EQUAL( a[3][n], l+1 );
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
          boost::array<int, 4>
          a = nt2::ind2sub( make_vector(3,2,5,3), i + 3*(j+2*(k+5*l)), make_vector(-1,1,-2,2) );
          boost::array<int, 4> b = {{i-1,j+1,k-2,l+2}};
          for(int n=0;n<4;++n) NT2_TEST_EQUAL( a[n], b[n] );
        }
      }
    }
  }
}

NT2_TEST_CASE_TPL( ind2sub_4D_simd_base, (nt2::int32_t)(nt2::uint32_t)(nt2::int64_t)(nt2::uint64_t) )
{
  using boost::simd::meta::vector_of;
  using boost::fusion::make_vector;
  using boost::mpl::int_;

  typedef typename vector_of<T, BOOST_SIMD_BYTES/sizeof(T)>::type idx_t;
  typedef typename boost::dispatch::meta::as_signed<idx_t>::type sidx_t;
  static const int sz = boost::simd::meta::cardinal_of<idx_t>::value;

  for(int l=0;l<3;++l)
  {
    for(int k=0;k<5;++k)
    {
      for(int j=0;j<2;++j)
      {
        boost::array<sidx_t, 4>
        a = nt2::ind2sub( make_vector(sz,2,5,3)
                        , nt2::arith<idx_t>(sz*(j+2*(k+5*l)),1)
                        , make_vector(-1,1,-2,2)
                        );

        std::cout << boost::fusion::as_vector(a) << "\n";

        for(std::ptrdiff_t n=0;n<sz;++n)
        {
          NT2_TEST_EQUAL( a[0][n], n-1 );
          NT2_TEST_EQUAL( a[1][n], j+1 );
          NT2_TEST_EQUAL( a[2][n], k-2 );
          NT2_TEST_EQUAL( a[3][n], l+2 );
        }
      }
    }
  }
}
