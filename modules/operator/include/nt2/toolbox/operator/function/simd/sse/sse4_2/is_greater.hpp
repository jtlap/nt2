//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II         
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI         
//                                                                              
//          Distributed under the Boost Software License, Version 1.0.          
//                 See accompanying file LICENSE.txt or copy at                 
//                     http://www.boost.org/LICENSE_1_0.txt                     
//==============================================================================
#ifndef NT2_TOOLBOX_OPERATOR_FUNCTION_SIMD_SSE_SSE4_2_IS_GREATER_HPP_INCLUDED
#define NT2_TOOLBOX_OPERATOR_FUNCTION_SIMD_SSE_SSE4_2_IS_GREATER_HPP_INCLUDED

#include <nt2/toolbox/operator/function/simd/sse/sse4_1/is_greater.hpp>

////////////////////////////////////////////////////////////////////////////////
// Overloads implementation for int64 types
////////////////////////////////////////////////////////////////////////////////
namespace nt2 { namespace meta
{
  NT2_FUNCTOR_IMPLEMENTATION( tag::is_greater_, tag::sse4_2_
                            , (A0)
                            , ((simd_<int64_<A0>,tag::sse_>))
                              ((simd_<int64_<A0>,tag::sse_>))
                            )
  {
    typedef A0 result_type;

    NT2_FUNCTOR_CALL_REPEAT(2)
    {
      A0 that = { _mm_cmpgt_epi64(a0,a1)  };
      return that;
    }
  };
} }

#endif
