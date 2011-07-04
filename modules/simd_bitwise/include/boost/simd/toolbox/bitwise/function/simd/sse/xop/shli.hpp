//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II         
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI         
//                                                                              
//          Distributed under the Boost Software License, Version 1.0.          
//                 See accompanying file LICENSE.txt or copy at                 
//                     http://www.boost.org/LICENSE_1_0.txt                     
//==============================================================================
#ifndef BOOST_SIMD_TOOLBOX_BITWISE_FUNCTION_SIMD_SSE_XOP_SHLI_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_BITWISE_FUNCTION_SIMD_SSE_XOP_SHLI_HPP_INCLUDED

#include <boost/simd/sdk/meta/strip.hpp>

#include <boost/simd/include/functions/details/simd/sse/sse4_1/shli.hpp>


/////////////////////////////////////////////////////////////////////////////
// Implementation when type  is arithmetic_
/////////////////////////////////////////////////////////////////////////////
BOOST_SIMD_REGISTER_DISPATCH(tag::shli_, tag::cpu_,
                       (A0),
                       ((simd_<arithmetic_<A0>,tag::xop_>))
                       ((simd_<arithmetic_<A0>,tag::xop_>))
                      );

namespace boost { namespace simd { namespace ext
{
  template<class Dummy>
  struct call<tag::shli_(tag::simd_<tag::arithmetic_, tag::xop_),
                         tag::simd_<tag::arithmetic_, tag::xop_)),
              tag::cpu_, Dummy> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0, class A1>
    struct result<This(A0,A1)> : meta::strip<A0>{};//

    BOOST_SIMD_FUNCTOR_CALL(2)
    {
      typedef typename meta::scalar_of<A0>::type sctype;
      typedef typename simd::native<sctype, tag::sse_ >  svtype;
      svtype a00 = { _mm256_extractf128_si256(a0, 0)};
      svtype a01 = { _mm256_extractf128_si256(a0, 1)};
      A0 that = { _mm256_insertf128_si256(that,boost::simd::shli( a00, a1), 0)};
      that =  _mm256_insertf128_si256(that, boost::simd::shli(a01, a1), 1);
      return that;
     }

  };
} } }

#endif
