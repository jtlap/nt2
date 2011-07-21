//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II         
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI         
//                                                                              
//          Distributed under the Boost Software License, Version 1.0.          
//                 See accompanying file LICENSE.txt or copy at                 
//                     http://www.boost.org/LICENSE_1_0.txt                     
//==============================================================================
#ifndef BOOST_SIMD_TOOLBOX_OPERATOR_FUNCTION_SIMD_SSE_SSE4_1_IS_EQUAL_TO_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_OPERATOR_FUNCTION_SIMD_SSE_SSE4_1_IS_EQUAL_TO_HPP_INCLUDED

#include <boost/simd/toolbox/operator/function/simd/sse/ssse3/is_equal.hpp>

////////////////////////////////////////////////////////////////////////////////
// Overloads implementation for ints64
////////////////////////////////////////////////////////////////////////////////
namespace boost { namespace dispatch { namespace meta
{
  BOOST_DISPATCH_FUNCTOR_IMPLEMENTATION( tag::is_equal_, tag::sse4_1_
                            , (A0)
                            , ((simd_<ints64_<A0>,tag::sse_>))
                              ((simd_<ints64_<A0>,tag::sse_>))
                            )
  {
    typedef A0 result_type;

    BOOST_DISPATCH_FUNCTOR_CALL_REPEAT(2)
    {
      A0 that = { _mm_cmpeq_epi64(a0,a1) };
      return that;
    }
  };
} } }


#endif
