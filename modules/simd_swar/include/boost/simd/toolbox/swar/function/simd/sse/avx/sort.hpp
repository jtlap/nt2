//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II         
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI         
//                                                                              
//          Distributed under the Boost Software License, Version 1.0.          
//                 See accompanying file LICENSE.txt or copy at                 
//                     http://www.boost.org/LICENSE_1_0.txt                     
//==============================================================================
#ifndef BOOST_SIMD_TOOLBOX_SWAR_FUNCTION_SIMD_SSE_AVX_SORT_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_SWAR_FUNCTION_SIMD_SSE_AVX_SORT_HPP_INCLUDED
#include <boost/simd/sdk/meta/as_real.hpp>
#include <boost/simd/sdk/meta/strip.hpp>
#include <boost/simd/include/functions/details/simd/sse/sse4_1/sort.hpp>
#include <boost/simd/include/functions/min.hpp>
#include <boost/simd/include/functions/max.hpp>
/////////////////////////////////////////////////////////////////////////////
// Implementation when type  is arithmetic_
/////////////////////////////////////////////////////////////////////////////
namespace boost { namespace simd { namespace meta
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION(tag::sort_, tag::cpu_,
                       (A0),
                       ((simd_<arithmetic_<A0>,tag::avx_>))
                      )
  {
    typedef A0 result_type;
  };
} } }
#endif
