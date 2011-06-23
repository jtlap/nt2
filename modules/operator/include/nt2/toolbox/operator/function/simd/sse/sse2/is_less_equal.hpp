//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II         
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI         
//                                                                              
//          Distributed under the Boost Software License, Version 1.0.          
//                 See accompanying file LICENSE.txt or copy at                 
//                     http://www.boost.org/LICENSE_1_0.txt                     
//==============================================================================
#ifndef NT2_TOOLBOX_OPERATOR_FUNCTION_SIMD_SSE_SSE2_IS_LESS_EQUAL_HPP_INCLUDED
#define NT2_TOOLBOX_OPERATOR_FUNCTION_SIMD_SSE_SSE2_IS_LESS_EQUAL_HPP_INCLUDED

#include <nt2/sdk/meta/strip.hpp>
#include <nt2/include/functions/minus.hpp>
#include <nt2/include/functions/complement.hpp>
#include <nt2/include/functions/is_greater.hpp>

namespace nt2 { namespace meta
{
  NT2_FUNCTOR_IMPLEMENTATION( tag::is_less_equal_, tag::cpu_
                            , (A0)
                            , ((simd_<double_<A0>,tag::sse_>))
                              ((simd_<double_<A0>,tag::sse_>))
                            )
  {
    typedef A0 result_type;

    NT2_FUNCTOR_CALL_REPEAT(2)
    {
      A0 that = { _mm_cmple_pd(a0,a1) };
      return that;
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION( tag::is_less_equal_, tag::cpu_
                            , (A0)
                            , ((simd_<float_<A0>,tag::sse_>))
                              ((simd_<float_<A0>,tag::sse_>))
                            )
  {
    typedef A0 result_type;

    NT2_FUNCTOR_CALL_REPEAT(2)
    {
      A0 that = { _mm_cmple_ps(a0,a1) };
      return that;
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION( tag::is_less_equal_, tag::cpu_
                            , (A0)
                            , ((simd_<integer_<A0>,tag::sse_>))
                              ((simd_<integer_<A0>,tag::sse_>))
                            )
  {
    typedef A0 result_type;

    NT2_FUNCTOR_CALL_REPEAT(2)
    {
      A0 that = { nt2::complement(nt2::gt(a0,a1)) };
      return that;
    }
  };
} }

#endif
