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

template< typename T, int IA, int IB, int IC, int ID
                    , int IE, int IF, int IG, int IH
        >
inline void unary_shuffle()
{
  using boost::simd::shuffle;
  using boost::simd::meta::vector_of;
  typedef BOOST_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef typename vector_of<T,8>::type    vT;

  vT ref, a;

  a[0] = boost::simd::Valmax<T>();
  a[1] = T(66);
  a[2] = T(99);
  a[3] = T(55);
  a[4] = T(-1);
  a[5] = T(77);
  a[6] = T(23);
  a[7] = boost::simd::Valmin<T>();

  ref[0] = (IA == -1) ? 0 : a[IA];
  ref[1] = (IB == -1) ? 0 : a[IB];
  ref[2] = (IC == -1) ? 0 : a[IC];
  ref[3] = (ID == -1) ? 0 : a[ID];
  ref[4] = (IE == -1) ? 0 : a[IE];
  ref[5] = (IF == -1) ? 0 : a[IF];
  ref[6] = (IG == -1) ? 0 : a[IG];
  ref[7] = (IH == -1) ? 0 : a[IH];

  NT2_TEST_EQUAL( (shuffle<IA,IB,IC,ID,IE,IF,IG,IH>(a)), ref);
}

template< typename T, int IA, int IB, int IC, int ID
                    , int IE, int IF, int IG, int IH
        >
inline void binary_shuffle()
{
  using boost::simd::shuffle;
  using boost::simd::meta::vector_of;
  typedef BOOST_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef typename vector_of<T,8>::type    vT;

  vT ref, a, b;

  a[0] = boost::simd::Valmax<T>();
  a[1] = T(66);
  a[2] = T(99);
  a[3] = T(55);
  a[4] = T(-1);
  a[5] = T(77);
  a[6] = T(23);
  a[7] = boost::simd::Valmin<T>();

  b[0] = T(1);
  b[1] = T(22);
  b[2] = boost::simd::Valmax<T>();
  b[3] = T(55);
  b[4] = T(-7);
  b[5] = boost::simd::Valmin<T>();
  b[6] = T(42);
  b[7] = T(-1);

  ref[0] = (IA == -1) ? 0 : (IA<8 ? a[IA] : b[IA-8]);
  ref[1] = (IB == -1) ? 0 : (IB<8 ? a[IB] : b[IB-8]);
  ref[2] = (IC == -1) ? 0 : (IC<8 ? a[IC] : b[IC-8]);
  ref[3] = (ID == -1) ? 0 : (ID<8 ? a[ID] : b[ID-8]);
  ref[4] = (IE == -1) ? 0 : (IE<8 ? a[IE] : b[IE-8]);
  ref[5] = (IF == -1) ? 0 : (IF<8 ? a[IF] : b[IF-8]);
  ref[6] = (IG == -1) ? 0 : (IG<8 ? a[IG] : b[IG-8]);
  ref[7] = (IH == -1) ? 0 : (IH<8 ? a[IH] : b[IH-8]);

  NT2_TEST_EQUAL( (shuffle<IA,IB,IC,ID,IE,IF,IG,IH>(a,b)), ref);
}

NT2_TEST_CASE_TPL( identity_shuffle, BOOST_SIMD_SIMD_TYPES)
{
  unary_shuffle <T, 0, 1, 2, 3, 4, 5, 6, 7>();
  binary_shuffle<T, 0, 1, 2, 3, 4, 5, 6, 7>();
  binary_shuffle<T, 8, 9,10,11,12,13,14,15>();
}

NT2_TEST_CASE_TPL( zero_shuffle, BOOST_SIMD_SIMD_TYPES)
{
  unary_shuffle <T,-1,-1,-1,-1,-1,-1,-1,-1>();
  binary_shuffle<T,-1,-1,-1,-1,-1,-1,-1,-1>();
}

NT2_TEST_CASE_TPL( reverse_shuffle, BOOST_SIMD_SIMD_TYPES)
{
  unary_shuffle <T,7 ,6 ,5 ,4 ,3 ,2 ,1,0>();
  binary_shuffle<T,7 ,6 ,5 ,4 ,3 ,2 ,1,0>();
  binary_shuffle<T,15,14,13,12,11,10,9,8>();
}

NT2_TEST_CASE_TPL( interleave_shuffle, BOOST_SIMD_SIMD_TYPES)
{
  unary_shuffle <T, 0, 0, 1, 1, 2, 2, 3, 3>();
  binary_shuffle<T, 0, 0, 1, 1, 2, 2, 3, 3>();
  unary_shuffle <T, 4, 4, 5, 5, 6, 6, 7, 7>();
  binary_shuffle<T, 4, 4, 5, 5, 6, 6, 7, 7>();
  binary_shuffle<T, 8, 8, 9, 9,10,10,11,11>();
  binary_shuffle<T,12,12,13,13,14,14,15,15>();
  binary_shuffle<T, 0, 8, 1, 9, 2,10, 3,11>();
  binary_shuffle<T, 4,12, 5,13, 6,14, 7,15>();
}

NT2_TEST_CASE_TPL( broadcast_shuffle, BOOST_SIMD_SIMD_TYPES)
{
  unary_shuffle <T,0,0,0,0,0,0,0,0>();
  unary_shuffle <T,1,1,1,1,1,1,1,1>();
  unary_shuffle <T,2,2,2,2,2,2,2,2>();
  unary_shuffle <T,3,3,3,3,3,3,3,3>();
  unary_shuffle <T,4,4,4,4,4,4,4,4>();
  unary_shuffle <T,5,5,5,5,5,5,5,5>();
  unary_shuffle <T,6,6,6,6,6,6,6,6>();
  unary_shuffle <T,7,7,7,7,7,7,7,7>();
  binary_shuffle<T,0,0,0,0,0,0,0,0>();
  binary_shuffle<T,1,1,1,1,1,1,1,1>();
  binary_shuffle<T,2,2,2,2,2,2,2,2>();
  binary_shuffle<T,3,3,3,3,3,3,3,3>();
  binary_shuffle<T,4,4,4,4,4,4,4,4>();
  binary_shuffle<T,5,5,5,5,5,5,5,5>();
  binary_shuffle<T,6,6,6,6,6,6,6,6>();
  binary_shuffle<T,7,7,7,7,7,7,7,7>();
  binary_shuffle<T,8,8,8,8,8,8,8,8>();
  binary_shuffle<T,9,9,9,9,9,9,9,9>();
  binary_shuffle<T,10,10,10,10,10,10,10,10>();
  binary_shuffle<T,11,11,11,11,11,11,11,11>();
  binary_shuffle<T,12,12,12,12,12,12,12,12>();
  binary_shuffle<T,13,13,13,13,13,13,13,13>();
  binary_shuffle<T,14,14,14,14,14,14,14,14>();
  binary_shuffle<T,15,15,15,15,15,15,15,15>();
}

NT2_TEST_CASE_TPL( repeat_shuffle, BOOST_SIMD_SIMD_TYPES)
{
  unary_shuffle <T, 0, 1, 2, 3, 0, 1, 2, 3>();
  unary_shuffle <T, 4, 5, 6, 7, 4, 5, 6, 7>();
  binary_shuffle<T, 0, 1, 2, 3, 0, 1, 2, 3>();
  binary_shuffle<T, 4, 5, 6, 7, 4, 5, 6, 7>();

  binary_shuffle<T, 8, 9,10,11, 8, 9,10,11>();
  binary_shuffle<T,12,13,14,15,12,13,14,15>();
}

NT2_TEST_CASE_TPL( avx_shuffle, BOOST_SIMD_SIMD_TYPES)
{
  unary_shuffle <T, 0, 0, 2, 2, 4, 4, 6, 6>();
  binary_shuffle<T, 0, 0, 2, 2, 4, 4, 6, 6>();
  binary_shuffle<T, 8, 8,10,10,12,12,14,14>();

  unary_shuffle <T, 1, 1, 3, 3, 5, 5, 7, 7>();
  binary_shuffle<T, 1, 1, 3, 3, 5, 5, 7, 7>();
  binary_shuffle<T, 9, 9,11,11,13,13,15,15>();


  binary_shuffle<T, 0, 3,8,11,4,7,12,15>();
}
