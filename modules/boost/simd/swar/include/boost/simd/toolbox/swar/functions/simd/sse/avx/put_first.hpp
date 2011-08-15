//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II         
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI         
//                                                                              
//          Distributed under the Boost Software License, Version 1.0.          
//                 See accompanying file LICENSE.txt or copy at                 
//                     http://www.boost.org/LICENSE_1_0.txt                     
//==============================================================================
#ifndef BOOST_SIMD_TOOLBOX_SWAR_FUNCTIONS_SIMD_SSE_AVX_PUT_FIRST_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_SWAR_FUNCTIONS_SIMD_SSE_AVX_PUT_FIRST_HPP_INCLUDED
#ifdef BOOST_SIMD_HAS_AVX_SUPPORT
#include <boost/dispatch/meta/as_real.hpp>
#include <boost/simd/sdk/meta/templatize.hpp>
#include <boost/dispatch/meta/strip.hpp>
#include <boost/simd/include/functions/shli.hpp>
#include <boost/simd/include/functions/details/simd/sse/sse4_1/put_first.hpp>
/////////////////////////////////////////////////////////////////////////////
// Implementation when type  is arithmetic_
/////////////////////////////////////////////////////////////////////////////
namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION(boost::simd::tag::put_first_, boost::simd::tag::avx_,
                            (A0),
                            ((simd_<arithmetic_<A0>,boost::simd::tag::avx_>))
                            ((simd_<arithmetic_<A0>,boost::simd::tag::avx_>))
                           )
  {
typedef A0 result_type; 
    BOOST_SIMD_FUNCTOR_CALL_REPEAT(2){return a0; }
  };
} } }
#endif
#endif
