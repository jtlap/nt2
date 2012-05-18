//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II         
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI         
//                                                                              
//          Distributed under the Boost Software License, Version 1.0.          
//                 See accompanying file LICENSE.txt or copy at                 
//                     http://www.boost.org/LICENSE_1_0.txt                     
//==============================================================================
#ifndef BOOST_SIMD_TOOLBOX_OPERATOR_FUNCTIONS_SIMD_SSE_SSE_BITWISE_AND_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_OPERATOR_FUNCTIONS_SIMD_SSE_SSE_BITWISE_AND_HPP_INCLUDED
#ifdef BOOST_SIMD_HAS_SSE_SUPPORT

#include <boost/simd/toolbox/operator/functions/bitwise_and.hpp>
#include <boost/simd/include/functions/simd/genmask.hpp>

// namespace boost { namespace simd { namespace ext
// {
//   BOOST_SIMD_FUNCTOR_IMPLEMENTATION(boost::simd::tag::bitwise_and_, boost::simd::tag::sse_,
//                                 (A0),
//                                 ((simd_<logical_<A0>,boost::simd::tag::sse_>))
//                                 ((simd_<logical_<A0>,boost::simd::tag::sse_>))
//                               )
//   {
//     typedef A0 result_type;
//     BOOST_SIMD_FUNCTOR_CALL_REPEAT(2)
//     {
//       return is_true(bitwise_and(genmask(a0), genmask(a1)));
//     }
//   };
// } } }

#endif
#endif
