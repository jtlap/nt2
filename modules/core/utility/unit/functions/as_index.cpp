/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#define NT2_UNIT_MODULE "nt2::as_index function"

#include <nt2/core/utility/as_index.hpp>
#include <nt2/include/functions/enumerate.hpp>

#include <boost/fusion/include/make_vector.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/basic.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>

NT2_TEST_CASE( as_index_0D )
{
  using nt2::as_index;
  using boost::fusion::make_vector;

  NT2_TEST_EQUAL( as_index( make_vector(), make_vector() ), 0u);
}

NT2_TEST_CASE( as_index_1D )
{
  using nt2::as_index;
  using boost::fusion::make_vector;

  NT2_TEST_EQUAL( as_index( make_vector(5), make_vector(0) ), 0u);
  NT2_TEST_EQUAL( as_index( make_vector(5), make_vector(1) ), 1u);
  NT2_TEST_EQUAL( as_index( make_vector(5), make_vector(2) ), 2u);
  NT2_TEST_EQUAL( as_index( make_vector(5), make_vector(3) ), 3u);
  NT2_TEST_EQUAL( as_index( make_vector(5), make_vector(4) ), 4u);
}

NT2_TEST_CASE_TPL ( as_index_1D_simd
                  , (nt2::int32_t)(nt2::uint32_t)(nt2::int64_t)(nt2::uint64_t)
                  )
{
  using nt2::as_index;
  using boost::simd::meta::vector_of;
  using boost::fusion::make_vector;
  using boost::mpl::int_;

  typedef typename vector_of<T, BOOST_SIMD_BYTES/sizeof(T)>::type idx_t;
  typedef typename boost::dispatch::meta::as_unsigned<idx_t>::type sidx_t;
  static const std::size_t sz = boost::simd::meta::cardinal_of<idx_t>::value;

  NT2_TEST_EQUAL( as_index( make_vector(16)
                          , make_vector(nt2::enumerate<idx_t>(0))
                          )
                , nt2::enumerate<sidx_t>(0)
                );
}

NT2_TEST_CASE( as_index_2D )
{
  using nt2::as_index;
  using boost::fusion::make_vector;

  NT2_TEST_EQUAL( as_index( make_vector(3,5), make_vector(0,0) ), 0u);
  NT2_TEST_EQUAL( as_index( make_vector(3,5), make_vector(1,0) ), 1u);
  NT2_TEST_EQUAL( as_index( make_vector(3,5), make_vector(2,0) ), 2u);

  NT2_TEST_EQUAL( as_index( make_vector(3,5), make_vector(0,1) ), 3u);
  NT2_TEST_EQUAL( as_index( make_vector(3,5), make_vector(1,1) ), 4u);
  NT2_TEST_EQUAL( as_index( make_vector(3,5), make_vector(2,1) ), 5u);

  NT2_TEST_EQUAL( as_index( make_vector(3,5), make_vector(0,2) ), 6u);
  NT2_TEST_EQUAL( as_index( make_vector(3,5), make_vector(1,2) ), 7u);
  NT2_TEST_EQUAL( as_index( make_vector(3,5), make_vector(2,2) ), 8u);

  NT2_TEST_EQUAL( as_index( make_vector(3,5), make_vector(0,3) ), 9u);
  NT2_TEST_EQUAL( as_index( make_vector(3,5), make_vector(1,3) ), 10u);
  NT2_TEST_EQUAL( as_index( make_vector(3,5), make_vector(2,3) ), 11u);

  NT2_TEST_EQUAL( as_index( make_vector(3,5), make_vector(0,4) ), 12u);
  NT2_TEST_EQUAL( as_index( make_vector(3,5), make_vector(1,4) ), 13u);
  NT2_TEST_EQUAL( as_index( make_vector(3,5), make_vector(2,4) ), 14u);
}

NT2_TEST_CASE( as_index_3D )
{
  using nt2::as_index;
  using boost::fusion::make_vector;

  NT2_TEST_EQUAL( as_index( make_vector(2,2,2), make_vector(0,0,0) ), 0u);
  NT2_TEST_EQUAL( as_index( make_vector(2,2,2), make_vector(1,0,0) ), 1u);

  NT2_TEST_EQUAL( as_index( make_vector(2,2,2), make_vector(0,1,0) ), 2u);
  NT2_TEST_EQUAL( as_index( make_vector(2,2,2), make_vector(1,1,0) ), 3u);

  NT2_TEST_EQUAL( as_index( make_vector(2,2,2), make_vector(0,0,1) ), 4u);
  NT2_TEST_EQUAL( as_index( make_vector(2,2,2), make_vector(1,0,1) ), 5u);

  NT2_TEST_EQUAL( as_index( make_vector(2,2,2), make_vector(0,1,1) ), 6u);
  NT2_TEST_EQUAL( as_index( make_vector(2,2,2), make_vector(1,1,1) ), 7u);
}

NT2_TEST_CASE( as_index_4D )
{
  using nt2::as_index;
  using boost::fusion::make_vector;

  NT2_TEST_EQUAL( as_index( make_vector(2,2,2,2), make_vector(0,0,0,0) ), 0u);
  NT2_TEST_EQUAL( as_index( make_vector(2,2,2,2), make_vector(1,0,0,0) ), 1u);

  NT2_TEST_EQUAL( as_index( make_vector(2,2,2,2), make_vector(0,1,0,0) ), 2u);
  NT2_TEST_EQUAL( as_index( make_vector(2,2,2,2), make_vector(1,1,0,0) ), 3u);

  NT2_TEST_EQUAL( as_index( make_vector(2,2,2,2), make_vector(0,0,1,0) ), 4u);
  NT2_TEST_EQUAL( as_index( make_vector(2,2,2,2), make_vector(1,0,1,0) ), 5u);

  NT2_TEST_EQUAL( as_index( make_vector(2,2,2,2), make_vector(0,1,1,0) ), 6u);
  NT2_TEST_EQUAL( as_index( make_vector(2,2,2,2), make_vector(1,1,1,0) ), 7u);

  NT2_TEST_EQUAL( as_index( make_vector(2,2,2,2), make_vector(0,0,0,1) ), 8u);
  NT2_TEST_EQUAL( as_index( make_vector(2,2,2,2), make_vector(1,0,0,1) ), 9u);

  NT2_TEST_EQUAL( as_index( make_vector(2,2,2,2), make_vector(0,1,0,1) ), 10u);
  NT2_TEST_EQUAL( as_index( make_vector(2,2,2,2), make_vector(1,1,0,1) ), 11u);

  NT2_TEST_EQUAL( as_index( make_vector(2,2,2,2), make_vector(0,0,1,1) ), 12u);
  NT2_TEST_EQUAL( as_index( make_vector(2,2,2,2), make_vector(1,0,1,1) ), 13u);

  NT2_TEST_EQUAL( as_index( make_vector(2,2,2,2), make_vector(0,1,1,1) ), 14u);
  NT2_TEST_EQUAL( as_index( make_vector(2,2,2,2), make_vector(1,1,1,1) ), 15u);
}
