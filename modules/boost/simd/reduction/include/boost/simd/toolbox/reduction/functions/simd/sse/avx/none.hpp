//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II         
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI         
//                                                                              
//          Distributed under the Boost Software License, Version 1.0.          
//                 See accompanying file LICENSE.txt or copy at                 
//                     http://www.boost.org/LICENSE_1_0.txt                     
//==============================================================================
#ifndef BOOST_SIMD_TOOLBOX_REDUCTION_FUNCTIONS_SIMD_SSE_AVX_NONE_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_REDUCTION_FUNCTIONS_SIMD_SSE_AVX_NONE_HPP_INCLUDED
#ifdef BOOST_SIMD_HAS_AVX_SUPPORT
#include <boost/simd/sdk/simd/logical.hpp>
#include <boost/simd/toolbox/reduction/functions/none.hpp>
#include <boost/simd/toolbox/arithmetic/functions/abs.hpp>
#include <boost/simd/include/constants/allbits.hpp>
#include <boost/dispatch/meta/as_integer.hpp>
#include <boost/simd/sdk/simd/native_cast.hpp>

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION(boost::simd::tag::none_, boost::simd::tag::avx_,
                        (A0),
                        ((simd_<arithmetic_<A0>,boost::simd::tag::avx_>))
                       )
  {
    typedef typename meta::scalar_of<A0>::type sA0;
    typedef typename meta::as_logical<sA0>::type result_type;
    BOOST_SIMD_FUNCTOR_CALL(1)
    {
      typedef typename dispatch::meta::as_integer<A0>::type itype;
      return result_type(_mm256_testz_si256(native_cast<itype>(a0), Allbits<itype>()));
    }
  };
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION(boost::simd::tag::none_, boost::simd::tag::avx_,
                        (A0),
                        ((simd_<logical_<A0>,boost::simd::tag::avx_>))
                       )
  {
    typedef typename meta::scalar_of<A0>::type sA0;
    typedef typename meta::as_logical<sA0>::type result_type;
    BOOST_SIMD_FUNCTOR_CALL(1)
    {
      typedef typename A0::type type; 
      return boost::simd::none(native_cast<type>(a0));
    }
  };
} } }

#endif
#endif
