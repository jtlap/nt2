//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II         
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI         
//                                                                              
//          Distributed under the Boost Software License, Version 1.0.          
//                 See accompanying file LICENSE.txt or copy at                 
//                     http://www.boost.org/LICENSE_1_0.txt                     
//==============================================================================
#ifndef NT2_TOOLBOX_OPERATOR_FUNCTION_SIMD_SSE_SSE2_MINUS_HPP_INCLUDED
#define NT2_TOOLBOX_OPERATOR_FUNCTION_SIMD_SSE_SSE2_MINUS_HPP_INCLUDED

#include <nt2/sdk/meta/strip.hpp>
#include <nt2/sdk/functor/preprocessor/call.hpp>

namespace nt2 { namespace meta
{
  NT2_FUNCTOR_IMPLEMENTATION( tag::minus_, tag::cpu_
                            , (A0)
                            , ((simd_<double_<A0>,tag::sse_>))
                              ((simd_<double_<A0>,tag::sse_>))
                            )
  {
    typedef A0 result_type;

    NT2_FUNCTOR_CALL_REPEAT(2)
    {
      A0 that = { _mm_sub_pd(a0,a1) };
      return that;
    }
  };
} }

namespace nt2 { namespace meta
{
  NT2_FUNCTOR_IMPLEMENTATION( tag::minus_, tag::cpu_
                            , (A0)
                            , ((simd_<float_<A0>,tag::sse_>))
                              ((simd_<float_<A0>,tag::sse_>))
                            )
  {
    typedef A0 result_type;

    NT2_FUNCTOR_CALL_REPEAT(2)
    {
      A0 that = { _mm_sub_ps(a0,a1) };
      return that;
    }
  };
} }

namespace nt2 { namespace meta
{
  NT2_FUNCTOR_IMPLEMENTATION( tag::minus_, tag::cpu_
                            , (A0)
                            , ((simd_<ints8_<A0>,tag::sse_>))
                              ((simd_<ints8_<A0>,tag::sse_>))
                            )
  {
    typedef A0 result_type;

    NT2_FUNCTOR_CALL_REPEAT(2)
    {
      A0 that = { _mm_sub_epi8(a0,a1) };
      return that;
    }
  };
} }

namespace nt2 { namespace meta
{
  NT2_FUNCTOR_IMPLEMENTATION( tag::minus_, tag::cpu_
                            , (A0)
                            , ((simd_<ints16_<A0>,tag::sse_>))
                              ((simd_<ints16_<A0>,tag::sse_>))
                            )
  {
    typedef A0 result_type;

    NT2_FUNCTOR_CALL_REPEAT(2)
    {
      A0 that = { _mm_sub_epi16(a0,a1) };
      return that;
    }
  };
} }

namespace nt2 { namespace meta
{
  NT2_FUNCTOR_IMPLEMENTATION( tag::minus_, tag::cpu_
                            , (A0)
                            , ((simd_<ints32_<A0>,tag::sse_>))
                              ((simd_<ints32_<A0>,tag::sse_>))
                            )
  {
    typedef A0 result_type;

    NT2_FUNCTOR_CALL_REPEAT(2)
    {
      A0 that = { _mm_sub_epi32(a0,a1) };
      return that;
    }
  };
} }

namespace nt2 { namespace meta
{
  NT2_FUNCTOR_IMPLEMENTATION( tag::minus_, tag::cpu_
                            , (A0)
                            , ((simd_<ints64_<A0>,tag::sse_>))
                              ((simd_<ints64_<A0>,tag::sse_>))
                            )
  {
    typedef A0 result_type;

    NT2_FUNCTOR_CALL_REPEAT(2)
    {
      A0 that = { _mm_sub_epi64(a0,a1) };
      return that;
    }
  };
} }

#endif
