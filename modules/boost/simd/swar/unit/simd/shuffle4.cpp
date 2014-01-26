//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <boost/simd/swar/include/functions/shuffle.hpp>
#include <boost/simd/include/constants/valmax.hpp>
#include <boost/simd/include/constants/valmin.hpp>
#include <boost/simd/sdk/simd/native.hpp>
#include <boost/simd/sdk/simd/io.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>

template<typename T, int IA, int IB, int IC, int ID>
inline void unary_shuffle()
{
  using boost::simd::shuffle;
  using boost::simd::meta::vector_of;
  typedef BOOST_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef typename vector_of<T,4>::type    vT;

  vT ref, a;

  a[0] = boost::simd::Valmax<T>();
  a[1] = T(66);
  a[2] = T(99);
  a[3] = boost::simd::Valmin<T>();

  ref[0] = (IA == -1) ? 0 : a[IA];
  ref[1] = (IB == -1) ? 0 : a[IB];
  ref[2] = (IC == -1) ? 0 : a[IC];
  ref[3] = (ID == -1) ? 0 : a[ID];

  NT2_TEST_EQUAL( (shuffle<IA,IB,IC,ID>(a)), ref);
}

template<typename T, int IA, int IB, int IC, int ID>
inline void binary_shuffle()
{
  using boost::simd::shuffle;
  using boost::simd::meta::vector_of;
  typedef BOOST_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef typename vector_of<T,4>::type    vT;

  vT ref, a, b;

  a[0] = boost::simd::Valmax<T>();
  a[1] = T(66);
  a[2] = T(99);
  a[3] = boost::simd::Valmin<T>();

  b[0] = T(77);
  b[1] = boost::simd::Valmin<T>();
  b[2] = boost::simd::Valmax<T>();
  b[3] = T(44);

  ref[0] = (IA == -1) ? 0 : (IA<4 ? a[IA] : b[IA-4]);
  ref[1] = (IB == -1) ? 0 : (IB<4 ? a[IB] : b[IB-4]);;
  ref[2] = (IC == -1) ? 0 : (IC<4 ? a[IC] : b[IC-4]);;
  ref[3] = (ID == -1) ? 0 : (ID<4 ? a[ID] : b[ID-4]);;

  NT2_TEST_EQUAL( (shuffle<IA,IB,IC,ID>(a,b)), ref);
}

NT2_TEST_CASE_TPL( identity_shuffle, BOOST_SIMD_SIMD_TYPES)
{
  unary_shuffle <T, 0, 1, 2, 3>();
  binary_shuffle<T, 0, 1, 2, 3>();
  binary_shuffle<T, 4, 5, 6, 7>();
}

NT2_TEST_CASE_TPL( zero_shuffle, BOOST_SIMD_SIMD_TYPES)
{
  unary_shuffle<T,-1,-1,-1,-1>();
  binary_shuffle<T,-1,-1,-1,-1>();
}

NT2_TEST_CASE_TPL( reverse_shuffle, BOOST_SIMD_SIMD_TYPES)
{
  unary_shuffle <T,3,2,1,0>();
  binary_shuffle<T,7,6,5,4>();
}

NT2_TEST_CASE_TPL( interleave_shuffle, BOOST_SIMD_SIMD_TYPES)
{
  unary_shuffle <T, 0, 0, 1, 1>();
  binary_shuffle<T, 0, 0, 1, 1>();

  unary_shuffle <T, 0,-1, 1,-1>();
  binary_shuffle<T, 0,-1, 1,-1>();

  unary_shuffle <T,-1, 0,-1, 1>();
  binary_shuffle<T,-1, 0,-1, 1>();

  unary_shuffle <T, 2, 2, 3, 3>();
  unary_shuffle <T, 2,-1, 3,-1>();
  unary_shuffle <T,-1, 2,-1, 3>();

  binary_shuffle<T, 2, 2, 3, 3>();
  binary_shuffle<T, 2,-1, 3,-1>();
  binary_shuffle<T,-1, 2,-1, 3>();

  binary_shuffle<T, 4, 4, 5, 5>();
  binary_shuffle<T,-1, 4,-1, 5>();
  binary_shuffle<T, 4,-1, 5,-1>();

  binary_shuffle<T, 6, 6, 7, 7>();
  binary_shuffle<T,-1, 6,-1, 7>();
  binary_shuffle<T, 6,-1, 7,-1>();

  binary_shuffle<T,0,4,1,5>();
  binary_shuffle<T,2,6,3,7>();
  binary_shuffle<T,0,4,2,6>();
  binary_shuffle<T,1,5,3,7>();
  binary_shuffle<T,0,2,4,6>();
  binary_shuffle<T,1,3,5,7>();
}

NT2_TEST_CASE_TPL( broadcast_shuffle, BOOST_SIMD_SIMD_TYPES)
{
  unary_shuffle <T,0,0,0,0>();
  unary_shuffle <T,1,1,1,1>();
  unary_shuffle <T,2,2,2,2>();
  unary_shuffle <T,3,3,3,3>();
  binary_shuffle<T,0,0,0,0>();
  binary_shuffle<T,1,1,1,1>();
  binary_shuffle<T,2,2,2,2>();
  binary_shuffle<T,3,3,3,3>();
  binary_shuffle<T,4,4,4,4>();
  binary_shuffle<T,5,5,5,5>();
  binary_shuffle<T,6,6,6,6>();
  binary_shuffle<T,7,7,7,7>();
}

NT2_TEST_CASE_TPL( repeat_shuffle, BOOST_SIMD_SIMD_TYPES)
{
  unary_shuffle <T, 0, 1, 0, 1>();
  unary_shuffle <T, 2, 3, 2, 3>();
  binary_shuffle<T, 0, 1, 0, 1>();
  binary_shuffle<T, 2, 3, 2, 3>();
  binary_shuffle<T, 4, 5, 4, 5>();
  binary_shuffle<T, 6, 7, 6, 7>();
}

NT2_TEST_CASE_TPL( sse2_style_shuffle, BOOST_SIMD_SIMD_TYPES)
{
  unary_shuffle <T,-1,-1, 0, 1>();
  binary_shuffle<T,-1,-1, 0, 1>();

  unary_shuffle <T, 0, 1,-1,-1>();
  binary_shuffle<T, 0, 1,-1,-1>();

  unary_shuffle <T,-1,-1, 2, 3>();
  binary_shuffle<T,-1,-1, 2, 3>();

  unary_shuffle <T, 2, 3,-1,-1>();
  binary_shuffle<T, 2, 3,-1,-1>();

  binary_shuffle<T,-1,-1, 4, 5>();
  binary_shuffle<T, 4, 5,-1,-1>();

  binary_shuffle<T,-1,-1, 6, 7>();
  binary_shuffle<T, 6, 7,-1,-1>();

  binary_shuffle<T,0,1,4,5>();
  binary_shuffle<T,2,3,6,7>();
  binary_shuffle<T,6,7,2,3>();
  binary_shuffle<T,4,5,0,1>();
}

NT2_TEST_CASE_TPL( avx_style_shuffle, BOOST_SIMD_SIMD_TYPES)
{
  unary_shuffle <T, 0, 0, 2, 2>();
  binary_shuffle<T, 0, 0, 2, 2>();

  unary_shuffle <T, 1,-1, 2,-1>();
  binary_shuffle<T, 1,-1, 2,-1>();

  unary_shuffle <T,-1, 0,-1, 2>();
  binary_shuffle<T,-1, 0,-1, 2>();

  binary_shuffle<T, 4, 4, 6, 6>();

  binary_shuffle<T, 1, 4, 2, 6>();
  binary_shuffle<T, 1, 0, 2, 2>();
}

NT2_TEST_CASE_TPL( avx_zero_shuffle, BOOST_SIMD_SIMD_TYPES)
{
  unary_shuffle<T,0,-1,2,-1>();
  unary_shuffle<T,0,-1,3,-1>();
  unary_shuffle<T,1,-1,3,-1>();
  unary_shuffle<T,1,-1,2,-1>();

  binary_shuffle<T,0,-1,2,-1>();
  binary_shuffle<T,0,-1,3,-1>();
  binary_shuffle<T,1,-1,2,-1>();
  binary_shuffle<T,1,-1,3,-1>();

  unary_shuffle<T,-1,0,-1,2>();
  unary_shuffle<T,-1,0,-1,3>();
  unary_shuffle<T,-1,1,-1,2>();
  unary_shuffle<T,-1,1,-1,3>();

  binary_shuffle<T,-1,0,-1,2>();
  binary_shuffle<T,-1,0,-1,3>();
  binary_shuffle<T,-1,1,-1,2>();
  binary_shuffle<T,-1,1,-1,3>();

  binary_shuffle<T,4,-1,6,-1>();
  binary_shuffle<T,4,-1,7,-1>();
  binary_shuffle<T,5,-1,6,-1>();
  binary_shuffle<T,5,-1,7,-1>();

  binary_shuffle<T,-1,4,-1,6>();
  binary_shuffle<T,-1,4,-1,7>();
  binary_shuffle<T,-1,5,-1,6>();
  binary_shuffle<T,-1,5,-1,7>();

}

NT2_TEST_CASE_TPL( other_shuffle, BOOST_SIMD_SIMD_TYPES)
{
  binary_shuffle<T,0,7,2,6>();
  binary_shuffle<T,0,3,7,4>();
  binary_shuffle<T,7,4,0,3>();

  binary_shuffle<T,0,-1,2,6>();
  binary_shuffle<T,0,3,7,-1>();

  binary_shuffle<T,7,4,-1,3>();
}
