//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II         
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI         
//                                                                              
//          Distributed under the Boost Software License, Version 1.0.          
//                 See accompanying file LICENSE.txt or copy at                 
//                     http://www.boost.org/LICENSE_1_0.txt                     
//==============================================================================
#ifndef BOOST_SIMD_TOOLBOX_OPERATOR_FUNCTIONS_SIMD_VMX_ALTIVEC_BITWISE_AND_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_OPERATOR_FUNCTIONS_SIMD_VMX_ALTIVEC_BITWISE_AND_HPP_INCLUDED
#ifdef BOOST_SIMD_HAS_VMX_SUPPORT

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::bitwise_and_, boost::simd::tag::altivec_, (A0)(A1)
                            , ((simd_<arithmetic_<A0>,boost::simd::tag::altivec_>))
                              ((simd_<arithmetic_<A1>,boost::simd::tag::altivec_>))
                            )
  {
    typedef A0 result_type;

    BOOST_SIMD_FUNCTOR_CALL(2)
    {
      A0 other = simd::bitwise_cast<A0>( a1 );
      A0 that = { vec_and(a0(),other()) };
      return that;
    }
  };
} } }

#endif
#endif
