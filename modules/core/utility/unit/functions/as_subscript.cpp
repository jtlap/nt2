/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#define NT2_UNIT_MODULE "nt2::as_subscript function"

#include <nt2/core/utility/as_subscript.hpp>
#include <nt2/include/functions/enumerate.hpp>
#include <nt2/include/functions/arith.hpp>

#include <boost/array.hpp>
#include <boost/fusion/include/make_vector.hpp>
#include <boost/mpl/int.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/basic.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>

NT2_TEST_CASE_TPL ( as_subscript_1D
                  , (nt2::int32_t)(nt2::uint32_t)(nt2::int64_t)(nt2::uint64_t)
                  )
{
  typedef typename boost::dispatch::meta::as_unsigned<T>::type idx_t;
  using boost::fusion::make_vector;
  using boost::mpl::int_;

  for(std::size_t i=0;i<3;++i)
  {
    boost::array<idx_t, 1>
    a = nt2::as_subscript( make_vector(idx_t(3)), idx_t(i) );

    NT2_TEST_EQUAL( a[0], idx_t(i) );
  }
}

NT2_TEST_CASE_TPL ( as_subscript_1D_simd
                  , (nt2::int32_t)(nt2::uint32_t)(nt2::int64_t)(nt2::uint64_t)
                  )
{
  using boost::simd::meta::vector_of;
  using boost::fusion::make_vector;
  using boost::mpl::int_;

  typedef typename vector_of<T, BOOST_SIMD_BYTES/sizeof(T)>::type idx_t;
  typedef typename boost::dispatch::meta::as_unsigned<idx_t>::type sidx_t;
  static const size_t sz = boost::simd::meta::cardinal_of<idx_t>::value;

  boost::array<sidx_t, 1> a = nt2::as_subscript ( make_vector(16)
                                                , nt2::enumerate<idx_t>(0)
                                                );
    for(std::size_t j=0;j<sz;++j)
      NT2_TEST_EQUAL( a[0][j], j );
}

NT2_TEST_CASE_TPL ( as_subscript_2D
                  , (nt2::int32_t)(nt2::uint32_t)(nt2::int64_t)(nt2::uint64_t)
                  )
{
  typedef typename boost::dispatch::meta::as_unsigned<T>::type idx_t;
  using boost::fusion::make_vector;
  using boost::mpl::int_;

  for(std::size_t j=0;j<2;++j)
    for(std::size_t i=0;i<3;++i)
    {
      boost::array<idx_t, 2>
      a = nt2::as_subscript( make_vector(idx_t(3),idx_t(2)), idx_t(i+3*j) );

      NT2_TEST_EQUAL( a[0], idx_t(i) );
      NT2_TEST_EQUAL( a[1], idx_t(j) );
    }
}

NT2_TEST_CASE_TPL ( as_subscript_2D_simd
                  , (nt2::int32_t)(nt2::uint32_t)(nt2::int64_t)(nt2::uint64_t)
                  )
{
  using boost::simd::meta::vector_of;
  using boost::fusion::make_vector;
  using boost::mpl::int_;

  typedef typename vector_of<T, BOOST_SIMD_BYTES/sizeof(T)>::type idx_t;
  typedef typename boost::dispatch::meta::as_unsigned<idx_t>::type sidx_t;
  static const std::size_t sz = boost::simd::meta::cardinal_of<idx_t>::value;

  for(std::size_t j=0;j<2;++j)
  {
    boost::array<sidx_t, 2>
    a = nt2::as_subscript( make_vector(sz,2), nt2::arith<idx_t>(j*sz,1) );

    for(std::size_t k=0;k<sz;++k)
    {
      NT2_TEST_EQUAL( a[0][k], k );
      NT2_TEST_EQUAL( a[1][k], j );
    }
  }
}

NT2_TEST_CASE_TPL ( as_subscript_3D
                  , (nt2::int32_t)(nt2::uint32_t)(nt2::int64_t)(nt2::uint64_t)
                  )
{
  typedef typename boost::dispatch::meta::as_unsigned<T>::type idx_t;
  using boost::fusion::make_vector;
  using boost::mpl::int_;

  for(std::size_t k=0;k<5;++k)
    for(std::size_t j=0;j<2;++j)
      for(std::size_t i=0;i<3;++i)
      {
        boost::array<idx_t, 3>
        a = nt2::as_subscript ( make_vector(idx_t(3),idx_t(2),idx_t(5))
                              , idx_t(i + 3*(j+2*k))
                              );

        NT2_TEST_EQUAL( a[0], idx_t(i) );
        NT2_TEST_EQUAL( a[1], idx_t(j) );
        NT2_TEST_EQUAL( a[2], idx_t(k) );
      }
}

NT2_TEST_CASE_TPL ( as_subscript_3D_simd
                  , (nt2::int32_t)(nt2::uint32_t)(nt2::int64_t)(nt2::uint64_t)
                  )
{
  using boost::simd::meta::vector_of;
  using boost::fusion::make_vector;
  using boost::mpl::int_;

  typedef typename vector_of<T, BOOST_SIMD_BYTES/sizeof(T)>::type idx_t;
  typedef typename boost::dispatch::meta::as_unsigned<idx_t>::type sidx_t;
  static const std::size_t sz = boost::simd::meta::cardinal_of<idx_t>::value;

  for(std::size_t k=0;k<5;++k)
  {
    for(std::size_t j=0;j<2;++j)
    {
      boost::array<sidx_t, 3>
      a = nt2::as_subscript ( make_vector(sz,2,5)
                            , nt2::arith<idx_t>(sz*(j+2*k),1)
                            );

      for(std::size_t n=0;n<sz;++n)
      {
        NT2_TEST_EQUAL( a[0][n], n );
        NT2_TEST_EQUAL( a[1][n], j );
        NT2_TEST_EQUAL( a[2][n], k );
      }
    }
  }
}


NT2_TEST_CASE_TPL ( as_subscript_4D
                  , (nt2::int32_t)(nt2::uint32_t)(nt2::int64_t)(nt2::uint64_t)
                  )
{
  typedef typename boost::dispatch::meta::as_unsigned<T>::type idx_t;
  using boost::fusion::make_vector;
  using boost::mpl::int_;

  for(int l=0;l<3;++l)
    for(std::size_t k=0;k<5;++k)
      for(std::size_t j=0;j<2;++j)
        for(std::size_t i=0;i<3;++i)
        {
          boost::array<idx_t, 4>
          a = nt2::as_subscript ( make_vector(idx_t(3),idx_t(2),idx_t(5),idx_t(3))
                                , idx_t(i + 3*(j+2*(k+5*l)))
                                );

          NT2_TEST_EQUAL( a[0], idx_t(i) );
          NT2_TEST_EQUAL( a[1], idx_t(j) );
          NT2_TEST_EQUAL( a[2], idx_t(k) );
          NT2_TEST_EQUAL( a[3], idx_t(l) );
      }
}

NT2_TEST_CASE_TPL( as_subscript_4D_simd, (nt2::int32_t)(nt2::uint32_t)(nt2::int64_t)(nt2::uint64_t) )
{
  using boost::simd::meta::vector_of;
  using boost::fusion::make_vector;
  using boost::mpl::int_;

  typedef typename vector_of<T, BOOST_SIMD_BYTES/sizeof(T)>::type idx_t;
  typedef typename boost::dispatch::meta::as_unsigned<idx_t>::type sidx_t;
  static const std::size_t sz = boost::simd::meta::cardinal_of<idx_t>::value;

  for(std::size_t l=0;l<3;++l)
  {
    for(std::size_t k=0;k<5;++k)
    {
      for(std::size_t j=0;j<2;++j)
      {
        boost::array<sidx_t, 4>
        a = nt2::as_subscript ( make_vector(sz,2,5,3)
                              , nt2::arith<idx_t>(sz*(j+2*(k+5*l)),1)
                              );

        for(std::size_t n=0;n<sz;++n)
        {
          NT2_TEST_EQUAL( a[0][n], n );
          NT2_TEST_EQUAL( a[1][n], j );
          NT2_TEST_EQUAL( a[2][n], k );
          NT2_TEST_EQUAL( a[3][n], l );
        }
      }
    }
  }
}

NT2_TEST_CASE_TPL ( as_subscript_empty
                  , (nt2::int32_t)(nt2::uint32_t)(nt2::int64_t)(nt2::uint64_t)
                  )
{
  typedef typename boost::dispatch::meta::as_unsigned<T>::type idx_t;
  using boost::fusion::make_vector;
  using boost::mpl::int_;

  boost::array<idx_t, 1>
  a1 = nt2::as_subscript( make_vector(idx_t(0)), idx_t(0) );

  NT2_TEST_EQUAL( a1[0], idx_t(0) );

  boost::array<idx_t, 2>
  a2 = nt2::as_subscript( make_vector(idx_t(0),idx_t(1)), idx_t(0) );

  NT2_TEST_EQUAL( a2[0], idx_t(0) );
  NT2_TEST_EQUAL( a2[1], idx_t(0) );

  boost::array<idx_t, 3>
  a3 = nt2::as_subscript( make_vector(idx_t(0),idx_t(1),idx_t(1)), idx_t(0) );

  NT2_TEST_EQUAL( a3[0], idx_t(0) );
  NT2_TEST_EQUAL( a3[1], idx_t(0) );
  NT2_TEST_EQUAL( a3[2], idx_t(0) );

  boost::array<idx_t, 4>
  a4 = nt2::as_subscript( make_vector(idx_t(0),idx_t(1),idx_t(1),idx_t(1)), idx_t(0) );

  NT2_TEST_EQUAL( a4[0], idx_t(0) );
  NT2_TEST_EQUAL( a4[1], idx_t(0) );
  NT2_TEST_EQUAL( a4[2], idx_t(0) );
  NT2_TEST_EQUAL( a4[3], idx_t(0) );
}
