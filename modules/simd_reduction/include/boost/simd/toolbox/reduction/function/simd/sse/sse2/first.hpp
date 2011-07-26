//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II         
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI         
//                                                                              
//          Distributed under the Boost Software License, Version 1.0.          
//                 See accompanying file LICENSE.txt or copy at                 
//                     http://www.boost.org/LICENSE_1_0.txt                     
//==============================================================================
#ifndef BOOST_SIMD_TOOLBOX_REDUCTION_FUNCTION_SIMD_SSE_SSE2_FIRST_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_REDUCTION_FUNCTION_SIMD_SSE_SSE2_FIRST_HPP_INCLUDED
#include <boost/dispatch/meta/strip.hpp>
#include <boost/simd/sdk/meta/as_bits.hpp>
#include <boost/dispatch/meta/as_real.hpp>
#include <boost/simd/sdk/meta/from_bits.hpp>
#include <boost/dispatch/meta/as_integer.hpp>
/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is type8_
/////////////////////////////////////////////////////////////////////////////
namespace boost { namespace dispatch { namespace meta
{
  BOOST_DISPATCH_FUNCTOR_IMPLEMENTATION(boost::simd::tag::first_, tag::cpu_,
                        (A0),
                        ((simd_<type8_<A0>,boost::simd::tag::sse_>))
                       )
  {
    typedef typename meta::scalar_of<A0 > ::type result_type;
    BOOST_DISPATCH_FUNCTOR_CALL_REPEAT(1)
    {
      typedef result_type type;
      int that = _mm_extract_epi16(a0, 0);
      return that & 0xFF;
    }
  };

/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is double
/////////////////////////////////////////////////////////////////////////////


  BOOST_DISPATCH_FUNCTOR_IMPLEMENTATION(boost::simd::tag::first_, tag::cpu_,
                        (A0),
                        ((simd_<double_<A0>,boost::simd::tag::sse_>))
                       )
  {
    typedef typename meta::scalar_of<A0 > ::type result_type;
    BOOST_DISPATCH_FUNCTOR_CALL_REPEAT(1)
    {
      return _mm_cvtsd_f64(a0);
    }
  };

/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is float
/////////////////////////////////////////////////////////////////////////////


  BOOST_DISPATCH_FUNCTOR_IMPLEMENTATION(boost::simd::tag::first_, tag::cpu_,
                        (A0),
                        ((simd_<float_<A0>,boost::simd::tag::sse_>))
                       )
  {
    typedef typename meta::scalar_of<A0>::type result_type;
    BOOST_DISPATCH_FUNCTOR_CALL_REPEAT(1)
    {
      typedef typename meta::as_integer<A0>::type type;
      meta::from_bits<float>::type t = {_mm_cvtsi128_si32(simd::native_cast<type>(a0))};
      return t.value;
    }
  };

/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is ints32_
/////////////////////////////////////////////////////////////////////////////


  BOOST_DISPATCH_FUNCTOR_IMPLEMENTATION(boost::simd::tag::first_, tag::cpu_,
                        (A0),
                        ((simd_<ints32_<A0>,boost::simd::tag::sse_>))
                       )
  {
    typedef typename meta::scalar_of<A0>::type result_type;
    BOOST_DISPATCH_FUNCTOR_CALL_REPEAT(1)
    {
      typedef typename meta::as_integer<A0>::type type;
      return _mm_cvtsi128_si32(simd::native_cast<type>(a0));
    }
  };

/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is ints64_
/////////////////////////////////////////////////////////////////////////////


  BOOST_DISPATCH_FUNCTOR_IMPLEMENTATION(boost::simd::tag::first_, tag::cpu_,
                        (A0),
                        ((simd_<ints64_<A0>,boost::simd::tag::sse_>))
                       )
  {
    typedef typename meta::scalar_of<A0>::type result_type;
    BOOST_DISPATCH_FUNCTOR_CALL_REPEAT(1)
    {
      typedef typename meta::as_integer<A0>::type type;
      typedef typename meta::as_real<A0>::type rtype;
      meta::as_bits<double>::type t = {_mm_cvtsd_f64(simd::native_cast<rtype>(a0))};
      return t.bits;    
    }
  };

/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is type16_
/////////////////////////////////////////////////////////////////////////////


  BOOST_DISPATCH_FUNCTOR_IMPLEMENTATION(boost::simd::tag::first_, tag::cpu_,
                        (A0),
                        ((simd_<type16_<A0>,boost::simd::tag::sse_>))
                       )
  {
    typedef typename meta::scalar_of<A0 > ::type result_type;
    BOOST_DISPATCH_FUNCTOR_CALL_REPEAT(1)
    {
      return _mm_extract_epi16(a0, 0);
    }
  };
} } }
#endif
