//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II         
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI         
//                                                                              
//          Distributed under the Boost Software License, Version 1.0.          
//                 See accompanying file LICENSE.txt or copy at                 
//                     http://www.boost.org/LICENSE_1_0.txt                     
//==============================================================================
#ifndef BOOST_SIMD_TOOLBOX_BITWISE_FUNCTIONS_SIMD_SSE_AVX_BITWISE_NOTAND_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_BITWISE_FUNCTIONS_SIMD_SSE_AVX_BITWISE_NOTAND_HPP_INCLUDED
#ifdef BOOST_SIMD_HAS_AVX_SUPPORT

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION_IF ( boost::simd::tag::bitwise_notand_, boost::simd::tag::sse2_, (A0)(A1)
                                , (boost::mpl::equal_to < boost::mpl::sizeof_<A0>
                                                        , boost::mpl::sizeof_<A1>
                                                        >
                                  )
                                , ( boost::simd::tag::bitwise_notand_
                                    ( simd_<arithmetic_<A0>,boost::simd::tag::avx_>
                                    , simd_<arithmetic_<A1>,boost::simd::tag::avx_>
                                    )
                                  )
                                , ((simd_<arithmetic_<A0>,boost::simd::tag::avx_>))
                                  ((simd_<arithmetic_<A1>,boost::simd::tag::avx_>))
                              )
  {
    typedef A0 result_type;
    BOOST_SIMD_FUNCTOR_CALL(2)
    {
      typedef simd::native<double, boost::simd::tag::avx_> dtype; 
      return simd::native_cast<A0>(b_notand(bitwise_cast<dtype>(a0),
					    bitwise_cast<dtype>(a1)));
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION(boost::simd::tag::bitwise_notand_, boost::simd::tag::sse2_, (A0),
                             ((simd_<double_<A0>,boost::simd::tag::avx_>))
                             ((simd_<double_<A0>,boost::simd::tag::avx_>))
                            )
  {
    typedef A0 result_type;
    BOOST_SIMD_FUNCTOR_CALL_REPEAT(2)
    {
      A0 that = {_mm256_andnot_pd(a0, a1)};
      return that;
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::bitwise_notand_, boost::simd::tag::avx_, (A0)
                            , ((simd_<float_<A0>,boost::simd::tag::avx_>))
                              ((simd_<float_<A0>,boost::simd::tag::avx_>))
                            )
  {
    typedef A0 result_type;
    BOOST_SIMD_FUNCTOR_CALL_REPEAT(2)
    {
      A0 that = {_mm256_andnot_ps(a0, a1)};
      return that;
    }
  }; 
} } }

#endif
#endif
