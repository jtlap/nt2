//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II         
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI         
//                                                                              
//          Distributed under the Boost Software License, Version 1.0.          
//                 See accompanying file LICENSE.txt or copy at                 
//                     http://www.boost.org/LICENSE_1_0.txt                     
//==============================================================================
#ifndef NT2_TOOLBOX_REDUCTION_FUNCTION_SIMD_SSE_SSE2_FIRST_HPP_INCLUDED
#define NT2_TOOLBOX_REDUCTION_FUNCTION_SIMD_SSE_SSE2_FIRST_HPP_INCLUDED
#include <nt2/sdk/meta/strip.hpp>
#include <nt2/sdk/meta/as_real.hpp>
#include <nt2/sdk/meta/as_integer.hpp>
/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is type8_
/////////////////////////////////////////////////////////////////////////////
namespace nt2 { namespace meta
{
  NT2_FUNCTOR_IMPLEMENTATION(tag::first_, tag::cpu_,
                        (A0),
                        ((simd_<type8_<A0>,tag::sse_>))
                       )
  {
    typedef typename meta::scalar_of<A0 > ::type result_type;
    NT2_FUNCTOR_CALL_REPEAT(1)
    {
      typedef result_type type;
      int that = _mm_extract_epi16(a0, 0);
      return that & 0xFF;
    }
  };

/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is double
/////////////////////////////////////////////////////////////////////////////


  NT2_FUNCTOR_IMPLEMENTATION(tag::first_, tag::cpu_,
                        (A0),
                        ((simd_<double_<A0>,tag::sse_>))
                       )
  {
    typedef typename meta::scalar_of<A0 > ::type result_type;
    NT2_FUNCTOR_CALL_REPEAT(1)
    {
      return _mm_cvtsd_f64(a0);
    }
  };

/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is float
/////////////////////////////////////////////////////////////////////////////


  NT2_FUNCTOR_IMPLEMENTATION(tag::first_, tag::cpu_,
                        (A0),
                        ((simd_<float_<A0>,tag::sse_>))
                       )
  {
    typedef typename meta::scalar_of<A0>::type result_type;
    NT2_FUNCTOR_CALL_REPEAT(1)
    {
      typedef typename meta::as_integer<A0>::type type;
      typedef typename meta::scalar_of<type>::type stype;

      stype tmp = {_mm_cvtsi128_si32(simd::native_cast<type>(a0))}; 
      return nt2::bitwise_cast<result_type>(tmp); 
    }
  };

/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is ints32_
/////////////////////////////////////////////////////////////////////////////


  NT2_FUNCTOR_IMPLEMENTATION(tag::first_, tag::cpu_,
                        (A0),
                        ((simd_<ints32_<A0>,tag::sse_>))
                       )
  {
    typedef typename meta::scalar_of<A0>::type result_type;
    NT2_FUNCTOR_CALL_REPEAT(1)
    {
      typedef typename meta::as_integer<A0>::type type;
      return bitwise_cast<result_type,float >(_mm_cvtsi128_si32(simd::native_cast<type>(a0)));
    }
  };

/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is ints64_
/////////////////////////////////////////////////////////////////////////////


  NT2_FUNCTOR_IMPLEMENTATION(tag::first_, tag::cpu_,
                        (A0),
                        ((simd_<ints64_<A0>,tag::sse_>))
                       )
  {
    typedef typename meta::scalar_of<A0>::type result_type;
    NT2_FUNCTOR_CALL_REPEAT(1)
    {
      typedef typename meta::as_integer<A0>::type type;
      typedef typename meta::as_real<A0>::type rtype;
      return bitwise_cast<result_type, double >(_mm_cvtsd_f64(simd::native_cast<rtype>(a0))); 
    }
  };

/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is type16_
/////////////////////////////////////////////////////////////////////////////


  NT2_FUNCTOR_IMPLEMENTATION(tag::first_, tag::cpu_,
                        (A0),
                        ((simd_<type16_<A0>,tag::sse_>))
                       )
  {
    typedef typename meta::scalar_of<A0 > ::type result_type;
    NT2_FUNCTOR_CALL_REPEAT(1)
    {
      return _mm_extract_epi16(a0, 0);
    }
  };
} }
#endif
