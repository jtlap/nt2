//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II         
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI         
//                                                                              
//          Distributed under the Boost Software License, Version 1.0.          
//                 See accompanying file LICENSE.txt or copy at                 
//                     http://www.boost.org/LICENSE_1_0.txt                     
//==============================================================================
#ifndef BOOST_SIMD_TOOLBOX_PREDICATES_FUNCTION_SIMD_SSE_AVX_IS_NGE_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_PREDICATES_FUNCTION_SIMD_SSE_AVX_IS_NGE_HPP_INCLUDED
#include <boost/simd/sdk/meta/strip.hpp>

#include <boost/simd/include/functions/details/simd/sse/sse4_1/is_nge.hpp>


/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is arithmetic_
/////////////////////////////////////////////////////////////////////////////
BOOST_SIMD_REGISTER_DISPATCH(tag::is_nge_, tag::cpu_,
                         (A0),
                         ((simd_<arithmetic_<A0>,tag::avx_>))
                         ((simd_<arithmetic_<A0>,tag::avx_>))
                        );

namespace boost { namespace simd { namespace ext
{
  template<class Dummy>
  struct call<tag::is_nge_(tag::simd_<tag::arithmetic_, tag::avx_),
                           tag::simd_<tag::arithmetic_, tag::avx_)),
              tag::cpu_, Dummy> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0,A0)>
      : meta::strip<A0>{};//

    BOOST_SIMD_FUNCTOR_CALL(2)
    {
      return ~boost::simd::is_ge(a0, a1);
    }
  };
} } }

/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is double
/////////////////////////////////////////////////////////////////////////////
BOOST_SIMD_REGISTER_DISPATCH(tag::is_nge_, tag::cpu_,
                         (A0),
                         ((simd_<double_<A0>,tag::avx_>))
                         ((simd_<double_<A0>,tag::avx_>))
                        );

namespace boost { namespace simd { namespace ext
{
  template<class Dummy>
  struct call<tag::is_nge_(tag::simd_<tag::double_, tag::avx_),
                           tag::simd_<tag::double_, tag::avx_)),
              tag::cpu_, Dummy> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0,A0)>
      : meta::strip<A0>{};//

    BOOST_SIMD_FUNCTOR_CALL(2)
    {
      A0 that = {_mm256_cmp_pd(a0,a1, _CMP_NGE_UQ)};
      return that;
    }
  };
} } }

/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is float
/////////////////////////////////////////////////////////////////////////////
BOOST_SIMD_REGISTER_DISPATCH(tag::is_nge_, tag::cpu_,
                         (A0),
                         ((simd_<float_<A0>,tag::avx_>))
                         ((simd_<float_<A0>,tag::avx_>))
                        );

namespace boost { namespace simd { namespace ext
{
  template<class Dummy>
  struct call<tag::is_nge_(tag::simd_<tag::float_, tag::avx_),
                           tag::simd_<tag::float_, tag::avx_)),
              tag::cpu_, Dummy> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0,A0)>
      : meta::strip<A0>{};//

    BOOST_SIMD_FUNCTOR_CALL(2)
    {
      A0 that = {_mm256_cmp_ps(a0,a1, _CMP_NGE_UQ)};
      return that;
    }
  };
} } }

#endif
