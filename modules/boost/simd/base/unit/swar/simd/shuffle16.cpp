//==============================================================================
//         Copyright 2014 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2014 MetaScale SAS
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
#include <nt2/sdk/unit/tests.hpp>

#include <nt2/sdk/unit/tests/relation.hpp>

template< typename T, int IA, int IB, int IC, int ID
                    , int IE, int IF, int IG, int IH
                    , int II, int IJ, int IK, int IL
                    , int IM, int IN, int IO, int IP
        >
inline void unary_shuffle()
{
  using boost::simd::shuffle;
  using boost::simd::meta::vector_of;
  typedef typename vector_of<T,16>::type    vT;

  vT ref, a;

  a[0] = boost::simd::Valmax<T>();
  a[1] = T(66);
  a[2] = T(99);
  a[3] = T(55);
  a[4] = T(-1);
  a[5] = T(77);
  a[6] = T(23);
  a[7] = T(37);
  a[8] = T(86);
  a[9] = T(43);
  a[10] = T(98);
  a[11] = T(33);
  a[12] = T(21);
  a[13] = T(75);
  a[14] = T(32);
  a[15] = boost::simd::Valmin<T>();

  std::size_t ia = static_cast<std::size_t>(IA);
  std::size_t ib = static_cast<std::size_t>(IB);
  std::size_t ic = static_cast<std::size_t>(IC);
  std::size_t id = static_cast<std::size_t>(ID);
  std::size_t ie = static_cast<std::size_t>(IE);
  std::size_t jf = static_cast<std::size_t>(IF);
  std::size_t ig = static_cast<std::size_t>(IG);
  std::size_t ih = static_cast<std::size_t>(IH);
  std::size_t ii = static_cast<std::size_t>(II);
  std::size_t ij = static_cast<std::size_t>(IJ);
  std::size_t ik = static_cast<std::size_t>(IK);
  std::size_t il = static_cast<std::size_t>(IL);
  std::size_t im = static_cast<std::size_t>(IM);
  std::size_t in = static_cast<std::size_t>(IN);
  std::size_t io = static_cast<std::size_t>(IO);
  std::size_t ip = static_cast<std::size_t>(IP);

  ref[0] = (IA == -1) ? T(0) : T(a[ia]);
  ref[1] = (IB == -1) ? T(0) : T(a[ib]);
  ref[2] = (IC == -1) ? T(0) : T(a[ic]);
  ref[3] = (ID == -1) ? T(0) : T(a[id]);
  ref[4] = (IE == -1) ? T(0) : T(a[ie]);
  ref[5] = (IF == -1) ? T(0) : T(a[jf]);
  ref[6] = (IG == -1) ? T(0) : T(a[ig]);
  ref[7] = (IH == -1) ? T(0) : T(a[ih]);
  ref[8] = (II == -1) ? T(0) : T(a[ii]);
  ref[9] = (IJ == -1) ? T(0) : T(a[ij]);
  ref[10] = (IK == -1) ? T(0) : T(a[ik]);
  ref[11] = (IL == -1) ? T(0) : T(a[il]);
  ref[12] = (IM == -1) ? T(0) : T(a[im]);
  ref[13] = (IN == -1) ? T(0) : T(a[in]);
  ref[14] = (IO == -1) ? T(0) : T(a[io]);
  ref[15] = (IP == -1) ? T(0) : T(a[ip]);

  NT2_TEST_EQUAL( (shuffle<IA,IB,IC,ID,IE,IF,IG,IH,II,IJ,IK,IL,IM,IN,IO,IP>(a)), ref/*,1*/);
}

NT2_TEST_CASE_TPL( mic_shuffle, BOOST_SIMD_SIMD_TYPES)
{

  unary_shuffle <T, 1, 1, 3, 3, 5, 5, 7, 7, 9, 9,11,11,13,13,15,15>();
  unary_shuffle <T, 2,2,3,3,6,6,7,7,10,10,11,11,14,14,15,15>();
  unary_shuffle <T, 2,2,4,4,6,6,7,7,10,10,11,11,14,14,15,15>();
  unary_shuffle <T, 4,5,6,7,4,5,6,7,8,9,10,11,8,9,10,11>();
  unary_shuffle <T, 0,1,3,2,4,5,7,6,8,9,11,10,12,13,15,14>();
  unary_shuffle <T, -1,1,3,2,4,5,7,6,8,9,11,10,12,13,15,14>();

  // move{h/l}
  unary_shuffle <T, 0, 0, 2, 2, 4, 4, 6, 6, 8, 8, 10, 10, 12, 12, 14, 14>();
  unary_shuffle<T,1,0,3,2,5,4,7,6,9,8,11,10,13,12,15,14>();
  unary_shuffle<T,2,3,0,1,6,7,4,5,10,11,8,9,14,15,12,13>();
  unary_shuffle<T,0,0,0,0,4,4,4,4,8,8,8,8,12,12,12,12>();
  unary_shuffle<T,1,1,1,1,5,5,5,5,9,9,9,9,13,13,13,13>();
  unary_shuffle<T,2,2,2,2,6,6,6,6,10,10,10,10,14,14,14,14>();
  unary_shuffle<T,3,3,3,3,7,7,7,7,11,11,11,11,15,15,15,15>();
  unary_shuffle<T,1,2,0,3,5,6,4,7,9,10,8,11,13,14,12,15>();

  unary_shuffle <T, 1, 1, 3, 3, 5, 5, 7, 7, 9, 9,11,11,13,13,15,15>();
}
