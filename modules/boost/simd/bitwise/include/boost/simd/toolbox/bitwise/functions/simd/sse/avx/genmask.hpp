//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II         
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI         
//                                                                              
//          Distributed under the Boost Software License, Version 1.0.          
//                 See accompanying file LICENSE.txt or copy at                 
//                     http://www.boost.org/LICENSE_1_0.txt                     
//==============================================================================
#ifndef BOOST_SIMD_TOOLBOX_BITWISE_FUNCTIONS_SIMD_SSE_AVX_GENMASK_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_BITWISE_FUNCTIONS_SIMD_SSE_AVX_GENMASK_HPP_INCLUDED
#ifdef BOOST_SIMD_HAS_AVX_SUPPORT
#include <boost/simd/include/functions/genmask.hpp>
#include <boost/dispatch/meta/scalar_of.hpp>
#include <boost/dispatch/meta/downgrade.hpp>
#include <boost/simd/include/functions/complement.hpp>
#include <boost/simd/include/functions/is_equal.hpp>
#include <boost/simd/include/functions/bitwise_or.hpp>
#include <boost/simd/include/functions/minus.hpp>
#include <boost/simd/include/constants/zero.hpp>
#include <boost/simd/include/constants/allbits.hpp>
#include <boost/simd/include/functions/if_else.hpp>

namespace boost { namespace simd { namespace ext
{

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::genmask_, boost::simd::tag::avx_, 
                                   (A0), 
                                   ((simd_<double_<A0>,boost::simd::tag::avx_>))
                                  )
  {
    typedef A0 result_type;
    BOOST_SIMD_FUNCTOR_CALL(1)
    {
      result_type that = { _mm256_cmp_pd(a0,Zero<A0>(), _CMP_NEQ_UQ) };
      return that;
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::genmask_, boost::simd::tag::avx_
                            , (A0)
                            , ((simd_<single_<A0>,boost::simd::tag::avx_>))
                            )
  {
    typedef A0 result_type;
    BOOST_SIMD_FUNCTOR_CALL(1)
    {
      result_type that = { _mm256_cmp_ps(a0,Zero<A0>(), _CMP_NEQ_UQ) };
      return that;
    }
  };
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::genmask_, boost::simd::tag::avx_
                            , (A0)
                            , ((simd_<ints8_<A0>, boost::simd::tag::avx_>))
                            )
  {
    typedef A0 result_type;
    BOOST_SIMD_FUNCTOR_CALL(1)
    {
       typedef typename meta::scalar_of<A0>::type                       sctype;
       typedef typename dispatch::meta::as_integer<sctype>::type        sitype;
       typedef simd::native<sitype, boost::simd::tag::sse_ >           isvtype;
       typedef typename dispatch::meta::as_integer<A0>::type             itype;

       isvtype a00 = { _mm256_extractf128_si256(simd::bitwise_cast<itype>(a0), 0)};
       isvtype a01 = { _mm256_extractf128_si256(simd::bitwise_cast<itype>(a0), 1)};
       itype that = { _mm256_insertf128_si256(that,genmask(a00), 0)};
       return  simd::bitwise_cast<A0>(_mm256_insertf128_si256(that, genmask(a01), 1));
      //      return if_else(is_nez(a0), Allbits<A0> (), Zero<A0>());
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::genmask_, boost::simd::tag::avx_
                            , (A0)
                            , ((simd_<ints16_<A0>, boost::simd::tag::avx_>))
                            )
  {
    typedef A0 result_type;
    BOOST_SIMD_FUNCTOR_CALL(1)
    {
       typedef typename meta::scalar_of<A0>::type                       sctype;
       typedef typename dispatch::meta::as_integer<sctype>::type        sitype;
       typedef simd::native<sitype, boost::simd::tag::sse_ >           isvtype;
       typedef typename dispatch::meta::as_integer<A0>::type             itype;

       isvtype a00 = { _mm256_extractf128_si256(simd::bitwise_cast<itype>(a0), 0)};
       isvtype a01 = { _mm256_extractf128_si256(simd::bitwise_cast<itype>(a0), 1)};
       itype that = { _mm256_insertf128_si256(that,genmask(a00), 0)};
       return  simd::bitwise_cast<A0>(_mm256_insertf128_si256(that, genmask(a01), 1));
      //      return if_else(is_nez(a0), Allbits<A0> (), Zero<A0>());
    }
  }; 
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::genmask_, boost::simd::tag::avx_
                            , (A0)
                            , ((simd_<ints32_<A0>, boost::simd::tag::avx_>))
                            )
  {
    typedef A0 result_type;
    BOOST_SIMD_FUNCTOR_CALL(1)
    {
       typedef typename meta::scalar_of<A0>::type                       sctype;
       typedef typename dispatch::meta::as_integer<sctype>::type        sitype;
       typedef simd::native<sitype, boost::simd::tag::sse_ >           isvtype;
       typedef typename dispatch::meta::as_integer<A0>::type             itype;

       isvtype a00 = { _mm256_extractf128_si256(simd::bitwise_cast<itype>(a0), 0)};
       isvtype a01 = { _mm256_extractf128_si256(simd::bitwise_cast<itype>(a0), 1)};
       itype that = { _mm256_insertf128_si256(that,genmask(a00), 0)};
       return  simd::bitwise_cast<A0>(_mm256_insertf128_si256(that, genmask(a01), 1));
      //      return if_else(is_nez(a0), Allbits<A0> (), Zero<A0>());
    }
  }; 
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::genmask_, boost::simd::tag::avx_
                            , (A0)
                            , ((simd_<ints64_<A0>, boost::simd::tag::avx_>))
                            )
  {
    typedef A0 result_type;
    BOOST_SIMD_FUNCTOR_CALL(1)
    {
       typedef typename meta::scalar_of<A0>::type                       sctype;
       typedef typename dispatch::meta::as_integer<sctype>::type        sitype;
       typedef simd::native<sitype, boost::simd::tag::sse_ >           isvtype;
       typedef typename dispatch::meta::as_integer<A0>::type             itype;

       isvtype a00 = { _mm256_extractf128_si256(simd::bitwise_cast<itype>(a0), 0)};
       isvtype a01 = { _mm256_extractf128_si256(simd::bitwise_cast<itype>(a0), 1)};
       itype that = { _mm256_insertf128_si256(that,genmask(a00), 0)};
       return  simd::bitwise_cast<A0>(_mm256_insertf128_si256(that, genmask(a01), 1));
      //      return if_else(is_nez(a0), Allbits<A0> (), Zero<A0>());
    }
  };  
//   BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::genmask_, boost::simd::tag::avx_
//                             , (A0)(X)
//                             , ((simd_<logical_<A0>,X>))
//                             )
//   {
//     typedef typename A0::type result_type;
//     BOOST_SIMD_FUNCTOR_CALL(1)
//     {
//       return if_else(a0, Allbits<result_type>(), Zero<result_type>());
//     }
//   };
//   BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::genmask_, boost::simd::tag::avx_
//                             , (A0)
//                             , ((simd_<double_<A0>,boost::simd::tag::sse_>))
//                             )
//   {
//     typedef typename meta::as_logical<A0>::type result_type;
//     BOOST_SIMD_FUNCTOR_CALL(1)
//     {
//       result_type that = { _mm_cmp_pd(a0,Zero<A0>(), _CMP_NEQ_UQ) };
//       return that;
//     }
//   };

//   BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::genmask_, boost::simd::tag::avx_
//                             , (A0)
//                             , ((simd_<single_<A0>,boost::simd::tag::sse_>))
//                             )
//   {
//     typedef typename meta::as_logical<A0>::type result_type;
//     BOOST_SIMD_FUNCTOR_CALL(1)
//     {
//       result_type that = { _mm_cmp_ps(a0,Zero<A0>(), _CMP_NEQ_UQ) };
//       return that;
//     }
//   };
} } }

#endif
#endif
