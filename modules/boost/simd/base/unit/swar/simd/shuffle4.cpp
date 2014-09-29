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
  typedef typename vector_of<T,4>::type    vT;

  vT ref, a;

  a[0] = boost::simd::Valmax<T>();
  a[1] = T(66);
  a[2] = T(99);
  a[3] = boost::simd::Valmin<T>();

  std::size_t ia = static_cast<std::size_t>(IA);
  std::size_t ib = static_cast<std::size_t>(IB);
  std::size_t ic = static_cast<std::size_t>(IC);
  std::size_t id = static_cast<std::size_t>(ID);

  ref[0] = (IA == -1) ? T(0) : a[ia];
  ref[1] = (IB == -1) ? T(0) : a[ib];
  ref[2] = (IC == -1) ? T(0) : a[ic];
  ref[3] = (ID == -1) ? T(0) : a[id];

  NT2_TEST_EQUAL( (shuffle<IA,IB,IC,ID>(a)), ref);
}

template<typename T, int IA, int IB, int IC, int ID>
inline void binary_shuffle()
{
  using boost::simd::shuffle;
  using boost::simd::meta::vector_of;
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

  std::size_t ia = static_cast<std::size_t>(IA);
  std::size_t ib = static_cast<std::size_t>(IB);
  std::size_t ic = static_cast<std::size_t>(IC);
  std::size_t id = static_cast<std::size_t>(ID);

  ref[0] = (IA == -1) ? T(0) : (IA<4 ? a[ia] : b[ia-4]);
  ref[1] = (IB == -1) ? T(0) : (IB<4 ? a[ib] : b[ib-4]);;
  ref[2] = (IC == -1) ? T(0) : (IC<4 ? a[ic] : b[ic-4]);;
  ref[3] = (ID == -1) ? T(0) : (ID<4 ? a[id] : b[id-4]);;

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
  binary_shuffle<T, 4, 4, 6, 6>();

  // <0, 4, 2, 6> is interleave_even
  binary_shuffle<T, 4, 0, 6, 2>();
  // <0, 0, 2, 2> is just up

  binary_shuffle<T, 1, 4, 2, 6>();
  binary_shuffle<T, 5, 0, 6, 2>();
  unary_shuffle <T, 1, 0, 2, 2>();
  binary_shuffle<T, 1, 0, 2, 2>();

  binary_shuffle<T, 0, 5, 2, 6>();
  binary_shuffle<T, 4, 1, 6, 2>();
  unary_shuffle <T, 0, 1, 2, 2>();
  binary_shuffle<T, 0, 1, 2, 2>();

  binary_shuffle<T, 1,5,2,6>();
  binary_shuffle<T, 5,1,6,2>();
  unary_shuffle <T, 1,1,2,2>();
  binary_shuffle<T, 1,1,2,2>();

  binary_shuffle<T, 0,4,3,6>();
  binary_shuffle<T, 4,0,7,2>();
  unary_shuffle <T, 0,0,3,2>();
  binary_shuffle<T, 0,0,3,2>();

  binary_shuffle<T, 1,4,3,6>();
  binary_shuffle<T, 5,0,7,2>();
  unary_shuffle <T, 1,0,3,2>();
  binary_shuffle<T, 1,0,3,2>();

  binary_shuffle<T, 0,5,3,6>();
  binary_shuffle<T, 4,1,7,2>();
  unary_shuffle <T, 0,1,3,2>();
  binary_shuffle<T, 0,1,3,2>();

  binary_shuffle<T, 1,5,3,6>();
  binary_shuffle<T, 5,1,7,2>();
  unary_shuffle <T, 1,1,3,2>();
  binary_shuffle<T, 1,1,3,2>();

  binary_shuffle<T, 0,4,2,7>();
  binary_shuffle<T, 4,0,6,3>();
  unary_shuffle <T, 0,0,2,3>();
  binary_shuffle<T, 0,0,2,3>();

  binary_shuffle<T, 1,4,2,7>();
  binary_shuffle<T, 5,0,6,3>();
  unary_shuffle <T, 1,0,2,3>();
  binary_shuffle<T, 1,0,2,3>();

  binary_shuffle<T, 0,5,2,7>();
  binary_shuffle<T, 4,1,6,3>();
  // Dupe shuffle of <0 5 2 7> is <0 1 2 3>

  binary_shuffle<T, 1,5,2,7>();
  binary_shuffle<T, 5,1,6,3>();
  unary_shuffle <T, 1,1,2,3>();
  binary_shuffle<T, 1,1,2,3>();

  binary_shuffle<T, 0,4,3,7>();
  binary_shuffle<T, 4,0,7,3>();
  unary_shuffle <T, 0,0,3,3>();
  binary_shuffle<T, 0,0,3,3>();

  binary_shuffle<T, 1,4,3,7>();
  binary_shuffle<T, 5,0,7,3>();
  unary_shuffle <T, 1,0,3,3>();
  binary_shuffle<T, 1,0,3,3>();

  binary_shuffle<T, 0,5,3,7>();
  binary_shuffle<T, 4,1,7,3>();
  unary_shuffle <T, 0,1,3,3>();
  binary_shuffle<T, 0,1,3,3>();

  // <1,5,3,7> is interleave_odd
  binary_shuffle<T, 5,1,7,3>();
  unary_shuffle <T, 1,1,3,3>();
  binary_shuffle<T, 1,1,3,3>();
}

NT2_TEST_CASE_TPL( avx_zero_shuffle, BOOST_SIMD_SIMD_TYPES)
{
  unary_shuffle <T, 1,-1, 2,-1>();
  binary_shuffle<T, 1,-1, 2,-1>();
  binary_shuffle<T, 4,-1, 6,-1>();
  unary_shuffle <T,-1, 0,-1, 2>();
  binary_shuffle<T,-1, 0,-1, 2>();

  binary_shuffle<T,-1, 4,-1, 6>();
  unary_shuffle <T, 0,-1, 2,-1>();
  binary_shuffle<T, 0,-1, 2,-1>();
  binary_shuffle<T, 5,-1, 6,-1>();
  unary_shuffle <T,-1, 1,-1, 2>();
  binary_shuffle<T,-1, 1,-1, 2>();

  binary_shuffle<T,-1, 5,-1, 6>();
  unary_shuffle <T, 1,-1, 2,-1>();
  binary_shuffle<T, 1,-1, 2,-1>();
  binary_shuffle<T, 5,-1, 6,-1>();
  unary_shuffle <T,-1, 1,-1, 2>();
  binary_shuffle<T,-1, 1,-1, 2>();
  binary_shuffle<T,-1, 5,-1, 6>();
}

NT2_TEST_CASE_TPL( avx_blend_shuffle, BOOST_SIMD_SIMD_TYPES)
{
  binary_shuffle <T, 0, 1, 2, 7>();
  binary_shuffle <T, 0, 1, 6, 3>();
  binary_shuffle <T, 0, 5, 2, 3>();
  binary_shuffle <T, 4, 1, 2, 3>();

  binary_shuffle <T, 0, 1, 6, 7>();
  binary_shuffle <T, 0, 5, 6, 3>();
  binary_shuffle <T, 4, 5, 2, 3>();
  binary_shuffle <T, 0, 5, 2, 7>();
  binary_shuffle <T, 4, 1, 6, 3>();
  binary_shuffle <T, 4, 1, 2, 7>();

  binary_shuffle <T, 0, 5, 6, 7>();
  binary_shuffle <T, 4, 5, 6, 3>();
  binary_shuffle <T, 4, 5, 2, 7>();
  binary_shuffle <T, 4, 1, 6, 7>();

}
NT2_TEST_CASE_TPL( vmx_shuffle, BOOST_SIMD_SIMD_TYPES)
{
  // vec_slo
  binary_shuffle<T,1,2,3,4>();
  binary_shuffle<T,2,3,4,5>();
  binary_shuffle<T,3,4,5,6>();

  // vec_slo + zeroing
  unary_shuffle<T,1, 2, 3,-1>();
  unary_shuffle<T,2, 3,-1,-1>();
  unary_shuffle<T,3,-1,-1,-1>();
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
