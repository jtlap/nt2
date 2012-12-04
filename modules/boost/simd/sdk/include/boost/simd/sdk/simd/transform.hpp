//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_SDK_SIMD_TRANSFORM_HPP_INCLUDED
#define BOOST_SIMD_SDK_SIMD_TRANSFORM_HPP_INCLUDED

#include <boost/simd/sdk/simd/meta/unroll.hpp>

////////////////////////////////////////////////////////////////////////////////
// boost::simd::transform implementation
// N needs to be specified
////////////////////////////////////////////////////////////////////////////////

namespace boost{ namespace simd{

  //============================================================================
  // Unary operation version
  //============================================================================
  template<class SimdInputIterator, class SimdOutputIterator, class UnOp, int N>
  void transform( SimdInputIterator  begin, SimdInputIterator end
                , SimdOutputIterator out, UnOp f, meta::unroll<N> unroller)
  {
    unroller.apply(begin, end, out, f);
  }

  template<class SimdInputIterator, class SimdOutputIterator, class UnOp>
  void transform( SimdInputIterator  begin, SimdInputIterator end
                , SimdOutputIterator out, UnOp f)
  {
    meta::unroll<0>::apply(begin, end, out, f);
  }

  //============================================================================
  // Binary operation version
  //============================================================================
  template<class SimdInputIterator, class SimdOutputIterator, class BinOp, int N>
  void transform( SimdInputIterator  begin1, SimdInputIterator end
                , SimdInputIterator  begin2, SimdOutputIterator out
                , BinOp f, meta::unroll<N> unroller)
  {
    unroller.apply(begin1, begin2, end, out, f);
  }

  template<class SimdInputIterator, class SimdOutputIterator, class BinOp>
  void transform( SimdInputIterator  begin1, SimdInputIterator end
                , SimdInputIterator  begin2, SimdOutputIterator out
                , BinOp f)
  {
    meta::unroll<0>::apply(begin1, begin2, end, out, f);
  }

} }

#endif
