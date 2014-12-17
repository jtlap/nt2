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

template<typename T, int IA, int IB> void unary_shuffle()
{
  using boost::simd::shuffle;
  using boost::simd::meta::vector_of;
  typedef typename vector_of<T,2>::type    vT;

  vT ref, a;

  a[0] = boost::simd::Valmax<T>();
  a[1] = T(66);

  std::size_t ia = static_cast<std::size_t>(IA);
  std::size_t ib = static_cast<std::size_t>(IB);

  ref[0] = (IA == -1) ? T(0) : a[ia];
  ref[1] = (IB == -1) ? T(0) : a[ib];

  NT2_TEST_EQUAL( (shuffle<IA,IB>(a)), ref);
}

template<typename T, int IA, int IB> void binary_shuffle()
{
  using boost::simd::shuffle;
  using boost::simd::meta::vector_of;
  typedef typename vector_of<T,2>::type    vT;

  vT ref, a, b;

  a[0] = boost::simd::Valmax<T>();
  a[1] = T(66);

  b[0] = T(99);
  b[1] = boost::simd::Valmin<T>();

  std::size_t ia = static_cast<std::size_t>(IA);
  std::size_t ib = static_cast<std::size_t>(IB);

  ref[0] = (IA == -1) ? T(0) : (IA<2 ? a[ia] : b[ia-2]);
  ref[1] = (IB == -1) ? T(0) : (IB<2 ? a[ib] : b[ib-2]);;

  NT2_TEST_EQUAL( (shuffle<IA,IB>(a,b)), ref);
}

NT2_TEST_CASE_TPL( identity_shuffle, BOOST_SIMD_SIMD_TYPES)
{
  unary_shuffle <T, 0, 1>();
  binary_shuffle<T, 0, 1>();
  binary_shuffle<T, 2, 3>();
}

NT2_TEST_CASE_TPL( zero_shuffle, BOOST_SIMD_SIMD_TYPES)
{
  unary_shuffle<T,-1,-1>();
  binary_shuffle<T,-1,-1>();
}

NT2_TEST_CASE_TPL( unary_shuffle, BOOST_SIMD_SIMD_TYPES)
{
  unary_shuffle<T, 0, 0>();
  unary_shuffle<T, 0,-1>();
  unary_shuffle<T, 1, 0>();
  unary_shuffle<T, 1, 1>();
  unary_shuffle<T, 1,-1>();
  unary_shuffle<T,-1, 0>();
  unary_shuffle<T,-1, 1>();
}

NT2_TEST_CASE_TPL( binary_shuffle_over_a0, BOOST_SIMD_SIMD_TYPES)
{
  // All is A
  binary_shuffle<T, 0, 0>();
  binary_shuffle<T, 0,-1>();
  binary_shuffle<T, 1, 0>();
  binary_shuffle<T, 1, 1>();
  binary_shuffle<T, 1,-1>();
  binary_shuffle<T,-1, 0>();
  binary_shuffle<T,-1, 1>();
}

NT2_TEST_CASE_TPL( binary_shuffle_over_a1, BOOST_SIMD_SIMD_TYPES)
{
  // All is b
  binary_shuffle<T, 2, 2>();
  binary_shuffle<T, 2,-1>();
  binary_shuffle<T, 3, 2>();
  binary_shuffle<T, 3, 3>();
  binary_shuffle<T, 3,-1>();
  binary_shuffle<T,-1, 2>();
  binary_shuffle<T,-1, 3>();
}

NT2_TEST_CASE_TPL( mixed_binary_shuffle, BOOST_SIMD_SIMD_TYPES)
{
  // Mixed a/b
  binary_shuffle<T, 0, 2>();
  binary_shuffle<T, 0, 3>();
  binary_shuffle<T, 1, 2>();
  binary_shuffle<T, 1, 3>();
  binary_shuffle<T, 2, 0>();
  binary_shuffle<T, 2, 1>();
  binary_shuffle<T, 3, 0>();
  binary_shuffle<T, 3, 1>();
}
