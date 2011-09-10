//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II         
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI         
//                                                                              
//          Distributed under the Boost Software License, Version 1.0.          
//                 See accompanying file LICENSE.txt or copy at                 
//                     http://www.boost.org/LICENSE_1_0.txt                     
//==============================================================================
#ifndef BOOST_SIMD_TOOLBOX_REDUCTION_FUNCTIONS_SIMD_SSE_AVX_ANY_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_REDUCTION_FUNCTIONS_SIMD_SSE_AVX_ANY_HPP_INCLUDED
#ifdef BOOST_SIMD_HAS_AVX_SUPPORT

#include <boost/simd/toolbox/reduction/functions/any.hpp>
#include <boost/simd/include/constants/true.hpp>

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION(boost::simd::tag::any_, boost::simd::tag::avx_,
                        (A0),
                        ((simd_<integer_<A0>,boost::simd::tag::avx_>))
                       )
  {
    typedef bool result_type;
    BOOST_SIMD_FUNCTOR_CALL(1)
    {
      return !_mm256_testz_si256(a0, True<A0>());
    }
  };
  
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION(boost::simd::tag::any_, boost::simd::tag::avx_,
                        (A0),
                        ((simd_<float_<A0>,boost::simd::tag::avx_>))
                       )
  {
    typedef bool result_type;
    BOOST_SIMD_FUNCTOR_CALL(1)
    {
      return !_mm256_testz_ps(a0, True<A0>());
    }
  };
  
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION(boost::simd::tag::any_, boost::simd::tag::avx_,
                        (A0),
                        ((simd_<double_<A0>,boost::simd::tag::avx_>))
                       )
  {
    typedef bool result_type;
    BOOST_SIMD_FUNCTOR_CALL(1)
    {
      return !_mm256_testz_pd(a0, True<A0>());
    }
  };
} } }  
#endif
#endif
