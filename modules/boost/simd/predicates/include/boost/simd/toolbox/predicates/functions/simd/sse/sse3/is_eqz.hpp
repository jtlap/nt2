//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_TOOLBOX_PREDICATES_FUNCTIONS_SIMD_SSE_SSE3_IS_EQZ_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_PREDICATES_FUNCTIONS_SIMD_SSE_SSE3_IS_EQZ_HPP_INCLUDED
#ifdef BOOST_SIMD_HAS_SSE3_SUPPORT
#include <boost/simd/toolbox/predicates/functions/is_eqz.hpp>
#include <boost/simd/sdk/simd/logical.hpp>
#include <boost/simd/sdk/meta/make_dependent.hpp>
#include <boost/simd/include/constants/zero.hpp>

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::is_eqz_
                                    , boost::simd::tag::sse3_
                                    , (A0)
                                    , ((simd_<arithmetic_<A0>,boost::simd::tag::sse_>))
                                    )
  {
    typedef typename meta::as_logical<A0>::type result_type;
    BOOST_SIMD_FUNCTOR_CALL(1)
    {
      return eq(a0,Zero<A0>());
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::is_eqz_
                                    , boost::simd::tag::sse3_
                                    , (A0)
                                    , ((simd_<int64_<A0>,boost::simd::tag::sse_>))
                                    )
  {
    typedef typename meta::as_logical<A0>::type             result_type;
    typedef typename meta::make_dependent<int32_t,A0>::type i32_t;
    typedef typename meta::make_dependent<float,A0>::type   f32_t;
    typedef simd::native<i32_t, boost::simd::tag::sse_>     itype;
    typedef simd::native<f32_t, boost::simd::tag::sse_>     ftype;

    BOOST_SIMD_FUNCTOR_CALL(1)
    {
      ftype tmp1 = bitwise_cast<ftype>(eq(bitwise_cast<itype>(a0),Zero<itype>()));
      A0  l = bitwise_cast<A0>(_mm_moveldup_ps(tmp1));
      A0  h = bitwise_cast<A0>(_mm_movehdup_ps(tmp1));
      return bitwise_cast<result_type>(b_and(l,h));
    }
  };
} } }

#endif
#endif
