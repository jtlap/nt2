//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II         
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI         
//                                                                              
//          Distributed under the Boost Software License, Version 1.0.          
//                 See accompanying file LICENSE.txt or copy at                 
//                     http://www.boost.org/LICENSE_1_0.txt                     
//==============================================================================
#ifndef BOOST_SIMD_TOOLBOX_OPERATOR_FUNCTIONS_SIMD_SSE_AVX_BITWISE_XOR_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_OPERATOR_FUNCTIONS_SIMD_SSE_AVX_BITWISE_XOR_HPP_INCLUDED
#ifdef BOOST_SIMD_HAS_AVX_SUPPORT
#include <boost/simd/toolbox/operator/functions/bitwise_xor.hpp>
#include <boost/simd/include/functions/genmask.hpp>

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::bitwise_xor_, boost::simd::tag::avx_
                            , (A0)(A1)
                            , ((simd_<arithmetic_<A0>,boost::simd::tag::avx_>))
                              ((simd_<arithmetic_<A1>,boost::simd::tag::avx_>))
                            )
  {
    typedef A0 result_type;
    BOOST_SIMD_FUNCTOR_CALL(2)
    {
      typedef native<float, tag::avx_> ftype;
      A0 that = { bitwise_cast<A0>
        ( _mm256_xor_ps ( bitwise_cast<ftype>(a0), 
            bitwise_cast<ftype>(a1)
          )
        )
      };
      return that;
    }
  };
  
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::bitwise_xor_, boost::simd::tag::avx_
                            , (A0)(A1)
                            , ((simd_<double_<A0>,boost::simd::tag::avx_>))
                              ((simd_<double_<A1>,boost::simd::tag::avx_>))
                            )
  {
    typedef A0 result_type;
    BOOST_SIMD_FUNCTOR_CALL(2)
    {
      A0 that = { _mm256_xor_pd(a0, a1) };
      return that;
    }
  };
} } }

#endif
#endif
