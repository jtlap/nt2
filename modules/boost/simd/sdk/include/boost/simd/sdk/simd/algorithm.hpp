//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_SDK_SIMD_ALGORITHM_HPP_INCLUDED
#define BOOST_SIMD_SDK_SIMD_ALGORITHM_HPP_INCLUDED

#include <boost/simd/sdk/native.hpp>
#include <boost/simd/include/functions/load.hpp>
#include <boost/simd/include/functions/store.hpp>
#include <boost/simd/include/functions/unaligned_load.hpp>
#include <boost/simd/include/functions/splat.hpp>
#include <boost/simd/sdk/memory/align_on.hpp>
#include <boost/mpl/assert.hpp>

namespace boost { namespace simd
{
  template<class T, class U, class UnOp>
  U* transform(T const* begin, T const* end, U* out, UnOp f)
  {
    typedef boost::simd::native<T, BOOST_SIMD_DEFAULT_EXTENSION> vT;
    typedef boost::simd::native<U, BOOST_SIMD_DEFAULT_EXTENSION> vU;

    BOOST_MPL_ASSERT_MSG( vT::static_size == vU::static_size
                        , BOOST_SIMD_TRANSFORM_INPUT_OUTPUT_NOT_SAME_SIZE
                        , (T, U)
                        );

    static const std::size_t N = vU::static_size;

    std::size_t shift = simd::align_on(out, N * sizeof(U)) - out;
    T const* end2 = begin + shift;
    T const* end3 = end2 + (end - end2)/N*N;

    // prologue
    for(; begin!=end2; ++begin, ++end)
      *out = f(*begin);

    for(; begin!=end3; begin += N, end += N)
      simd::store(f(simd::unaligned_load<vT>(begin)), out);

    // epilogue
    for(; begin!=end; ++begin, ++end)
      *out = f(*begin);

    return out;
  }

  template<class T1, class T2, class U, class BinOp>
  U* transform(T1 const* begin1, T1 const* end, T2 const* begin2, U* out, BinOp f)
  {
    typedef boost::simd::native<T1, BOOST_SIMD_DEFAULT_EXTENSION> vT1;
    typedef boost::simd::native<T2, BOOST_SIMD_DEFAULT_EXTENSION> vT2;
    typedef boost::simd::native<U, BOOST_SIMD_DEFAULT_EXTENSION> vU;

    BOOST_MPL_ASSERT_MSG( vT1::static_size == vT2::static_size == vU::static_size
                        , BOOST_SIMD_TRANSFORM_INPUT_OUTPUT_NOT_SAME_SIZE
                        , (T, U)
                        );

    static const std::size_t N = vU::static_size;

    std::size_t shift = simd::align_on(out, N * sizeof(U)) - out;
    T1 const* end2 = begin1 + shift;
    T1 const* end3 = end2 + (end - end2)/N*N;

    // prologue
    for(; begin1!=end2; ++begin1, ++begin2, ++end)
      *out = f(*begin1, *begin2);

    for(; begin1!=end3; begin1 += N, begin2 += N, end += N)
      simd::store(f(simd::unaligned_load<vT1>(begin1), simd::unaligned_load<vT2>(begin2)), out);

    // epilogue
    for(; begin1!=end; ++begin1, ++end)
      *out = f(*begin1, *begin2);

    return out;
  }

  template<class T, class U, class F>
  U accumulate(T const* begin, T const* end, U init, F f)
  {
    typedef boost::simd::native<T, BOOST_SIMD_DEFAULT_EXTENSION> vT;
    typedef boost::simd::native<U, BOOST_SIMD_DEFAULT_EXTENSION> vU;

    BOOST_MPL_ASSERT_MSG( vT::static_size == vU::static_size
                        , BOOST_SIMD_ACCUMULATE_INPUT_OUTPUT_NOT_SAME_SIZE
                        , (T, U)
                        );

    static const std::size_t N = vT::static_size;

    T const* end2 = simd::align_on(begin, N * sizeof(T));
    T const* end3 = end2 + (end - end2)/N*N;

    vU cur = simd::splat<vU>(init);

    // prologue
    for(; begin!=end2; ++begin)
      init = f(init, *begin);

    for(; begin!=end3; begin =+ N)
      cur = f(cur, boost::simd::load<vT>(begin));

    // reduce cur
    for(U const* b = cur.begin(); b != cur.end(); ++b)
      init = f(init, *b);

    // epilogue
    for(; begin!=end; ++begin)
      init = f(init, *begin);

    return init;
  }
} }

#endif
