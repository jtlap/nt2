//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II         
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI         
//                                                                              
//          Distributed under the Boost Software License, Version 1.0.          
//                 See accompanying file LICENSE.txt or copy at                 
//                     http://www.boost.org/LICENSE_1_0.txt                     
//==============================================================================
#ifndef NT2_TOOLBOX_OPERATOR_FUNCTION_SIMD_SSE_SSE2_BITWISE_OR_HPP_INCLUDED
#define NT2_TOOLBOX_OPERATOR_FUNCTION_SIMD_SSE_SSE2_BITWISE_OR_HPP_INCLUDED

#include <nt2/sdk/meta/as_integer.hpp>
#include <nt2/sdk/simd/native_cast.hpp>

////////////////////////////////////////////////////////////////////////////////
// Generic overload implementation
////////////////////////////////////////////////////////////////////////////////
namespace nt2 { namespace meta
{
  NT2_FUNCTOR_IMPLEMENTATION( tag::bitwise_or_, tag::cpu_
                            , (A0)(A1)
                            , ((simd_<arithmetic_<A0>,tag::sse_>))((simd_<arithmetic_<A1>,tag::sse_>))
                            )
  {

    typedef typename meta::strip<A0>::type result_type;

    NT2_FUNCTOR_CALL(2)
    {
      typedef typename meta::as_integer< A0 >::type int_type;
      int_type t0 = simd::native_cast<int_type>( a0 );
      int_type t1 = simd::native_cast<int_type>( a1 );
      A0     that = { simd::native_cast<A0>(_mm_or_si128(t0,t1)) };
      return that;
    }
  };
} }


//////////////////////////////////////////////////////////////////////////////
// double/double use the seemingly faster and_pd
//////////////////////////////////////////////////////////////////////////////
namespace nt2 { namespace meta
{
  NT2_FUNCTOR_IMPLEMENTATION( tag::bitwise_or_, tag::cpu_
                            , (A0)(A1)
                            , ((simd_<double_<A0>,tag::sse_>))((simd_<double_<A1>,tag::sse_>))
                            )
  {

    typedef typename meta::strip<A0>::type result_type;

    NT2_FUNCTOR_CALL(2)
    {
      A0 that = { _mm_or_pd(a0,a1) };
      return that;
    }
  };
} }


//////////////////////////////////////////////////////////////////////////////
// float/float use the seemingly faster or_ps
//////////////////////////////////////////////////////////////////////////////
namespace nt2 { namespace meta
{
  NT2_FUNCTOR_IMPLEMENTATION( tag::bitwise_or_, tag::cpu_
                            , (A0)(A1)
                            , ((simd_<float_<A0>,tag::sse_>))((simd_<float_<A1>,tag::sse_>))
                            )
  {

    typedef typename meta::strip<A0>::type result_type;

    NT2_FUNCTOR_CALL(2)
    {
      A0 that = { _mm_or_ps(a0,a1) };
      return that;
    }
  };
} }


#endif
