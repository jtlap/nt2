//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II         
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI         
//                                                                              
//          Distributed under the Boost Software License, Version 1.0.          
//                 See accompanying file LICENSE.txt or copy at                 
//                     http://www.boost.org/LICENSE_1_0.txt                     
//==============================================================================
#ifndef BOOST_SIMD_TOOLBOX_OPERATOR_FUNCTIONS_SIMD_SSE_AVX_SELECT_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_OPERATOR_FUNCTIONS_SIMD_SSE_AVX_SELECT_HPP_INCLUDED
#ifdef BOOST_SIMD_HAS_AVX_SUPPORT
#include <boost/simd/toolbox/operator/functions/if_else.hpp>
#include <boost/simd/include/functions/genmask.hpp>
#include <iostream>
#include <nt2/sdk/details/type_id.hpp>

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::if_else_, boost::simd::tag::avx_
                            , (A0)(A1)
                            , ((simd_<arithmetic_<A0>, boost::simd::tag::avx_>))
                              ((simd_<single_<A1>, boost::simd::tag::avx_>))
                              ((simd_<single_<A1>, boost::simd::tag::avx_>))
                            )
  {
    typedef A1 result_type;
    inline result_type operator()(A0 const& a0,A1 const& a1,A1 const& a2) const
    {
      return boost::simd::bitwise_cast<A1>(_mm256_blendv_ps(a2, a1,  bitwise_cast<A1>(genmask(a0)))); 
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::if_else_, boost::simd::tag::avx_
                            , (A0)(A1)
                            , ((simd_<arithmetic_<A0>, boost::simd::tag::avx_>))
                              ((simd_<double_<A1>, boost::simd::tag::avx_>))
                              ((simd_<double_<A1>, boost::simd::tag::avx_>))
                            )
  {
    typedef A1 result_type;
    inline result_type operator()(A0 const& a0,A1 const& a1,A1 const& a2) const
    {
      return boost::simd::bitwise_cast<A1>(_mm256_blendv_pd(a2, a1, bitwise_cast<A1>(genmask(a0)))); 
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::if_else_, boost::simd::tag::avx_
                            , (A0)(A1)
                            , ((simd_<logical_<A0>, boost::simd::tag::avx_>))
                              ((simd_<single_<A1>, boost::simd::tag::avx_>))
                              ((simd_<single_<A1>, boost::simd::tag::avx_>))
                            )
  {
    typedef A1 result_type;
    inline result_type operator()(A0 const& a0,A1 const& a1,A1 const& a2) const
    {
      return boost::simd::bitwise_cast<A1>(_mm256_blendv_ps(a2, a1, bitwise_cast<A1>(a0))); 
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::if_else_, boost::simd::tag::avx_
                            , (A0)(A1)
                            , ((simd_<logical_<A0>, boost::simd::tag::avx_>))
                              ((simd_<double_<A1>, boost::simd::tag::avx_>))
                              ((simd_<double_<A1>, boost::simd::tag::avx_>))
                            )
  {
    typedef A1 result_type;
    inline result_type operator()(A0 const& a0,A1 const& a1,A1 const& a2) const
    {
      return boost::simd::bitwise_cast<A1>(_mm256_blendv_pd(a2, a1, bitwise_cast<A1>(a0))); 
    }
  };
  
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::if_else_, boost::simd::tag::avx_
                            , (A0)(A1)
                            , ((simd_<logical_<A0>, boost::simd::tag::avx_>))
                              ((simd_<int32_<A1>, boost::simd::tag::avx_>))
                              ((simd_<int32_<A1>, boost::simd::tag::avx_>))
                            )
  {
    typedef A1 result_type;
    inline result_type operator()(A0 const& a0,A1 const& a1,A1 const& a2) const
    {
      typedef native < float, boost::simd::tag::avx_ > ctype;
      typedef meta::as_logical<ctype>::type ltype; 
      return bitwise_cast<result_type>(if_else(bitwise_cast<ltype>(a0), bitwise_cast<ctype>(a1),bitwise_cast<ctype>(a2)));
    }
  };
  
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::if_else_, boost::simd::tag::avx_
                            , (A0)(A1)
                            , ((simd_<arithmetic_<A0>, boost::simd::tag::avx_>))
                              ((simd_<int32_<A1>, boost::simd::tag::avx_>))
                              ((simd_<int32_<A1>, boost::simd::tag::avx_>))
                            )
  {
    typedef A1 result_type;
    inline result_type operator()(A0 const& a0,A1 const& a1,A1 const& a2) const
    {
      typedef native < float, boost::simd::tag::avx_ > ctype;
      return bitwise_cast<result_type>(if_else(bitwise_cast<ctype>(a0), bitwise_cast<ctype>(a1),bitwise_cast<ctype>(a2))); 
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::if_else_, boost::simd::tag::avx_
                            , (A0)(A1)
                            , ((simd_<logical_<A0>, boost::simd::tag::avx_>))
                              ((simd_<uint32_<A1>, boost::simd::tag::avx_>))
                              ((simd_<uint32_<A1>, boost::simd::tag::avx_>))
                            )
  {
    typedef A1 result_type;
    inline result_type operator()(A0 const& a0,A1 const& a1,A1 const& a2) const
    {
      typedef native < float, boost::simd::tag::avx_ > ctype;
      typedef meta::as_logical<ctype>::type ltype; 
      return bitwise_cast<result_type>(if_else(bitwise_cast<ltype>(a0), bitwise_cast<ctype>(a1),bitwise_cast<ctype>(a2)));
    }
  };
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::if_else_, boost::simd::tag::avx_
                            , (A0)(A1)
                            , ((simd_<arithmetic_<A0>, boost::simd::tag::avx_>))
                              ((simd_<uint32_<A1>, boost::simd::tag::avx_>))
                              ((simd_<uint32_<A1>, boost::simd::tag::avx_>))
                            )
  {
    typedef A1 result_type;
    inline result_type operator()(A0 const& a0,A1 const& a1,A1 const& a2) const
    {
      typedef native < float, boost::simd::tag::avx_ > ctype;
      return bitwise_cast<result_type>(if_else(bitwise_cast<ctype>(a0), bitwise_cast<ctype>(a1),bitwise_cast<ctype>(a2))); 
    }
  };

   BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::if_else_, boost::simd::tag::avx_
                            , (A0)(A1)
                            , ((simd_<logical_<A0>, boost::simd::tag::avx_>))
                              ((simd_<int64_<A1>, boost::simd::tag::avx_>))
                              ((simd_<int64_<A1>, boost::simd::tag::avx_>))
                            )
  {
    typedef A1 result_type;
    inline result_type operator()(A0 const& a0,A1 const& a1,A1 const& a2) const
    {
      typedef native < float, boost::simd::tag::avx_ > ctype;
      typedef meta::as_logical<ctype>::type ltype; 
      return bitwise_cast<result_type>(if_else(bitwise_cast<ltype>(a0), bitwise_cast<ctype>(a1),bitwise_cast<ctype>(a2)));
    }
  };
  
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::if_else_, boost::simd::tag::avx_
                            , (A0)(A1)
                            , ((simd_<arithmetic_<A0>, boost::simd::tag::avx_>))
                              ((simd_<int64_<A1>, boost::simd::tag::avx_>))
                              ((simd_<int64_<A1>, boost::simd::tag::avx_>))
                            )
  {
    typedef A1 result_type;
    inline result_type operator()(A0 const& a0,A1 const& a1,A1 const& a2) const
    {
      typedef native < float, boost::simd::tag::avx_ > ctype;
      return bitwise_cast<result_type>(if_else(bitwise_cast<ctype>(a0), bitwise_cast<ctype>(a1),bitwise_cast<ctype>(a2))); 
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::if_else_, boost::simd::tag::avx_
                            , (A0)(A1)
                            , ((simd_<logical_<A0>, boost::simd::tag::avx_>))
                              ((simd_<uint64_<A1>, boost::simd::tag::avx_>))
                              ((simd_<uint64_<A1>, boost::simd::tag::avx_>))
                            )
  {
    typedef A1 result_type;
    inline result_type operator()(A0 const& a0,A1 const& a1,A1 const& a2) const
    {
      typedef native < float, boost::simd::tag::avx_ > ctype;
      typedef meta::as_logical<ctype>::type ltype; 
      return bitwise_cast<result_type>(if_else(bitwise_cast<ltype>(a0), bitwise_cast<ctype>(a1),bitwise_cast<ctype>(a2)));
    }
  };
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::if_else_, boost::simd::tag::avx_
                            , (A0)(A1)
                            , ((simd_<arithmetic_<A0>, boost::simd::tag::avx_>))
                              ((simd_<uint64_<A1>, boost::simd::tag::avx_>))
                              ((simd_<uint64_<A1>, boost::simd::tag::avx_>))
                            )
  {
    typedef A1 result_type;
    inline result_type operator()(A0 const& a0,A1 const& a1,A1 const& a2) const
    {
      typedef native < float, boost::simd::tag::avx_ > ctype;
      return bitwise_cast<result_type>(if_else(bitwise_cast<ctype>(a0), bitwise_cast<ctype>(a1),bitwise_cast<ctype>(a2))); 
    }
  };
   
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::if_else_, boost::simd::tag::avx_
                            , (A0)(A1)
                            , ((simd_<logical_<A0>, boost::simd::tag::avx_>))
                              ((simd_<arithmetic_<A1>, boost::simd::tag::avx_>))
                              ((simd_<arithmetic_<A1>, boost::simd::tag::avx_>))
                            )
  {
    typedef A1 result_type;
    inline result_type operator()(A0 const& a0,A1 const& a1,A1 const& a2) const
    {
      typedef typename meta::scalar_of<A1>::type             sctype;
      typedef simd::native<sctype, boost::simd::tag::sse_ >  svtype;
      typedef typename meta::as_logical<svtype>::type       lsvtype; 
      lsvtype a00 = { _mm256_extractf128_si256(bitwise_cast<A1>(a0), 0)};
      svtype a10 = { _mm256_extractf128_si256(a1, 0)};
      svtype a20 = { _mm256_extractf128_si256(a2, 0)};
      svtype  r0 = if_else(a00,a10,a20);
      result_type that  = {_mm256_insertf128_si256(that, r0, 0)};
      lsvtype a01 = { _mm256_extractf128_si256(bitwise_cast<A1>(a0), 1)};
      svtype a11 = { _mm256_extractf128_si256(a1, 1)};
      svtype a21 = { _mm256_extractf128_si256(a2, 1)};
      svtype r1 = if_else(a01,a11,a21);
      that = _mm256_insertf128_si256(that, r1, 1);
      return that;       
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::if_else_, boost::simd::tag::avx_
                            , (A0)(A1)
                            , ((simd_<arithmetic_<A0>, boost::simd::tag::avx_>))
                              ((simd_<arithmetic_<A1>, boost::simd::tag::avx_>))
                              ((simd_<arithmetic_<A1>, boost::simd::tag::avx_>))
                            )
  {
    typedef A1 result_type;
    inline result_type operator()(A0 const& a0,A1 const& a1,A1 const& a2) const
    {
      typedef typename meta::scalar_of<A1>::type             sctype;
      typedef simd::native<sctype, boost::simd::tag::sse_ >  svtype;
      svtype a00 = { _mm256_extractf128_si256(bitwise_cast<A1>(a0), 0)};
      svtype a10 = { _mm256_extractf128_si256(a1, 0)};
      svtype a20 = { _mm256_extractf128_si256(a2, 0)};
      svtype  r0 = if_else(a00,a10,a20);
      result_type that  = {_mm256_insertf128_si256(that, r0, 0)};
      svtype a01 = { _mm256_extractf128_si256(bitwise_cast<A1>(a0), 1)};
      svtype a11 = { _mm256_extractf128_si256(a1, 1)};
      svtype a21 = { _mm256_extractf128_si256(a2, 1)};
      svtype r1 = if_else(a01,a11,a21);
      that = _mm256_insertf128_si256(that, r1, 1);
      return that;       
    }
  };  
} } }

#endif
#endif

