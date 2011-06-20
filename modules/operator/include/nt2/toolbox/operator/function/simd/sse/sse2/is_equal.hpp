//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II         
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI         
//                                                                              
//          Distributed under the Boost Software License, Version 1.0.          
//                 See accompanying file LICENSE.txt or copy at                 
//                     http://www.boost.org/LICENSE_1_0.txt                     
//==============================================================================
#ifndef NT2_TOOLBOX_OPERATOR_FUNCTION_SIMD_SSE_SSE2_IS_EQUAL_TO_HPP_INCLUDED
#define NT2_TOOLBOX_OPERATOR_FUNCTION_SIMD_SSE_SSE2_IS_EQUAL_TO_HPP_INCLUDED

#include <nt2/sdk/meta/strip.hpp>
#include <nt2/sdk/meta/scalar_of.hpp>
#include <nt2/sdk/meta/downgrade.hpp>
#include <nt2/include/functions/bitwise_and.hpp>
#include <nt2/include/functions/minus.hpp>
#include <nt2/include/constants/digits.hpp>

////////////////////////////////////////////////////////////////////////////////
// Overloads implementation for double
////////////////////////////////////////////////////////////////////////////////
namespace nt2 { namespace meta
{
  NT2_FUNCTOR_IMPLEMENTATION( tag::is_equal_, tag::cpu_
                            , (A0)
                            , ((simd_<double_<A0>,tag::sse_>))((simd_<double_<A0>,tag::sse_>))
                            )
  {

    typedef typename meta::strip<A0>::type result_type;

    NT2_FUNCTOR_CALL(2)
    {
      A0 that = { _mm_cmpeq_pd(a0,a1) };
      return that;
    }
  };
} }


////////////////////////////////////////////////////////////////////////////////
// Overloads implementation for float
////////////////////////////////////////////////////////////////////////////////
namespace nt2 { namespace meta
{
  NT2_FUNCTOR_IMPLEMENTATION( tag::is_equal_, tag::cpu_
                            , (A0)
                            , ((simd_<float_<A0>,tag::sse_>))((simd_<float_<A0>,tag::sse_>))
                            )
  {

    typedef typename meta::strip<A0>::type result_type;

    NT2_FUNCTOR_CALL(2)
    {
      A0 that = { _mm_cmpeq_ps(a0,a1) };
      return that;
    }
  };
} }


////////////////////////////////////////////////////////////////////////////////
// Overloads implementation for ints8
////////////////////////////////////////////////////////////////////////////////
namespace nt2 { namespace meta
{
  NT2_FUNCTOR_IMPLEMENTATION( tag::is_equal_, tag::cpu_
                            , (A0)
                            , ((simd_<ints8_<A0>,tag::sse_>))((simd_<ints8_<A0>,tag::sse_>))
                            )
  {

    typedef typename meta::strip<A0>::type result_type;

    NT2_FUNCTOR_CALL(2)
    {
      A0 that = { _mm_cmpeq_epi8(a0,a1) };
      return that;
    }
  };
} }


////////////////////////////////////////////////////////////////////////////////
// Overloads implementation for ints16
////////////////////////////////////////////////////////////////////////////////
namespace nt2 { namespace meta
{
  NT2_FUNCTOR_IMPLEMENTATION( tag::is_equal_, tag::cpu_
                            , (A0)
                            , ((simd_<ints16_<A0>,tag::sse_>))((simd_<ints16_<A0>,tag::sse_>))
                            )
  {

    typedef typename meta::strip<A0>::type result_type;

    NT2_FUNCTOR_CALL(2)
    {
      A0 that = { _mm_cmpeq_epi16(a0,a1) };
      return that;
    }
  };
} }


////////////////////////////////////////////////////////////////////////////////
// Overloads implementation for ints32
////////////////////////////////////////////////////////////////////////////////
namespace nt2 { namespace meta
{
  NT2_FUNCTOR_IMPLEMENTATION( tag::is_equal_, tag::cpu_
                            , (A0)
                            , ((simd_<ints32_<A0>,tag::sse_>))((simd_<ints32_<A0>,tag::sse_>))
                            )
  {

    typedef typename meta::strip<A0>::type result_type;

    NT2_FUNCTOR_CALL(2)
    {
      A0 that = { _mm_cmpeq_epi32(a0,a1) };
      return that;
    }
  };
} }


////////////////////////////////////////////////////////////////////////////////
// Overloads implementation for ints64
////////////////////////////////////////////////////////////////////////////////
namespace nt2 { namespace meta
{
  NT2_FUNCTOR_IMPLEMENTATION( tag::is_equal_, tag::cpu_
                            , (A0)
                            , ((simd_<ints64_<A0>,tag::sse_>))((simd_<ints64_<A0>,tag::sse_>))
                            )
  {

    typedef typename meta::strip<A0>::type result_type;

    NT2_FUNCTOR_CALL(2)
    {
      typedef typename meta::downgrade<A0, unsigned>::type  type;
      type tmp      = { a0 - a1 };
      tmp           = nt2::eq(tmp,Zero<type>());
      type shuffled = { _mm_shuffle_epi32(tmp, _MM_SHUFFLE(2, 3, 0, 1)) };
      A0   that     = { tmp & shuffled };
      return that;
    }
  };
} }


#endif
