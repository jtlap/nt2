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

  std::size_t ia = static_cast<std::size_t>(IA);
  std::size_t ib = static_cast<std::size_t>(IB);
  std::size_t ic = static_cast<std::size_t>(IC);
  std::size_t id = static_cast<std::size_t>(ID);
  std::size_t ie = static_cast<std::size_t>(IE);
  std::size_t jf = static_cast<std::size_t>(IF);
  std::size_t ig = static_cast<std::size_t>(IG);
  std::size_t ih = static_cast<std::size_t>(IH);

  ref[0] = (IA == -1) ? T(0) : a[ia];
  ref[1] = (IB == -1) ? T(0) : a[ib];
  ref[2] = (IC == -1) ? T(0) : a[ic];
  ref[3] = (ID == -1) ? T(0) : a[id];
  ref[4] = (IE == -1) ? T(0) : a[ie];
  ref[5] = (IF == -1) ? T(0) : a[jf];
  ref[6] = (IG == -1) ? T(0) : a[ig];
  ref[7] = (IH == -1) ? T(0) : a[ih];

  NT2_TEST_EQUAL( (shuffle<IA,IB,IC,ID,IE,IF,IG,IH>(a)), ref);
}

template< typename T, int IA, int IB, int IC, int ID
                    , int IE, int IF, int IG, int IH
        >
inline void binary_shuffle()
{
  using boost::simd::shuffle;
  using boost::simd::meta::vector_of;
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

  std::size_t ia = static_cast<std::size_t>(IA);
  std::size_t ib = static_cast<std::size_t>(IB);
  std::size_t ic = static_cast<std::size_t>(IC);
  std::size_t id = static_cast<std::size_t>(ID);
  std::size_t ie = static_cast<std::size_t>(IE);
  std::size_t jf = static_cast<std::size_t>(IF);
  std::size_t ig = static_cast<std::size_t>(IG);
  std::size_t ih = static_cast<std::size_t>(IH);

  ref[0] = (IA == -1) ? T(0) : (IA<8 ? a[ia] : b[ia-8]);
  ref[1] = (IB == -1) ? T(0) : (IB<8 ? a[ib] : b[ib-8]);
  ref[2] = (IC == -1) ? T(0) : (IC<8 ? a[ic] : b[ic-8]);
  ref[3] = (ID == -1) ? T(0) : (ID<8 ? a[id] : b[id-8]);
  ref[4] = (IE == -1) ? T(0) : (IE<8 ? a[ie] : b[ie-8]);
  ref[5] = (IF == -1) ? T(0) : (IF<8 ? a[jf] : b[jf-8]);
  ref[6] = (IG == -1) ? T(0) : (IG<8 ? a[ig] : b[ig-8]);
  ref[7] = (IH == -1) ? T(0) : (IH<8 ? a[ih] : b[ih-8]);

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
  // perm2f128
  unary_shuffle <T,0, 1, 2, 3,-1,-1,-1,-1>();
  binary_shuffle<T,0, 1, 2, 3,-1,-1,-1,-1>();
  binary_shuffle<T,0, 1, 2, 3, 8, 9,10,11>();
  binary_shuffle<T,0, 1, 2, 3,12,13,14,15>();

  unary_shuffle <T, 4, 5, 6, 7, 0, 1, 2, 3>();
  binary_shuffle<T, 4, 5, 6, 7, 0, 1, 2, 3>();
  binary_shuffle<T, 4, 5, 6, 7,12,13,14,15>();

  binary_shuffle<T, 8, 9,10,11, 0, 1, 2, 3>();
  binary_shuffle<T, 8, 9,10,11, 4, 5, 6, 7>();

  binary_shuffle<T,12,13,14,15, 0, 1, 2, 3>();
  binary_shuffle<T,12,13,14,15, 4, 5, 6, 7>();
  binary_shuffle<T,12,13,14,15, 8, 9,10,11>();

  unary_shuffle <T,-1,-1,-1,-1, 0, 1, 2, 3>();
  binary_shuffle<T,-1,-1,-1,-1, 0, 1, 2, 3>();
  unary_shuffle <T,-1,-1,-1,-1, 4, 5, 6, 7>();
  binary_shuffle<T,-1,-1,-1,-1, 4, 5, 6, 7>();
  binary_shuffle<T,-1,-1,-1,-1, 8, 9,10,11>();
  binary_shuffle<T,-1,-1,-1,-1,12,13,14,15>();

  // move{h/l}
  unary_shuffle <T, 0, 0, 2, 2, 4, 4, 6, 6>();
  binary_shuffle<T, 0, 0, 2, 2, 4, 4, 6, 6>();
  binary_shuffle<T, 8, 8,10,10,12,12,14,14>();

  unary_shuffle <T, 1, 1, 3, 3, 5, 5, 7, 7>();
  binary_shuffle<T, 1, 1, 3, 3, 5, 5, 7, 7>();
  binary_shuffle<T, 9, 9,11,11,13,13,15,15>();

  // direct shuffle
  binary_shuffle<T,3,2,9,8,7,6,13,12>();

  // swapped shuffle
  binary_shuffle<T,9,8,3,2,13,12,7,6>();

  // duplicate shuffle
  binary_shuffle<T,3,2,0,1,7,6,4,5>();

  // right zeroing shuffle
  binary_shuffle<T,3,2,-1,-1,7,6,-1,-1>();

  // left zeroing shuffle
  binary_shuffle<T,-1,-1,9,8,-1,-1,13,12>();
}

NT2_TEST_CASE_TPL( vmx_shuffle, BOOST_SIMD_SIMD_TYPES)
{
  // vec_slo
  binary_shuffle<T, 1, 2, 3, 4, 5, 6, 7, 8>();
  binary_shuffle<T, 2, 3, 4, 5, 6, 7, 8, 9>();
  binary_shuffle<T, 3, 4, 5, 6, 7, 8, 9,10>();
  binary_shuffle<T, 4, 5, 6, 7, 8, 9,10,11>();
  binary_shuffle<T, 5, 6, 7, 8, 9,10,11,12>();
  binary_shuffle<T, 6, 7, 8, 9,10,11,12,13>();
  binary_shuffle<T, 7, 8, 9,10,11,12,13,14>();

  // vec_slo + zeroing
  unary_shuffle<T, 1, 2, 3, 4, 5, 6, 7,-1>();
  unary_shuffle<T, 2, 3, 4, 5, 6, 7,-1,-1>();
  unary_shuffle<T, 3, 4, 5, 6, 7,-1,-1,-1>();
  unary_shuffle<T, 4, 5, 6, 7,-1,-1,-1,-1>();
  unary_shuffle<T, 5, 6, 7,-1,-1,-1,-1,-1>();
  unary_shuffle<T, 6, 7,-1,-1,-1,-1,-1,-1>();
  unary_shuffle<T, 7,-1,-1,-1,-1,-1,-1,-1>();
}
